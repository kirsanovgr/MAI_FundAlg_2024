
/*
 * описание интерфейса взаимодействия кучами
 */

#pragma once

#include "../application/application.h"
#include "binary-heap/binary-heap.h"
#include "binomial-heap/binomial-heap.h"
#include "fibonacci-heap/fibonacci-heap.h"
#include "leftist-heap/leftist-heap.h"
#include "skew-heap/skew-heap.h"
#include "treap/treap.h"

typedef union Q_queue {
	BinaryHeap bin_h;
	BinomialHeap binomial_h;
	FibonacciHeap fibonacci_h;
	SkewHeap skew_h;
	LeftistHeap leftist_h;
	Treap treap;
} Q_queue;

typedef struct V_table_queue {
	error_msg (*create_heap)(Q_queue **);
	error_msg (*insert_heap)(Q_queue *, Application *);
	error_msg (*delete_heap)(Q_queue *, Application **);
	error_msg (*merge_heap_with_destroy)(Q_queue *, Q_queue *, Q_queue **);
	error_msg (*merge_heap_without_destroy)(Q_queue *, Q_queue *, Q_queue **);
	error_msg (*destroy_heap)(Q_queue *);
	Application *(*find_max_priority_elem)(const Q_queue *);
	int (*is_empty)(Q_queue * queue);
	size_t (*get_size)(Q_queue * queue);
} V_table_queue;

typedef struct Queue {
	Q_queue *q;
	V_table_queue v;
} Queue;

extern V_table_queue heaps_functions[];

// Binary head
error_msg create_binary(Q_queue **queue);
error_msg insert_binary(Q_queue *queue, Application *application);
error_msg delete_binary(Q_queue *queue, Application **result);
error_msg merge_binary_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
error_msg merge_binary_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
Application *find_max_priority_elem_binary(const Q_queue *queue);
error_msg destroy_binary(Q_queue *queue);
int is_empty_binary(Q_queue * queue);
size_t get_size_bin(Q_queue *queue);

// Binomial head
error_msg create_binomial(Q_queue ** queue);
error_msg insert_binomial(Q_queue * queue, Application * application);
error_msg delete_binomial(Q_queue * queue, Application ** result);
error_msg merge_binomial_with_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
error_msg merge_binomial_without_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
Application *find_max_priority_elem_binomial(const Q_queue *queue);
error_msg destroy_binomial(Q_queue *queue);
int is_empty_binomial(Q_queue * queue);
size_t get_size_binomial(Q_queue *queue);

// Fibonacci head
error_msg create_fibonacci(Q_queue **queue);
error_msg insert_fibonacci(Q_queue *queue, Application *application);
error_msg delete_fibonacci(Q_queue *queue, Application **result);
error_msg merge_fibonacci_with_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
error_msg merge_fibonacci_without_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
Application *find_max_priority_elem_fibonacci(const Q_queue *queue);
error_msg destroy_fibonacci(Q_queue* queue);
int is_empty_fibonacci(Q_queue * queue);
size_t get_size_fibonacci(Q_queue *queue);

// Skew head
error_msg create_skew(Q_queue **queue);
error_msg insert_skew(Q_queue *queue, Application *application);
error_msg delete_skew(Q_queue *queue, Application **result);
error_msg merge_skew_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
error_msg merge_skew_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
Application *find_max_priority_elem_skew(const Q_queue *queue);
error_msg destroy_skew(Q_queue *queue);
int is_empty_skew(Q_queue * queue);
size_t get_size_skew(Q_queue *queue);

// Leftist head
error_msg create_leftist(Q_queue ** queue);
error_msg insert_leftist(Q_queue * queue, Application * application);
error_msg delete_leftist(Q_queue * queue, Application ** result);
error_msg merge_leftist_with_destroy(Q_queue * first, Q_queue * second, Q_queue ** result);
error_msg merge_leftist_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result);
Application * find_max_priority_elem_leftist(const Q_queue * queue);
error_msg destroy_leftist(Q_queue * queue);
int is_empty_leftist(Q_queue * queue);
size_t get_size_leftist(Q_queue *queue);


// Treap
error_msg create_treap_r(Q_queue **queue);
error_msg insert_treap_r(Q_queue *queue, Application *application);
error_msg delete_treap_r(Q_queue *queue, Application **result);
error_msg merge_treap_with_destroy_r(Q_queue *first, Q_queue *second, Q_queue **result);
error_msg merge_treap_without_destroy_r(Q_queue *first, Q_queue *second, Q_queue **result);
Application * find_max_priority_elem_treap_r(const Q_queue * queue);
error_msg destroy_treap_r(Q_queue *queue);
int is_empty_tr(Q_queue *queue);
size_t get_size_tr(Q_queue *queue);