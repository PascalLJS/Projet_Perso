#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment(lib, "ws2_32.lib")

static constexpr char embeddedCert[] = R"(-----BEGIN CERTIFICATE-----
MIIGgTCCBGmgAwIBAgIUcL0yWz0JwkmM4ePHUf4EyARg4/AwDQYJKoZIhvcNAQEM
BQAwgc8xCzAJBgNVBAYTAkNBMRMwEQYDVQQIDApOb3J0aC1Qb2xlMR8wHQYDVQQH
DBZCcm9rZW5DaHJpc3RtYXNGYWN0b3J5MRgwFgYDVQQKDA9Ccm9rZW5DaHJpc3Rt
YXMxHzAdBgNVBAsMFkJyb2tlbkNocmlzdG1hc0RldlRlYW0xITAfBgNVBAMMGFRo
ZUJyb2tlbkNocmlzdG1hc1NlcnZlcjEsMCoGCSqGSIb3DQEJARYdQnJva2VuQ2hy
aXNtYXNATm9ydGgtUG9sZS5jb20wHhcNMjYxMDAzMDA1NjM5WhcNMjcxMDAzMDA1
NjM5WjCBzzELMAkGA1UEBhMCQ0ExEzARBgNVBAgMCk5vcnRoLVBvbGUxHzAdBgNV
BAcMFkJyb2tlbkNocmlzdG1hc0ZhY3RvcnkxGDAWBgNVBAoMD0Jyb2tlbkNocmlz
dG1hczEfMB0GA1UECwwWQnJva2VuQ2hyaXN0bWFzRGV2VGVhbTEhMB8GA1UEAwwY
VGhlQnJva2VuQ2hyaXN0bWFzU2VydmVyMSwwKgYJKoZIhvcNAQkBFh1Ccm9rZW5D
aHJpc21hc0BOb3J0aC1Qb2xlLmNvbTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCC
AgoCggIBAJ8fukwHSZSaHZ9EZk7uswXzEuDtifWJJT+L3vmgEGbHm571GCcgRdeC
L3uzdF+dpqnUKob5V9Ty17aOOTVmog989ucmsxzFZ62W3ceqgbnaxNB+zhOW0rc3
pqUr1vY9aR6/Pwf8C2DgfDUbXyn9dObnyI7My7QRTWrInrQQdiq4I7S85NTtBVuN
+q29pzH/MYaVAFXz2mb4yY2udVPliOBDKB4yd3+nidj+GMMla/9V4enwaJZ6gDN1
2mAysWSzqkaExErH3V7GEs/ezgz7EpzTgV3atuO8oajJ125IuRRZp0Ctot2puZhq
SF/+Hk4u/rRtUXLwPtN1Ccy0r6xyl2QP64fZeo0mmS2/HfD2bBGkTCbAiUEXQ3k1
CUDTrsU+sLObPC8Joequqnyuq8nJhi7TL1i/FLRykuU1sSSEPAkkQwCUtmoSmcv1
gBVjERY9Bryl4MAvL65PxJcw1fDzxES2A0D3gOhhPmJsca6aBsxV9nl5tIp2BJJn
VYkdywp28U7KSEMSEZRrtr1cwla6vM5IPL8TBxqHaVpw18jk/bHRsPFQXFCAR8P5
72hzyZzyk13CGY8rBEQ44cIDlIYixGqaxdkQkxLccvM3eDU3OguzmX58x22QtxUA
0b+FRpLeMCM2GGl93VZQ3Nl61Orzx+kn7t+JIocMZ3rTLF6bz34LAgMBAAGjUzBR
MB0GA1UdDgQWBBQY+7Fk9281dcHTlxPVHvEq4IfJRDAfBgNVHSMEGDAWgBQY+7Fk
9281dcHTlxPVHvEq4IfJRDAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBDAUA
A4ICAQBF8UXLw4tY2hdEjgjDpt1vWCy1AHHxNMHmY0hI7eNKpdwfLwPh90Kqtmgp
atdt/uqgQy2aU1YCXvhsvlKtZtr6DpbY+iEhGAtlDXfCNnCJoEZI3MFjpg3r/wLW
FnBb8lYP4OvxC6gtThHaIVlse6yZhdFlLBKmOD4mU+eooH/oZe94LcdHrJDLOCNI
IlyTAEk7mTrqhe4ZV0z0OS3sXRWlz5qGfQ9ZkfWa6acNLhYSAdupEzVdVYVhLfAl
P4DRD0nASNe6T2XESM2jy98Jn1q0wjqyd8uvUYE6ygYmtjspwY547hY5KgQ6/JJN
icYB8/QJU637Y/pBspHXrYWX/l9d6nizxWf9VdFqJzFtesqsfk1/7RhNsTBIuOR3
o//XSsCHvsDMJFtrmxobRZqFeJWlKWraX3eXNC4WNNlKLwmhuB5UFZ+RaFnO0NAg
gIe0Jfo9zGyIbAZOI8zkZCT/QmEFzp9ycuSMxO653VY5MDiMd2SNYAPZfOloJvjy
D2ix8cwbvsSZM0UlCmFokha8i/4/6HIzh4N/sYFayEyW6K/G24+LALnp72baEMLd
s95Ym5b7ZpPBhEaQ4ZXifzTVHdDd2XgtD/rd5MHd31KVJZldeEHIWOkhwEidxtKB
VXekpxhfBLW966PzoJImYW+4m+aNTdLLwWjDZhIX2HIimGYitg==
-----END CERTIFICATE-----
)";

class ClientConnection {
    private:
        PCSTR serverAddress = "192.168.91.167"; // Need to change for the server Ip
        unsigned short port = 8443;
        SSL_CTX* ctx;
        SSL* ssl = nullptr;
        SOCKET sock = INVALID_SOCKET;
        WSADATA data;
        sockaddr_in addr{};
        bool handshakeDone = false;
        bool codeIsReceived = false;
        static constexpr const char* serverName = "TheBrokenChristmasServer";
        static constexpr DWORD connectTimeoutMs = 10 * 1000;
        static constexpr DWORD gameTimeoutMs = 5 * 60 * 1000;

        void InitializeSSLCTX() {
            ctx = SSL_CTX_new(TLS_client_method());
            SSL_CTX_set_min_proto_version(ctx, TLS1_3_VERSION);

            BIO* bio = BIO_new_mem_buf(embeddedCert, -1);
            X509* cert = bio ? PEM_read_bio_X509(bio, nullptr, nullptr, nullptr) : nullptr;
            BIO_free(bio);

            if (!cert || X509_STORE_add_cert(SSL_CTX_get_cert_store(ctx), cert) != 1) {
                X509_free(cert);
                SSL_CTX_free(ctx);
                ctx = nullptr;
                return;
            }

            X509_free(cert);
            SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, nullptr);
        }

        bool connectWithTimeout(SOCKET s, const sockaddr* a, int len, DWORD ms) {
            u_long nonBlocking = 1;
            ioctlsocket(s, FIONBIO, &nonBlocking);
    
            int r = connect(s, a, len);
            if (r == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
                return false;
    
            if (r == SOCKET_ERROR) {
                fd_set writeSet, errSet;
                FD_ZERO(&writeSet); FD_ZERO(&errSet);
                FD_SET(s, &writeSet); FD_SET(s, &errSet);
                timeval tv{ (long)(ms / 1000), (long)((ms % 1000) * 1000) };
    
                if (select(0, nullptr, &writeSet, &errSet, &tv) <= 0 || FD_ISSET(s, &errSet))
                    return false;               // timeout or failure
    
                int soErr = 0, soLen = sizeof(soErr);
                getsockopt(s, SOL_SOCKET, SO_ERROR, (char*)&soErr, &soLen);
                if (soErr != 0) return false;
            }
    
            nonBlocking = 0;                     // back to blocking for SSL
            ioctlsocket(s, FIONBIO, &nonBlocking);
            return true;
        }

        bool isTimeoutError(SSL* ssl, int ret) {
            int sslErr = SSL_get_error(ssl, ret);
            if (sslErr == SSL_ERROR_SYSCALL) {
                int wsaErr = WSAGetLastError();
                return wsaErr == WSAETIMEDOUT;
            }
            return false;
        }

        static void setSocketTimeouts(SOCKET s, DWORD ms) {
            setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&ms, sizeof(ms));
            setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (const char*)&ms, sizeof(ms));
        }

        void disconnect() {
            if (ssl) {
                if (handshakeDone)
                    SSL_shutdown(ssl);
                SSL_free(ssl);
                ssl = nullptr;
            }
            handshakeDone = false;
            if (sock != INVALID_SOCKET) {
                closesocket(sock);
                sock = INVALID_SOCKET;
            }
        }

        std::string fail(std::string message) {
            disconnect();
            return message;
        }

    public:
        ClientConnection() {
            WSAStartup(MAKEWORD(2, 2), &data);
            InitializeSSLCTX();
        }

        ~ClientConnection() {
            disconnect();
            if (ctx) SSL_CTX_free(ctx);
            WSACleanup();
        }

        std::string setConnection() {
            disconnect();

            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock == INVALID_SOCKET)
                return fail("socket() failed");

            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            if (inet_pton(AF_INET, serverAddress, &addr.sin_addr) != 1)
                return fail("Invalid server address.. Sorry :(");

            if (!connectWithTimeout(sock, (sockaddr*)&addr, sizeof(addr), connectTimeoutMs))
                return fail("TCP connect failed or timed out");

            setSocketTimeouts(sock, gameTimeoutMs);

            ssl = SSL_new(ctx);
            if (!ssl)
                return fail("SSL_new failed");
            SSL_set_fd(ssl, (int)sock);
            SSL_set_tlsext_host_name(ssl, serverName);
            SSL_set1_host(ssl, serverName);

            int connectRet = SSL_connect(ssl);
            if (connectRet <= 0) {
                bool timedOut = isTimeoutError(ssl, connectRet);
                long vr = SSL_get_verify_result(ssl);
                if (vr != X509_V_OK) {
                    return fail("Certificated rejected");
                }
                return fail("TLS handshake timed out or failed");
            }
            handshakeDone = true;

            long vr = SSL_get_verify_result(ssl);
            if (vr != X509_V_OK) {
                return fail("Certificated rejected");
            }

            char buf[64] = {0};
            int bytesRead = SSL_read(ssl, buf, sizeof(buf) - 1);
            if (bytesRead <= 0) {
                bool timedOut = isTimeoutError(ssl, bytesRead);
                return fail("Timed out waiting for server code");
            }

            std::string receivedCode = std::string(buf);
            
            while (!receivedCode.empty() && (receivedCode.back() == '\n' || receivedCode.back() == '\r'))
                receivedCode.pop_back();

            codeIsReceived = true;
            return receivedCode;
        }

        bool isCodeReceived() {
            return codeIsReceived;
        }

        std::string writeToServer(std::string message) {
            if (!ssl) {
                return "Error: not connected";
            }

            int written = SSL_write(ssl, message.c_str(), static_cast<int>(message.size()));
            if (written <= 0) {
                ERR_print_errors_fp(stderr);
                return "Error sending message";
            }

            char buf[1024] = {0};
            int bytesRead = SSL_read(ssl, buf, sizeof(buf) - 1);
            if (bytesRead <= 0) {
                ERR_print_errors_fp(stderr);
                return "Error reading message";
            }

            buf[bytesRead] = '\0';
            return std::string(buf);
        }
};