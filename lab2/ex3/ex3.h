#ifndef LAB2_EX3_H
#define LAB2_EX3_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../SystemErrors/errors.h"
#include "../vector/intvector.h"
#include "../vector/stringvector.h"


error_msg FilesStrStr(int n, StringVector * result, char * string, ...);

#endif