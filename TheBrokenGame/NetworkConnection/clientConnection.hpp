#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment(lib, "ws2_32.lib")

class ClientConnection {

    private:
        PCSTR serverAddress = "127.0.0.1";
        unsigned short port = 8443;
        SSL_CTX* ctx;
        SSL* ssl;
        SOCKET sock;
        WSADATA data;
        sockaddr_in addr{};

        void InitializeSSLCTX() {
            SSL_load_error_strings();
            OpenSSL_add_ssl_algorithms();
            const SSL_METHOD* method = TLS_client_method();
            ctx = SSL_CTX_new(method);

            if (SSL_CTX_load_verify_locations(ctx, "server_cert.pem", nullptr) != 1) {
                ERR_print_errors_fp(stderr);
                throw std::runtime_error("failed to load trusted server certificate");
            }

            SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, nullptr);
        }

    public:
        ClientConnection() {
            WSAStartup(MAKEWORD(2, 2), &data);
            InitializeSSLCTX();
        }

        ~ClientConnection() {
            SSL_free(ssl);
            closesocket(sock);
            SSL_CTX_free(ctx);
            WSACleanup();
        }

        void setConnection() {
            sock = socket(AF_INET, SOCK_STREAM, 0);
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            inet_pton(AF_INET, serverAddress, &addr.sin_addr);

            connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        }

        std::string writeToServer(std::string message) {
            ssl = SSL_new(ctx);
            SSL_set_fd(ssl, (int)sock);

            if (SSL_connect(ssl) <= 0) {
                ERR_print_errors_fp(stderr);
            } else {
                long verify_result = SSL_get_verify_result(ssl);
                if (verify_result != X509_V_OK) {
                    std::cerr << "Certificate verification failed: "
                            << X509_verify_cert_error_string(verify_result) << "\n";
                } else {
                    int written = SSL_write(ssl, message.c_str(), static_cast<int>(message.size()));
                    if (written <= 0) {
                        ERR_print_errors_fp(stderr);
                    } else {
                        char buf[1024] = {0};
                        int bytesRead = SSL_read(ssl, buf, sizeof(buf) - 1);
                        if (bytesRead <= 0) {
                            ERR_print_errors_fp(stderr);
                        } else {
                            buf[bytesRead] = '\0';
                            std::string response(buf);
                            SSL_shutdown(ssl);
                            SSL_free(ssl);
                            return response;
                        }
                    }
                }
            }
            SSL_shutdown(ssl);
            SSL_free(ssl);
            return "error";
        }
};