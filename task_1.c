#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_BASE = 1
} StatusCode;

#define MAX_NUMBER 4294967295U // Максимальное значение для unsigned int

int is_valid_number(const char *input) {
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++) {
        if (!isdigit(input[i])) {
            return 0; 
        }
    }

    unsigned long long number = strtoull(input, NULL, 10);
    if (number > MAX_NUMBER) {
        return 0; // Число превышает допустимый диапазон
    }

    return 1;
}

StatusCode convert_to_base(unsigned int number, unsigned int r, char *result, size_t buffer_size) {
    if (r < 1 || r > 5) {
        return ERROR_INVALID_BASE;
    }

    unsigned int base = 1 << r; // Основание системы счисления: 2^r
    size_t index = 0;

    while (number > 0 || index == 0) {
        if (index >= buffer_size - 1) {
            return ERROR_INVALID_BASE;
        }

        unsigned int remainder = number & (base - 1); // Остаток от деления
        number >>= r;                                // Делим число на 2^r

        // Преобразуем остаток в символ
        if (remainder < 10) {
            result[index++] = '0' + remainder;
        } else {
            result[index++] = 'A' + (remainder - 10);
        }
    }

    result[index] = '\0';

    for (size_t i = 0, j = index - 1; i < j; ++i, --j) {
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }

    return SUCCESS;
}

int main() {
    char input[64]; // Буфер для ввода числа

    printf("Введите число (не более %u): ", MAX_NUMBER);
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Ошибка: неверный ввод.\n");
        return 255;
    }

    // Убираем символ новой строки, если есть
    input[strcspn(input, "\n")] = '\0';

    // Проверяем корректность ввода
    if (!is_valid_number(input)) {
        printf("Ошибка: число некорректно или превышает максимально допустимое значение %u.\n", MAX_NUMBER);
        return 255;
    }

    // Преобразуем строку в число
    unsigned int number = (unsigned int)strtoul(input, NULL, 10);

    const size_t BUFFER_SIZE = 33; // Максимум 32 цифры + '\0'
    char result[BUFFER_SIZE];

    for (unsigned int r = 1; r <= 5; ++r) {
        StatusCode status = convert_to_base(number, r, result, BUFFER_SIZE);
        if (status != SUCCESS) {
            printf("Ошибка: недопустимое значение r.\n");
            return 255;
        }

        unsigned int base = 1 << r;
        printf("Число в системе счисления с основанием %u: %s\n", base, result);
    }

    return EXIT_SUCCESS;
}
