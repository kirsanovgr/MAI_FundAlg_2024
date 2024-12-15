#pragma once

#include <stdlib.h>

#include "../../lib2/SystemErrors2/errors.h"
#include "bin-tree/bin-tree.h"
#include "dinamyc-array/dinamyc-array.h"
#include "hash-table/hash-table.h"
#include "trie/trie.h"

typedef union Data_storages {
	HashTable hash_t;
	DynamicArrayDepartments dynamic_arr;
	BinTree bin_tree;
	Trie trie;

} Data_storages;

typedef struct V_table_data_storages {
	error_msg (*create_storage)(Data_storages *storage, [[maybe_unused]] size_t capacity);
	error_msg (*push_into_storage)(Data_storages *storage, size_t id_department, size_t count_operators,
	                               char what_queue);
	error_msg (*get_storage)(Data_storages *storage, size_t id, Departament **departament);
	error_msg (*destroy_storage)(Data_storages *storage);
} V_table_data_storages;

typedef struct DStorage {
	Data_storages s;
	V_table_data_storages v;
} DStorage;

extern V_table_data_storages data_storages_functions[];

// Hash table
error_msg create_hash_t(Data_storages *dataStorages, size_t size);
error_msg push_into_hash_t(Data_storages *dataStorages, size_t id_department, size_t count_operators, char what_queue);
error_msg get_hash_t(Data_storages *dataStorages, size_t id, Departament **departament);
error_msg destroy_hast_t(Data_storages *storages);

// Dynamic array
error_msg create_dynamic_arr(Data_storages *storages, size_t capacity);
error_msg push_into_dynamic_arr(Data_storages *storages, size_t id_department, size_t count_operators, char what_queue);
error_msg get_dynamic_arr(Data_storages *dataStorages, size_t id, Departament **departament);
error_msg destroy_dynamic_arr(Data_storages *storages);

// Binary tree
error_msg create_bin_t(Data_storages *storages, [[maybe_unused]] size_t capacity);
error_msg push_into_bin_t(Data_storages *storages, size_t id_department, size_t count_operators, char what_queue);
error_msg get_bin_t(Data_storages *dataStorages, size_t id, Departament **departament);
error_msg destroy_bin_t(Data_storages *storages);

// Trie
error_msg create_trie_t(Data_storages *storages, [[maybe_unused]] size_t capacity);
error_msg push_into_trie_t(Data_storages *storages, size_t id_department, size_t count_operators, char what_queue);
error_msg get_trie_t(Data_storages *dataStorages, size_t id, Departament **departament);
error_msg destroy_trie_t(Data_storages *storages);