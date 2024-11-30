#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_func.h"

// Функция для вычисления длины строки
size_t my_strlen(const char *str) {
    const char *s = str;
    while (*s) {
        s++;
    }
    return s - str;
}

// Преобразование строки в число с базой от 2 до 36
long long my_strtoll(const char *nptr, char **endptr, int base) {
    const char *s = nptr;
    long long result = 0;
    int sign = 1;

    // Пропуск пробелов
    while (*s == ' ') {
        s++;
    }

    // Обработка знака
    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }

    // Если база 0 или 16, ошибка
    if (base == 0 || base == 16) {
        if (endptr) *endptr = (char *)nptr;
        return 0;
    }

    // Проверка допустимой базы
    if (base < 2 || base > 36) {
        if (endptr) *endptr = (char *)nptr;
        return 0;
    }

    // Преобразование строки в число
    while (*s) {
        int digit = 0;
        if (*s >= '0' && *s <= '9') {
            digit = *s - '0';
        } else if (*s >= 'a' && *s <= 'z') {
            digit = *s - 'a' + 10;
        } else if (*s >= 'A' && *s <= 'Z') {
            digit = *s - 'A' + 10;
        } else {
            break;
            return INVALID_ARGUMENT;  // Прекращаем при недопустимом символе
        }

        if (digit >= base) {
            break;
            return INVALID_ARGUMENT; 
        }

        result = result * base + digit;
        s++;
    }

    if (endptr) {
        *endptr = (char *)s;
    }

    return result * sign;
}

// Определение, является ли многоугольник выпуклым
int is_convex_polygon(int num_points, ...) {
    if (num_points < 3) {
        return INVALID_ARGUMENT;  // Многоугольник должен иметь хотя бы 3 вершины
    }

    va_list args;
    va_start(args, num_points);

    double x1 = va_arg(args, double);
    double y1 = va_arg(args, double);
    double x2 = va_arg(args, double);
    double y2 = va_arg(args, double);
    int sign = 0;

    for (int i = 2; i < num_points; i++) {
        double x3 = va_arg(args, double);
        double y3 = va_arg(args, double);

        double cross_product = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);

        if (cross_product < 0) {
            if (sign == 1) {
                va_end(args);
                return NOT_CONVEX;
            }
            sign = -1;
        } else if (cross_product > 0) {
            if (sign == -1) {
                va_end(args);
                return NOT_CONVEX;
            }
            sign = 1;
        }

        x1 = x2;
        y1 = y2;
        x2 = x3;
        y2 = y3;
    }

    va_end(args);
    return CONVEX;
}

// Вычисление значения многочлена
double evaluate_polynomial(double x, int degree, ...) {
    if (degree < 0) {
        return INVALID_ARGUMENT;
    }

    va_list args;
    va_start(args, degree);

    double result = va_arg(args, double);  // Коэффициент при старшей степени
    for (int i = 1; i <= degree; i++) {
        double coeff = va_arg(args, double);
        result = result * x + coeff;
    }

    va_end(args);
    return result;
}

// Проверка, является ли число числом Капрекара в заданной системе счисления
int is_kaprekar_number_in_base(int base, int num_strings, ...) {
    if (base < 2 || base > 36) {
        return INVALID_ARGUMENT;
    }

    va_list args;
    va_start(args, num_strings);

    for (int i = 0; i < num_strings; i++) {
        const char* number_str = va_arg(args, const char*);
        char* end_ptr;
        long long number = my_strtoll(number_str, &end_ptr, base);

        if (*end_ptr != '\0') {
            continue;
        }

        long long square = number * number;
        char square_str[64];    
        snprintf(square_str, sizeof(square_str), "%lld", square);

        int len = my_strlen(square_str);
        long long right_part = my_strtoll(square_str + len / 2, NULL, base);
        long long left_part = len > 1 ? my_strtoll(square_str, NULL, base) : 0;

        if (left_part + right_part == number) {
            printf("%s является числом Капрекара в системе счисления с основанием %d\n", number_str, base);
        }
    }

    va_end(args);
    return 0;
}
