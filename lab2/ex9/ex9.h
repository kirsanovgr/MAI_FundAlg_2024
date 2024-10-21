
#ifndef LAB2_EX9_H
#define LAB2_EX9_H

#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#include "../SystemErrors/errors.h"
#include "../vector/stringvector.h"
#include "../vector/intvector.h"

error_msg AreCorrectFractions(StringVector * vec, int base, int n, ...);

#endif
