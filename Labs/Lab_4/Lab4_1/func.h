#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 128

// Структура для хранения макроса
typedef struct Macro {
    char *name;
    char *value;
    struct Macro *next;
} Macro;

// Хеш-таблица для макросов
Macro *hashtable[HASHSIZE];

typedef enum Error {
    SUCCESS = 0,
    INCORRECT_OPTIONS = -1,
    ERROR_FILE_OPEN = -2,
    ERROR_WITH_MACROS = -3,
    ERROR_MEMORY = -4
} Status;