#include "ex9.h"

void clear_buffer() {
	while (getchar() != '\n')
		;
}

// Поиск слова и вывод информации о нем
int find_word_main(Dictionary *dict, const char **MSG) {
	printf("%s", MSG[3]);
	String word;
	error_msg errorMsg = create_string(&word, "");
	if (errorMsg) {
		return errorMsg;
	}
	int n = read_string(stdin, &word);
	if (n == 0) {
		destroy_string(&word);
		printf("%s", MSG[6]);
		return -1;
	}
	Word *fw = find_word(dict, &word);
	if (!fw) {
		destroy_string(&word);
		printf("%s", MSG[6]);
		return -1;
	}
	printf("%s %d\n", fw->word.arr, fw->n);
	destroy_string(&word);
	return 0;
}

int print_dictionary(Dictionary *dict, const char **MSG) {
	error_msg errorMsg;
	printf("%s", MSG[2]);
	String filename;
	errorMsg = create_string(&filename, "");
	if (errorMsg) {
		return errorMsg;
	}

	int n = read_string(stdin, &filename);
	if (n == 0) {
		printf("%s", MSG[6]);
		return -1;
	}
	FILE *out = fopen(filename.arr, "w");
	if (!out) {
		destroy_string(&filename);
		return INPUT_FILE_ERROR;
	}
	errorMsg = print_dictionary_tree(out, dict->word);
	if (errorMsg) {
		destroy_string(&filename);
		fclose(out);
		return errorMsg;
	}
	fclose(out);
	destroy_string(&filename);
	return 0;
}

int find_n_words(Dictionary *dict, const char **MSG) {
	error_msg errorMsg;
	int n;
	printf("%s", MSG[4]);
	if (scanf("%d", &n) != 1) {
		printf("%s", MSG[6]);
		clear_buffer();
		return -1;
	}
	Word **res;
	errorMsg = find_n_words_in_dictionary(dict, n, &res);
	if (errorMsg) {
		return errorMsg;
	}
	int min_n = min(dict->count_words, n);
	for (int i = 0; i < min_n; ++i) {
		printf("%s %d\n", res[i]->word.arr, res[i]->n);
	}
	clear_buffer();
	free(res);
	return 0;
}

int find_the_longest_word(Dictionary *dict, const char **MSG) {
	Word *head = dict->word;
	if (!head) {
		printf("%s", MSG[6]);
		return 0;
	}
	while (head->right) {
		head = head->right;
	}
	printf("%s %d\n", head->word.arr, head->n);
	return 0;
}

int find_the_smallest_word(Dictionary *dict, const char **MSG) {
	Word *head = dict->word;
	if (!head) {
		printf("%s", MSG[6]);
		return 0;
	}
	while (head->left) {
		head = head->left;
	}
	printf("%s %d\n", head->word.arr, head->n);
	return 0;
}

int find_depth(Dictionary *dict, const char **MSG) {
	int d = 0;
	error_msg errorMsg = max_depth(dict, &d);
	if (errorMsg) {
		return errorMsg;
	}
	printf("%s%d\n", MSG[7], d);
	return 0;
}

int download(Dictionary *dict, const char **MSG) {
	error_msg errorMsg;
	printf("%s", MSG[2]);
	String filename;
	errorMsg = create_string(&filename, "");
	if (errorMsg) {
		return errorMsg;
	}

	int n = read_string(stdin, &filename);
	if (n == 0) {
		destroy_string(&filename);
		printf("%s", MSG[6]);
		clear_buffer();
		return -1;
	}
	errorMsg = download_to_file(&filename, dict);
	if(errorMsg == OUTPUT_FILE_ERROR){
		printf("%s", MSG[6]);
		destroy_string(&filename);
		return -1;
	}
	else if (errorMsg) {
		destroy_string(&filename);
		return errorMsg;
	}

	destroy_string(&filename);
	return 0;
}

int load(Dictionary *dict, const char **MSG) {

	error_msg errorMsg;
	printf("%s", MSG[2]);
	String filename;
	errorMsg = create_string(&filename, "");
	if (errorMsg) {
		return errorMsg;
	}

	int n = read_string(stdin, &filename);
	if (n == 0) {
		destroy_string(&filename);
		clear_buffer();
		printf("%s", MSG[6]);
		return -1;
	}


	errorMsg = load_dictionary_from_file(&filename, dict);
	if(errorMsg == INPUT_FILE_ERROR){
		printf("%s", MSG[6]);
		destroy_string(&filename);
		return -1;
	}
	else if (errorMsg) {
		destroy_string(&filename);
		return errorMsg;
	}

	destroy_string(&filename);
	return 0;
}

int is_command(String *command, const char **COMMANDS) {
	if (string_cmp(command->arr, COMMANDS[0]) || string_cmp(command->arr, "1\n")) return 0;
	if (string_cmp(command->arr, COMMANDS[1]) || string_cmp(command->arr, "2\n")) return 1;
	if (string_cmp(command->arr, COMMANDS[2]) || string_cmp(command->arr, "3\n")) return 2;
	if (string_cmp(command->arr, COMMANDS[3]) || string_cmp(command->arr, "4\n")) return 3;
	if (string_cmp(command->arr, COMMANDS[4]) || string_cmp(command->arr, "5\n")) return 4;
	if (string_cmp(command->arr, COMMANDS[5]) || string_cmp(command->arr, "6\n")) return 5;
	if (string_cmp(command->arr, COMMANDS[6]) || string_cmp(command->arr, "7\n")) return 6;
	if (string_cmp(command->arr, COMMANDS[7]) || string_cmp(command->arr, "8\n")) return 7;
	if (string_cmp(command->arr, COMMANDS[8]) || string_cmp(command->arr, "9\n")) return 8;

	return -1;
}

int main(int argc, char **argv) {
	const char *MSG[] = {"You can write one of these commands(or its indices):\n",
	                     "Incorrect command\n",
	                     "Write filename: ",
	                     "Write word: ",
	                     "Write n: ",
	                     "If you need help, write help\n\n",
	                     "Incorrect data\n",
	                     "Max depth: "};
	const char *COMMANDS[] = {"help\n",         "print all words\n",       "find word\n",
	                          "find n words\n", "find the longest word\n", "find the smallest word\n",
	                          "find depth\n",   "download tree\n",         "load tree\n"};

	Dictionary dictionary;
	dictionary.word = NULL;
	error_msg errorMsg;

	errorMsg = parse_to_binary_tree(argc, argv, &dictionary);
	if (errorMsg) {
		destroy_dictionary(dictionary.word);
		return errorMsg;
	}

	int n;
	String command;
	errorMsg = create_string(&command, "");
	if (errorMsg) {
		destroy_dictionary(dictionary.word);
		return errorMsg;
	}

	int (*handlers[8])(Dictionary *dictionary, const char **MSG) = {
	    print_dictionary,       find_word_main, find_n_words, find_the_longest_word,
	    find_the_smallest_word, find_depth,     download,     load};


	printf("%s", MSG[5]);
	while (1) {
		clear_string(&command);
		if (!string_cmp(command.arr, "\n")) {
			printf("> ");
		}
		n = read_line(stdin, &command);
		if (n == 0) {
			break;
		}

		int is_cmd = is_command(&command, COMMANDS);
		if (!is_cmd) {
			printf("%s", MSG[0]);
			for (int i = 0; i < 9; ++i) {
				printf("%d. %s", i + 1, COMMANDS[i]);
			}
			continue;
		}
		if (is_cmd == -1) {
			printf("%s", MSG[1]);
			continue;
		}

		int er = handlers[is_cmd - 1](&dictionary, MSG);
		if (er == -1) {
			continue;
		} else if (er) {
			destroy_string(&command);
			errorMsg = destroy_dictionary(dictionary.word);
			if (errorMsg) {
				return print_error(errorMsg);
			}
			return er;
		}
	}

	destroy_string(&command);
	errorMsg = destroy_dictionary(dictionary.word);
	if (errorMsg) {
		return print_error(errorMsg);
	}
	return 0;
}
