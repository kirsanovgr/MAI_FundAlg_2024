#pragma once

#include <stdlib.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../department/department.h"

#define DEFAULT_CAPACITY_TRIE_NODE 10

typedef struct TrieNode {
	Departament *departament;
	struct TrieNode **next;
	size_t capacity;
	size_t size;
} TrieNode;

typedef struct Trie {
	TrieNode *head;
	size_t size;
} Trie;

error_msg create_trie(Trie *trie);
error_msg push_into_trie(Trie *trie, size_t id_department, size_t count_operators, char what_queue);
error_msg get_trie(Trie *trie, size_t id, Departament **departament);
error_msg destroy_trie(Trie *trie);
