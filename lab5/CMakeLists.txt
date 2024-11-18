cmake_minimum_required(VERSION 3.28)
project(lab5)

set(CMAKE_CXX_STANDARD 26)

add_executable(ex1 ex1/ex1.cpp ex1/ex1.h
        ex1/main.cpp)


set(CMAKE_C_FLAGS -fsanitize=address)