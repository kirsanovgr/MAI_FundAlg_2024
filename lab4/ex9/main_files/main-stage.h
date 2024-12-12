#pragma once

#include "../../lib2/SystemErrors2/errors.h"
#include "preparing.h"

#define NAME_LOG_FILE "LOG_FILE"

error_msg print_new_request(FILE *file, Application *application);
error_msg print_handling_started(FILE *file, Operator *operator, Time * now);
error_msg print_handling_finished(FILE *file, Operator *operator, Time * now);
error_msg print_overloaded(FILE *file, size_t id_app, size_t new_id_departament, Time *now);

error_msg modeling(DStorage *storage, Application **mas_applications, size_t size_mas, Time *time_begin, Time *time_end,
                   size_t min_minutes, size_t max_minutes, double overload_coefficient, size_t count_departments,
                   const char *log_filename);