cmake_minimum_required(VERSION 3.28)
project(client)

set(CMAKE_CXX_STANDARD 20)

add_executable(client
        client.cpp
        client.hpp
        ../helpers/BufferManager.hpp
        ../helpers/BufferManager.cpp
)

target_link_libraries(client pthread)