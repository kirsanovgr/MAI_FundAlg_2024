#include "hash-table.h"

size_t hash(size_t number, [[maybe_unused]] size_t size) { return (number * 31) % size; }

error_msg create_hash_table_list_node(HashTableListNode** node, size_t id_department, size_t count_operators,
                                      char what_queue) {
	if (node == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_hash_table_list_node", "get pointer to null"};
	}
	HashTableListNode* tmp = (HashTableListNode*)calloc(1, sizeof(HashTableListNode));
	if (tmp == NULL) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_hash_table_list_node", "memory allocated"};
	}
	error_msg errorMsg = create_departament(&(tmp->departament), count_operators, id_department, what_queue);
	if (errorMsg.type) {
		free(tmp);
		return errorMsg;
	}
	*node = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg destroy_hash_table_list_node(HashTableListNode* node) {
	if (node == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_hash_table_list_node", "get pointer to null"};
	}
	error_msg errorMsg = destroy_departament(node->departament);
	if (errorMsg.type) {
		return errorMsg;
	}
	node->left = NULL;
	node->right = NULL;
	free(node);
	return (error_msg){SUCCESS, "", ""};
}

error_msg create_hash_table_list(HashTableList** hashTableList) {
	if (hashTableList == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_hash_table_list", "get pointer to null"};
	}
	HashTableList* tmp = (HashTableList*)calloc(1, sizeof(HashTableList));
	if (tmp == NULL) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_hash_table_list", "memory allocated"};
	}
	*hashTableList = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg destroy_hash_table_list(HashTableList* list) {
	if (list == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_hash_table_list", "get pointer to null"};
	}
	HashTableListNode* moving = list->head;
	HashTableListNode* prev;
	for (size_t i = 0; i < list->size; ++i) {
		prev = moving;
		moving = moving->right;
		destroy_hash_table_list_node(prev);
	}
	free(list);
	return (error_msg){SUCCESS, "", ""};
}

error_msg create_hash_table(HashTable* hashTable, size_t size) {
	if (hashTable == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_hash_table", "get pointer to null"};
	}
	hashTable->data = (HashTableList**)calloc(size, sizeof(HashTableList*));
	if (!hashTable->data) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_hash_table", "memory allocated"};
	}
	hashTable->size = size;
	hashTable->count = 0;
	return (error_msg){SUCCESS, "", ""};
}

error_msg push_end_hash_table_list(HashTableList* hashTableList, HashTableListNode* node) {
	if (hashTableList == NULL || node == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "push_end_hash_table_list", "get pointer to null"};
	}
	hashTableList->size += 1;
	if (hashTableList->size == 1) {
		hashTableList->head = node;
		node->left = node;
		node->right = node;
	} else {
		HashTableListNode* tmp = hashTableList->head->left;
		hashTableList->head->left = node;
		node->right = hashTableList->head;
		node->left = tmp;
		tmp->right = node;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg check_and_rehash(HashTable* table) {
	if (table == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "check_and_rehash", "get pointer to null"};
	}
	size_t min_list_len = table->size;
	size_t max_list_len = 0;
	for (size_t i = 0; i < table->size; ++i) {
		if (table->data[i]) {
			max_list_len = max(max_list_len, table->data[i]->size);
			if (table->data[i]->size != 0) {
				min_list_len = min(min_list_len, table->data[i]->size);
			}
		}
	}
	if (table->size == 0 || max_list_len / min_list_len <= 2) {
		return (error_msg){SUCCESS, "", ""};
	}
	size_t new_size = table->size * 2;
	HashTable new_table;
	error_msg errorMsg = create_hash_table(&new_table, new_size);
	if (errorMsg.type) {
		return errorMsg;
	}
	for (size_t i = 0; i < table->size; ++i) {
		if (table->data[i]) {
			HashTableListNode* moving = table->data[i]->head;
			HashTableListNode* prev;
			size_t new_h = hash(moving->departament->id, new_size);
			if (new_table.data[new_h] == NULL) {
				errorMsg = create_hash_table_list(&(new_table.data[new_h]));
				if (errorMsg.type) {
					destroy_hash_table(&new_table);
					return errorMsg;
				}
			}
			for (size_t j = 0; j < table->data[i]->size; ++i) {
				prev = moving;
				moving = moving->right;
				errorMsg = push_end_hash_table_list(new_table.data[new_h], prev);
				if (errorMsg.type) {
					destroy_hash_table(&new_table);
					return errorMsg;
				}
			}
		}
	}
	table->data = new_table.data;
	return (error_msg){SUCCESS, "", ""};
}

error_msg push_into_hash_table(HashTable* table, size_t id_department, size_t count_operators, char what_queue) {
	if (table == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "push_into_hash_table", "get pointer to null"};
	}
	size_t h = hash(id_department, table->size);
	HashTableListNode* tmp;
	error_msg errorMsg = create_hash_table_list_node(&tmp, id_department, count_operators, what_queue);
	if (errorMsg.type) {
		return errorMsg;
	}
	if (table->data[h] == NULL) {
		errorMsg = create_hash_table_list(&(table->data[h]));
		if (errorMsg.type) {
			destroy_hash_table_list_node(tmp);
			return errorMsg;
		}
	}
	errorMsg = push_end_hash_table_list(table->data[h], tmp);
	if (errorMsg.type) {
		destroy_hash_table_list(table->data[h]);
		destroy_hash_table_list_node(tmp);
		return errorMsg;
	}
	table->count += 1;
	errorMsg = check_and_rehash(table);
	if (errorMsg.type) {
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg destroy_hash_table(HashTable* table) {
	if (table == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_hash_table", " get pointer to null"};
	}
	for (size_t i = 0; i < table->size; ++i) {
		if (table->data[i]) {
			destroy_hash_table_list(table->data[i]);
		}
	}
	free(table->data);
	return (error_msg){SUCCESS, "", ""};
}

error_msg get_hash_table(HashTable* table, size_t id, Departament** departament) {
	if (table == NULL || departament == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "get_hash_table", " get pointer to null"};
	}
	size_t h = hash(id, table->size);
	if(table->data[h] == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "get_hash_table", "this id didn't register"};
	}
	HashTableListNode * moving = table->data[h]->head;
	for(size_t i = 0; i < table->data[h]->size; ++i){
		if(moving->departament->id == id){
			*departament = moving->departament;
			return (error_msg){SUCCESS, "", ""};
		}
	}
	return (error_msg){INCORRECT_ARG_FUNCTION, "get_hash_table", "this id didn't register"};
}