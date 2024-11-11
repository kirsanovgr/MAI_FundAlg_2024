#include "intvector.h"

#include <stdio.h>
#include <stdlib.h>

IntVector* create_int_vector(int capacity) {
	IntVector* vector = (IntVector*)malloc(sizeof(IntVector));
	if (!vector) {
		return NULL;
	}
	vector->arr = (int*)malloc(sizeof(int) * capacity);
	if (!(vector->arr)) {
		return NULL;
	}
	vector->size = 0;
	vector->capacity = capacity;
	return vector;
}

int resize_int_vector(IntVector* vector, int new_capacity) {
	vector->arr = (int*)realloc(vector->arr, sizeof(int) * new_capacity);
	if (!(vector->arr)) {
		return MEMORY_ALLOCATED_ERROR;
	}
	vector->capacity = new_capacity;
	return SUCCESS;
}

error_msg push_end_intvector(IntVector* vector, int new_element) {
	if (vector->size == vector->capacity) {
		error_msg error = resize_int_vector(vector, vector->capacity * 2);
		if (error) return error;
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
	return SUCCESS;
}

error_msg get_intvector(IntVector* vector, int index, int* value) {
	if (index >= vector->size) {
		return INDEX_VECTOR_ERROR;
	}
	*value = vector->arr[index];
	return SUCCESS;
}

error_msg at_intvector(IntVector* vector, int index, int new_element) {
	if (index >= vector->size) {
		return INDEX_VECTOR_ERROR;
	}
	vector->arr[index] = new_element;
	return SUCCESS;
}

int size_intvector(IntVector* vector) { return vector->size; }

void destroy_int_vector(IntVector* vector) {
	free(vector->arr);
	free(vector);
}

void print_intvector(FILE * stream, IntVector* vector, char * separator) {
	for (int i = 0; i < vector->size; ++i) {
		fprintf(stream, "%d%s", vector->arr[i], separator);
	}
}
