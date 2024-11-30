#include "func.h"
#include <stdio.h>

double my_function(double x) {
    return x * x - 2.0;
}

int main() {
    double x0 = 0, x1 = 2;
    double epsilon = 1e-6;
    double root;

    StatusCode status = Dychotomy(x0, x1, my_function, epsilon, &root);
    
    if (status == SUCCESS) {
        printf("Корень уравнения: %.8f\n", root);
    } else if (status == ERROR_INVALID_BOUNDS) {
        printf("Ошибка: Неверные границы интервала или точность.\n");
    } else if (status == ERROR_NO_ROOT) {
        printf("Ошибка: На данном интервале нет корня.\n");
    }

    return SUCCESS;
}
