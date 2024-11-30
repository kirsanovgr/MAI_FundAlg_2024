#pragma once

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char *data;     // Указатель на массив символов
    int length;     // Длина строки
} String;

// Функции для работы с строками
int string_length(const char *str);
void string_copy(char *dest, const char *src);
int string_compare(const char *str1, const char *str2);
void string_concat(char *dest, const char *src);

int String_create(String *str, const char *initial);
void String_destroy(String *str);
int String_compare(const String *str1, const String *str2);
int String_equals(const String *str1, const String *str2);
int String_copy(String *dest, const String *src);
int String_copy_new(String **dest, const String *src);
void String_concat(String *str1, const String *str2);

typedef enum Errors {
    STRING_SUCCESS = 0,
    STRING_ALLOCATION_ERROR = -1
} Errors;