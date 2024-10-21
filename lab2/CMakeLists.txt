cmake_minimum_required(VERSION 3.28)
project(lab2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex1/ex1.c
        ex1/ex1.h
        ex1/main.c
        vector/charvector.h
        vector/charvector.c)


add_executable(ex2 ex2/main.c
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex2/ex2.c
        ex2/ex2.h
        ex2/test.c
        ex2/test.h)


add_executable(ex3 ex3/ex3.c
        ex3/ex3.h
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex3/main.c
        vector/intvector.c
        vector/stringvector.c)

add_executable(ex4 ex4/main.c
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex4/ex4.c
        ex4/ex4.h
        vector/charvector.c
        vector/charvector.h
        vector/stringvector.c
        vector/stringvector.h
        ex4/test.c
        ex4/test.h)

add_executable(ex5 ex5/main.c
        ex5/overloads.c
        ex5/overloads.h
        vector/stringvector.c
        vector/charvector.c
        vector/charvector.h
        ex5/test.c
        ex5/test.h
        SystemErrors/errors.c)

add_executable(ex6 ex6/ex6.c ex6/ex6.h
        ex6/main.c
        vector/stringvector.c
        ex6/test.c
        ex6/test.h)

add_executable(ex8 ex8/main.c
        ex8/ex8.c
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex8/ex8.h
        vector/stringvector.c
        vector/charvector.c
        vector/charvector.h
        ex8/test.c
        ex8/test.h)

add_executable(ex7 ex7/main.c
        ex7/ex7.c
        ex7/ex7.h
        ex7/test.c
        ex7/test.h
)
add_executable(ex9 ex9/ex9.c ex9/ex9.h
        ex9/main.c
        vector/stringvector.c
        vector/intvector.c
        vector/intvector.h
        SystemErrors/errors.c
        ex9/test.c
        ex9/test.h)

add_executable(ex10 ex10/ex10.c ex10/ex10.h
        ex10/main.c
        SystemErrors/errors.c
        ex10/test.c
        ex10/test.h
        ex10/test.c
        ex10/test.c
        ex10/test.c
        ex10/test.c)

target_link_libraries(ex2 m check subunit rt pthread)
target_link_libraries(ex3 m)
target_link_libraries(ex4 m check subunit rt pthread)
target_link_libraries(ex5 m check subunit rt pthread)
target_link_libraries(ex6 check subunit rt pthread)
target_link_libraries(ex7 m)
target_link_libraries(ex9 m)
target_link_libraries(ex10 m)

