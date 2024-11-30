#pragma once

#include <stdio.h>

typedef enum {
    SUCCESS = 0,
    ERROR_WITH_FILE
} Status;

int roman_to_int(const char *str);
unsigned int zeckendorf_to_int(const char *str);
int base_to_int(const char *str, int base, int is_upper);
int overfscanf(FILE *file, const char *format, ...);
int oversscanf(const char *str, const char *format, ...);