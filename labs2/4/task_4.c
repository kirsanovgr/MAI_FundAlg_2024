#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Проверка выпуклости многоугольника
int check_of_convex(int n, ...) {
    va_list vl;
    va_start(vl, n);

    if (n < 6 || n % 2 != 0) {
        printf("Invalid number of coordinates. Must be even and at least 6 (3 vertices).\n");
        return -1;
    }

    int count = n / 2;
    double x[count], y[count];
    
    for (int i = 0; i < count; i++) {
        x[i] = va_arg(vl, double);
        y[i] = va_arg(vl, double);
    }

    va_end(vl);

    int sign = 0;

    for (int i = 0; i < count; i++) {
        double x1 = x[i];
        double y1 = y[i];
        double x2 = x[(i + 1) % count];
        double y2 = y[(i + 1) % count];
        double x3 = x[(i + 2) % count];
        double y3 = y[(i + 2) % count];

        double cross_product = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
        int current_sign = (cross_product > 0) ? 1 : (cross_product < 0) ? -1 : 0;

        if (current_sign == 0) continue;

        if (sign == 0) {
            sign = current_sign;
        } else if (sign != current_sign) {
            printf("The polygon is not convex\n");
            return 0;
        }
    }

    printf("The polygon is convex\n");
    return 1;
}

// Вычисления значения многочлена
double horner_scheme(double x, double a[], int n) {
    double result = a[0];
    for (int i = 1; i <= n; i++) {
        result = result * x + a[i];
    }
    return result;
}

double polynomial_value(double x, int n, ...) {
    va_list vl;
    va_start(vl, n);
    
    double a[n + 1];
    for (int i = 0; i <= n; i++) {
        a[i] = va_arg(vl, double);
    }

    va_end(vl);

    double result = horner_scheme(x, a, n);
    printf("Polynomial value at x = %.2f is: %.2f\n", x, result);
    return result;
}

// Числа Капрекара
int is_kaprekar(int num, int base) {
    long square = (long) num * num;
    char str_square[50];
    
    snprintf(str_square, sizeof(str_square), "%ld", square);
    
    int len = strlen(str_square);
    for (int i = 1; i < len; i++) {
        char left_part[50], right_part[50];
        strncpy(left_part, str_square, i);
        left_part[i] = '\0';
        strcpy(right_part, &str_square[i]);

        int left = atoi(left_part);
        int right = atoi(right_part);

        if (right > 0 && left + right == num) {
            return 1;
        }
    }
    return 0;
}

void find_kaprekar_numbers(int base, int count, ...) {
    va_list vl;
    va_start(vl, count);
    
    printf("\nKaprekar Numbers in Base %d:\n", base);
    
    for (int i = 0; i < count; i++) {
        char *num_str = va_arg(vl, char*);
        int num = strtol(num_str, NULL, base);

        if (is_kaprekar(num, base)) {
            printf(" - Number %s is a Kaprekar number\n", num_str);
        } else {
            printf(" - Number %s is NOT a Kaprekar number\n", num_str);
        }
    }

    va_end(vl);
}

int main() {
    printf("\n=== Polygon Convexity Check ===\n");
    check_of_convex(10, 0.0, 0.0, 2.0, 1.0, 1.0, 2.0, -1.0, 1.0, -0.5, 0.5);
    check_of_convex(10, 0.0, 0.0, 2.0, 1.0, 1.0, 2.0, 0.5, 1.5, 1.5, 0.5);
    
    printf("\n=== Polynomial Evaluation ===\n");
    polynomial_value(2.0, 2, 3.0, -2.0, 1.0); // 3x^2 - 2x + 1, x = 2
    
    printf("\n=== Finding Kaprekar Numbers ===");
    find_kaprekar_numbers(10, 4, "45", "10", "55", "15");

    return 0;
}
