cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 14)

project(Shuffle-Implementation)

set(SOURCES shuffle.h 
            ../randomgen.h 
            ../common/data/data_std_array.h
            ../common/data/data_vec.h
            main.cpp
   )

add_executable(shuffle-test ${SOURCES})

target_include_directories(shuffle-test PRIVATE 
                           ..
                           ../common/data
                           )


