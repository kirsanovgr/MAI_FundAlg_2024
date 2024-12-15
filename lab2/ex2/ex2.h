#ifndef LAB2_EX2_H
#define LAB2_EX2_H

#include "../SystemErrors/errors.h"

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <check.h>

error_msg geometric_mean(double * result, int n, ...);
double QuitPow(double x, int n);
#endif
