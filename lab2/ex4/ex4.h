#ifndef LAB2_EX4_H
#define LAB2_EX4_H

#include <stdarg.h>
#include <stdlib.h>
#include "../SystemErrors/errors.h"
#include "../vector/charvector.h"
#include "../vector/stringvector.h"

typedef struct Point {
	double x;
	double y;
} Point;

int IsConvexPolygon(int n, ...);

double ValueOfPolynomial(double x, int n, ...);

error_msg FindNumbersKarper(StringVector *, int base, int n, ...);

error_msg AdditionNumbers(char *a, char *b, char *result, int base);
error_msg ProductNumbers(char *a, char *b, char *result, int base);

#endif
