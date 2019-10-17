cmake_minimum_required(VERSION 3.15)
project(heap C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(heap
        include/heap.h
        src/heap.c
        src/main.c)
