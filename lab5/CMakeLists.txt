cmake_minimum_required(VERSION 3.22.1)
project(lab5)

set(CMAKE_CXX_STANDARD 20)


find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ex1 ex1/ex1.cpp ex1/ex1.hpp
        ex1/main.cpp)

set(CMAKE_C_FLAGS -fsanitize=address)


add_executable(ex3 ex3/ex3.cpp ex3/ex3.hpp
        ex3/main.cpp
        ex3/main.cpp)


add_executable(ex4 ex4/ex4.cpp ex4/ex4.hpp
        ex4/main.cpp)

add_executable(test_ex3 ex3/test_logical_values_array.cpp ex3/ex3.cpp ex3/ex3.hpp)

add_executable(test_ex4 ex4/ex4.cpp ex4/ex4.hpp
        ex4/test_complex.cpp)


add_executable(ex6 ex6/ex6.cpp ex6/ex6.hpp
        ex6/main.cpp)


add_executable(test_ex6
        ex6/test_vector.cpp
        ex6/ex6.cpp
        ex6/ex6.hpp)


add_executable(ex7 ex7/ex7.cpp ex7/ex7.hpp
        ex7/main.cpp)

add_executable(test_ex7 ex7/test_ex7.cpp
        ex7/ex7.cpp ex7/ex7.hpp)



add_executable(test_ex1 ex1/binary_int_test.cpp ex1/ex1.cpp)


target_link_libraries(test_ex3 ${GTEST_LIBRARIES} pthread)

target_link_libraries(test_ex4 ${GTEST_LIBRARIES} pthread)

target_link_libraries(test_ex6 ${GTEST_LIBRARIES} pthread)

target_link_libraries(test_ex7 ${GTEST_LIBRARIES} pthread)
target_link_libraries(test_ex1 ${GTEST_LIBRARIES} pthread)

