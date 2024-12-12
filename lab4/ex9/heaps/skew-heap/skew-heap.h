#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../application/application.h"

typedef struct SkewNode {
	Application * application;
	struct SkewNode * left;
	struct SkewNode * right;
} SkewNode;

typedef struct SkewHeap {
	SkewNode * head;
	size_t size;
} SkewHeap;


error_msg create_skew_heap(SkewHeap ** heap);
error_msg merge_skew_heap_with_destroy(SkewHeap * first, SkewHeap * second, SkewHeap ** result);
error_msg merge_skew_heap_without_destroy(SkewHeap* first, SkewHeap* second, SkewHeap** result);
error_msg insert_skew_heap(SkewHeap * h, Application* application);
error_msg delete_skew_heap(SkewHeap * heap, Application ** result);
Application * find_max_priority_element_skew_heap(const SkewHeap * skewHeap);
error_msg destroy_skew_heap(SkewHeap* heap);
int is_empty_skew_heap(const SkewHeap* heap);
size_t get_size_skew_heap(const SkewHeap* heap);
error_msg copy_skew_heap(SkewHeap * src, SkewHeap ** dst);