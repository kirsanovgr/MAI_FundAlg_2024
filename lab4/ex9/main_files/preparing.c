#include "preparing.h"

error_msg preparing(int argc, char** argv, DStorage* storages, Time* begin, Time* end, size_t* min_minutes,
                    size_t* max_minutes, size_t* count_departments, double* overload_coefficient, size_t* max_priority,
                    size_t* size_mas, size_t* capacity_mas, Application*** mas) {
	error_msg errorMsg = process_file_with_the_model_parameters_and_create_storage(
	    argv[2], storages, begin, end, min_minutes, max_minutes, overload_coefficient, count_departments);
	if (errorMsg.type) {
		return errorMsg;
	}
	const char** filenames = (const char**)&(argv[3]);
	int count_files = argc - 3;

	String s;
	create_string(&s, argv[1]);
	errorMsg = string_to_u_long(&s, max_priority);
	if (errorMsg.type) {
		return errorMsg;
	}
	destroy_string(&s);

	errorMsg = process_files_with_applications(filenames, count_files, mas, size_mas, capacity_mas, *count_departments,
	                                           begin, end, *max_priority);
	if (errorMsg.type) {
		storages->v.destroy_storage(&(storages->s));
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}