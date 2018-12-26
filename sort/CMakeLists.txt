cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 14)

project(my-sort-algorithms-testing)

set(SOURCES selection_sort.h 
            insertion_sort.h
            data_vec.h 
            data_array.h 
            data_std_array.h 
            ../common.h 
            main.cpp)

add_executable(sorttest ${SOURCES})

target_include_directories(sorttest
      PRIVATE
      ..
 )


