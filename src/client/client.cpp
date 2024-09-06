#include "client.hpp"

void Client::startThreads(BufferManager &bm) {
    std::thread inputThread(&Client::runInputThread, this, std::ref(bm));
    std::thread processingThread(&Client::runProcessingThread, this, std::ref(bm));

    inputThread.detach();
    processingThread.detach();
}

void Client::runInputThread(BufferManager &bm) {
    string input;

    while (true) {
        bm.waitProcess();

        std::cout << "=======================================================================\n";
        std::cout << "Enter the line: ";
        std::getline(std::cin, input);

        if (const bool digitsOnly = isDigitsOnly(input); input.length() > 64 || !digitsOnly) {
            std::cout << "Line must be no longer than 64 characters and contain only numbers\n";
            continue;
        }

        std::sort(input.rbegin(), input.rend());
        replaceCharacters(input);

        bm.setData(input);
    }
}

void Client::runProcessingThread(BufferManager &bm) {
    while (true) {
        string data = bm.getData();
        if (data.empty()) continue;

        std::cout << "Processed data: " << data << '\n';

        int sum = 0;
        for (const auto &elem: data) {
            if (std::isdigit(elem))
                sum += elem - '0';
        }

        sendDataToServer(sum);

        bm.setProcessRunning(false);
    }
}

bool Client::isDigitsOnly(const string &line) const {
    return std::ranges::all_of(line, [](const char &elem) { return std::isdigit(elem); });
}

void Client::replaceCharacters(string &line) {
    string result;
    result.reserve(line.length() * 2);

    for (const auto &elem: line) {
        if ((elem - '0') % 2 == 0)
            result += "KB";
        else
            result += elem;
    }

    line = std::move(result);
}

void Client::sendDataToServer(const int data) {
    int clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    sockaddr_un serverAddr{};
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, SOCKET_PATH);

    if (clientSocket < 0) {
        std::cout << "socket: " << strerror(errno) << '\n';
        throw std::runtime_error("Failed to create socket");
    }

    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, SOCKET_PATH);

    if (connect(clientSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cout << "connect: " << strerror(errno) << std::endl;
        close(clientSocket);
        return;
    }

    ssize_t bytesSent = write(clientSocket, &data, sizeof(data));
    if (bytesSent < 0) {
        std::cout << "write: " << strerror(errno) << '\n';
    }

    close(clientSocket);
}

int main() {
    BufferManager bm;
    Client client;

    client.startThreads(bm);

    while (true) {}
}
