#include "stringvector.h"

#include <stdlib.h>
#include <string.h>

error_msg str_to_k(const char **string, char *separator, char *result) {
	error_msg error;
	int len_string = SizeString(*string);
	int len_separator = SizeString(separator);
	char b[len_separator + 1];
	if (len_string == 0) {
		result = NULL;
		return NORMAL;
	}
	for (int i = 0; i < len_string; ++i) {
		//        printf("%s\n", *string);
		error = strcopy(*string, b, 0, len_separator);
		if (error) return error;
		if (string_cmp(b, separator)) {
			result[i] = '\0';
			*string += len_separator;
			break;
		}
		if (len_separator == SizeString(*string)) {
			result[i] = '\0';
			error = my_strcat(result, *string);
			if (error) return error;
			*string = "\0";
			break;
		}
		result[i] = **string;
		*string += 1;
	}
	return NORMAL;
}

error_msg my_strcat(char *a, const char *b) {
	int i = SizeString(a);
	for (int j = 0; j < SizeString(b); ++i, ++j) {
		a[i] = b[j];
	}
	a[i] = '\0';
	return NORMAL;
}

int string_cmp(const char *a, const char *b) {
	int i;
	for (i = 0; a[i] != '\0' && b[i] != '\0'; ++i) {
		if (a[i] != b[i]) return 0;
	}
	if (a[i] != b[i]) return 0;
	return 1;
}

error_msg strcopy(const char *a, char *result, int start, int end) {
	int i = 0;
	int end_for = end - start;
	if (start > 0) end_for++;
	for (; i < end_for; ++i) {
		result[i] = a[i + start];
	}
	result[i] = '\0';
	return NORMAL;
}

int SizeString(const char *a) {
	int i = 0;
	for (; a[i] != '\0'; ++i)
		;
	return i;
}

StringVector *create_string_vector(int size) {
	StringVector *vec = (StringVector *)malloc(sizeof(StringVector));
	if (!vec) return NULL;
	vec->data = (char **)malloc(size * sizeof(char *));
	if (!vec->data) {
		free(vec);
		return NULL;
	}
	vec->capacity = size;
	vec->size = 0;
	return vec;
}

error_msg resize_string_vector(StringVector *vec) {
	char **new_data = (char **)realloc(vec->data, vec->capacity * 2 * sizeof(char *));
	if (!new_data) {
		return MEMORY_ALLOCATED_ERROR;
	}
	vec->data = new_data;
	vec->capacity *= 2;
	return NORMAL;
}

error_msg push_end_string_vector(StringVector *vec, char *string) {
	error_msg error;
	if (vec->size == vec->capacity) {
		error = resize_string_vector(vec);
		if (error) return error;
	}
	vec->data[vec->size] = (char *)malloc((SizeString(string) + 1) * sizeof(char));
	if (!(vec->data[vec->size])) {
		destroy_string_vector(vec);
		return MEMORY_ALLOCATED_ERROR;
	}
	strcopy(string, vec->data[vec->size], 0, SizeString(string));
	vec->size += 1;
	//	print_string_vector(vec);
	return NORMAL;
}

error_msg at_string_vector(StringVector *vec, int index, char *res) {
	if (index >= vec->size) {
		return INDEX_VECTOR_ERROR;
	}
	free(vec->data[index]);
	vec->data[index] = (char *)malloc((SizeString(res) + 1) * sizeof(char));
	if (!vec->data[index]) {
		destroy_string_vector(vec);
		return MEMORY_ALLOCATED_ERROR;
	}
	strcopy(res, vec->data[index], 0, SizeString(res));
	return NORMAL;
}

error_msg get_string_vector(StringVector *vec, int index, char **res) {
	if (index >= vec->size) {
		return INDEX_VECTOR_ERROR;
	}
	*res = vec->data[index];
	return NORMAL;
}

void print_string_vector(FILE * stream, StringVector *vec, char *separator) {
	for (int i = 0; i < vec->size; ++i) {
		fprintf(stream, "%s%s", (vec->data)[i], separator);
	}
}

void destroy_string_vector(StringVector *vec) {
	if (!vec) return;
	if (vec->data) {
		for (int i = 0; i < vec->size; i++) {
			if (vec->data[i]) {
				free(vec->data[i]);
			}
		}
		free(vec->data);
	}
	free(vec);
}