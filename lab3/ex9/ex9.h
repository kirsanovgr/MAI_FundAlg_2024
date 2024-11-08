#ifndef LAB3_EX9_H
#define LAB3_EX9_H

#include <stdio.h>
#include <stdlib.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/vector/charvector.h"


typedef struct Word{
	String word;
	int n;
	struct Word * left;
	struct Word * right;
} Word;

typedef struct Dictionary {
	int count_words;
	Word * word;
} Dictionary;

typedef struct Stack{
	Word * node;
	struct Stack * next;
} Stack;



#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b

int checks_names_files(int argc, char **argv);
error_msg parse_to_binary_tree(int argc, char** argv, Dictionary * dictionary);

// Функции для взаимодействия со словами
error_msg create_word(Word ** word, String * s);
Word * find_word(Dictionary * dictionary, String * find);
error_msg max_depth(Dictionary * dict, int *max_d);
int el_depth(Dictionary *dictionary, String *s);
void destroy_word(Word * word);

// Функции для обработки дерева
error_msg destroy_dictionary(Word * word);
error_msg push_word_into_dictionary(Dictionary * dict, String * word);
error_msg print_dictionary_tree(FILE * stream, Word * word);
error_msg find_n_words_in_dictionary(Dictionary * dictionary, int n, Word *** result);
error_msg from_tree_to_arr(Word *word, Word **arr);
error_msg load_dictionary_from_file(String * filename, Dictionary * dictionary);
error_msg download_to_file(String * filename, Dictionary * dictionary);

// Функции для обработки стэка
error_msg push_stack(Stack ** head, Word * node);
Word *pop_stack(Stack ** head);
Word *top_stack(Stack **head);
int is_empty_stack(Stack * head);
void destroy_stack(Stack * stack);
#endif  // LAB3_EX9_H
