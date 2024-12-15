
#ifndef LAB4_VECTOR_H
#define LAB4_VECTOR_H

#include <stdlib.h>

#include "../SystemErrors2/errors.h"

#define VECTOR(type, st_type)       \
	struct vector_##type {          \
		st_type *data;              \
		size_t capacity, size;      \
		void (*deleter)(st_type *); \
	};

#define VECTOR_CREATE(type, st_type)                                                                             \
	error_msg vector_##type##_create(struct vector_##type *vec, size_t capacity, void (*deleter)(st_type *)) {   \
		vec->data = (st_type *)calloc(capacity, sizeof(st_type));                                                \
		if (!vec->data) {                                                                                        \
			return (error_msg){MEMORY_ALLOCATED_ERROR, "macros create vector ##type", "memory allocated error"}; \
		}                                                                                                        \
		vec->capacity = capacity;                                                                                \
		vec->size = 0;                                                                                           \
		vec->deleter = deleter;                                                                                  \
		return (error_msg){SUCCESS, "", ""};                                                                     \
	}

#define VECTOR_DELETE(type)                                  \
	void vector_##type##_delete(struct vector_##type *vec) { \
		if (vec->data) {                                     \
			vec->deleter(vec->data);                         \
			vec->data = NULL;                                \
			vec->size = 0;                                   \
			vec->capacity = 0;                               \
		}                                                    \
	}

#define VECTOR_RESIZE(type, st_type)                                                                              \
	error_msg vector_##type##_resize(struct vector_##type *vec, size_t new_capacity) {                            \
		if (new_capacity > vec->capacity) {                                                                       \
			st_type *new_data = (st_type *)realloc(vec->data, new_capacity * sizeof(st_type));                    \
			if (new_data) {                                                                                       \
				vec->data = new_data;                                                                             \
				vec->capacity = new_capacity;                                                                     \
			} else {                                                                                              \
				return (error_msg){MEMORY_ALLOCATED_ERROR, "macros resize vector ##r", "memory allocated error"}; \
			}                                                                                                     \
		}                                                                                                         \
		return (error_msg){SUCCESS, "", ""};                                                                      \
	}

#define VECTOR_PUSH_BACK(types, st_type)                                              \
	error_msg vector_##types##_push_back(struct vector_##types *vec, st_type value) { \
		if (vec->size >= vec->capacity) {                                             \
			size_t new_capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;         \
			error_msg errorMsg = vector_##types##_resize(vec, new_capacity);          \
			if (errorMsg.type) {                                                      \
				return errorMsg;                                                      \
			}                                                                         \
		}                                                                             \
		vec->data[vec->size++] = value;                                               \
		return (error_msg){SUCCESS, "", ""};                                          \
	}

#endif  // LAB4_VECTOR_H
