#include "server/server.hpp"
#include "client/client.hpp"

int main(int argc, char *argv[]) {
    bool runServer = false;
    bool runClient = false;

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-server") == 0) {
            runServer = true;
        } else if (std::strcmp(argv[i], "-client") == 0) {
            runClient = true;
        } else {
            std::cerr << "Unknown argument: " << argv[i] << std::endl;
            return 1;
        }
    }

    if (runServer) {
        Server server;
        server.startThreads();

        while (true) {}
    } else if (runClient) {
        BufferManager bm;
        Client client;
        client.startThreads(bm);

        while (true) {}
    } else {
        std::cerr << "No valid arguments provided. Use -server or -client" << std::endl;
        return 1;
    }
}
