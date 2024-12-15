#pragma once

#include "../lib2/SystemErrors2/errors.h"
#include "../lib2/vector/charvector.h"

typedef struct MemoryCell {
	String name;
	int value;
} MemoryCell;

typedef struct {
	int size;
	int capacity;
	MemoryCell** data;
} ArrayOfMemoryCell;

typedef struct Operation {
	/*
	 * + 0
	 * - 1
	 * * 2
	 * / 3
	 * % 4
	 */
	int operation;
	int index;
} Operation;

// Взаимодействие с ячейками
error_msg create_memory_cell(MemoryCell** memoryCell, String* name, int value);
void destroy_memory_cell(MemoryCell* memoryCell);

// Компоратор для сортировки
int compare_greater_memory_cell(const void* a, const void* b);

// Взаимодействие с массивом
error_msg create_array_memory_cells(ArrayOfMemoryCell* array);
error_msg resize_array_memory_cells(ArrayOfMemoryCell* arrayOfMemoryCell);
void destroy_array_memory_cells(ArrayOfMemoryCell* arrayOfMemoryCell);
error_msg push_end_array_memory_cells(ArrayOfMemoryCell* arrayOfMemoryCell, MemoryCell* memoryCell);
void print_array_memory_cells(FILE* stream, ArrayOfMemoryCell arrayOfMemoryCell);
MemoryCell* find_memory_cell(ArrayOfMemoryCell* arrayOfMemoryCell, String* name);
error_msg get_memory_cell(ArrayOfMemoryCell* arrayOfMemoryCell, String* name, MemoryCell** memoryCell);

// Работа с инструкциями
error_msg processing_file(FILE* stream, ArrayOfMemoryCell* arrayOfMemoryCell);
error_msg read_instruction(FILE* stream, String* instruction);
Operation what_operation(String* instruction);

// Операции

error_msg equate(ArrayOfMemoryCell* arrayOfMemoryCell, String* instruction, MemoryCell* memoryCell, int index_eq);

