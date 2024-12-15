#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../../lib2/SystemErrors2/errors.h"
#include "../application/application.h"
#include "../data-storages/data-storages.h"

error_msg process_file_with_the_model_parameters_and_create_storage(const char* filename, DStorage* dataStorages,
                                                                    Time* time_begin, Time* time_end,
                                                                    size_t* min_minutes, size_t* max_minutes,
                                                                    double* overload_coefficient,
                                                                    size_t* count_departments);

error_msg process_files_with_applications(const char** filenames, int count_files, Application*** mas, size_t* size,
                                          size_t* capacity, size_t count_departments, const Time* time_start,
                                          const Time* time_end, size_t max_priority);
error_msg process_file_with_applications(const char* filename, Application*** applications, size_t* size,
                                        size_t* capacity, size_t max_priority, size_t count_departments,
                                        const Time* time_start, const Time* time_end);