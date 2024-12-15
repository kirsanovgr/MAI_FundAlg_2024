#pragma once

#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../application/application.h"

typedef struct FibonacciNode {
	Application * application;
	size_t degree;
	int marked;
	struct FibonacciNode * right;
	struct FibonacciNode * left;
	struct FibonacciNode * parent;
	struct FibonacciNode * child;

} FibonacciNode;


typedef struct FibonacciHeap{
	size_t size;
	FibonacciNode * head;
} FibonacciHeap;

// Функции для кучи
error_msg create_fibonacci_heap(FibonacciHeap ** fibonacciHeap);
error_msg insert_fibonacci_heap(FibonacciHeap * fibonacciHeap, Application * application);
error_msg delete_fibonacci_heap(FibonacciHeap * heap, Application ** application);
Application * find_max_priority_element_fibonacci_heap(const FibonacciHeap * fibonacciHeap);
error_msg merge_fibonacci_heap_with_destroy(FibonacciHeap * first, FibonacciHeap * second, FibonacciHeap ** result);
error_msg merge_fibonacci_heap_without_destroy(FibonacciHeap * first, FibonacciHeap * second, FibonacciHeap ** result);
error_msg destroy_fibonacci_heap(FibonacciHeap* heap);

int is_empty_fibonacci_heap(const FibonacciHeap* heap);

error_msg copy_fibonacci_heap_new(FibonacciHeap * src, FibonacciHeap ** dst);

size_t get_size_fibonacci_heap(const FibonacciHeap* heap);
