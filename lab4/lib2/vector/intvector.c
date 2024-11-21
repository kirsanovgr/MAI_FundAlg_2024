#include "intvector.h"

#include <stdio.h>
#include <stdlib.h>

error_msg create_int_vector(IntVector** vector, int capacity) {
	*vector = (IntVector*)malloc(sizeof(IntVector));
	if (!*vector) {
		return (error_msg ){MEMORY_ALLOCATED_ERROR, "create_int_vector", "memory allocated error"};
	}
	(*vector)->arr = (int*)malloc(sizeof(int) * capacity);
	if (!((*vector)->arr)) {
		return (error_msg ){MEMORY_ALLOCATED_ERROR, "create_int_vector", "memory allocated error"};
	}
	(*vector)->size = 0;
	(*vector)->capacity = capacity;
	return (error_msg ){SUCCESS, "", ""};
}

error_msg resize_int_vector(IntVector* vector, int new_capacity) {
	int* tmp = (int*)realloc(vector->arr, sizeof(int) * new_capacity);
	if (!tmp) {
		return (error_msg ){MEMORY_ALLOCATED_ERROR, "resize_int_vector", "memory allocated error"};
	}
	vector->arr = tmp;
	vector->capacity = new_capacity;
	return (error_msg){SUCCESS, "", ""};
}

error_msg push_end_intvector(IntVector* vector, int new_element) {
	if (vector->size == vector->capacity) {
		error_msg error = resize_int_vector(vector, vector->capacity * 2);
		if (error.type) return error;
	}
	vector->size += 1;
	vector->arr[vector->size - 1] = new_element;
	return (error_msg ){SUCCESS, "", ""};
}

error_msg get_intvector(IntVector* vector, int index, int* value) {
	if (index >= vector->size) {
		return (error_msg ){INDEX_VECTOR_ERROR, "get_int_vector", "incorrect index"};
	}
	*value = vector->arr[index];
	return (error_msg ){SUCCESS, "", ""};
}

error_msg at_intvector(IntVector* vector, int index, int new_element) {
	if (index >= vector->size) {
		return (error_msg ){INDEX_VECTOR_ERROR, "at_int_vector", "incorrect index"};
	}
	vector->arr[index] = new_element;
	return (error_msg ){SUCCESS, "", ""};
}

int size_intvector(IntVector* vector) { return vector->size; }

void destroy_int_vector(IntVector* vector) {
	free(vector->arr);
	free(vector);
}

void print_intvector(FILE* stream, IntVector* vector, char* separator) {
	for (int i = 0; i < vector->size; ++i) {
		if (i != vector->size - 1) {
			fprintf(stream, "%d%s", vector->arr[i], separator);
		} else {
			fprintf(stream, "%d", vector->arr[i]);
		}
	}
}

error_msg remove_int_vector(IntVector* vector, int index) {
	if (index >= vector->size || index < 0) {
		return (error_msg ){INDEX_VECTOR_ERROR, "remove_int_vector", "incorrect index"};
	}
	for (int i = index; i < vector->size - 1; ++i) {
		vector->arr[i] = vector->arr[i + 1];
	}
	vector->size -= 1;
	return (error_msg ){SUCCESS, "", ""};
}

int find_max(IntVector* vector) {
	if (vector->size == 0) {
		return -1;
	}
	int maxc = vector->arr[0];
	int index_max = 0;
	for (int i = 1; i < vector->size; ++i) {
		if (vector->arr[i] > maxc) {
			maxc = vector->arr[i];
			index_max = i;
		}
	}
	return index_max;
}

int find_min(IntVector* vector) {
	if (vector->size == 0) {
		return -1;
	}
	int minc = vector->arr[0];
	int index_min = 0;
	for (int i = 1; i < vector->size; ++i) {
		if (vector->arr[i] < minc) {
			minc = vector->arr[i];
			index_min = i;
		}
	}
	return index_min;
}

int find_most_frequent_value(IntVector * vector){
	if(vector->size == 0){
		return -1;
	}
	int max_count = 0;
	int count;
	int index_max_count =0;
	for(int i = 0; i < vector->size; ++i){
		count = 0;
		for(int j = 0; j < vector->size; ++j){
			if(vector->arr[i] == vector->arr[j]){
				count++;
			}
		}
		if(count >= max_count){
			max_count = count;
			index_max_count = i;
		}
	}
	return index_max_count;
}

double find_average_value(IntVector * vector){
	if(vector->size == 0){
		return 0;
	}
	double average = 0;
	for(int i = 0; i < vector->size; ++i){
		average += vector->arr[i];
	}
	return average / vector->size;
}