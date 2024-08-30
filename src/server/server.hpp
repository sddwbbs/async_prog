#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <condition_variable>
#include <thread>

#include "../helpers/constants.hpp"

using std::mutex;
using std::condition_variable;

class Server {
public:
    Server();

    ~Server() = default;

    void startThreads();

private:
    void listeningThread();

    void handleClient(int clientSocket);

    bool running;
    mutex mtx;
    condition_variable cv;
};


#endif //SERVER_HPP
