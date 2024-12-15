#include <stdio.h>

#include "../../lib2/SystemErrors2/errors.h"
#include "../../lib2/vector/charvector.h"
#include "../application/application.h"

error_msg read_filename(String* tmp, char** MSG, int* count, FILE** f) {
	if (tmp == NULL || count == NULL || MSG == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "read_filename", "get pointer to null"};
	}
	printf("%s", MSG[*count]);
	int n = read_string(stdin, tmp);
	if (n == -1) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "read_string", "memory allocated"};
	} else if (n != 0) {
		strip(tmp);
		*count += 1;
		*f = fopen(tmp->arr, "w");
		if (!*f) {
			destroy_string(tmp);
			return (error_msg){INPUT_FILE_ERROR, "read_string", "input file didn't open"};
		}
	}
	return (error_msg){SUCCESS, "", ""};
}

void print_data_struct_for_application() {
	char* s[] = {
	    "○ BinaryHeap - двоичная приоритетная очередь\n",        "○ BinomialHeap - биномиальная приоритетная очередь\n",
	    "○ FibonacciHeap - фибоначчиева приоритетная очередь\n", "○ SkewHeap - косая приоритетная очередь\n",
	    "○ LeftistHeap - левосторонняя приоритетная очередь\n",  "○ Treap - декартово дерево\n",
	};
	for (int i = 0; i < 6; ++i) {
		printf("%s", s[i]);
	}
}

void print_data_struct_for_queue() {
	char* s[] = {"○ HashSet - хеш-таблица с методом цепочек разрешения коллизий\n",
	             "○ DynamicArray - динамический массив (отсортированный по ключу) дихотомическим поиском\n",
	             "○ BinarySearchTree - двоичное дерево поиска\n", "○ Trie - бор\n"};
	for (int i = 0; i < 4; ++i) {
		printf("%s", s[i]);
	}
}

error_msg read_and_write_struct_data_for_application(String* tmp, char** MSG, int* count, FILE* f) {
	if (tmp == NULL || count == NULL || MSG == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "read_and_write_struct_data_for_queue", "get pointer to null"};
	}
	printf("%s\n", MSG[*count]);
	print_data_struct_for_application();
	int n = read_string(stdin, tmp);
	if (n == -1) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "read_string", "memory allocated"};
	} else if (n != 0) {
		strip(tmp);

		if (string_cmp(tmp->arr, "BinaryHeap") || string_cmp(tmp->arr, "BinomialHeap") ||
		    string_cmp(tmp->arr, "FibonacciHeap") || string_cmp(tmp->arr, "SkewHeap") ||
		    string_cmp(tmp->arr, "LeftistHeap") || string_cmp(tmp->arr, "Treap")) {
			*count += 1;
			fprintf(f, "%s\n", tmp->arr);
		} else {
			printf("\nIncorrect data\n\n");
		}
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg read_and_write_struct_data_for_queue(String* tmp, char** MSG, int* count, FILE* f) {
	if (tmp == NULL || count == NULL || MSG == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "read_and_write_struct_data_for_queue", "get pointer to null"};
	}
	printf("%s\n", MSG[*count]);
	print_data_struct_for_queue();
	int n = read_string(stdin, tmp);
	if (n == -1) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "read_string", "memory allocated"};
	} else if (n != 0) {
		strip(tmp);
		if (string_cmp(tmp->arr, "HashSet") || string_cmp(tmp->arr, "DynamicArray") ||
		    string_cmp(tmp->arr, "BinarySearchTree") || string_cmp(tmp->arr, "Trie")) {
			*count += 1;
			fprintf(f, "%s\n", tmp->arr);
		} else {
			printf("\nIncorrect data\n\n");
		}
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg read_time_in(String* tmp, char** MSG, int* count, FILE* f) {
	if (tmp == NULL || count == NULL || MSG == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "read_time_in", "get pointer to null"};
	}

	printf("%s", MSG[*count]);

	Time create;
	Time end;
	error_msg errorMsg = read_time(stdin, &create);
	if (errorMsg.type && errorMsg.type != INCORRECT_OPTIONS_ERROR) {
		return errorMsg;
	} else if (errorMsg.type == INCORRECT_OPTIONS_ERROR) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	}

	printf("%s", MSG[(*count) + 1]);
	errorMsg = read_time(stdin, &end);
	if (errorMsg.type && errorMsg.type != INCORRECT_OPTIONS_ERROR) {
		return errorMsg;
	} else if (errorMsg.type == INCORRECT_OPTIONS_ERROR) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	}

	if (compare_time(&create, &end) == 1) {
		printf("End time must be more than create time\n");
	} else {
		print_time(f, &create);
		putc('\n', f);
		print_time(f, &end);
		putc('\n', f);
		*count += 2;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg read_count_minutes(String* tmp, char** MSG, int* count, FILE* f) {
	if (tmp == NULL || count == NULL || MSG == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "read_count_minutes", "get pointer to null"};
	}

	size_t min_m = 0;
	size_t max_m = 0;

	printf("%s", MSG[*count]);
	int n = read_string(stdin, tmp);
	if (n == -1) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "read_count_minutes", "memory allocated"};
	}
	if (n == 0) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	}
	strip(tmp);

	error_msg errorMsg = string_to_u_long(tmp, &min_m);
	if (errorMsg.type == INCORRECT_OPTIONS_ERROR) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	} else if (errorMsg.type) {
		return errorMsg;
	}

	clear_string(tmp);

	printf("%s", MSG[(*count) + 1]);
	n = read_string(stdin, tmp);
	if (n == -1) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "read_count_minutes", "memory allocated"};
	}
	if (n == 0) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	}
	strip(tmp);

	errorMsg = string_to_u_long(tmp, &max_m);
	if (errorMsg.type == INCORRECT_OPTIONS_ERROR) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	} else if (errorMsg.type) {
		return errorMsg;
	}

	if (min_m > max_m || min_m == 0) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	}

	fprintf(f, "%zu\n", min_m);
	fprintf(f, "%zu\n", max_m);
	*count += 2;
	return (error_msg){SUCCESS, "", ""};
}

error_msg read_departments_and_operators(String* tmp, char** MSG, int* count, FILE* f) {
	if (tmp == NULL || count == NULL || MSG == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "read_count_minutes", "get pointer to null"};
	}

	size_t count_departments = 0;

	printf("%s", MSG[*count]);
	int n = read_string(stdin, tmp);
	if (n == -1) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "read_count_minutes", "memory allocated"};
	}
	if (n == 0) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	}
	strip(tmp);

	error_msg errorMsg = string_to_u_long(tmp, &count_departments);
	if (errorMsg.type == INCORRECT_OPTIONS_ERROR || count_departments == 0 || count_departments > 100) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	} else if (errorMsg.type) {
		return errorMsg;
	}

	clear_string(tmp);

	printf("%s", MSG[(*count) + 1]);
	size_t operators[count_departments];
	for (size_t i = 0; i < count_departments; ++i) {
		clear_string(tmp);
		n = read_string(stdin, tmp);
		if (n == -1) {
			return (error_msg){MEMORY_ALLOCATED_ERROR, "read_count_minutes", "memory allocated"};
		}
		if (n == 0) {
			printf("\nIncorrect data\n\n");
			return (error_msg){SUCCESS, "", ""};
		}
		strip(tmp);
		errorMsg = string_to_u_long(tmp, &(operators[i]));
		if (errorMsg.type == INCORRECT_OPTIONS_ERROR || operators[i] < 10 || operators[i] > 50) {
			printf("\nIncorrect data\n\n");
			return (error_msg){SUCCESS, "", ""};
		} else if (errorMsg.type) {
			return errorMsg;
		}
	}
	*count += 2;
	fprintf(f, "%zu\n", count_departments);
	for (size_t i = 0; i < count_departments; ++i) {
		fprintf(f, "%zu ", operators[i]);
	}
	putc('\n', f);
	return (error_msg){SUCCESS, "", ""};
}

error_msg read_overload_coefficient(String* tmp, char** MSG, int* count, FILE* f) {
	if (tmp == NULL || count == NULL || MSG == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "read_count_minutes", "get pointer to null"};
	}
	printf("%s", MSG[*count]);
	double coefficient;
	int n = read_string(stdin, tmp);
	if (n == -1) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "read_count_minutes", "memory allocated"};
	}
	if (n == 0) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	}
	strip(tmp);

	error_msg errorMsg = string_to_double(tmp, &coefficient);
	if (errorMsg.type == INCORRECT_OPTIONS_ERROR || errorMsg.type == OVERFLOW_ERROR || coefficient <= 1) {
		printf("\nIncorrect data\n\n");
		return (error_msg){SUCCESS, "", ""};
	} else if (errorMsg.type) {
		return errorMsg;
	} else {
		fprintf(f, "%f\n", coefficient);
	}

	*count += 1;

	return (error_msg){SUCCESS, "", ""};
}

int main() {
	char* MSG[] = {"Write filename: ",
	               "Write struct data for save applications: ",
	               "Write struct data for save queue: ",
	               "Write create time in ISO8601 format: ",
	               "Write end time in ISO8601 format: ",
	               "Write min minutes: ",
	               "Write max minutes: ",
	               "Write count departments: ",
	               "Write count operators for departments: ",
	               "Write overload coefficient: "};

	String tmp;
	error_msg errorMsg = create_string(&tmp, "");
	if (errorMsg.type) {
		return print_error(errorMsg);
	}
	int count = 0;
	FILE* f;
	int fl = 0;

	while (1) {
		clear_string(&tmp);
		switch (count) {
			case 0:
				errorMsg = read_filename(&tmp, MSG, &count, &f);
				if (errorMsg.type) {
					destroy_string(&tmp);
					return print_error(errorMsg);
				}
				break;
			case 1:
				errorMsg = read_and_write_struct_data_for_application(&tmp, MSG, &count, f);
				if (errorMsg.type) {
					fclose(f);
					destroy_string(&tmp);
					return print_error(errorMsg);
				}
				break;
			case 2:
				errorMsg = read_and_write_struct_data_for_queue(&tmp, MSG, &count, f);
				if (errorMsg.type) {
					fclose(f);
					destroy_string(&tmp);
					return print_error(errorMsg);
				}
				break;
			case 3:
				errorMsg = read_time_in(&tmp, MSG, &count, f);
				if (errorMsg.type) {
					fclose(f);
					destroy_string(&tmp);
					return print_error(errorMsg);
				}
				break;
			case 5:
				errorMsg = read_count_minutes(&tmp, MSG, &count, f);
				if (errorMsg.type) {
					fclose(f);
					destroy_string(&tmp);
					return print_error(errorMsg);
				}
				break;

			case 7:
				errorMsg = read_departments_and_operators(&tmp, MSG, &count, f);
				if (errorMsg.type) {
					fclose(f);
					destroy_string(&tmp);
					return print_error(errorMsg);
				}
				break;
			case 9:
				errorMsg = read_overload_coefficient(&tmp, MSG, &count, f);
				if (errorMsg.type) {
					fclose(f);
					destroy_string(&tmp);
					return print_error(errorMsg);
				}
				break;
			default:
				fl = 1;
		}
		if (fl) {
			break;
		}
	}
	fclose(f);
	destroy_string(&tmp);
	return 0;
}