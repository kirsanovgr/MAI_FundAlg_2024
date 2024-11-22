#include "ex7.h"

int is_figures(const String* s) {
	for (int i = 0; i < s->size; ++i) {
		if ((s->arr[i] < '0' || s->arr[i] > '9')) return 0;
	}
	return 1;
}

int is_correct_variable(const String* s) {
	for (int i = 0; i < s->size; ++i) {
		if ((s->arr[i] < 'a' || s->arr[i] > 'z') && (s->arr[i] < 'A' || s->arr[i] > 'Z')) {
			return 0;
		}
	}
	return 1;
}

error_msg create_memory_cell(MemoryCell** memoryCell, String* name, int value) {
	*memoryCell = (MemoryCell*)malloc(sizeof(MemoryCell));
	if (!*memoryCell) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_memory_cell", "memory allocated"};
	}
	error_msg errorMsg = mstrcopynew(name, &((*memoryCell)->name));
	if (errorMsg.type) {
		return errorMsg;
	}
	(*memoryCell)->value = value;
	return (error_msg){SUCCESS, "", ""};
}

void destroy_memory_cell(MemoryCell* memoryCell) {
	destroy_string(&memoryCell->name);
	memoryCell->value = 0;
	free(memoryCell);
}

error_msg create_array_memory_cells(ArrayOfMemoryCell* array) {
	array->size = 0;
	array->capacity = 10;
	array->data = (MemoryCell**)calloc(sizeof(MemoryCell*), array->capacity);
	if (!(array->data)) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_array_memory_cells", "memory allocated"};
	}
	return (error_msg){SUCCESS, "", ""};
}

void destroy_array_memory_cells(ArrayOfMemoryCell* arrayOfMemoryCell) {
	for (int i = 0; i < arrayOfMemoryCell->size; ++i) {
		destroy_memory_cell(arrayOfMemoryCell->data[i]);
	}
	arrayOfMemoryCell->size = 0;
	arrayOfMemoryCell->capacity = 0;
	free(arrayOfMemoryCell->data);
}

error_msg resize_array_memory_cells(ArrayOfMemoryCell* arrayOfMemoryCell) {
	MemoryCell** tmp;
	tmp = (MemoryCell**)realloc(arrayOfMemoryCell->data, arrayOfMemoryCell->capacity * 2);
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "resize_array_memory_cells", "memory allocated"};
	}
	arrayOfMemoryCell->data = tmp;
	arrayOfMemoryCell->capacity *= 2;

	return (error_msg){SUCCESS, "", ""};
}

error_msg push_end_array_memory_cells(ArrayOfMemoryCell* arrayOfMemoryCell, MemoryCell* memoryCell) {
	error_msg errorMsg;
	if (arrayOfMemoryCell->capacity == arrayOfMemoryCell->size) {
		errorMsg = resize_array_memory_cells(arrayOfMemoryCell);
		if (errorMsg.type) {
			return errorMsg;
		}
	}
	arrayOfMemoryCell->data[arrayOfMemoryCell->size] = memoryCell;
	arrayOfMemoryCell->size += 1;
	qsort(arrayOfMemoryCell->data, arrayOfMemoryCell->size, sizeof(MemoryCell*), compare_greater_memory_cell);

	return (error_msg){SUCCESS, "", ""};
}

int compare_greater_memory_cell(const void* a, const void* b) {
	MemoryCell* first = *((MemoryCell**)a);
	MemoryCell* second = *((MemoryCell**)b);
	return string_comp(&(first->name), &(second->name));
}

void print_array_memory_cells(FILE* stream, ArrayOfMemoryCell arrayOfMemoryCell) {
	for (int i = 0; i < arrayOfMemoryCell.size; ++i) {
		fprintf(stream, "%s: %d\n", arrayOfMemoryCell.data[i]->name.arr, arrayOfMemoryCell.data[i]->value);
	}
}

Operation what_operation(String* instruction) {
	int index = find_index_string(instruction, '+');
	if (index != -1) {
		return (Operation){0, index};
	}
	index = find_index_string(instruction, '-');
	if (index != -1) {
		return (Operation){1, index};
	}
	index = find_index_string(instruction, '*');
	if (index != -1) {
		return (Operation){2, index};
	}
	index = find_index_string(instruction, '/');
	if (index != -1) {
		return (Operation){3, index};
	}

	index = find_index_string(instruction, '%');
	if (index != -1) {
		return (Operation){4, index};
	}
	return (Operation){-1, -1};
}

MemoryCell* find_memory_cell(ArrayOfMemoryCell* arrayOfMemoryCell, String* name) {
	int left = 0;
	int right = arrayOfMemoryCell->size;
	int c = (left + right) / 2;
	int k;
	int i = 0;
	if (right == 0) {
		return NULL;
	}
	while ((k = string_comp(name, &(arrayOfMemoryCell->data[c]->name))) != 0) {
		if (i >= arrayOfMemoryCell->size) {
			return NULL;
		}
		if (k < 0) {
			right = c;
			i += (right - c + 1);
		} else if (k > 0) {
			left = c;
			i += (c - left + 1);
		}
		c = (left + right) / 2;
	}
	return arrayOfMemoryCell->data[c];
}

error_msg read_instruction(FILE* stream, String* instruction) {
	if (!stream) {
		return (error_msg){INPUT_FILE_ERROR, "read_instruction", "input file didn't open"};
	}

	clear_string(instruction);
	char c = getc(stream);
	while (!feof(stream) && (c == ' ' || c == '\n' || c == '\t')) c = getc(stream);
	while (!feof(stream)) {
		if (c == ';') {
			strip(instruction);
			return (error_msg){SUCCESS, "", ""};
		} else {
			error_msg errorMsg = push_end_string(instruction, c);
			if (errorMsg.type) {
				return errorMsg;
			}
		}
		c = getc(stream);
	}
	strip(instruction);
	if (instruction->size > 0) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, "read_instruction", "incorrect data"};
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg get_memory_cell(ArrayOfMemoryCell* arrayOfMemoryCell, String* name, MemoryCell** memoryCell) {
	MemoryCell* tmp = find_memory_cell(arrayOfMemoryCell, name);
	if (tmp) {
		*memoryCell = tmp;
		return (error_msg){SUCCESS, "", ""};
	}
	error_msg errorMsg = create_memory_cell(memoryCell, name, 0);
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = push_end_array_memory_cells(arrayOfMemoryCell, *memoryCell);
	if (errorMsg.type) {
		return errorMsg;
	}

	return (error_msg){SUCCESS, "", ""};
}

error_msg print_instruction(ArrayOfMemoryCell* arrayOfMemoryCell, String* instruction, String* lhs) {
	if (string_cmp(lhs->arr, "print")) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, "print_instruction", "incorrect command"};
	}
	error_msg errorMsg;
	int index_space = find_index_string(instruction, ' ');
	if (index_space == -1) {
		print_array_memory_cells(stdout, *arrayOfMemoryCell);
	} else {
		String rhs;
		errorMsg = create_string(&rhs, "");
		if (errorMsg.type) {
			return errorMsg;
		}
		errorMsg = mstrcopy(instruction, &rhs, index_space + 1, instruction->size);
		if (errorMsg.type) {
			destroy_string(&rhs);
			return errorMsg;
		}
		strip(&rhs);
		if (!is_correct_variable(&rhs)) {
			destroy_string(&rhs);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "print_instruction", "incorrect name of variable"};
		}
		MemoryCell* find;
		find = find_memory_cell(arrayOfMemoryCell, &rhs);
		if (!find) {
			destroy_string(&rhs);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "print_instruction", "This variable doesn't exist"};
		}
		printf("%s %d\n", find->name.arr, find->value);

		destroy_string(&rhs);
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg equate(ArrayOfMemoryCell* arrayOfMemoryCell, String* instruction, MemoryCell* memoryCell, int index_eq) {
	String rhs;
	error_msg errorMsg = create_string(&rhs, "");
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &rhs, index_eq + 1, instruction->size);
	if (errorMsg.type) {
		destroy_string(&rhs);
		return errorMsg;
	}
	strip(&rhs);
	int data = 0;
	errorMsg = string_to_int(&rhs, &data);
	if (errorMsg.type == INCORRECT_OPTIONS_ERROR) {
		if (!is_correct_variable(&rhs)) {
			destroy_string(&rhs);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "equate", "incorrect name of variable"};
		}
		MemoryCell* rhs_cell = find_memory_cell(arrayOfMemoryCell, &rhs);
		if (!rhs_cell) {
			destroy_string(&rhs);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "equate", "This variable doesn't exist"};
		}
		data = rhs_cell->value;
	} else if (errorMsg.type) {
		destroy_string(&rhs);
		return errorMsg;
	}
	memoryCell->value = data;

	destroy_string(&rhs);
	return (error_msg){SUCCESS, "", ""};
}

int add(int a, int b) { return a + b; }

int multiple(int a, int b) { return a * b; }

int sub(int a, int b) { return a - b; }

int divide(int a, int b) { return a / b; }

int remain(int a, int b) { return a % b; }

error_msg counting(ArrayOfMemoryCell* arrayOfMemoryCell, String* instruction, MemoryCell* memoryCell, int index_eq,
                   Operation operation) {
	int (*operations[5])(int a, int b) = {add, sub, multiple, divide, remain};

	error_msg errorMsg;
	String rhs_first;
	String rhs_second;
	errorMsg = create_string(&rhs_first, "");
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = create_string(&rhs_second, "");
	if (errorMsg.type) {
		destroy_string(&rhs_second);
		return errorMsg;
	}

	errorMsg = mstrcopy(instruction, &rhs_first, index_eq + 1, operation.index);
	if (errorMsg.type) {
		destroy_string(&rhs_first);
		destroy_string(&rhs_second);
		return errorMsg;
	}

	errorMsg = mstrcopy(instruction, &rhs_second, operation.index + 1, instruction->size);
	if (errorMsg.type) {
		destroy_string(&rhs_first);
		destroy_string(&rhs_second);
		return errorMsg;
	}
	strip(&rhs_first);
	strip(&rhs_second);

	// Получаем первое и второй значение
	int data_first = 0;
	int data_second = 0;
	errorMsg = string_to_int(&rhs_first, &data_first);
	if (errorMsg.type == INCORRECT_OPTIONS_ERROR) {
		if (!is_correct_variable(&rhs_first)) {
			destroy_string(&rhs_first);
			destroy_string(&rhs_second);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "equate", "incorrect name of variable"};
		}
		MemoryCell* rhs_cell = find_memory_cell(arrayOfMemoryCell, &rhs_first);
		if (!rhs_cell) {
			destroy_string(&rhs_first);
			destroy_string(&rhs_second);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "counting", "This variable doesn't exist"};
		}
		data_first = rhs_cell->value;
	} else if (errorMsg.type) {
		destroy_string(&rhs_first);
		destroy_string(&rhs_second);
		return errorMsg;
	}
	errorMsg = string_to_int(&rhs_second, &data_second);

	if (errorMsg.type == INCORRECT_OPTIONS_ERROR) {
		if (!is_correct_variable(&rhs_second)) {
			destroy_string(&rhs_first);
			destroy_string(&rhs_second);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "equate", "incorrect name of variable"};
		}
		MemoryCell* rhs_cell = find_memory_cell(arrayOfMemoryCell, &rhs_second);
		if (!rhs_cell) {
			destroy_string(&rhs_first);
			destroy_string(&rhs_second);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "counting", "This variable doesn't exist"};
		}
		data_second = rhs_cell->value;
	} else if (errorMsg.type) {
		destroy_string(&rhs_first);
		destroy_string(&rhs_second);
		return errorMsg;
	}

	memoryCell->value = operations[operation.operation](data_first, data_second);

	destroy_string(&rhs_first);
	destroy_string(&rhs_second);
	return (error_msg){SUCCESS, "", ""};
}

error_msg execution_instruction(ArrayOfMemoryCell* arrayOfMemoryCell, String* instruction) {
	if (instruction->size == 0) {
		return (error_msg){SUCCESS, "", ""};
	}
	// Выделяем левую часть выражения
	String lhs;
	error_msg errorMsg = create_string(&lhs, "");
	if (errorMsg.type) {
		return errorMsg;
	}

	int index_eq = find_index_string(instruction, '=');
	// Обработка принта
	if (index_eq == -1) {
		errorMsg = print_instruction(arrayOfMemoryCell, instruction, &lhs);
		destroy_string(&lhs);
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &lhs, 0, index_eq);
	if (errorMsg.type) {
		destroy_string(&lhs);
		return errorMsg;
	}
	strip(&lhs);
	if (!is_correct_variable(&lhs)) {
		destroy_string(&lhs);
		return (error_msg){INCORRECT_OPTIONS_ERROR, "execution_instruction", "incorrect name of variable"};
	}

	MemoryCell* lhs_cell;
	errorMsg = get_memory_cell(arrayOfMemoryCell, &lhs, &lhs_cell);
	if (errorMsg.type) {
		destroy_string(&lhs);
		return errorMsg;
	}


	Operation operation = what_operation(instruction);
	if (operation.operation == -1) {
		errorMsg = equate(arrayOfMemoryCell, instruction, lhs_cell, index_eq);
		if (errorMsg.type) {
			destroy_string(&lhs);
			return errorMsg;
		}
	} else {
		errorMsg = counting(arrayOfMemoryCell, instruction, lhs_cell, index_eq, operation);
		if (errorMsg.type) {
			destroy_string(&lhs);
			return errorMsg;
		}
	}

	destroy_string(&lhs);
	return (error_msg){SUCCESS, "", ""};
}

error_msg processing_file(FILE* stream, ArrayOfMemoryCell* arrayOfMemoryCell) {
	error_msg errorMsg;
	String instruction;
	errorMsg = create_string(&instruction, "");
	if (errorMsg.type) {
		return errorMsg;
	}
	while (!feof(stream)) {
		errorMsg = read_instruction(stream, &instruction);
		if (errorMsg.type) {
			destroy_string(&instruction);
			return errorMsg;
		}
		errorMsg = execution_instruction(arrayOfMemoryCell, &instruction);
		if (errorMsg.type) {
			destroy_string(&instruction);
			return errorMsg;
		}
	}
	destroy_string(&instruction);
	return (error_msg){SUCCESS, "", ""};
}