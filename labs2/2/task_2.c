#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

#define SUCCESS 0
#define ERROR_INVALID_ARGUMENT -1
#define EPSILON 1e-6

int geometric_mean(int n, double *result, ...) {
    if (n <= 0 || result == NULL) {
        return ERROR_INVALID_ARGUMENT;
    }

    va_list vl;
    double product = 1.0;
    va_start(vl, result);

    for (int i = 0; i < n; i++) {
        double num = va_arg(vl, double);
        if (num <= 0) {
            va_end(vl);
            return ERROR_INVALID_ARGUMENT;
        }
        product *= num;
    }
    va_end(vl);

    *result = pow(product, 1.0 / n);
    return SUCCESS;
}

int recursive_pow(double base, int exponent, double *result) {
    if (result == NULL) {
        return ERROR_INVALID_ARGUMENT;
    }
    
    if (fabs(base - 0.0) < EPSILON && exponent < 0) {
        return ERROR_INVALID_ARGUMENT;
    }

    if (exponent == 0) {
        *result = 1.0;
    } else if (exponent < 0) {
        *result = 1.0 / pow(base, -exponent);
    } else if (exponent % 2 == 0) {
        double half_result;
        recursive_pow(base, exponent / 2, &half_result);
        *result = half_result * half_result;
    } else {
        double recursive_result;
        recursive_pow(base, exponent - 1, &recursive_result);
        *result = base * recursive_result;
    }

    return SUCCESS;
}

int main() {
    double mean;
    int status = geometric_mean(3, &mean, 2.5, 4.5, 8.0);
    if (status == SUCCESS) {
        printf("Result of the geometric mean: %g\n", mean);
    } else {
        printf("Error: invalid arguments for geometric mean\n");
    }

    double power_result;
    status = recursive_pow(4.5, 2, &power_result);
    if (status == SUCCESS) {
        printf("The result of recursive pow: %g\n", power_result);
    } else {
        printf("Error: invalid arguments for recursive pow\n");
    }

    return 0;
}
