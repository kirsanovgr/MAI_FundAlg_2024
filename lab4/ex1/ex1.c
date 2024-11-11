#include "ex1.h"

int seq_numbers(char c) {
	if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 10;
	} else if (c >= 'a' && c <= 'z') {
		return c - 'a' + 10 + 26;
	} else if (c >= '0' && c <= '9') {
		return c - '0';
	} else {
		return -1;
	}
}

unsigned long hash_62(String *string, const int hash_size) {
	unsigned long hash = 0;
	int seq;
	for (int i = 0; i < string->size; ++i) {
		seq = seq_numbers(string->arr[i]);
		if (seq == -1) {
			return -1;
		}
		hash = hash % hash_size + seq;
	}
	return hash % hash_size;
}

error_msg create_list(List **list) {
	*list = (List *)calloc(1, sizeof(List));
	if (!*list) {
		return MEMORY_ALLOCATED_ERROR;
	}
	return SUCCESS;
}

error_msg list_push_end(List *list, String *def_name, String *value, unsigned long hash) {
	ListNode *listNode = (ListNode *)calloc(1, sizeof(ListNode));
	if (!listNode) {
		return MEMORY_ALLOCATED_ERROR;
	}
	if (!list->head) {
		list->head = listNode;
		listNode->next = listNode;
		listNode->last = listNode;
	} else {
		listNode->next = list->head;
		listNode->last = list->head->last;
		list->head->last->next = listNode;
		list->head->last = listNode;
	}

	error_msg errorMsg = mstrcopynew(def_name, &(listNode->def_name));
	if (errorMsg) {
		free(listNode);
		return errorMsg;
	}

	errorMsg = mstrcopynew(value, &(listNode->value));
	if (errorMsg) {
		destroy_string(&(listNode->value));
		free(listNode);
		return errorMsg;
	}
	list->size += 1;
	listNode->hash = hash;
	return SUCCESS;
}

error_msg list_push_start(List *list, String *def_name, String *value, unsigned long hash) {
	ListNode *listNode = (ListNode *)calloc(1, sizeof(ListNode));
	if (!listNode) {
		return MEMORY_ALLOCATED_ERROR;
	}
	if (!list->head) {
		list->head = listNode;
		listNode->next = listNode;
		listNode->last = listNode;
	} else {
		listNode->next = list->head;
		list->head->last = listNode;
		listNode->last = list->head->last;
		list->head = listNode;
	}

	error_msg errorMsg = mstrcopynew(def_name, &(listNode->def_name));
	if (errorMsg) {
		free(listNode);
		return errorMsg;
	}

	errorMsg = mstrcopynew(value, &(listNode->value));
	if (errorMsg) {
		destroy_string(&(listNode->value));
		free(listNode);
		return errorMsg;
	}
	listNode->hash = hash;
	list->size += 1;
	return SUCCESS;
}

void destroy_list(List *list) {
	ListNode *moving_head = list->head;
	ListNode *t;
	int i = 0;
	while (i < list->size) {
		t = moving_head;
		moving_head = moving_head->next;
		destroy_list_node(t);
		i += 1;
	}
	free(list);
}

void destroy_list_node(ListNode *listNode) {
	listNode->next = NULL;
	listNode->last = NULL;
	listNode->hash = 0;
	destroy_string(&(listNode->value));
	destroy_string(&(listNode->def_name));
	free(listNode);
}

void print_list(FILE *stream, List *list) {
	ListNode *moving = list->head;
	for (int i = 0; i < list->size; ++i) {
		print_string(stream, &(moving->def_name), "");
		putc(' ', stream);
		print_string(stream, &(moving->value), "");
		putc(' ', stream);
		fprintf(stream, "%ld\n", moving->hash);
		moving = moving->next;
	}
}

error_msg create_hash_table(HashTable *hash_table, int hash_size) {
	hash_table->data = (List **)calloc(hash_size, sizeof(List *));
	if (!hash_table->data) {
		return MEMORY_ALLOCATED_ERROR;
	}
	hash_table->hash_size = hash_size;
	hash_table->hash_count = 0;
	return SUCCESS;
}

void destroy_hash_table(HashTable *hash_table) {
	for (int i = 0; i < hash_table->hash_size; ++i) {
		if (hash_table->data[i]) {
			destroy_list(hash_table->data[i]);
		}
	}
	free(hash_table->data);
}

error_msg push_into_hash_table(HashTable *hash_table, String *def_name, String *value, int *max_size_list,
                               int *min_size_list, unsigned int h) {
	if (!hash_table->data) {
		return MEMORY_ALLOCATED_ERROR;
	}

	// Если не было до этого хэша
	if (h == (unsigned long )hash_table->hash_size + 1) {
		h = hash_62(def_name, hash_table->hash_size);
	}
	unsigned long index = h % hash_table->hash_size;
	error_msg errorMsg;

	if (!hash_table->data[index]) {
		errorMsg = create_list(&(hash_table->data[index]));
		if (errorMsg) {
			return errorMsg;
		}
	}
	errorMsg = list_push_end(hash_table->data[index], def_name, value, h);
	if (errorMsg) {
		return errorMsg;
	}
	*max_size_list = max(*max_size_list, hash_table->data[index]->size);
	for (int i = 0; i < hash_table->hash_size; ++i) {
		if (hash_table->data[i] && hash_table->data[i]->size > 1) *min_size_list = min(*min_size_list, hash_table->data[i]->size);
	}
	hash_table->hash_count += 1;
	return SUCCESS;
}

error_msg renew_hash_table_with_new_size(const HashTable *dst, HashTable *src) {
	int new_hash_size = calculate_new_size(dst->hash_count);
	;
	error_msg errorMsg = create_hash_table(src, new_hash_size);
	if (errorMsg) {
		return errorMsg;
	}
	int max_size_list = -1;
	int min_size_list = 1000;
	ListNode *moving;
	for (int i = 0; i < dst->hash_size; ++i) {
		if (dst->data[i]) {
			moving = dst->data[i]->head;
			for (int j = 0; j < dst->data[i]->size; ++j) {
				errorMsg = push_into_hash_table(src, &(moving->def_name), &(moving->value), &max_size_list,
				                                &min_size_list, moving->hash);
				if (errorMsg) {
					destroy_hash_table(src);
					return errorMsg;
				}
				moving = moving->next;
			}
		}
	}
	return SUCCESS;
}

int calculate_new_size(int hash_count) { return (int)((double)hash_count * 2); }

int is_correct_def_name(String *s) {
	for (int i = 0; i < s->size; ++i) {
		if ((s->arr[i] < '0' || s->arr[i] > '9') && (s->arr[i] < 'a' || s->arr[i] > 'z') &&
		    (s->arr[i] < 'A' || s->arr[i] > 'Z')) {
			return 0;
		}
	}
	return 1;
}

error_msg check_all_def(String *res, String *tmp, HashTable *hashTable) {
	String substring;
	error_msg errorMsg = create_string(&substring, "");
	if (errorMsg) {
		return errorMsg;
	}
	int fl;
	for (int i = 0; i < tmp->size; ++i) {
		fl = 0;
		for (int j = tmp->size; j >= i; --j) {
			clear_string(&substring);

			errorMsg = mstrcopy(tmp, &substring, i, j);
			if (errorMsg) {
				destroy_string(&substring);
				return errorMsg;
			}
			unsigned long h = hash_62(&substring, hashTable->hash_size) % hashTable->hash_size;
			if (hashTable->data[h]) {
				ListNode *moving = hashTable->data[h]->head;
				for (int k = 0; k < hashTable->data[h]->size; ++k) {
					if (string_cmp(moving->def_name.arr, substring.arr)) {
						fl = 1;
						// Вставляем вместо def_name -> value
						errorMsg = mstrcat(res, &(moving->value));
						if (errorMsg) {
							destroy_string(&substring);
							return errorMsg;
						}
						i = j - 1;
						break;
					}
					moving = moving->next;
				}
			}

		}
		if (!fl) {
			errorMsg = push_end_string(res, tmp->arr[i]);
			if (errorMsg) {
				destroy_string(&substring);
				return errorMsg;
			}
		}
	}

	destroy_string(&substring);
	return SUCCESS;
}

error_msg build_hash_table(FILE *stream, HashTable *hashTable, String *result) {
	error_msg errorMsg;
	errorMsg = create_hash_table(hashTable, DEFAULT_HASH_TABLE_SIZE);
	if (errorMsg) {
		destroy_hash_table(hashTable);
		return print_error(errorMsg);
	}

	String tmp;
	errorMsg = create_string(&tmp, "");
	if (errorMsg) {
		destroy_hash_table(hashTable);
		return errorMsg;
	}

	int n = read_string(stream, &tmp);
	String def_name;
	String value;
	errorMsg = create_string(&def_name, "");
	if (errorMsg) {
		destroy_hash_table(hashTable);
		destroy_string(&tmp);
		return errorMsg;
	}
	errorMsg = create_string(&value, "");
	if (errorMsg) {
		destroy_hash_table(hashTable);
		destroy_string(&tmp);
		destroy_string(&def_name);
		return errorMsg;
	}

	int max_size = -1;
	int min_size = 100000;
	int position = n;
	while (!feof(stream)) {
		if (string_cmp(tmp.arr, "#define")) {
			clear_string(&value);
			clear_string(&def_name);
			n = read_string(stream, &def_name);
			position += n;

			if (!is_correct_def_name(&def_name) || n == 0) {
				destroy_hash_table(hashTable);
				destroy_string(&tmp);
				destroy_string(&def_name);
				destroy_string(&value);
				return errorMsg;
			}
			n = read_line(stream, &value);
			if (value.size > 0) {
				value.arr[value.size - 1] = '\0';
				value.size -= 1;
			}
			position += n;

			errorMsg = push_into_hash_table(hashTable, &def_name, &value, &max_size, &min_size, hashTable->hash_size + 1);
			if (errorMsg) {
				destroy_hash_table(hashTable);
				destroy_string(&tmp);
				destroy_string(&def_name);
				destroy_string(&value);
				return errorMsg;
			}
			if (max_size / min_size >= 2) {
				HashTable new_hash_table;
				errorMsg = renew_hash_table_with_new_size(hashTable, &new_hash_table);
				if (errorMsg) {
					destroy_hash_table(hashTable);
					destroy_string(&tmp);
					destroy_string(&value);
					destroy_string(&def_name);
					return errorMsg;
				}
				destroy_hash_table(hashTable);
				*hashTable = new_hash_table;
			}
			errorMsg = mstrcat(result, &tmp);
			if (errorMsg) {
				destroy_hash_table(hashTable);
				destroy_string(&tmp);
				destroy_string(&value);
				destroy_string(&def_name);
				return errorMsg;
			}
		} else {
			break;
		}
		clear_string(&tmp);
		n = read_string(stream, &tmp);
		position += n;
	}
	destroy_string(&tmp);
	destroy_string(&value);
	destroy_string(&def_name);
	return SUCCESS;
}

error_msg read_instruction(FILE *stream, String *result) {
	error_msg errorMsg;

	HashTable hashTable;
	errorMsg = build_hash_table(stream, &hashTable, result);
	if (errorMsg) {
		return errorMsg;
	}

	String def_name;
	String value;
	errorMsg = create_string(&def_name, "");
	if (errorMsg) {
		destroy_hash_table(&hashTable);
		return errorMsg;
	}
	errorMsg = create_string(&value, "");
	if (errorMsg) {
		destroy_hash_table(&hashTable);
		destroy_string(&def_name);
		return errorMsg;
	}

	String tmp;
	errorMsg = create_string(&tmp, "");
	if (errorMsg) {
		destroy_hash_table(&hashTable);
		return errorMsg;
	}

	// Записываем в строку результата define
	char c;
	rewind(stream);
	clear_string(result);
	for (int i = 0; i < hashTable.hash_count; ++i) {
		while ((c = getc(stream)) != EOF && c != '\n') {
			errorMsg = push_end_string(result, c);
			if (errorMsg) {
				destroy_hash_table(&hashTable);
				destroy_string(&tmp);
				destroy_string(&value);
				destroy_string(&def_name);
				return errorMsg;
			}
		}
		errorMsg = push_end_string(result, '\n');
		if (errorMsg) {
			destroy_hash_table(&hashTable);
			destroy_string(&tmp);
			destroy_string(&value);
			destroy_string(&def_name);
			return errorMsg;
		}
	}
//	errorMsg = push_end_string(result, '\n');
//	if (errorMsg) {
//		destroy_hash_table(&hashTable);
//		destroy_string(&tmp);
//		destroy_string(&value);
//		destroy_string(&def_name);
//		return errorMsg;
//	}

	clear_string(&tmp);
	while (1) {
		c = getc(stream);
		if (c == EOF || ((c < '0' || c > '9') && (c < 'a' || c > 'z') && (c < 'A' || c > 'Z'))) {
			errorMsg = check_all_def(result, &tmp, &hashTable);
			if (errorMsg) {
				destroy_hash_table(&hashTable);
				destroy_string(&tmp);
				destroy_string(&value);
				destroy_string(&def_name);
				return errorMsg;
			}
			if(c == EOF){
				break;
			}
			errorMsg = push_end_string(result, c);
			if (errorMsg) {
				destroy_hash_table(&hashTable);
				destroy_string(&tmp);
				destroy_string(&value);
				destroy_string(&def_name);
				return errorMsg;
			}
			clear_string(&tmp);
			//			printf("%s\n", result->arr);
		} else {
			errorMsg = push_end_string(&tmp, c);
			if (errorMsg) {
				destroy_hash_table(&hashTable);
				destroy_string(&tmp);
				destroy_string(&value);
				destroy_string(&def_name);
				return errorMsg;
			}
		}
	}
	//	printf("%s\n", result->arr);
	destroy_hash_table(&hashTable);
	destroy_string(&def_name);
	destroy_string(&value);
	destroy_string(&tmp);
	return SUCCESS;
}