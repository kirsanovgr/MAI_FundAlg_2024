#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../department/department.h"
#include "../../heaps/heaps.h"

#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b


typedef struct HashTableListNode {
	Departament* departament;
	struct HashTableListNode* left;
	struct HashTableListNode* right;

} HashTableListNode;

typedef struct HashTableList {
	HashTableListNode* head;
	size_t size;
} HashTableList;

typedef struct HashTable {
	size_t count;
	size_t size;
	HashTableList** data;
} HashTable;

// Функции для таблицы
error_msg create_hash_table(HashTable* hashTable, size_t size);
error_msg push_into_hash_table(HashTable* table, size_t id_department, size_t count_operators, char what_queue);
error_msg get_hash_table(HashTable* table, size_t id, Departament** departament);
error_msg destroy_hash_table(HashTable* table);

// Функции для листа
error_msg create_hash_table_list(HashTableList** hashTableList);
error_msg push_end_hash_table_list(HashTableList* hashTableList, HashTableListNode* node);
error_msg destroy_hash_table_list(HashTableList* list);

// Функции для узлов
error_msg create_hash_table_list_node(HashTableListNode** node, size_t id_department, size_t count_operators,
                                      char what_queue);
error_msg destroy_hash_table_list_node(HashTableListNode* node);