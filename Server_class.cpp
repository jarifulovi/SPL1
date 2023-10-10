#include <windows.h>
#include <iostream>
#include <winsock2.h>
#include <fstream>

#define PORT 9999
#define MAX_CLIENTS 5

class Server {
private:
    int nListener;
    struct sockaddr_in srv;
    int nMaxFd;
    fd_set fr;
    int nClient[MAX_CLIENTS] = {0};
    int numConnectedClients;  // Number of connected clients
    bool clientConnected;  // Flag to track client connection

public:
    Server() : nListener(0), nMaxFd(0), numConnectedClients(0), clientConnected(false) {
        // Initialize Winsock
        WSADATA ws;
        if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
            std::cout << "The WSAStartup failed.." << std::endl;
            exit(EXIT_FAILURE);
        }

        // Create socket
        nListener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (nListener < 0) {
            std::cout << "Not able to open the socket.." << std::endl;
            exit(EXIT_FAILURE);
        }

        // Setup server address
        srv.sin_family = AF_INET;
        srv.sin_port = htons(PORT);
        srv.sin_addr.s_addr = INADDR_ANY;
        memset(&srv.sin_zero, 0, 8);

        // Bind the socket
        int err = bind(nListener, (struct sockaddr*)&srv, sizeof(sockaddr));
        if (err < 0) {
            std::cout << "The bind failed.." << std::endl;
            exit(EXIT_FAILURE);
        }

        // Listen for incoming connections
        err = listen(nListener, 5);
        if (err < 0) {
            std::cout << "The listen failed.." << std::endl;
            exit(EXIT_FAILURE);
        }

        nMaxFd = nListener + 1;
    }

    void handleConnections() {
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        while (true) {
            FD_ZERO(&fr);
            FD_SET(nListener, &fr);
            for (int nIndex = 0; nIndex < MAX_CLIENTS; nIndex++) {
                if (nClient[nIndex] != 0) {
                    FD_SET(nClient[nIndex], &fr);
                }
            }

            int err = select(nMaxFd, &fr, NULL, NULL, &tv);
            if (err < 0) {
                std::cerr << "Select failed.." << std::endl;
                exit(EXIT_FAILURE);
            } else if (err == 0) {
                std::cout << "No client available to connect/message" << std::endl;
            } else {
                if (!clientConnected) {
                    clientConnected = true;
                    // Print the initial number of connected clients
                    numConnectedClients = 0;
                    for (int i = 0; i < MAX_CLIENTS; i++) {
                        if (nClient[i] != 0)
                            numConnectedClients++;
                    }
                    std::cout << "Number of clients connected: " << numConnectedClients << std::endl;
                }

                // Update the number of connected clients
                int connectedCount = 0;
                for (int i = 0; i < MAX_CLIENTS; i++) {
                    if (nClient[i] != 0)
                        connectedCount++;
                }

                if (connectedCount != numConnectedClients) {
                    numConnectedClients = connectedCount;
                    std::cout << "Number of clients connected: " << numConnectedClients+1 << std::endl;
                }

                // Rest of the processing to connect/recv the req
            }
        }
    }
};

int main() {
    Server server;
    server.handleConnections();

    return 0;
}
