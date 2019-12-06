cmake_minimum_required(VERSION 3.15)
project(lista_duplamente_encadeada C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(lista_duplamente_encadeada
        include/lista_ded.h
        src/lista_ded.c
        src/main.c)
