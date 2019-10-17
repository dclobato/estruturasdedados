cmake_minimum_required(VERSION 3.15)
project(fila_estatica C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(fila_estatica
        include/fila_est.h
        src/fila_est.c
        src/main.c)
