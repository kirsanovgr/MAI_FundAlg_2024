#ifndef LAB2_STRINGVECTOR_H
#define LAB2_STRINGVECTOR_H

#include <stdlib.h>

#include "../SystemErrors/errors.h"

typedef struct StringVector {
	char **data;
	int size;
	int capacity;
} StringVector;


// Функции применяемые ко всем строкам
error_msg strcopy(const char *a, char *result, int start, int end);
int string_cmp(const char *a, const char *b);
error_msg str_to_k(const char **string, char *separator, char * result);
int SizeString(const char *a);
error_msg my_strcat(char *a, const char *b);

StringVector *create_string_vector(int size);
error_msg resize_string_vector(StringVector *vec);
error_msg push_end_string_vector(StringVector *vec, char *string);
error_msg at_string_vector(StringVector *vec, int index, char *res);
error_msg get_string_vector(StringVector *vec, int index, char **res);
void print_string_vector(FILE * stream, StringVector *vec, char *separator);
void destroy_string_vector(StringVector *vec);

#endif
