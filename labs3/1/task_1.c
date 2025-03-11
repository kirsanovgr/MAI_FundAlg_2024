#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUCCESS,
    ERROR_INVALID_BASE,
    ERROR_INVALID_INPUT,
    ERROR_MEMORY_ALLOCATION_FAILED
} StatusCode;

int add(int x, int y) {
    int sum, carry;
    while (y) {
        sum = x ^ y;
        carry = (x & y) << 1;
        x = sum;
        y = carry;
    }
    return x;
}

char intToChar(int x) {
    if (x >= 0 && x <= 9)
        return add(x, '0');
    if (x >= 10 && x <= 36)
        return add(add(x, -10), 'A');
    return -1;
}

void reverseString(char *str) {
    int length = 0, i = 0;
    char tmp;

    while (str[length] != '\0') {
        length = add(length, 1);
    }
    int halfLength = length >> 1;
     for (i = 0; i < halfLength; ++i) {
        tmp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = tmp;
        i = add(i, 1);
    }
}

StatusCode decimalToBase(int number, int basePower, char *result) {
    if (basePower < 1 || basePower > 5) {
        return ERROR_INVALID_BASE;
    }
    int index = 0;
    if (number == 0) {
        result[index++] = '0';
    } else {
        while (number) {
            int remainder = add(number, -((number >> basePower) << basePower));
            result[index++] = intToChar(remainder);
            number >>= basePower;
        }
    }
    result[index] = '\0';
    reverseString(result);
    return SUCCESS;
}

int main() {
    int number, basePower;
    char result[BUFSIZ];
    StatusCode status;

    printf("Enter number = ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Error: invalid input, expected an integer.\n");
        return ERROR_INVALID_INPUT;
    }

    printf("Enter base power (1 to 5) = ");
    if (scanf("%d", &basePower) != 1 || basePower < 1 || basePower > 5) {
        fprintf(stderr, "Error: base power must be between 1 and 5.\n");
        return ERROR_INVALID_BASE;
    }

    status = decimalToBase(number, basePower, result);
    if (status == SUCCESS) {
        printf("Result: %s\n", result);
    } else if (status == ERROR_INVALID_BASE) {
        fprintf(stderr, "Error: invalid base power.\n");
    }

    return status;
}
