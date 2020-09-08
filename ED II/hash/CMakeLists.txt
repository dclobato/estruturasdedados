cmake_minimum_required(VERSION 3.17)
project(hash C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(hash
        include/espalhamento.h
        src/espalhamento.c
        src/main.c)
