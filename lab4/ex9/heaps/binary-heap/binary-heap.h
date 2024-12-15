
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../application/application.h"

#define DEFAULT_CAPACITY_BINARY_HEAP 10

typedef struct BinaryHeap {
	Application** data;
	size_t size;
	size_t capacity;
} BinaryHeap;

error_msg create_binary_heap(BinaryHeap** binaryHeap);
error_msg resize_binary_heap(BinaryHeap* binaryHeap, size_t new_capacity);
error_msg insert_binary_heap(BinaryHeap* binaryHeap, Application* application);
error_msg delete_binary_heap(BinaryHeap* binaryHeap, Application** result);
error_msg destroy_binary_heap(BinaryHeap* binaryHeap);
Application* find_max_priority_elem_binary_heap(const BinaryHeap* binaryHeap);

error_msg sift_down_binary_heap(BinaryHeap* binaryHeap, size_t index);
error_msg sift_up_binary_heap(BinaryHeap* binaryHeap);

error_msg merge_binary_heaps_without_destroy(const BinaryHeap* first, const BinaryHeap* second, BinaryHeap** result);
error_msg merge_binary_heaps_with_destroy(BinaryHeap* first, BinaryHeap* second, BinaryHeap** result);


int binary_queue_is_empty(const BinaryHeap *binaryHeap);
void print_binary_queue(const BinaryHeap *binaryHeap);
size_t get_size_binary_queue(const BinaryHeap *binaryHeap);