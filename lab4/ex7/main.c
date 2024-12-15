#include "ex7.h"

int main(int argc, char** argv){
	if(argc != 2){
		return print_error((error_msg){INCORRECT_OPTIONS_ERROR, "main", "incorrect count args"});
	}

	ArrayOfMemoryCell array;
	error_msg errorMsg = create_array_memory_cells(&array);
	if(errorMsg.type){
		return print_error(errorMsg);
	}

	FILE * stream = fopen(argv[1], "r");
	if(!stream){
		destroy_array_memory_cells(&array);
		return print_error((error_msg){INPUT_FILE_ERROR, "main", "input file didn't open"});	}


	errorMsg = processing_file(stream, &array);
	if(errorMsg.type){
		fclose(stream);
		destroy_array_memory_cells(&array);
		return print_error(errorMsg);
	}


	fclose(stream);
	destroy_array_memory_cells(&array);
	return 0;
}