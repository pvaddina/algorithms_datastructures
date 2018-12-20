cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 14)

project(MyDeque-Implementation)

set(SOURCES deque.h main.cpp)

add_executable(deque-test ${SOURCES})


