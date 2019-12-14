cmake_minimum_required(VERSION 3.15)
project(lista_sequencial C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(lista_sequencial
        include/lista_seq.h
        src/lista_seq.c
        src/main.c)
