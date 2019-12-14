cmake_minimum_required(VERSION 3.15)
project(lista_encadeada_dinamica C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(lista_encadeada_dinamica
        include/lista_ed.h
        src/lista_ed.c
        src/main.c)
