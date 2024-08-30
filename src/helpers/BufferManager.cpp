#include "BufferManager.hpp"

BufferManager::BufferManager() : dataReady(false), isProcessRunning(false) {}

void BufferManager::setData(const string &data) {
    std::unique_lock<mutex> lock(mtx);
    buffer = data;
    dataReady = true;
    isProcessRunning = true;
    lock.unlock();
    cv.notify_one();
}

string BufferManager::getData() {
    std::unique_lock<mutex> lock(mtx);
    cv.wait(lock, [this] { return dataReady; });

    string dataFromBuffer = std::move(buffer);
    buffer.clear();
    dataReady = false;
    return dataFromBuffer;
}

void BufferManager::waitProcess() {
    std::unique_lock<mutex> lock(mtx);
    cv.wait(lock, [this] { return !isProcessRunning; });
}

void BufferManager::setProcessRunning(const bool status) {
    isProcessRunning = status;
    cv.notify_one();
}
