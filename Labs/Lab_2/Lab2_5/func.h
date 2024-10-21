#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdarg.h>

typedef enum {
    SUCCESS = 0,
    ERROR = -1
} Status;

void int_to_roman(int num, char *result);
void my_strcat(char *dest, const char *src);
void print_fibonacci_reverse(int n, FILE *stream);
void print_in_base(int num, int base, FILE *stream, int is_upper);
void print_memory_representation(const void *ptr, size_t size, FILE *stream);
int overfprintf(FILE *stream, const char *format, ...);

#endif
