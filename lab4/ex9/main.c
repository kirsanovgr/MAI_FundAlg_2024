#include "main_files/main-stage.h"

int main(int argc, char** argv) {
	if (argc <= 3) {
		return print_error((error_msg){INCORRECT_OPTIONS_ERROR, "main", "incorrect count args"});
	}

	srand(time(0));

	Time t1, t2;
	double overload_coefficient;
	size_t min_minutes, max_minutes;
	DStorage storage;
	size_t count_departments;
	size_t max_priority;
	size_t size_mas_applications = 0, capacity_mas_applications = 10;
	Application** mas_applications = NULL;

	error_msg errorMsg = preparing(argc, argv, &storage, &t1, &t2, &min_minutes, &max_minutes, &count_departments,
	                               &overload_coefficient, &max_priority, &size_mas_applications, &capacity_mas_applications, &mas_applications);
	if (errorMsg.type) {
		return print_error(errorMsg);
	}

	errorMsg = modeling(&storage, mas_applications, size_mas_applications, &t1, &t2, min_minutes, max_minutes, overload_coefficient, count_departments,
	                    NAME_LOG_FILE);
	if(errorMsg.type){
		storage.v.destroy_storage(&(storage.s));
		return print_error(errorMsg);
	}

	free(mas_applications);
	storage.v.destroy_storage(&(storage.s));
	return 0;
}