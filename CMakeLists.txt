cmake_minimum_required(VERSION 3.14)
project(g C)

set(CMAKE_C_STANDARD 99)

add_executable(g main.c yap.c scanner.h scanner.c yap.h)