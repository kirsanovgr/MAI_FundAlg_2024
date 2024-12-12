#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../../lib2/SystemErrors2/errors.h"
#include "../../lib2/vector/charvector.h"
#include "../process_files/process_files.h"

error_msg preparing(int argc, char** argv, DStorage* storages, Time* begin, Time* end, size_t* min_minutes,
                    size_t* max_minutes, size_t* count_departments, double* overload_coefficient, size_t* max_priority,
                    size_t* size_mas, size_t* capacity_mas, Application*** mas);