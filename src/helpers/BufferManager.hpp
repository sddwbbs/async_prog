#ifndef BUFFERMANAGER_HPP
#define BUFFERMANAGER_HPP

#include <string>
#include <mutex>
#include <condition_variable>

using std::string;
using std::mutex;
using std::condition_variable;

class BufferManager {
public:
    BufferManager();

    void setData(const string &data);

    string getData();

    void waitProcess();

    void setProcessRunning(const bool status);

private:
    mutex mtx;
    condition_variable cv;
    string buffer;
    bool dataReady;
    bool isProcessRunning;
};


#endif //BUFFERMANAGER_HPP
