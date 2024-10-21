#include "func.h"
#include <math.h>
#include <stdlib.h>

StatusCode Dychotomy(double x0, double x1, double (*func)(double), double epsilon, double *root) {
    if (epsilon <= 0 || root == NULL) {
        return ERROR_INVALID_BOUNDS;
    }

    if (func(x0) * func(x1) > 0) {
        return ERROR_NO_ROOT;
    }

    double res = (x1 + x0) / 2.0;
    double last = x0;

    while (fabsl(func(res)) >= epsilon && fabsl(res - last) >= epsilon) {
        if (func(res) * func(x0) < 0) {
            x1 = res;
        } else {
            x0 = res;
        }

        last = res;
        res = (x0 + x1) / 2.0;
    }

    *root = res;
    return SUCCESS;
}
