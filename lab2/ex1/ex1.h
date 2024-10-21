#ifndef LAB2_EX1_H
#define LAB2_EX1_H

#include <limits.h>
#include <stdlib.h>

#include "../SystemErrors/errors.h"
#include "../vector/charvector.h"
#include "../vector/stringvector.h"

typedef enum kOpts { OPT_L, OPT_R, OPT_U, OPT_N, OPT_C } kOpts;
error_msg GetOpts(int argc, char **argv, kOpts *opt);
error_msg CharToUInt(const char *string, unsigned int *x);
int SizeString(const char *string);

error_msg HandlerOptL(char **argv, int *size);
error_msg HandlerOptR(char **argv, char **new_string);
error_msg HandlerOptU(char **argv, char **new_string);
error_msg HandlerOptN(char **argv, char **new_string);
error_msg HandlerOptC(int argc, char **argv, char **new_string);

#endif
