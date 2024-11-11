cmake_minimum_required(VERSION 3.28)
project(lab4 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1 ex1/main.c
        ex1/ex1.c
        ex1/ex1.h
        lib/SystemErrors/errors.c
        lib/vector/charvector.c
        lib/mstring/mstring.c
        )
