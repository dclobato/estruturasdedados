cmake_minimum_required(VERSION 3.15)
project(arvore_binaria_dinamica C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(arvore_binaria_dinamica
        include/arvorebinaria.h
        src/arvorebinaria.c
        src/main.c)
