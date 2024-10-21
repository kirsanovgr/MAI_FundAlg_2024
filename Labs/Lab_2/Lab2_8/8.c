#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

const int MAX_BASE = 36;

size_t my_strlen(const char *str) {
    const char *s = str;
    while (*s) {
        s++;
    }
    return s - str;
}

int char_to_value(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    return 0;
}

char value_to_char(int value) {
    if (value < 10) {
        return value + '0';
    } else {
        return value - 10 + 'A';
    }
}

char* column_addition(const char* num1, const char* num2, int base) {
    int len1 = my_strlen(num1);
    int len2 = my_strlen(num2);
    int max_len = (len1 > len2) ? len1 : len2;

    char* result = (char*)malloc(max_len + 2); // +1 для переноса, +1 для нуля
    if (!result) return NULL;

    result[max_len + 1] = '\0';
    int carry = 0;

    for (int i = len1 - 1, j = len2 - 1, k = max_len; k >= 0; k--) {
        int digit1 = (i >= 0) ? char_to_value(num1[i]) : 0;
        int digit2 = (j >= 0) ? char_to_value(num2[j]) : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        result[k] = value_to_char(sum % base);

        i--;
        j--;
    }

    // Если есть перенос, добавляем его в результат
    if (carry > 0) {
        // Перенос в начало результата
        for (int i = max_len; i >= 0; i--) {
            result[i + 1] = result[i]; // Сдвигаем результат
        }
        result[0] = value_to_char(carry); // Записываем перенос
        result[max_len + 2] = '\0'; // Обновляем конец строки
    } else {
        // Удаление ведущих нулей
        char* start = result;
        while (*start == '0' && start < result + max_len) {
            start++;
        }

        // Если результат - пустая строка
        if (*start == '\0') {
            free(result);
            return "0"; // Если сумма равна нулю
        }

        // Создание финального результата
        int final_len = (result + max_len + 1) - start;
        char* final_result = (char*)malloc(final_len + 1);
        if (!final_result) {
            free(result);
            return NULL;
        }

        for (int k = 0; k < final_len; k++) {
            final_result[k] = start[k];
        }
        final_result[final_len] = '\0';

        free(result);
        return final_result;
    }

    return result;
}

char* sum_in_base(int base, int count, ...) {
    if (base < 2 || base > MAX_BASE) {
        return NULL;  
    }

    va_list args;
    va_start(args, count);

    char* total = malloc(2);
    if (!total) return NULL;
    total[0] = '0';
    total[1] = '\0';

    for (int i = 0; i < count; i++) {
        const char* current_num = va_arg(args, const char*);
        char* new_total = column_addition(total, current_num, base);

        if (!new_total) {
            free(total);
            va_end(args);
            return NULL;
        }

        free(total);
        total = new_total;
    }

    va_end(args);
    return total;
}
