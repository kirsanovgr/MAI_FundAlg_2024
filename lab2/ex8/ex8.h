#ifndef LAB2_EX8_H
#define LAB2_EX8_H

#include <stdio.h>
#include <stdarg.h>

#include "../SystemErrors/errors.h"
#include "../vector/charvector.h"
#include "../vector/stringvector.h"

error_msg AdditionNumbers(char *a, char *b, char *result, int base);

error_msg AdditionManyNumbers(char * result, int base, int n, ...);

#endif
