#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#include "../helpers/constants.hpp"

class Server {
public:
    Server();

    ~Server() = default;

    void start();

private:
    void handleClient(int clientSocket);

    bool running;
};


#endif //SERVER_HPP
