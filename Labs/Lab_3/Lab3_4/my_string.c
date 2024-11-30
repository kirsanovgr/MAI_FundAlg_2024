#include "my_string.h"

// Функция для вычисления длины строки
int string_length(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Функция для копирования строки
void string_copy(char *dest, const char *src) {
    while ((*dest++ = *src++) != '\0');
}

// Функция для сравнения двух строк
int string_compare(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Функция для объединения двух строк
void string_concat(char *dest, const char *src) {
    while (*dest) {
        dest++;
    }
    while ((*dest++ = *src++) != '\0');
}

// Функция для создания строки
int String_create(String *str, const char *initial) {
    if (!str || !initial) {
        return STRING_ALLOCATION_ERROR;
    }
    str->length = string_length(initial);
    str->data = (char *)malloc((str->length + 1) * sizeof(char));
    if (!str->data) {
        return STRING_ALLOCATION_ERROR;
    }
    string_copy(str->data, initial);
    return STRING_SUCCESS;
}

// Функция для уничтожения строки
void String_destroy(String *str) {
    if (str && str->data) {
        free(str->data);
        str->data = NULL;
        str->length = 0;
    }
}

// Функция для сравнения двух объектов String
int String_compare(const String *str1, const String *str2) {
    if (str1->length != str2->length) {
        return str1->length - str2->length;
    }
    return string_compare(str1->data, str2->data);
}

// Функция для проверки равенства двух объектов String
int String_equals(const String *str1, const String *str2) {
    return str1->length == str2->length && string_compare(str1->data, str2->data) == 0;
}

// Функция для копирования одного объекта String в другой
int String_copy(String *dest, const String *src) {
    if (!dest || !src) {
        return STRING_ALLOCATION_ERROR;
    }

    String_destroy(dest);
    dest->length = src->length;
    dest->data = (char *)malloc((src->length + 1) * sizeof(char));
    if (!dest->data) {
        return STRING_ALLOCATION_ERROR;
    }
    string_copy(dest->data, src->data);
    return STRING_SUCCESS;
}

// Функция для копирования одного объекта String в новый (динамически выделенный)
int String_copy_new(String **dest, const String *src) {
    if (!dest || !src) {
        return STRING_ALLOCATION_ERROR;
    }

    *dest = (String *)malloc(sizeof(String));
    if (!*dest) {
        return STRING_ALLOCATION_ERROR;
    }

    (*dest)->length = src->length;
    (*dest)->data = (char *)malloc((src->length + 1) * sizeof(char));
    if (!(*dest)->data) {
        free(*dest);
        return STRING_ALLOCATION_ERROR;
    }

    string_copy((*dest)->data, src->data);
    return STRING_SUCCESS;
}

// Функция для конкатенации строк
void String_concat(String *str1, const String *str2) {
    if (!str1 || !str2) {
        return;
    }

    str1->data = (char *)realloc(str1->data, (str1->length + str2->length + 1) * sizeof(char));
    if (!str1->data) {
        return;
    }

    string_concat(str1->data + str1->length, str2->data);
    str1->length += str2->length;
}

/*
int main() {
    // Создание и инициализация строк
    String str1, str2;
    String_create(&str1, "Hello");
    String_create(&str2, "World");

    // Демонстрация сравнения строк
    printf("str1 == str2? %d\n", String_equals(&str1, &str2));

    // Копирование строки
    String str3;
    String_copy(&str3, &str1);
    printf("str3: %s\n", str3.data);

    // Конкатенация строк
    String_concat(&str1, &str2);
    printf("str1 после конкатенации: %s\n", str1.data);

    // Копирование в новый объект
    String *str4;
    String_copy_new(&str4, &str1);
    printf("str4 (новая строка): %s\n", str4->data);

    // Очистка памяти
    String_destroy(&str1);
    String_destroy(&str2);
    String_destroy(&str3);
    String_destroy(str4);
    free(str4);  // Память для str4 была выделена динамически

    return 0;
}
*/