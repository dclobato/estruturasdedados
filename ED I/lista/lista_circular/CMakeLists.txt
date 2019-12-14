cmake_minimum_required(VERSION 3.15)
project(lista_circular C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(lista_circular
        include/lista_circ.h
        src/lista_circ.c src/main.c)
