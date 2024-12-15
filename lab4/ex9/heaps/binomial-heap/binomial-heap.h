#pragma once

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../application/application.h"

typedef struct BinomialNode {
	Application* application;
	struct BinomialNode* parent;
	struct BinomialNode* child;
	struct BinomialNode* brother;
	size_t degree;
} BinomialNode;

typedef struct BinomialHeap {
	BinomialNode* head;
	size_t size;
} BinomialHeap;


// Функции для кучи
error_msg create_binomial_heap(BinomialHeap** binomialHeap);
error_msg merge_binomial_heap_with_destroy(BinomialHeap* first, BinomialHeap* second, BinomialHeap** result);
error_msg merge_binomial_heap_without_destroy(BinomialHeap* first, BinomialHeap* second, BinomialHeap** result);
error_msg copy_binomial_heap_new(const BinomialHeap* src, BinomialHeap** dst);
error_msg insert_binomial_heap(BinomialHeap* binomialHeap, Application* application);
error_msg delete_binomial_heap(BinomialHeap* binomialHeap, Application** application);
Application* find_max_priority_elem_binomial_heap(const BinomialHeap* binaryHeap);
int is_empty_binomial_heap(const BinomialHeap* heap);
size_t get_size_binomial_heap(const BinomialHeap* heap);
error_msg destroy_binomial_heap(BinomialHeap* binomialHeap);
