#include "main-stage.h"

void operator_free(Operator *operator) {
	operator->is_busy = 0;
	operator->processing_time_in_minutes = 0;
	destroy_application(operator->application);
	operator->application = NULL;
}

void operator_busy(Operator **operator, Application * application, Time *now, size_t mn, size_t mx) {
	Operator *tmp = *operator;
	tmp->is_busy = 1;
	tmp->application = application;
	tmp->processing_time_in_minutes = rand() % (mx - mn + 1) + mn;
	tmp->end_time = add_minutes(*now, tmp->processing_time_in_minutes);
	*operator= tmp;
}

error_msg find_most_free_department(DStorage *storage, size_t count_departments, Departament **res) {
	Departament *f;
	size_t min = 100000;
	for (size_t i = 1; i <= count_departments; ++i) {
		error_msg errorMsg = storage->v.get_storage(&(storage->s), i, &f);
		if (errorMsg.type) {
			return errorMsg;
		}
		if (min > f->count_employed_operators) {
			min = f->count_employed_operators;
			*res = f;
		}
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg modeling(DStorage *storage, Application **mas_applications, size_t size_mas, Time *time_begin, Time *time_end,
                   size_t min_minutes, size_t max_minutes, double overload_coefficient, size_t count_departments, const char *log_filename) {
	if (mas_applications == NULL || time_begin == NULL || time_end == NULL || storage == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "modeling", "get pointer to null"};
	}

	FILE *log_file = (FILE *)fopen(log_filename, "w");
	if (log_file == NULL) {
		return (error_msg){OUTPUT_FILE_ERROR, "modeling", "log file didn't open"};
	}

	Time now = *time_begin;
	size_t index_mas = 0;
	error_msg errorMsg;
	Departament *departament;

	// Основный цикл
	while (compare_time(&now, time_end) != 1) {
		// Проходим по всем операторам и обрабатываем
		for (size_t j = 1; j <= count_departments; ++j) {
			// Получили департамент по индексу
			errorMsg = storage->v.get_storage(&(storage->s), j, &departament);
			if (errorMsg.type) {
				for (size_t i = index_mas + 1; i < size_mas; ++i) {
					destroy_application(mas_applications[i]);
				}
				free(mas_applications);
				fclose(log_file);
				return errorMsg;
			}
			// Проходим всех операторов и смотрим какие закончили свою деятельность
			for (size_t k = 0; k < departament->count_operators; ++k) {
				if (departament->operators[k]->is_busy &&
				    compare_time(&(departament->operators[k]->end_time), &now) == 0) {
					print_handling_finished(log_file, departament->operators[k], &now);
					operator_free(departament->operators[k]);
					departament->count_employed_operators -= 1;
				}
			}
		}
		// Получаем новые заявки и добавляем их в очередь
		while (index_mas < size_mas && compare_time(&(mas_applications[index_mas]->time_create), &now) == 0) {
			errorMsg = storage->v.get_storage(&(storage->s), mas_applications[index_mas]->id_department, &departament);
			if (errorMsg.type) {
				for (size_t i = index_mas + 1; i < size_mas; ++i) {
					destroy_application(mas_applications[i]);
				}
				free(mas_applications);
				fclose(log_file);
				return errorMsg;
			}

			print_new_request(log_file, mas_applications[index_mas]);
			errorMsg = departament->queue.v.insert_heap(departament->queue.q, mas_applications[index_mas]);
			if (errorMsg.type) {
				for (size_t i = index_mas + 1; i < size_mas; ++i) {
					destroy_application(mas_applications[i]);
				}
				free(mas_applications);
				fclose(log_file);
				return errorMsg;
			}
			// TODO Проверка на переполнение
			if ((double)departament->queue.v.get_size(departament->queue.q) / (double)departament->count_operators >=
			    overload_coefficient) {
				Departament *most_free_department;
				// Находим наиболее свободную кучу
				errorMsg = find_most_free_department(storage, count_departments, &most_free_department);
				if (errorMsg.type) {
					for (size_t i = index_mas + 1; i < size_mas; ++i) {
						destroy_application(mas_applications[i]);
					}
					free(mas_applications);
					fclose(log_file);
					return errorMsg;
				}
				Queue res;
				// Сливаем наиболее свободную и нашу
				errorMsg = most_free_department->queue.v.merge_heap_without_destroy(most_free_department->queue.q,
				                                                                    departament->queue.q, &(res.q));
				if (errorMsg.type) {
					for (size_t i = index_mas + 1; i < size_mas; ++i) {
						destroy_application(mas_applications[i]);
					}
					free(mas_applications);
					fclose(log_file);
					return errorMsg;
				}
				// Очищаем нашу и создаем заново
				departament->queue.v.destroy_heap(departament->queue.q);
				errorMsg = departament->queue.v.create_heap(&(departament->queue.q));
				if (errorMsg.type) {
					for (size_t i = index_mas + 1; i < size_mas; ++i) {
						destroy_application(mas_applications[i]);
					}
					free(mas_applications);
					fclose(log_file);
					return errorMsg;
				}
				// Очищаем наиболее свободную и помещаем туда указатель на новую
				most_free_department->queue.v.destroy_heap(most_free_department->queue.q);
				most_free_department->queue = res;

				print_overloaded(log_file, mas_applications[index_mas]->id_application, most_free_department->id, &now);
			}
			index_mas++;
		}

		// Обрабатываем отправление заявок операторам
		for (size_t j = 1; j <= count_departments; ++j) {
			// Получили департамент по индексу
			errorMsg = storage->v.get_storage(&(storage->s), j, &departament);
			if (errorMsg.type) {
				for (size_t i = index_mas + 1; i < size_mas; ++i) {
					destroy_application(mas_applications[i]);
				}
				free(mas_applications);
				fclose(log_file);
				return errorMsg;
			}
			// Пока у нас в куче не закончились заявки и количество занятых операторов не равно общему их количеству
			while (departament->queue.v.is_empty(departament->queue.q) == 0 &&
			       departament->count_employed_operators != departament->count_operators) {
				Application *tmp;
				errorMsg = departament->queue.v.delete_heap(departament->queue.q, &tmp);
				if (errorMsg.type) {
					for (size_t i = index_mas + 1; i < size_mas; ++i) {
						destroy_application(mas_applications[i]);
					}
					free(mas_applications);
					fclose(log_file);
					return errorMsg;
				}
				for (size_t k = 0; k < departament->count_operators; ++k) {
					if (!(departament->operators[k]->is_busy)) {
						operator_busy(&(departament->operators[k]), tmp, &now, min_minutes, max_minutes);
						departament->count_employed_operators += 1;
						print_handling_started(log_file, departament->operators[k], &now);
						break;
					}
				}
			}
		}

		now = add_minutes(now, 1);
	}

	fclose(log_file);
	return (error_msg){SUCCESS, "", ""};
}

error_msg print_new_request(FILE *file, Application *application) {
	if (file == NULL || application == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "print_new_request", "get pointer to null"};
	}
	fprintf(file, "[");
	print_time(file, &(application->time_create));
	fprintf(file, "][NEW_REQUEST]: %zu %zu\n", application->id_application, application->id_department);
	return (error_msg){SUCCESS, "", ""};
}

error_msg print_handling_finished(FILE *file, Operator *operator, Time * now) {
	if (file == NULL || operator== NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "print_handling_finished", "get pointer to null"};
	}
	fprintf(file, "[");
	print_time(file, now);
	fprintf(file, "][REQUEST_HANDLING_FINISHED]: %zu %zu %s\n",
	              operator->application->id_application, operator->processing_time_in_minutes, operator->name.arr);
	return (error_msg){SUCCESS, "", ""};
}

error_msg print_handling_started(FILE *file, Operator *operator, Time * now) {
	if (file == NULL || operator== NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "print_handling_started", "get pointer to null"};
	}
	fprintf(file, "[");
	print_time(file, now);
	fprintf(file, "][REQUEST_HANDLING_STARTED]: %zu %s\n", operator->application->id_application, operator->name.arr);
	return (error_msg){SUCCESS, "", ""};
}

error_msg print_overloaded(FILE *file, size_t id_app, size_t new_id_departament, Time *now) {
	if (file == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "print_handling_started", "get pointer to null"};
	}

	fprintf(file, "[");
	print_time(file, now);
	fprintf(file, "][DEPARTMENT_OVERLOADED]: %zu %zu\n", id_app, new_id_departament);
	return (error_msg){SUCCESS, "", ""};
}