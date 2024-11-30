#include <stdio.h>
#include "func.h"

int main() {
    int base = 10;

    printf("Checking finite representation for fractions in base %d:\n", base);
    has_finite_representation(base, 5, 0.5, 0.333, 0.2, 0.125, 0.1);

    return 0;
}
