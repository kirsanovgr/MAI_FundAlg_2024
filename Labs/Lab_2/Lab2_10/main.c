#include "func.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    double epsilon = 1e-6;
    double a = 2.0;
    int n = 3;
    
    double *new_coeff = NULL;
    if (transform_polynomial(epsilon, a, n, &new_coeff, 1.0, 2.0, 3.0, 4.0) == 0) {   //f(x) = 1 + 2x + 3x^2 + 4x^3
        printf("Новый многочлен в степенях (x - %.2lf):\n", a);  
        print_polynomial(new_coeff, n, a);
    } else {
        printf("Ошибка при выделении памяти\n");
    }
    
    free(new_coeff);
    
    return 0;
}
