cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 14)

project(Selection-sort-testing)

set(SOURCES selection_sort.h 
            data_vec.h 
            data_array.h 
            ../common.h 
            main.cpp)

add_executable(selectionsort ${SOURCES})

target_include_directories(selectionsort
      PRIVATE
      ..
 )


