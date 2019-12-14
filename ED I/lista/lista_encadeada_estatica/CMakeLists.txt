cmake_minimum_required(VERSION 3.15)
project(lista_encadeada_estatica C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(lista_encadeada_estatica
        include/lista_ee.h
        src/lista_ee.c
        src/main.c)
