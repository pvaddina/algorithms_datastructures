cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 14)

project(MyQueue-Implementation)

set(SOURCES queue.h main.cpp)

add_executable(queue ${SOURCES})


