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
add_executable(ex2 ex2/ex2.c ex2/ex2.h
        ex2/main.c
        lib/SystemErrors/errors.c
        lib/vector/charvector.c
        lib/vector/intvector.c
        lib/mstring/mstring.c)
