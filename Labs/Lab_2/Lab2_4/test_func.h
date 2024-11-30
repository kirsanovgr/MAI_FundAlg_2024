#pragma once

#include <stdarg.h>

typedef enum {
    CONVEX = 0,
    NOT_CONVEX,
    INVALID_ARGUMENT = 1
} Status;

int is_convex_polygon(int num_points, ...);
double evaluate_polynomial(double x, int degree, ...);
int is_kaprekar_number_in_base(int base, int num_strings, ...);