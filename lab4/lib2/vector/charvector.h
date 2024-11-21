#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>

#include "../SystemErrors2/errors.h"
#include "../mstring/mstring.h"

typedef struct String {
	int capacity;
	int size;
	char* arr;
} String;

error_msg create_string(String* vec, char* src);
error_msg push_end_string(String* vector, char new_element);
int find_index_string(String* s, char c);
error_msg get_string(String* vector, int index, char* value);
error_msg mstrcopy(const String* dest, String* result, int start, int end);
int strings_equals(const String* s1, const String* s2);
void destroy_string(String* vector);
error_msg at_string(String* vector, int index, char new_element);
int size_string(String* vector);
void print_string(FILE* stream, String* vector, char* separator);
void vector_string(String* vector);
error_msg resize_string(String* vector, int new_capacity);
error_msg mstrcopynew(const String* dest, String* result);
error_msg mstrcat(String* first, const String* second);
int string_comp(const String* s1, const String* s2);
error_msg string_to_int(String* dst, int* res);
void string_to_upper(String* string);
int find_index_string_with_start_index(String* s, char c, int start_index);
void strip(String* string);


int read_string_before_separator(FILE* stream, String* string, char separator);
int read_string(FILE* stream, String* string);
int read_line(FILE* stream, String* string);

void clear_string(String* string);

#endif