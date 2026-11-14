#!/usr/bin/env python3
"""
Run:
  python3 tls_server.py --cert server_cert --key server_key --hostIp <Host-Ip>
"""

import argparse
import hmac
import logging
import os
import secrets
import socket
import ssl
import threading
import time
from collections import defaultdict, deque

logging.basicConfig(level=logging.INFO, format="%(asctime)s [%(levelname)s] %(message)s")
log = logging.getLogger("TheBrokenChrismasServer")

FLAG = "FLAG{8JSGD-GDPLSF-JSDGH}"
PORT = 8443
CODE_DIGITS = 8
RECV_TIMEOUT = 10
MAX_MESSAGE_BYTES = 64

# ---- DoS limits -------------------------------------------------------
HANDSHAKE_TIMEOUT = 10      # seconds to finish the TLS handshake
IDLE_TIMEOUT = 300          # seconds of silence before we drop a client
MAX_CONN_LIFETIME = 300     # hard cap on one connection's total lifetime
MAX_TOTAL_CONNS = 50        # simultaneous connections, all clients
MAX_CONNS_PER_IP = 5        # simultaneous connections, one IP
RATE_WINDOW = 10            # seconds
RATE_MAX_NEW = 10           # new connections allowed per IP per window


def gen_code(n: int) -> str:
    return f"{secrets.randbelow(10**n):0{n}d}"


class ConnectionLimiter:
    def __init__(self):
        self.lock = threading.Lock()
        self.total = 0
        self.active = {}      # ip -> current connection count
        self.recent = {}      # ip -> deque of recent connect timestamps
        self.last_sweep = time.monotonic()
 
    def _sweep(self, now):
        if now - self.last_sweep < 60:
            return
        self.last_sweep = now
        for ip in list(self.recent):
            q = self.recent[ip]
            while q and now - q[0] > RATE_WINDOW:
                q.popleft()
            if not q and ip not in self.active:
                del self.recent[ip]
 
    def try_acquire(self, ip: str) -> bool:
        now = time.monotonic()
        with self.lock:
            self._sweep(now)
            if self.total >= MAX_TOTAL_CONNS:
                return False
            if self.active.get(ip, 0) >= MAX_CONNS_PER_IP:
                return False
            q = self.recent.setdefault(ip, deque())
            while q and now - q[0] > RATE_WINDOW:
                q.popleft()
            if len(q) >= RATE_MAX_NEW:
                return False
            q.append(now)
            self.total += 1
            self.active[ip] = self.active.get(ip, 0) + 1
            return True
 
    def release(self, ip: str):
        with self.lock:
            self.total -= 1
            left = self.active.get(ip, 1) - 1
            if left <= 0:
                self.active.pop(ip, None)
            else:
                self.active[ip] = left

def handle_client(conn: ssl.SSLSocket, addr, limiter: ConnectionLimiter):
    ip = addr[0]
    try:
        conn.settimeout(HANDSHAKE_TIMEOUT)
        conn.do_handshake()
 
        conn.settimeout(IDLE_TIMEOUT)
        deadline = time.monotonic() + MAX_CONN_LIFETIME
        code = gen_code(CODE_DIGITS)
 
        conn.sendall((code + "\n").encode())
        log.info("[%s] sent challenge code (hidden in logs)", addr)
 
        while time.monotonic() < deadline:
            try:
                data = conn.recv(MAX_MESSAGE_BYTES)
            except socket.timeout:
                log.info("[%s] idle timeout", addr)
                try:
                    conn.sendall(b"Timeout")
                except OSError:
                    pass
                break
 
            if not data:
                log.info("[%s] client disconnected", addr)
                break
 
            guess = data.decode(errors="ignore").strip()

            if hmac.compare_digest(guess.encode(), code.encode()):
                log.info("[%s] correct guess", addr)
                conn.sendall(FLAG.encode())
                break
            else:
                log.info("[%s] incorrect guess: got %d chars", addr, len(guess))
                conn.sendall(b"Invalid code")
        else:
            log.info("[%s] max connection lifetime reached", addr)

    except OSError as e:
        log.warning("[%s] connection error: %s", addr, e)
    except Exception as e:
        log.warning("[%s] unexpected error: %s", addr, e)
    finally:
        try:
            conn.close()
        finally:
            limiter.release(ip)
 
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cert")
    parser.add_argument("--key")
    parser.add_argument("--hostIp")
    args = parser.parse_args()
    
    ssl_context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
    ssl_context.minimum_version = ssl.TLSVersion.TLSv1_3
    ssl_context.load_cert_chain(certfile=args.cert, keyfile=args.key)

    limiter = ConnectionLimiter()
 
    raw_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    raw_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    raw_sock.bind((args.hostIp, PORT))
    raw_sock.listen(128)
    log.info("Listening on %s:%d (TLS)", args.hostIp, PORT)
 
    try:
        while True:
            try:
                client_sock, addr = raw_sock.accept()
            except OSError as e:           # e.g. out of file descriptors
                log.warning("accept failed: %s", e)
                time.sleep(0.1)
                continue
 
            # cheap checks first: reject floods before spending any resources
            if not limiter.try_acquire(addr[0]):
                client_sock.close()
                continue
 
            try:
                tls_conn = ssl_context.wrap_socket(
                    client_sock, server_side = True, do_handshake_on_connect = False
                )
                threading.Thread(  
                    target = handle_client,
                    args = (tls_conn, addr, limiter),
                    daemon = True,
                ).start()
            except Exception as e:
                log.warning("[%s] could not start handler: %s", addr, e)
                client_sock.close()
                limiter.release(addr[0])
 
    except KeyboardInterrupt:
        log.info("Shutting down")
    finally:
        raw_sock.close()
 
 
if __name__ == "__main__":
    main()