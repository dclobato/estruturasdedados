cmake_minimum_required(VERSION 3.15)
project(fila_dinamica C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(fila_dinamica
        include/fila.h
        src/fila.c
        src/main.c)
