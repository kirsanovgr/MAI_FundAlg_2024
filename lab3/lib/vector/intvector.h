#ifndef LAB1_VECTOR_INTVECTOR_H
#define LAB1_VECTOR_INTVECTOR_H

#include "../SystemErrors/errors.h"

typedef struct IntVector {
	int capacity;
	int size;
	int* arr;
} IntVector;

IntVector * create_int_vector(int capacity);
error_msg push_end_intvector(IntVector* vector, int new_element);
error_msg get_intvector(IntVector* vector, int index, int* value);
void destroy_int_vector(IntVector* vector);
error_msg at_intvector(IntVector* vector, int index, int new_element);
int size_intvector(IntVector* vector);
void print_intvector(FILE * stream, IntVector* vector, char * separator);

#endif