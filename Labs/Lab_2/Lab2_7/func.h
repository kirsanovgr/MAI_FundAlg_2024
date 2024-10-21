#ifndef FUNC_H
#define FUNC_H

typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_BOUNDS,
    ERROR_NO_ROOT
} StatusCode;

StatusCode Dychotomy(double x0, double x1, double (*func)(double), double epsilon, double *root);

#endif
