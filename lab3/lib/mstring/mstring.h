#ifndef LAB3_MSTRING_H
#define LAB3_MSTRING_H

#include <stdio.h>
#include <stdlib.h>

#include "../SystemErrors/errors.h"

error_msg str_to_k(const char **string, char *separator, char *result);
error_msg my_strcat(char *a, const char *b);
int string_cmp(const char *a, const char *b);
error_msg strcopy(const char *a, char *result, int start, int end);
int SizeString(const char *a);
int string_compare(const char *s1, const char*s2);
int strtoint(const char * a);


#endif  // LAB3_MSTRING_H