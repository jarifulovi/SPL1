#include <iostream>
#include <winsock2.h>
#include<fstream>
#include<thread>
#define SERVER_IP "192.168.0.107"
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

    void connectToServerAndSendData() {
        // Connect to the server
        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Unable to connect to server: " << WSAGetLastError() << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Connected to server." << std::endl;

        // Open the file for reading
        std::ifstream file("profile.txt", std::ios::binary);

        if (!file.is_open()) {
            std::cerr << "Error opening file." << std::endl;
            return;
        }

        // Read the file into a buffer
        std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        // Send the data to the server
        int bytesSent = send(clientSocket, buffer.c_str(), buffer.size(), 0);

        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "Error sending data: " << WSAGetLastError() << std::endl;
        } else {
            std::cout << "Sent " << bytesSent << " bytes to the server." << std::endl;
        }

        file.close();
    }
};


int main() {
    Client client;
    client.connectToServerAndSendData();

    // Example: Sending data (will be handled in sendData method)
    //const char* message = "Hello, server!";
    //client.sendData(message, strlen(message));

    return 0;
}
