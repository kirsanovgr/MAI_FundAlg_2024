#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/vector/charvector.h"

typedef struct ListNode {
	struct ListNode *last;
	struct ListNode *next;
	String def_name;
	String value;
	unsigned long hash;
} ListNode;

typedef struct List {
	ListNode *head;
	int size;
} List;

typedef struct HashTable {
	List **data;
	int hash_size;
	int hash_count;
} HashTable;

#define DEFAULT_HASH_TABLE_SIZE 128
#define MAX_VALUE_HASH 100000

#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b

// Функция хэширования
unsigned long hash_62(String *string);

// Функции для двусвязного списка
error_msg create_list(List **list);
error_msg list_push_end(List *list, String *def_name, String *value, unsigned long hash);
error_msg list_push_start(List *list, String *def_name, String *value, unsigned long hash);
void print_list(FILE *stream, List *list);
void destroy_list(List *list);

// Функции для узлов
void destroy_list_node(ListNode *listNode);

// Функции для хэш таблицы
error_msg build_hash_table(FILE *stream, HashTable *hashTable, String *result);
int calculate_new_size(int hash_count);
error_msg create_hash_table(HashTable *hashTable, int hash_size);
error_msg push_into_hash_table(HashTable *hash_table, String *def_name, String *value, int *max_size_list,
                               int *min_size_list, unsigned int h);
error_msg renew_hash_table_with_new_size(const HashTable *dst, HashTable *src);
void destroy_hash_table(HashTable *hashTable);

error_msg read_instruction(FILE *stream, String *result);
