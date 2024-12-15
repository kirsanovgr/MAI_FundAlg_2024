#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../application/application.h"

/**
 * NPL - NULL PATH LENGTH \n
 * Условие левосторонней кучи. Пусть dist(u) — расстояние от вершины u
 * до ближайшей свободной позиции в ее поддереве. У пустых позиций dist=0.\n
 * Тогда потребуем для любой вершины u:dist(u.left)⩾dist(u.right).
 */

typedef struct LeftistNode {
	Application* application;
	size_t dist;
	struct LeftistNode* left;
	struct LeftistNode* right;
} LeftistNode;

typedef struct LeftistHeap {
	LeftistNode* head;
	size_t size;
} LeftistHeap;

error_msg create_leftist_heap(LeftistHeap ** heap);
error_msg merge_leftist_heap_with_destroy(LeftistHeap * first, LeftistHeap * second, LeftistHeap ** result);
error_msg merge_leftist_heap_without_destroy(LeftistHeap * first, LeftistHeap * second, LeftistHeap ** result);
error_msg insert_leftist_heap(LeftistHeap * heap, Application * application);
error_msg delete_leftist_heap(LeftistHeap * heap, Application ** result);
Application * find_max_priority_elem_leftist_heap(const LeftistHeap* leftistHeap);
error_msg destroy_leftist_heap(LeftistHeap * heap);

int is_empty_leftist_heap(const LeftistHeap* heap);
size_t get_size_leftist_heap(const LeftistHeap* h);
error_msg copy_leftist_heap(LeftistHeap * src, LeftistHeap ** dst);