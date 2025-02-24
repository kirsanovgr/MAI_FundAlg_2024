#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    SUCCESS = 0,
    MEMORY_ALLOCATION_ERROR = -1,
    INVALID_PARAMETER_ERROR = -2
} StatusCode;

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

double evaluate_polynomial(const double* coeffs, int degree, double x) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * pow(x, i);
    }
    return result;
}

StatusCode taylor_expand(double epsilon, double a, double** taylor_coeffs, int max_degree, ...) {
    if (taylor_coeffs == NULL || max_degree < 0 || epsilon <= 0.0 || !isfinite(a)) {
        return INVALID_PARAMETER_ERROR;
    }

    *taylor_coeffs = (double*)malloc((max_degree + 1) * sizeof(double));
    if (*taylor_coeffs == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    va_list args;
    va_start(args, max_degree);

    double* original_coeffs = (double*)malloc((max_degree + 1) * sizeof(double));
    if (original_coeffs == NULL) {
        free(*taylor_coeffs);
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i <= max_degree; i++) {
        original_coeffs[i] = va_arg(args, double);
    }

    va_end(args);

    printf("Original coefficients:\n");
    for (int i = 0; i <= max_degree; i++) {
        printf("f_%d = %lf\n", i, original_coeffs[i]);
    }

    (*taylor_coeffs)[0] = evaluate_polynomial(original_coeffs, max_degree, a);
    for (int i = 1; i <= max_degree; i++) {
        double derivative = 0.0;
        for (int j = i; j <= max_degree; j++) {
            derivative += original_coeffs[j] * factorial(j) / factorial(j - i) * pow(a, j - i);
        }
        (*taylor_coeffs)[i] = derivative / factorial(i);
    }

    for (int i = 0; i <= max_degree; i++) {
        if (fabs((*taylor_coeffs)[i]) < epsilon) {
            (*taylor_coeffs)[i] = 0.0;
        }
    }

    free(original_coeffs);
    return SUCCESS;
}

void print_coefficients(const double* coeffs, int degree, double a) {
    printf("\nTaylor series coefficients for polynomial expansion around (x - %lf):\n", a);
    for (int i = 0; i <= degree; i++) {
        printf("g_%d = %lf\n", i, coeffs[i]);
    }
}

int main() {
    double* taylor_coeffs = NULL;
    int max_degree = 2;
    double a = 1.0;
    double epsilon = 0.000001;
    double x = 2.0;

    StatusCode result = taylor_expand(epsilon, a, &taylor_coeffs, max_degree, 1.0, 3.0, 5.0);
    if (result != SUCCESS) {
        if (result == MEMORY_ALLOCATION_ERROR) {
            printf("Memory allocation error!\n");
        } else if (result == INVALID_PARAMETER_ERROR) {
            printf("Error: invalid input parameters!\n");
        }
        return result;
    }

    print_coefficients(taylor_coeffs, max_degree, a);

    double f_x = evaluate_polynomial((double[]){1.0, 3.0, 5.0}, max_degree, x);
    double g_x = evaluate_polynomial(taylor_coeffs, max_degree, x - a);

    printf("\nf(%lf) = %lf\n", x, f_x);
    printf("g(%lf) = %lf\n", x, g_x);

    free(taylor_coeffs);

    return 0;
}
