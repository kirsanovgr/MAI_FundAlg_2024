#include <stdio.h>
#include "test_func.h"

int main() {
    double epsilon = 1e-6;

    // Пример проверки выпуклости многоугольника
    int is_convex = is_convex_polygon(epsilon, 4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0);
    if (is_convex) {
        printf("Многоугольник выпуклый.\n");
    } else {
        printf("Многоугольник невыпуклый.\n");
    }

    // Пример нахождения значения многочлена
    double result = evaluate_polynomial(epsilon, 2.0, 2, 1.0, -3.0, 2.0); // x^2 - 3x + 2
    printf("Значение многочлена: %.2f\n", result);

    // Пример проверки чисел Капрекара
    is_kaprekar_number_in_base(10, 3, "1", "9", "45"); // Проверка 1, 9, 45 в десятичной системе

    return 0;
}
