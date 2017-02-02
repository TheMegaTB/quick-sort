cmake_minimum_required(VERSION 3.5)
project(quicksort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" -pthread)

set(GGT_SOURCE_FILES ggt.c)
add_executable(ggt ${GGT_SOURCE_FILES})
set(SOURCE_FILES quicksort.c)
add_executable(quicksort ${SOURCE_FILES})
set(SOURCE_FILES quicksort_multithreaded.c)
add_executable(quicksort_multithreaded ${SOURCE_FILES})