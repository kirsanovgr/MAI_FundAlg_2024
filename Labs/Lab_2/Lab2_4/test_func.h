#ifndef FUNC_H
#define FUNC_H

#include <stdarg.h>

typedef enum {
    CONVEX = 0,
    NOT_CONVEX,
    INVALID_ARGUMENT = 1
} Status;

int is_convex_polygon(double epsilon, int num_points, ...);
double evaluate_polynomial(double epsilon, double x, int degree, ...);
int is_kaprekar_number_in_base(int base, int num_strings, ...);

#endif // FUNC_H