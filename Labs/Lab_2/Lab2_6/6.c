#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include "func.h"

// Функция для преобразования римского числа в int
int roman_to_int(const char *str) {
    int result = 0;
    while (*str) {
        switch (*str) {
            case 'M': result += 1000; break;
            case 'D': result += 500; break;
            case 'C': result += 100; break;
            case 'L': result += 50; break;
            case 'X': result += 10; break;
            case 'V': result += 5; break;
            case 'I': result += 1; break;
            default: return -1;  // Недопустимый символ
        }
        str++;
    }
    return result;
}

// Функция для преобразования числа Цекендорфа в int
unsigned int zeckendorf_to_int(const char *str) {
    unsigned int result = 0;
    unsigned int fib1 = 1, fib2 = 2;

    while (*str) {
        if (*str == '1') {
            result += fib2;
        } else if (*str != '0') {
            return -1;  // Недопустимый символ
        }
        unsigned int temp = fib2;
        fib2 += fib1;
        fib1 = temp;
        str++;
    }
    return result;
}

// Функция для преобразования строки в целое число в произвольной системе счисления
int base_to_int(const char *str, int base, int is_upper) {
    int result = 0;
    while (*str) {
        int digit;
        if (*str >= '0' && *str <= '9')
            digit = *str - '0';
        else if (is_upper && *str >= 'A' && *str <= 'Z')
            digit = *str - 'A' + 10;
        else if (!is_upper && *str >= 'a' && *str <= 'z')
            digit = *str - 'a' + 10;
        else
            return -1;  // Недопустимый символ

        if (digit >= base)
            return -1;  // Недопустимая цифра для данной базы

        result = result * base + digit;
        str++;
    }
    return result;
}

// Реализация функции overfscanf
int overfscanf(FILE *file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = 0;

    if (strcmp(format, "%Ro") == 0) {
        int *value = va_arg(args, int *);
        char roman[100];
        fscanf(file, "%s", roman);
        *value = roman_to_int(roman);
    } else if (strcmp(format, "%Zg") == 0) {
        unsigned int *value = va_arg(args, unsigned int *);
        char zeckendorf[100];
        fscanf(file, "%s", zeckendorf);
        *value = zeckendorf_to_int(zeckendorf);
    } else if (strcmp(format, "%Cv") == 0 || strcmp(format, "%CV") == 0) {
        int *value = va_arg(args, int *);
        int base = va_arg(args, int);
        char base_num[100];
        fscanf(file, "%s", base_num);
        *value = base_to_int(base_num, base, (format[2] == 'V'));
    }

    va_end(args);
    return result;
}

// Реализация функции oversscanf
int oversscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = 0;

    if (strcmp(format, "%Ro") == 0) {
        int *value = va_arg(args, int *);
        *value = roman_to_int(str);
    } else if (strcmp(format, "%Zg") == 0) {
        unsigned int *value = va_arg(args, unsigned int *);
        *value = zeckendorf_to_int(str);
    } else if (strcmp(format, "%Cv") == 0 || strcmp(format, "%CV") == 0) {
        int *value = va_arg(args, int *);
        int base = va_arg(args, int);
        *value = base_to_int(str, base, (format[2] == 'V'));
    }

    va_end(args);
    return result;
}
