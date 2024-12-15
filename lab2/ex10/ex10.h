#ifndef LAB2_EX10_H
#define LAB2_EX10_H

#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>

#include "../SystemErrors/errors.h"
#include "../vector/stringvector.h"

int compare(double a, double b, double eps);
long long int special_product(int n, int p);
long long int fac(int x);

error_msg DecompositionPolynomial(double eps, double a, double ** result, int n, ...);

#endif
