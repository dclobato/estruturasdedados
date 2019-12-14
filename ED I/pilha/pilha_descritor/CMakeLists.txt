cmake_minimum_required(VERSION 3.15)
project(pilha_descritor C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(pilha_descritor
        include/pilha.h
        src/main.c
        src/pilha.c)
