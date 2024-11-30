#include <stdio.h>
#include "func.h"

int main() {
    int base = 16;
    char* result = sum_in_base(base, 3, "1A", "2B", "3C");

    if (result) {
        printf("Сумма в системе счисления с основанием %d: %s\n", base, result);
        free(result);
    } else {
        printf("Ошибка при вычислении суммы.\n");
    }

    return SUCCESS;
}
