#include <stdio.h>
#include "geom_mean_power.h"

int main() {
    double mean;
    int status;

    // Демонстрация функции среднего геометрического
    status = geometric_mean(&mean, 4, 1.0, 3.0, 9.0, 27.0);
    if (status == 0) {
        printf("Среднее геометрическое: %.6f\n", mean);
    } else {
        printf("Ошибка при вычислении среднего геометрического: %d\n", status);
    }

    // Демонстрация функции возведения в степень
    double base = 2.0;
    int exp = 10;
    printf("%.2f в степени %d = %.2f\n", base, exp, power(base, exp));

    return 0;
}
