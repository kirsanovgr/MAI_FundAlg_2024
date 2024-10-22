#ifndef LAB2_OVERLOADS_H
#define LAB2_OVERLOADS_H

#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

#include "../SystemErrors/errors.h"
#include "../vector/stringvector.h"

int overfprintf(FILE * restrict stream, const char * format, ...);

int oversprintf(char *string, const char *format, ...);




#endif