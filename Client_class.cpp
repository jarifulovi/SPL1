#include <iostream>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define PORT 9999

class Client {
private:
    WSADATA wsData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;

public:
    Client() : clientSocket(INVALID_SOCKET) {
        // Initialize Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
            std::cerr << "WSAStartup failed." << std::endl;
            exit(EXIT_FAILURE);
        }

        // Create a socket
        clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
            WSACleanup();
            exit(EXIT_FAILURE);
        }

        // Set up the server address structure
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    }

    ~Client() {
        // Cleanup and close the socket
        closesocket(clientSocket);
        WSACleanup();
    }

    void connectToServer() {
        // Connect to the server
        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Unable to connect to server: " << WSAGetLastError() << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Connected to server." << std::endl;
    }

    // Placeholder for sending data (to be implemented)
    void sendData(const char* data, int dataSize) {
        // Implement data sending here
        // This is currently left empty as a placeholder
    }

    // Add more methods to receive data or perform other operations as needed
};

int main() {
    Client client;
    client.connectToServer();

    // Example: Sending data (will be handled in sendData method)
    //const char* message = "Hello, server!";
    //client.sendData(message, strlen(message));

    return 0;
}
