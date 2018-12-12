cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 14)

project(MyStack-Implementation)

set(SOURCES stack.h main.cpp)

add_executable(stack ${SOURCES})


