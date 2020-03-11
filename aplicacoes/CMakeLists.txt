cmake_minimum_required(VERSION 3.15)
project(aplicacoes C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(aplicacoes
        estruturas.c
        estruturas.h
        huffman.c)
