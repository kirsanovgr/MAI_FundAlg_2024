#include "process_files.h"

int recognized_queue(String* s) {
	if (string_cmp(s->arr, "BinaryHeap")) {
		return 0;
	} else if (string_cmp(s->arr, "BinomialHeap")) {
		return 1;
	} else if (string_cmp(s->arr, "FibonacciHeap")) {
		return 2;
	} else if (string_cmp(s->arr, "SkewHeap")) {
		return 3;
	} else if (string_cmp(s->arr, "LeftistHeap")) {
		return 4;
	} else if (string_cmp(s->arr, "Treap")) {
		return 5;
	} else {
		return -1;
	}
}

int recognized_storage(String* s) {
	if (string_cmp(s->arr, "HashSet")) {
		return 0;
	} else if (string_cmp(s->arr, "DynamicArray")) {
		return 1;
	} else if (string_cmp(s->arr, "BinarySearchTree")) {
		return 2;
	} else if (string_cmp(s->arr, "Trie")) {
		return 3;
	} else {
		return -1;
	}
}

error_msg process_file_with_the_model_parameters_and_create_storage(const char* filename, DStorage* dataStorages,
                                                                    Time* time_begin, Time* time_end,
                                                                    size_t* min_minutes, size_t* max_minutes,
                                                                    double* overload_coefficient,
                                                                    size_t* count_departments) {
	int what_queue, what_storage;
	if (filename == NULL || dataStorages == NULL || time_begin == NULL || time_end == NULL || min_minutes == NULL ||
	    max_minutes == NULL || overload_coefficient == NULL || count_departments == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "process_file_with_the_model_parameters_and_create_storage",
		                   "get pointer to null"};
	}
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		return (error_msg){INPUT_FILE_ERROR, "process_file_with_the_model_parameters_and_create_storage",
		                   "file_with_the_model_parameters didn't open"};
	}

	String tmp;
	error_msg errorMsg = create_string(&tmp, "");
	if (errorMsg.type) {
		fclose(f);
		return errorMsg;
	}

	errorMsg = safe_read_string(f, &tmp);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}
	if ((what_queue = recognized_queue(&tmp)) == -1) {
		fclose(f);
		destroy_string(&tmp);
		return (error_msg){INCORRECT_OPTIONS_ERROR, "process_file_with_the_model_parameters_and_create_storage",
		                   "unrecognized queue"};
	}

	clear_string(&tmp);
	errorMsg = safe_read_string(f, &tmp);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}

	if ((what_storage = recognized_storage(&tmp)) == -1) {
		fclose(f);
		destroy_string(&tmp);
		return (error_msg){INCORRECT_OPTIONS_ERROR, "process_file_with_the_model_parameters_and_create_storage",
		                   "unrecognized queue"};
	}

	clear_string(&tmp);
	errorMsg = read_time(f, time_begin);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return (error_msg){INCORRECT_OPTIONS_ERROR, "process_file_with_the_model_parameters_and_create_storage",
		                   "read time"};
	}

	clear_string(&tmp);
	errorMsg = read_time(f, time_end);
	if (errorMsg.type || compare_time(time_begin, time_end) == 1) {
		fclose(f);
		destroy_string(&tmp);
		return (error_msg){INCORRECT_OPTIONS_ERROR, "process_file_with_the_model_parameters_and_create_storage",
		                   "read time"};
	}

	clear_string(&tmp);
	errorMsg = safe_read_string(f, &tmp);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}

	errorMsg = string_to_u_long(&tmp, min_minutes);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}

	clear_string(&tmp);
	errorMsg = safe_read_string(f, &tmp);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}

	errorMsg = string_to_u_long(&tmp, max_minutes);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}

	if (*max_minutes < *min_minutes || *min_minutes == 0) {
		fclose(f);
		destroy_string(&tmp);
		return (error_msg){INCORRECT_OPTIONS_ERROR, "process_file_with_the_model_parameters_and_create_storage",
		                   "max minutes < min minutes"};
	}

	clear_string(&tmp);
	errorMsg = safe_read_string(f, &tmp);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}

	errorMsg = string_to_u_long(&tmp, count_departments);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}

	if (*count_departments == 0 || *count_departments > 100) {
		fclose(f);
		destroy_string(&tmp);
		return (error_msg){INCORRECT_OPTIONS_ERROR, "process_file_with_the_model_parameters_and_create_storage",
		                   "count departments should be [1,100]"};
	}

	dataStorages->v = data_storages_functions[what_storage];
	errorMsg = dataStorages->v.create_storage(&(dataStorages->s), *count_departments);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}

	for (size_t i = 0; i < *count_departments; ++i) {
		size_t count_op;

		clear_string(&tmp);
		errorMsg = safe_read_string(f, &tmp);
		if (errorMsg.type) {
			fclose(f);
			destroy_string(&tmp);
			dataStorages->v.destroy_storage(&(dataStorages->s));
			return errorMsg;
		}

		errorMsg = string_to_u_long(&tmp, &count_op);
		if (errorMsg.type) {
			fclose(f);
			destroy_string(&tmp);
			dataStorages->v.destroy_storage(&(dataStorages->s));
			return errorMsg;
		}
		if (count_op < 10 || count_op > 50) {
			fclose(f);
			destroy_string(&tmp);
			dataStorages->v.destroy_storage(&(dataStorages->s));
			return (error_msg){INCORRECT_OPTIONS_ERROR, "process_file_with_the_model_parameters_and_create_storage",
			                   "count operators should be [10,50]"};
		}

		errorMsg = dataStorages->v.push_into_storage(&(dataStorages->s), i + 1, count_op, (char)what_queue);
		if (errorMsg.type) {
			fclose(f);
			destroy_string(&tmp);
			dataStorages->v.destroy_storage(&(dataStorages->s));
			return errorMsg;
		}
	}
	clear_string(&tmp);
	errorMsg = safe_read_string(f, &tmp);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		return errorMsg;
	}

	errorMsg = string_to_double(&tmp, overload_coefficient);
	if (errorMsg.type) {
		fclose(f);
		destroy_string(&tmp);
		dataStorages->v.destroy_storage(&(dataStorages->s));
		return errorMsg;
	}

	if ((*overload_coefficient) - 1 <= 1e-20) {
		fclose(f);
		destroy_string(&tmp);
		dataStorages->v.destroy_storage(&(dataStorages->s));
		return (error_msg){INCORRECT_OPTIONS_ERROR, "process_file_with_the_model_parameters_and_create_storage",
		                   "incorrect overload coefficient"};
	}

	fclose(f);
	destroy_string(&tmp);
	return (error_msg){SUCCESS, "", ""};
}

error_msg process_file_with_applications(const char* filename, Application*** applications, size_t* size,
                                         size_t* capacity, size_t max_priority, size_t count_departments,
                                         const Time* time_start, const Time* time_end) {
	static size_t id_application = 0;

	if (filename == NULL || applications == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "process_file_with_applications", "get pointer to null"};
	}

	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		return (error_msg){INPUT_FILE_ERROR, "process_file_with_applications", "input file didn't open"};
	}

	String tmp;
	error_msg errorMsg = create_string(&tmp, "");
	if (errorMsg.type) {
		fclose(f);
		return errorMsg;
	}

	Application** tmp_mas = *applications;
	if (tmp_mas == NULL) {
		if (*capacity < 10) {
			*capacity = 10;
		}
		tmp_mas = (Application**)calloc(*capacity, sizeof(Application*));
		if (tmp_mas == NULL) {
			fclose(f);
			destroy_string(&tmp);
			*applications = tmp_mas;
			return (error_msg){MEMORY_ALLOCATED_ERROR, "process_file_with_applications", "memory allocated"};
		}
		*size = 0;
	}

	Time t;
	size_t priority;
	size_t id;

	while (!feof(f)) {
		clear_string(&tmp);
		if (*size >= *capacity) {
			Application** tt = (Application**)realloc(tmp_mas, (*capacity) * 2 * sizeof(Application*));
			if (tt == NULL) {
				fclose(f);
				destroy_string(&tmp);
				for (size_t i = 0; i < *size; ++i) {
					destroy_application(tmp_mas[i]);
				}
				free(tmp_mas);
				return (error_msg){MEMORY_ALLOCATED_ERROR, "process_file_with_applications", "memory allocated"};
			}
			(*capacity) *= 2;
			tmp_mas = tt;
		}

		errorMsg = read_time(f, &t);
		if (feof(f)) {
			break;
		}
		if (errorMsg.type) {
			fclose(f);
			destroy_string(&tmp);
			for (size_t i = 0; i < *size; ++i) {
				destroy_application(tmp_mas[i]);
			}
			free(tmp_mas);
			return errorMsg;
		}
		clear_string(&tmp);

		errorMsg = safe_read_string(f, &tmp);
		if (errorMsg.type) {
			fclose(f);
			destroy_string(&tmp);
			for (size_t i = 0; i < *size; ++i) {
				destroy_application(tmp_mas[i]);
			}
			free(tmp_mas);
			return errorMsg;
		}
		strip(&tmp);

		errorMsg = string_to_u_long(&tmp, &priority);
		if (errorMsg.type) {
			fclose(f);
			destroy_string(&tmp);
			for (size_t i = 0; i < *size; ++i) {
				destroy_application(tmp_mas[i]);
			}
			free(tmp_mas);
			return errorMsg;
		}
		clear_string(&tmp);

		errorMsg = safe_read_string(f, &tmp);
		if (errorMsg.type) {
			fclose(f);
			destroy_string(&tmp);
			for (size_t i = 0; i < *size; ++i) {
				destroy_application(tmp_mas[i]);
			}
			free(tmp_mas);
			return errorMsg;
		}
		strip(&tmp);

		errorMsg = string_to_u_long(&tmp, &id);
		if (errorMsg.type) {
			fclose(f);
			destroy_string(&tmp);
			for (size_t i = 0; i < *size; ++i) {
				destroy_application(tmp_mas[i]);
			}
			free(tmp_mas);
			return errorMsg;
		}

		if (priority > max_priority || id > count_departments) {
			fclose(f);
			destroy_string(&tmp);
			for (size_t i = 0; i < *size; ++i) {
				destroy_application(tmp_mas[i]);
			}
			free(tmp_mas);
			return (error_msg){INCORRECT_OPTIONS_ERROR, "process_file_with_applications",
			                   "id > count departments or priority > max_priority"};
		}

		clear_string(&tmp);
		errorMsg = safe_read_string(f, &tmp);
		if (errorMsg.type) {
			fclose(f);
			destroy_string(&tmp);
			for (size_t i = 0; i < *size; ++i) {
				destroy_application(tmp_mas[i]);
			}
			free(tmp_mas);
			return errorMsg;
		}
		strip(&tmp);

		if (compare_time(time_start, &t) == -1 && compare_time(&t, time_end) == -1) {
			errorMsg = create_application(&(tmp_mas[*size]), t, priority, id, &tmp, id_application);
			if (errorMsg.type) {
				fclose(f);
				destroy_string(&tmp);
				for (size_t i = 0; i < *size; ++i) {
					destroy_application(tmp_mas[i]);
				}
				free(tmp_mas);
				return errorMsg;
			}
			id_application += 1;
			(*size) += 1;
		}
	}

	*applications = tmp_mas;
	destroy_string(&tmp);
	fclose(f);
	return (error_msg){SUCCESS, "", ""};
}

int compare_application_by_time(const void* a, const void* b) {
	Application* a1 = *((Application**)a);
	Application* b1 = *((Application**)b);
	return compare_time(&(a1->time_create), &(b1->time_create));
}

error_msg process_files_with_applications(const char** filenames, int count_files, Application*** mas, size_t* size,
                                          size_t* capacity, size_t count_departments, const Time* time_start,
                                          const Time* time_end, size_t max_priority) {
	if (filenames == NULL || mas == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "process_files_with_applications", "get pointer to null"};
	}
	error_msg errorMsg;
	for (int i = 0; i < count_files; ++i) {
		errorMsg = process_file_with_applications(filenames[i], mas, size, capacity, max_priority, count_departments,
		                                          time_start, time_end);
		if (errorMsg.type) {
			return errorMsg;
		}
	}

	qsort(*mas, *size, sizeof(Application*), compare_application_by_time);
	return (error_msg){SUCCESS, "", ""};
}