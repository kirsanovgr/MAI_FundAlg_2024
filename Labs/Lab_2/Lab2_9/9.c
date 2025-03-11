#include <stdarg.h>
#include <stdio.h>
#include "func.h"


int has_finite_representation(int base, int num_fractions, ...) {
    if (base < 2 || base > 36) {
        return INVALID_ARGUMENT; 
    }

    va_list args;
    va_start(args, num_fractions);

    for (int i = 0; i < num_fractions; i++) {
        double fraction = va_arg(args, double);
        if (fraction <= 0 || fraction >= 1) {
            continue;
        }

        int numerator = (int)(fraction * base);
        int denominator = base;

        while (denominator % 2 == 0) {
            denominator /= 2;
        }
        while (denominator % 5 == 0) {
            denominator /= 5;
        }

        if (denominator == 1) {
            printf("Fraction %.2f has a finite representation in base %d.\n", fraction, base);
        } else {
            printf("Fraction %.2f does not have a finite representation in base %d.\n", fraction, base);
        }
    }

    va_end(args);
    return SUCCESS;
}
