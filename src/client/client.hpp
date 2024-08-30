#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <algorithm>
#include <iostream>
#include <thread>
#include <mutex>
#include <bits/ranges_algo.h>
#include <condition_variable>
#include <cstring>
#include <chrono>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "../helpers/BufferManager.hpp"
#include "../helpers/constants.hpp"

using std::string;
using std::mutex;
using std::condition_variable;

class Client {
public:
    Client() = default;

    ~Client() = default;

    void startThreads(BufferManager &bm);

private:
    void runInputThread(BufferManager &bm);

    void runProcessingThread(BufferManager &bm);

    [[nodiscard]] bool isDigitsOnly(const string &line) const;

    void replaceCharacters(string &line);

    void sendDataToServer(int data);

    mutex mtx;
    condition_variable cv;
};


#endif //CLIENT_HPP
