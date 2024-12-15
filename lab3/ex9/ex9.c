#include "ex9.h"

error_msg create_word(Word **word, String *s) {
	Word *word_tmp;
	word_tmp = (Word *)calloc(1, sizeof(Word));
	if (!word_tmp) {
		return MEMORY_ALLOCATED_ERROR;
	}
	error_msg errorMsg = mstrcopynew(s, &(word_tmp->word));
	if (errorMsg) {
		return errorMsg;
	}
	word_tmp->n = 1;
	*word = word_tmp;
	return SUCCESS;
}

void destroy_word(Word *word) {
	destroy_string(&(word->word));
	word->n = 0;
	free(word);
}

error_msg push_word_into_dictionary(Dictionary *dict, String *word) {
	error_msg errorMsg;
	if (!dict->word) {
		errorMsg = create_word(&(dict->word), word);
		if (errorMsg) {
			return errorMsg;
		}
		dict->count_words = 1;
		return SUCCESS;
	}
	Word *current = dict->word;
	Word *parent = NULL;
	while (current) {
		parent = current;
		if (string_comp(&(parent->word), word) > 0) {
			current = current->left;
		} else if (string_comp(&(parent->word), word) < 0) {
			current = current->right;
		} else {
			current->n += 1;
			return SUCCESS;
		}
	}
	dict->count_words += 1;
	errorMsg = create_word(&current, word);
	if (errorMsg) {
		return errorMsg;
	}
	if (string_comp(&(parent->word), word) > 0) {
		parent->left = current;
	} else {
		parent->right = current;
	}
	return SUCCESS;
}

error_msg print_dictionary_tree(FILE *stream, Word *word) {
	Stack *stack = NULL;
	error_msg errorMsg;
	while (word || !is_empty_stack(stack)) {
		while (word) {
			errorMsg = push_stack(&stack, word);
			if (errorMsg) {
				destroy_stack(stack);
				return errorMsg;
			}
			word = word->left;
		}
		word = pop_stack(&stack);
		fprintf(stream, "%s %d\n", word->word.arr, word->n);
		word = word->right;
	}
	destroy_stack(stack);
	return SUCCESS;
}

int IsSeparator(int argc, char **argv, char c) {
	for (int i = 2; i < argc; ++i) {
		if (argv[i][0] == c) {
			return 1;
		}
	}
	return 0;
}

error_msg parse_to_binary_tree(int argc, char **argv, Dictionary *dictionary) {
	if (argc < 2) {
		return print_error(INCORRECT_OPTIONS_ERROR);
	}
	String filename;
	error_msg errorMsg = create_string(&filename, argv[1]);
	if (errorMsg) {
		return errorMsg;
	}
	FILE *stream = fopen(filename.arr, "r");
	if (!stream) {
		destroy_string(&filename);
		return INPUT_FILE_ERROR;
	}
	destroy_string(&filename);

	String tmp;
	errorMsg = create_string(&tmp, "");
	if (errorMsg) {
		fclose(stream);
		destroy_string(&filename);
		return errorMsg;
	}

	char c;
	c = getc(stream);
	while (!feof(stream)) {
		if (IsSeparator(argc, argv, c) && tmp.size) {
			errorMsg = push_word_into_dictionary(dictionary, &tmp);
			if (errorMsg) {
				fclose(stream);
				destroy_string(&tmp);
				destroy_string(&filename);
				return errorMsg;
			}
			clear_string(&tmp);
		} else if(!IsSeparator(argc, argv, c)){
			errorMsg = push_end_string(&tmp, c);
			if (errorMsg) {
				fclose(stream);
				destroy_string(&tmp);
				destroy_string(&filename);
				return errorMsg;
			}
		}else{
			clear_string(&tmp);
		}
		c = getc(stream);
	}
	if (tmp.size > 0) {
		errorMsg = push_word_into_dictionary(dictionary, &tmp);
		if (errorMsg) {
			fclose(stream);
			destroy_string(&tmp);
			destroy_string(&filename);
			return errorMsg;
		}
	}

	fclose(stream);
	destroy_string(&tmp);
	return SUCCESS;
}

error_msg destroy_dictionary(Word *word) {
	Stack *stack = NULL;
	error_msg errorMsg;
	while (word || !is_empty_stack(stack)) {
		while (word) {
			errorMsg = push_stack(&stack, word);
			if (errorMsg) {
				destroy_stack(stack);
				return errorMsg;
			}
			word = word->left;
		}
		word = pop_stack(&stack);
		Word *tmp = word;
		word = word->right;
		destroy_word(tmp);
	}
	destroy_stack(stack);
	return SUCCESS;
}

Word *find_word(Dictionary *dictionary, String *find) {
	Word *moving = (dictionary->word);
	while (moving) {
		if (string_comp(&(moving->word), find) > 0) {
			moving = moving->left;
		} else if (string_comp(&(moving->word), find) < 0) {
			moving = moving->right;
		} else {
			return moving;
		}
	}
	return NULL;
}

error_msg max_depth(Dictionary *dict, int *max_d) {
	Word *word = dict->word;
	Stack *stack = NULL;
	error_msg errorMsg;
	int max_depth = -1;
	while (word || !is_empty_stack(stack)) {
		while (word) {
			errorMsg = push_stack(&stack, word);
			if (errorMsg) {
				destroy_stack(stack);
				return errorMsg;
			}
			word = word->left;
		}
		word = pop_stack(&stack);
		Word *tmp = word;
		word = word->right;
		max_depth = max(max_depth, el_depth(dict, &(tmp->word)));
	}
	destroy_stack(stack);
	*max_d = max_depth;
	return SUCCESS;
}

int el_depth(Dictionary *dictionary, String *s) {
	int depth = 0;
	Word *moving = dictionary->word;
	while (moving) {
		if (string_comp(&(moving->word), s) > 0) {
			moving = moving->left;
			depth += 1;
		} else if (string_comp(&(moving->word), s) < 0) {
			moving = moving->right;
			depth += 1;
		} else {
			return depth;
		}
	}
	return -1;
}

int LessCompareWords(const void *a, const void *b) { return -((*((Word **)a))->n - (*((Word **)b))->n); }

error_msg from_tree_to_arr(Word *word, Word **arr) {
	int i = 0;
	Stack *stack = NULL;
	error_msg errorMsg;
	while (word || !is_empty_stack(stack)) {
		while (word) {
			errorMsg = push_stack(&stack, word);
			if (errorMsg) {
				destroy_stack(stack);
				return errorMsg;
			}
			word = word->left;
		}
		word = pop_stack(&stack);
		arr[i++] = word;
		word = word->right;
	}
	destroy_stack(stack);
	return SUCCESS;
}

error_msg find_n_words_in_dictionary(Dictionary *dictionary, int n, Word ***result) {
	Word **tmp = (Word **)calloc(dictionary->count_words, sizeof(Word *));
	if (!tmp) {
		return MEMORY_ALLOCATED_ERROR;
	}
	error_msg errorMsg = from_tree_to_arr(dictionary->word, tmp);
	if (errorMsg) {
		free(tmp);
		return errorMsg;
	}
	qsort(tmp, dictionary->count_words, sizeof(Word *), LessCompareWords);

	int min_n = min(n, dictionary->count_words);
	*result = (Word **)malloc(sizeof(Word *) * min_n);
	if (!*result) {
		free(tmp);
		return MEMORY_ALLOCATED_ERROR;
	}
	int i;
	for (i = 0; i < min_n; ++i) {
		(*result)[i] = tmp[i];
	}
	free(tmp);
	return SUCCESS;
}

error_msg push_stack(Stack **head, Word *node) {
	Stack *el = (Stack *)calloc(1, sizeof(Stack));
	if (!el) {
		return MEMORY_ALLOCATED_ERROR;
	}
	el->next = *head;
	el->node = node;
	*head = el;
	return SUCCESS;
}

Word *pop_stack(Stack **head) {
	if (!*head) {
		return NULL;
	}
	Stack *tmp = (*head);
	Word *t = (*head)->node;
	*head = (*head)->next;
	free(tmp);
	return t;
}


Word *top_stack(Stack **head) {
	if (!*head) {
		return NULL;
	}
	return (*head)->node;
}

int is_empty_stack(Stack *head) { return !head; }

void destroy_stack(Stack *stack) {
	if (!stack) {
		return;
	}
	Stack *t = stack;
	stack = stack->next;
	while (stack) {
		free(t);
		t = stack;
		stack = stack->next;
	}
}

error_msg download_to_file(String *filename, Dictionary *dictionary) {
	FILE *stream = fopen(filename->arr, "w");
	if (!stream) {
		return OUTPUT_FILE_ERROR;
	}
	Stack *stack = NULL;
	Word *word = dictionary->word;
	error_msg errorMsg = push_stack(&stack, word);
	if (errorMsg) {
		destroy_stack(stack);
		fclose(stream);
		return errorMsg;
	}
	while (!is_empty_stack(stack)) {
		Word *cur = pop_stack(&stack);
		if (cur) {
			fprintf(stream, "%s %d\n", cur->word.arr, cur->n);
			errorMsg = push_stack(&stack, cur->right);
			if (errorMsg) {
				destroy_stack(stack);
				fclose(stream);
				return errorMsg;
			}
			errorMsg = push_stack(&stack, cur->left);
			if (errorMsg) {
				destroy_stack(stack);
				fclose(stream);
				return errorMsg;
			}
		} else {
			fprintf(stream, "new_branch\n");
		}
	}
	destroy_stack(stack);
	fclose(stream);
	return SUCCESS;
}

error_msg load_dictionary_from_file(String *filename, Dictionary *dictionary) {
	FILE *stream = fopen(filename->arr, "r");
	if (!stream) {
		return INPUT_FILE_ERROR;
	}

	String tmp;
	error_msg errorMsg = create_string(&tmp, "");
	if (errorMsg) {
		fclose(stream);
		return errorMsg;
	}

	Stack *stack = NULL;
	Word *root = NULL;
	Word *cur = NULL;

	destroy_dictionary(dictionary->word);
 	dictionary->word = 0;
	dictionary->count_words = 0;
	// Считываем верхний корень и засовываем в стек
	int n = read_string(stream, &tmp);
	if (n == 0 || string_cmp(tmp.arr, "new_branch")) {
		fclose(stream);
		destroy_string(&tmp);
		return SUCCESS;
	}
	errorMsg = create_word(&root, &tmp);
	if (errorMsg) {
		fclose(stream);
		destroy_string(&tmp);
		return errorMsg;
	}
	fscanf(stream, "%d", &(root->n));
	getc(stream);
	errorMsg = push_stack(&stack, root);
	if (errorMsg) {
		fclose(stream);
		destroy_string(&tmp);
		return errorMsg;
	}

	int fl = 0;
	while (!is_empty_stack(stack)) {
		cur = top_stack(&stack);
		clear_string(&tmp);
		n = read_string(stream, &tmp);
		if ((n == 0 || string_cmp(tmp.arr, "new_branch"))) {
			if (cur->left || cur->right || fl) {
				pop_stack(&stack);
				fl = 0;
				continue;
			}
			cur->left = NULL;
			fl = 1;
		} else {
			while (cur->left && cur->right) {
				cur = pop_stack(&stack);
			}
			fl = 0;
			Word *x;
			dictionary->count_words += 1;
			errorMsg = create_word(&x, &tmp);
			if (errorMsg) {
				fclose(stream);
				destroy_string(&tmp);
				destroy_stack(stack);
				return errorMsg;
			}
			fscanf(stream, "%d", &(x->n));
			getc(stream);
			if (string_comp(&(x->word), &(cur->word)) > 0) {
				Word * tmp_x = top_stack(&stack);
				while ((cur->right) || (tmp_x && string_comp(&(tmp_x->word), &(tmp)) < 0)) {
					cur = pop_stack(&stack);
					tmp_x = top_stack(&stack);
				}
				cur->right = x;
			} else {
				while ((cur->left)) {
					cur = pop_stack(&stack);
				}
				cur->left = x;
			}
			errorMsg = push_stack(&stack, x);
			if (errorMsg) {
				destroy_word(x);
				fclose(stream);
				destroy_string(&tmp);
				destroy_stack(stack);
				return errorMsg;
			}
		}
	}

	dictionary->word = root;
	destroy_string(&tmp);
	fclose(stream);
	return SUCCESS;
}