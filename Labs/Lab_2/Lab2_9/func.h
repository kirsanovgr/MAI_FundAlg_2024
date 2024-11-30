#ifndef FUNC_H
#define FUNC_H

typedef enum {
    SUCCESS = 0,
    INVALID_ARGUMENT
} Status;

int has_finite_representation(int base, int num_fractions, ...);

#endif 
