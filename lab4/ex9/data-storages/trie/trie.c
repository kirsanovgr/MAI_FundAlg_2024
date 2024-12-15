#include "trie.h"

error_msg create_trie_node(TrieNode **node, size_t id_department, size_t count_operators, char what_queue) {
	if (node == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_trie_node", "get pointer to null"};
	}

	TrieNode *tmp = (TrieNode *)calloc(1, sizeof(TrieNode));
	if (tmp == NULL) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_trie_node", "memory allocated in object"};
	}
	error_msg errorMsg = create_departament(&(tmp->departament), count_operators, id_department, what_queue);
	if (errorMsg.type) {
		free(tmp);
		return errorMsg;
	}

	tmp->capacity = DEFAULT_CAPACITY_TRIE_NODE;
	tmp->size = 0;
	tmp->next = (TrieNode **)calloc(tmp->capacity, sizeof(TrieNode *));
	if (tmp->next == 0) {
		destroy_departament(tmp->departament);
		free(tmp);
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_trie_node", "memory allocated"};
	}
	*node = tmp;
	return (error_msg){SUCCESS, "", ""};
}

void destroy_tree_node(TrieNode *node) {
	if (node == NULL) {
		return;
	}
	for (size_t i = 0; i < node->capacity; ++i) {
		destroy_tree_node(node->next[i]);
	}

	if (node->departament) {
		destroy_departament(node->departament);
	}
	free(node->next);
	free(node);
}

error_msg create_trie_node_without_department(TrieNode **node) {
	if (node == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_trie_node_without_department", "get pointer to null"};
	}

	TrieNode *tmp = (TrieNode *)calloc(1, sizeof(TrieNode));
	if (tmp == NULL) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_trie_node_without_department", "memory allocated in object"};
	}
	tmp->departament = NULL;

	tmp->capacity = DEFAULT_CAPACITY_TRIE_NODE;
	tmp->size = 0;
	tmp->next = (TrieNode **)calloc(tmp->capacity, sizeof(TrieNode *));
	if (tmp->next == 0) {
		destroy_departament(tmp->departament);
		free(tmp);
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_trie_node_without_department", "memory allocated"};
	}
	*node = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg create_trie(Trie *trie) {
	if (trie == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_trie", "get pointer to null"};
	}
	error_msg errorMsg = create_trie_node_without_department(&(trie->head));
	if (errorMsg.type) {
		return errorMsg;
	}
	trie->size = 0;
	return (error_msg){SUCCESS, "", ""};
}

error_msg destroy_trie(Trie *trie) {
	if (trie == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_trie", "get pointer to null"};
	}
	destroy_tree_node(trie->head);
	trie->size = 0;
	return (error_msg){SUCCESS, "", ""};
}

error_msg push_into_trie(Trie *trie, size_t id_department, size_t count_operators, char what_queue) {
	if (trie == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "push_into_trie", "get pointer to null"};
	}
	String string_id;
	error_msg errorMsg = create_string(&string_id, "");
	if (errorMsg.type) {
		return errorMsg;
	}

	errorMsg = u_long_to_str(id_department, &string_id);
	if (errorMsg.type) {
		destroy_string(&string_id);
		return errorMsg;
	}

	char const_string_id[string_id.size + 1];
	strcpy(const_string_id, string_id.arr);
	size_t len_const_string_id = string_id.size;
	destroy_string(&string_id);

	TrieNode *node = trie->head;
	trie->size += 1;
	for (size_t i = 0; i < len_const_string_id; ++i) {
		size_t c = const_string_id[i] - '0';
		// Так как у нас строки это бывшие size_t числа, то длина массива максимум 10
		if (node->next[c] == NULL) {
			node->size += 1;
			errorMsg = create_trie_node_without_department(&(node->next[c]));
			if (errorMsg.type) {
				return errorMsg;
			}
		}
		node = node->next[c];
	}
	if (node->departament != NULL) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, "push_into_trie", "this idea already exist"};
	}
	errorMsg = create_departament(&(node->departament), count_operators, id_department, what_queue);
	if (errorMsg.type) {
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg get_trie(Trie *trie, size_t id, Departament **departament) {
	if (trie == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "get_into_trie", "get pointer to null"};
	}

	String string_id;
	error_msg errorMsg = create_string(&string_id, "");
	if (errorMsg.type) {
		return errorMsg;
	}

	errorMsg = u_long_to_str(id, &string_id);
	if (errorMsg.type) {
		destroy_string(&string_id);
		return errorMsg;
	}

	char const_string_id[string_id.size + 1];
	strcpy(const_string_id, string_id.arr);
	size_t len_const_string_id = string_id.size;
	destroy_string(&string_id);

	TrieNode *node = trie->head;
	for (size_t i = 0; i < len_const_string_id; ++i) {
		size_t c = const_string_id[i] - '0';
		if (node->next[c] == NULL) {
			return (error_msg){INCORRECT_OPTIONS_ERROR, "get_trie", "this id doesn't exist"};
		}
		node = node->next[c];
	}

	if (node->departament == NULL) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, "get_trie", "this id doesn't exist"};
	}
	*departament = node->departament;
	return (error_msg){SUCCESS, "", ""};
}