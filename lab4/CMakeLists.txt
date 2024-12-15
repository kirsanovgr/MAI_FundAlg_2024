cmake_minimum_required(VERSION 3.22)
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


add_executable(ex7 ex7/main.c
        ex7/ex7.c
        ex7/ex7.h
        lib2/SystemErrors2/errors.c
        lib2/vector/charvector.c
        lib2/mstring/mstring.c
)
add_executable(ex9
        ex9/main.c
        lib2/SystemErrors2/errors.c
        lib2/vector/charvector.c
        lib2/mstring/mstring.c
        lib2/universal_vector/vector.c
        lib2/universal_vector/vector.h
        ex9/application/application.h
        ex9/application/application.c
        ex9/heaps/heaps.c
        ex9/heaps/heaps.h
        ex9/heaps/binary-heap/binary-heap.c
        ex9/heaps/binary-heap/binary-heap.h
        ex9/heaps/binomial-heap/binomial-heap.c
        ex9/heaps/binomial-heap/binomial-heap.h
        ex9/heaps/fibonacci-heap/fibonacci-heap.c
        ex9/heaps/fibonacci-heap/fibonacci-heap.h
        ex9/heaps/skew-heap/skew-heap.c
        ex9/heaps/skew-heap/skew-heap.h
        ex9/heaps/leftist-heap/leftist-heap.c
        ex9/heaps/leftist-heap/leftist-heap.h
        ex9/heaps/treap/treap.c
        ex9/heaps/treap/treap.h
        ex9/department/department.c
        ex9/department/department.h
        ex9/data-storages/hash-table/hash-table.c
        ex9/data-storages/hash-table/hash-table.h
        ex9/data-storages/data-storages.c
        ex9/data-storages/data-storages.h
        ex9/data-storages/dinamyc-array/dinamyc-array.c
        ex9/data-storages/dinamyc-array/dinamyc-array.h
        ex9/data-storages/bin-tree/bin-tree.c
        ex9/data-storages/bin-tree/bin-tree.h
        ex9/data-storages/trie/trie.c
        ex9/data-storages/trie/trie.h
        ex9/process_files/process_files.c
        ex9/process_files/process_files.h
        ex9/main_files/preparing.c
        ex9/main_files/preparing.h
        ex9/main_files/main-stage.c
        ex9/main_files/main-stage.h
)

add_executable(ex_9_d1
        ex9/auxiliary_application_1/auxiliary_application_1.c
        lib2/SystemErrors2/errors.c
        lib2/vector/charvector.c
        lib2/mstring/mstring.c
        lib2/universal_vector/vector.c
        lib2/universal_vector/vector.h
        ex9/application/application.h
        ex9/application/application.c
        )


target_link_libraries(ex9 m)
target_link_libraries(ex_9_d1 m)

add_executable(ex_9_d2
        ex9/auxiliary_application_2/auxiliary_application_2.c
        lib2/mstring/mstring.c
        lib2/SystemErrors2/errors.c
        ex9/application/application.c
        lib2/vector/charvector.c
        lib2/mstring/mstring.c/)
