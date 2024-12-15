#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../application/application.h"

typedef struct TreapNode {
	Application *application;
	size_t priority;
	struct TreapNode *left;
	struct TreapNode *right;
} TreapNode;

typedef struct Treap {
	TreapNode *head;
	size_t size;
} Treap;

typedef struct PairNode {
	TreapNode *first;
	TreapNode *second;
} PairNode;

error_msg create_treap(Treap **treap);
error_msg insert_treap(Treap *treap, Application *application);
Application * find_max_priority_elem_treap(const Treap * treap);
error_msg delete_treap(Treap *treap, Application **result);
// Внимание все ключи в первом дереве должны быть меньше чем во втором
error_msg merge_treap_with_destroy(Treap *first, Treap *second, Treap **result);
error_msg merge_treap_without_destroy(Treap *first, Treap *second, Treap **result);
error_msg destroy_treap(Treap *treap);
int is_empty_treap(const Treap *treap);
size_t get_size_treap(const Treap *treap);