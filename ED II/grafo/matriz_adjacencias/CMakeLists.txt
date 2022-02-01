cmake_minimum_required(VERSION 3.19)
project(matriz_adjacencias C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(matriz_adjacencias
        include/grafo.h
        include/utilitarios.h
        src/grafo.c
        src/main.c
        src/utilitarios.c)
