cmake_minimum_required(VERSION 3.22.1)
project(lab5)

set(CMAKE_CXX_STANDARD 17)


find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ex1 ex1/ex1.cpp ex1/ex1.h
        ex1/main.cpp)

set(CMAKE_C_FLAGS -fsanitize=address)

add_executable(ex2 ex2/ex2.cpp ex2/ex2.h
        ex2/main.cpp)

add_executable(ex3 ex3/ex3.cpp ex3/ex3.h
        ex3/main.cpp)


add_executable(ex4 ex4/ex4.cpp ex4/ex4.h
        ex4/main.cpp)

add_executable(test_ex3 ex3/test_logical_values_array.cpp ex3/ex3.cpp ex3/ex3.h)

add_executable(test_ex4 ex4/ex4.cpp ex4/ex4.h
        ex4/test_complex.cpp)

target_link_libraries(test_ex3 ${GTEST_LIBRARIES} pthread)

target_link_libraries(test_ex4 ${GTEST_LIBRARIES} pthread)