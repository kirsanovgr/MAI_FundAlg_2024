#pragma once

#include <stdlib.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../department/department.h"

typedef struct DynamicArrayDepartments {
    Departament **data;
    size_t size;
    size_t capacity;
} DynamicArrayDepartments;

error_msg create_dynamic_array_departments(DynamicArrayDepartments *departments, size_t capacity);\
error_msg push_into_dynamic_array(DynamicArrayDepartments *departments, size_t id_department, size_t count_operators,
                                  char what_queue);
error_msg get_dynamic_array(DynamicArrayDepartments *departments, size_t id_department, Departament **dep);
error_msg destroy_dynamic_array(DynamicArrayDepartments *departments);