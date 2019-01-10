cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 14)

project(my-sort-algorithms-testing)

set(SOURCES selection_sort.h 
            insertion_sort.h
            merge_sort.h
            ../common/data/data_vec_10000.h 
            ../common/data/data_array_10000.h 
            ../common/data/data_std_array_10000.h 
            ../common/timer.h
            main.cpp)

add_executable(sorttest ${SOURCES})

target_include_directories(sorttest
      PRIVATE
      ../common
 )


