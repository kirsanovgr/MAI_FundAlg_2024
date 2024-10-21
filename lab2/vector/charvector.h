#ifndef LAB1_VECTOR_CHARVECTOR_H
#define LAB1_VECTOR_CHARVECTOR_H

#include "../SystemErrors/errors.h"

typedef struct CharVector {
	int capacity;
	int size;
	char* arr;
} CharVector;

CharVector* create_char_vector(int size);
error_msg push_end_charvector(CharVector* vector, char new_element);
error_msg get_charvector(CharVector* vector, int index, char* value);
void destroy_char_vector(CharVector* vector);
error_msg at_charvector(CharVector* vector, int index, char new_element);
int size_charvector(CharVector* vector);
void print_charvector(FILE* stream, CharVector* vector, char* separator);
void vector_char_clear(CharVector* vector);

#endif