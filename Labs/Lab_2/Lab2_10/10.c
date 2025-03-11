#include "func.h"
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>

typedef enum {
    SUCCESS = 0
} Status;

// Функция для вычисления производной многочлена в точке x
double derivative(int order, int n, double a, const double *coeff) {
    double result = 0.0;
    for (int i = order; i <= n; i++) {
        double term = coeff[i];
        for (int j = 0; j < order; j++) {
            term *= (i - j);  // Вычисляем производную i-го порядка
        }
        result += term * pow(a, i - order);  // Умножаем на (a^(i-order))
    }
    printf("Производная порядка .%d. a=%.2lf: %.2lf\n", order, a, result);
    return result;
}

// Функция для нахождения коэффициентов разложения многочлена по степеням (x - a)
int transform_polynomial(double epsilon, double a, int n, double **result, ...) {
    *result = (double *)malloc((n + 1) * sizeof(double));
    if (*result == NULL) {
    }

    va_list args;
    va_start(args, result);
    
    double *f = (double *)malloc((n + 1) * sizeof(double));
    if (f == NULL) {
        free(*result);
    }
    
    // Считываем коэффициенты исходного многочлена
    for (int i = 0; i <= n; i++) {
        f[i] = va_arg(args, double);
    }
    va_end(args);
    
    // Вычисляем новые коэффициенты
    for (int i = 0; i <= n; i++) {
        (*result)[i] = derivative(i, n, a, f) / tgamma(i + 1);  // tgamma(i+1) эквивалентно i!
        printf("Коэффициент g[%d] = %.2f\n", i, (*result)[i]); 
        
        if (fabs((*result)[i]) < epsilon) {
            (*result)[i] = 0.0;
        }
    }
    
    free(f);
    return SUCCESS;
}

void print_polynomial(const double *coeff, int n, double a) {
    printf("f(x) = ");
    for (int i = 0; i <= n; i++) {
        if (coeff[i] != 0) {
            printf("%+.2lf * (x - %.2lf)^%d ", coeff[i], a, i);
        }
    }
    printf("\n");
}
