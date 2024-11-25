cmake_minimum_required(VERSION 3.22.1)
project(lab5)

set(CMAKE_CXX_STANDARD 20)


find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ex1 ex1/ex1.cpp ex1/ex1.h
        ex1/main.cpp)

set(CMAKE_C_FLAGS -fsanitize=address)

add_executable(ex2 ex2/ex2.cpp ex2/ex2.h
        ex2/main.cpp)

add_executable(ex3 ex3/ex3.cpp ex3/ex3.h
        ex3/main.cpp
        ex3/main.cpp)


add_executable(ex4 ex4/ex4.cpp ex4/ex4.h
        ex4/main.cpp)

add_executable(test_ex3 ex3/test_logical_values_array.cpp ex3/ex3.cpp ex3/ex3.h)

add_executable(test_ex4 ex4/ex4.cpp ex4/ex4.h
        ex4/test_complex.cpp)

add_executable(ex5 ex5/main.cpp
        ex5/ex5.cpp ex5/ex5.h
)


add_executable(ex6 ex6/ex6.cpp ex6/ex6.h
        ex6/main.cpp)


add_executable(test_ex6
        ex6/test_vector.cpp
        ex6/ex6.cpp
        ex6/ex6.h)


add_executable(ex7 ex7/ex7.cpp ex7/ex7.h
        ex7/main.cpp)

add_executable(test_ex7 ex7/test_ex7.cpp
        ex7/ex7.cpp ex7/ex7.h)

target_link_libraries(test_ex3 ${GTEST_LIBRARIES} pthread)

target_link_libraries(test_ex4 ${GTEST_LIBRARIES} pthread)

target_link_libraries(test_ex6 ${GTEST_LIBRARIES} pthread)

target_link_libraries(test_ex7 ${GTEST_LIBRARIES} pthread)

