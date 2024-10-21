#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>

typedef enum {
    SUCCESS = 0,
    ERROR
} Status;


size_t my_strlen(const char *str);

char* column_addition(const char* num1, const char* num2, int base);

char* sum_in_base(int base, int count, ...);

#endif 
