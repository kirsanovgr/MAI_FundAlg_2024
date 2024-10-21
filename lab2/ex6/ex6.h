#ifndef LAB2_EX6_H
#define LAB2_EX6_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>
#include <math.h>

#include "../SystemErrors/errors.h"
#include "../vector/stringvector.h"

int overfscanf(FILE * stream, char * format, ...);
int oversscanf(char * buffer, char * format, ...);

#endif
