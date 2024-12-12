#include "dinamyc-array.h"


error_msg create_dynamic_array_departments(DynamicArrayDepartments *departments, size_t capacity) {
    if (departments == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "create_dynamic_array_departments", "get pointer to null"};
    }
    departments->data = (Departament **) calloc(capacity, sizeof(Departament *));
    if (!departments->data) {
        return (error_msg) {MEMORY_ALLOCATED_ERROR, "create_dynamic_array_departments", "memory allocated"};
    }
    departments->size = 0;
    departments->capacity = capacity;
    return (error_msg) {SUCCESS, "", ""};
}

int compare_dep(const void *first, const void *second) {
    return (int)(*((Departament **) first))->id - (int)(*((Departament **) second))->id;
}

error_msg push_into_dynamic_array(DynamicArrayDepartments *departments, size_t id_department, size_t count_operators,
                                  char what_queue) {
    if (departments == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "push_into_dynamic_array_departments", "get pointer to null"};
    }

    Departament* tmp1;
    error_msg errorMsg = get_dynamic_array(departments, id_department, &tmp1);
    if(errorMsg.type == SUCCESS){
        return (error_msg){INCORRECT_ARG_FUNCTION, "push_into_dynamic_array", "this idea already exist"};
    }

    if (departments->size == departments->capacity) {
        Departament **tmp = (Departament **) realloc(departments->data, departments->capacity * 2);
        if (!tmp) {
            return (error_msg) {MEMORY_ALLOCATED_ERROR, "push_into_dynamic_array", "memory allocated in resize"};
        }
        departments->data = tmp;
        departments->capacity = departments->capacity * 2;
    }
    departments->size += 1;
    errorMsg = create_departament(&(departments->data[departments->size - 1]), count_operators, id_department,
                                            what_queue);
    if (errorMsg.type) {
        return errorMsg;
    }
    qsort(departments->data, departments->size, sizeof(Departament *), compare_dep);
    return (error_msg) {SUCCESS, "", ""};
}

error_msg get_dynamic_array(DynamicArrayDepartments *departments, size_t id_department, Departament **dep) {
    if (departments == NULL || dep == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "get_dynamic_array", "get pointer to null"};
    }
    if(departments->size == 0){
        return (error_msg){INCORRECT_ARG_FUNCTION, "get_dynamic_array", "get from empty array"};
    }
    size_t a = 0;
    size_t b = departments->size;
    size_t c = (a + b) / 2;
    size_t i = 0;
    while (departments->data[c]->id != id_department) {
        if (departments->data[c]->id > id_department) {
            b = c;
        } else if (departments->data[c]->id < id_department) {
            a = c;
        }
        c = (a + b) / 2;
        i++;
        if(i == departments->size){
            return (error_msg){INCORRECT_OPTIONS_ERROR, "get_dynamic_array", "this department doesn't exist"};
        }
    }
    *dep = departments->data[c];

    return (error_msg) {SUCCESS, "", ""};
}


error_msg destroy_dynamic_array(DynamicArrayDepartments *departments) {
    if (departments == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "destroy_dynamic_array_departments", "get pointer to null"};
    }
    for (size_t i = 0; i < departments->size; ++i) {
        destroy_departament(departments->data[i]);
    }
    free(departments->data);

    return (error_msg) {SUCCESS, "", ""};
}