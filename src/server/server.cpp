#include "server.hpp"

Server::Server() : running(false) {}

void Server::start() {
    if (running) {
        std::cout << "\nSERVER | Server is already running\n";
        return;
    }

    int serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cout << "SERVER | socket: " << strerror(errno) << '\n';
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_un serverAddr{};
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, SOCKET_PATH);
    unlink(SOCKET_PATH);

    if (bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cout << "SERVER | bind: " << strerror(errno) << '\n';
        close(serverSocket);
    }

    if (listen(serverSocket, 5) < 0) {
        std::cout << "SERVER | listen: " << strerror(errno) << '\n';
        close(serverSocket);
    }

    std::cout << "\nSERVER | Server is listening...\n";

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            if (errno == EINTR) continue;
            std::cout << "SERVER | accept: " << strerror(errno) << '\n';
            break;
        }

        handleClient(clientSocket);
    }
}

void Server::handleClient(int clientSocket) {
    int dataFromClient;
    ssize_t bytesReceived = read(clientSocket, &dataFromClient, sizeof(dataFromClient));

    if (bytesReceived < 0) {
        std::cout << "SERVER | read: " << strerror(errno) << '\n';
        return;
    }

    if (dataFromClient < 10 || dataFromClient % 32 != 0) {
        std::cout << "\nSERVER | Invalid data, number must be more than two characters and a multiple of 32\n";
        return;
    }

    std::cout << "\nSERVER | Received data: " << dataFromClient << '\n';

    close(clientSocket);
}

int main() {
    Server server;
    server.start();

    while (true) {}
}