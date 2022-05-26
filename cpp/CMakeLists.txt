cmake_minimum_required(VERSION 3.22)
project(cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(server
        base/server.cpp)
add_executable(client base/client.cpp)
add_executable(multi_process_server multi_process/server.cpp)
