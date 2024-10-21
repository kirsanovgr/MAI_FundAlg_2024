#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include "geom_mean_power.h"

typedef enum {
    SUCCESS = 0,
    ERROR_ARGUMENTS,
    ERROR_INPUT,
} Status;

// Функция для вычисления среднего геометрического
int geometric_mean(double *result, int count, ...) {
    if (count <= 0 || result == NULL) {
        return ERROR_INPUT;
    }

    va_list args;
    va_start(args, count);
    double product = 1.0;
    for (int i = 0; i < count; i++) {
        double value = va_arg(args, double);
        if (value <= 0) {
            va_end(args);
            return ERROR_ARGUMENTS;
        }
        product *= value;
    }
    va_end(args);

    *result = pow(product, 1.0 / count);
    return SUCCESS;
}

double power(double base, int exp) {
    if (exp == 0) {
        return 1.0;
    }
    if (exp < 0) {
        return 1.0 / power(base, -exp); // отрицательная степень
    }
    double half = power(base, exp / 2);
    if (exp % 2 == 0) {
        return half * half;
    } else {
        return base * half * half;
    }
}
