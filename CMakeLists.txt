cmake_minimum_required(VERSION 3.28)
project(test_task)

set(CMAKE_CXX_STANDARD 20)

add_executable(test_task
        src/client/client.cpp
        src/client/client.hpp
        src/helpers/constants.hpp
        src/helpers/BufferManager.cpp
        src/helpers/BufferManager.hpp
        src/server/server.cpp
        src/server/server.hpp
        src/main.cpp
)