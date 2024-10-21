#include "charvector.h"

#include <stdio.h>
#include <stdlib.h>

CharVector* create_char_vector(int capacity) {
	CharVector *vector = (CharVector*)malloc(sizeof(CharVector));
	if(!vector){
		return NULL;
	}
	vector->arr = (char*)malloc(sizeof(char) * capacity);
	if (!vector->arr) {
		printf("Ошибка выделения памяти\n");
		return NULL;
	}
	vector->size = 0;
	vector->capacity = capacity;
	return vector;
}

error_msg resize_char_vector(CharVector* vector, int new_capacity) {
	vector->arr = (char*)realloc(vector->arr, sizeof(char) * new_capacity);
	if (!vector->arr) {
		return MEMORY_ALLOCATED_ERROR;
	}
	vector->capacity = new_capacity;
	return NORMAL;
}

error_msg push_end_charvector(CharVector* vector, char new_element) {
	if (vector->size == vector->capacity) {
		error_msg error = resize_char_vector(vector, vector->size * 2);
		if (error) return error;
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
	return NORMAL;
}

error_msg get_charvector(CharVector* vector, int index, char * value) {
	if (index >= vector->capacity) {
		return INDEX_VECTOR_ERROR;
	}
	*value = vector->arr[index];
	return NORMAL;
}

error_msg at_charvector(CharVector* vector, int index, char new_element) {
	if (index >= vector->capacity) {
		return INDEX_VECTOR_ERROR;
	}
	vector->arr[index] = new_element;
	return NORMAL;
}

int size_charvector(CharVector* vector) { return vector->size; }

void destroy_char_vector(CharVector* vector) {
	free(vector->arr);
	free(vector);
}

void print_charvector(FILE * stream, CharVector* vector, char * separator) {
	for (int i = 0; i < vector->size; ++i) {
		fprintf(stream, "%c%s", vector->arr[i], separator);
	}
}


void vector_char_clear(CharVector * vector){
	vector->size = 0;
}