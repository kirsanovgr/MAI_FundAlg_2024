#ifndef LAB1_VECTOR_INTVECTOR_H
#define LAB1_VECTOR_INTVECTOR_H

#include "../SystemErrors/errors.h"

typedef struct IntVector {
	int capacity;
	int size;
	int* arr;
} IntVector;

error_msg create_int_vector(IntVector** vector, int capacity);
error_msg push_end_intvector(IntVector* vector, int new_element);
error_msg get_intvector(IntVector* vector, int index, int* value);
error_msg remove_int_vector(IntVector* vector, int index);
int find_max(IntVector * vector);
int find_min(IntVector* vector);
int find_most_frequent_value(IntVector * vector);
double find_average_value(IntVector * vector);
void destroy_int_vector(IntVector* vector);
error_msg at_intvector(IntVector* vector, int index, int new_element);
int size_intvector(IntVector* vector);
void print_intvector(FILE* stream, IntVector* vector, char* separator);

#endif