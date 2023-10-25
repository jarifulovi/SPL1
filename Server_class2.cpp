#include <windows.h>
#include <iostream>
#include <winsock2.h>
#include <fstream>
#include<vector>
#include<ctime>
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
    tv.tv_sec = 1; // Set the timeout to 1 second
    tv.tv_usec = 0;

    // Vector to store data received from clients
    std::vector<std::string> dataFromClients(MAX_CLIENTS);

    time_t startTime = time(nullptr); // Get the current time

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

            // Check if the timeout has been reached
            time_t currentTime = time(nullptr);
            if (currentTime - startTime >= 5) {
                std::cout << "Timeout reached. Stopping the server." << std::endl;
                break;
            }

            // Rest of the processing to connect/recv the req
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (nClient[i] != 0 && FD_ISSET(nClient[i], &fr)) {
                    // Handle data received from client i
                    char buffer[1024]; // Adjust the buffer size as needed
                    int bytesRead = recv(nClient[i], buffer, sizeof(buffer), 0);
                    if (bytesRead <= 0) {
                        // Handle disconnection or error
                        // You may want to close the socket nClient[i] and reset it to 0
                        closesocket(nClient[i]);
                        nClient[i] = 0;
                    } else {
                        // Process and store the received data in the vector
                        dataFromClients[i] = std::string(buffer, bytesRead);
                    }
                }
            }
        }
    }
}

};

int main() {
    Server server;
    server.handleConnections();

    return 0;
}
