#include "ex2.h"


int main(int argc, char ** argv){
	if(argc != 2){
		return print_error(INCORRECT_OPTIONS_ERROR);
	}
	IntVector * arrays[26];
	memset(arrays, 0, sizeof(arrays));

	String s;
	create_string(&s, argv[1]);
	error_msg errorMsg = read_instructions(arrays, &s);
	if(errorMsg){
		destroy_arrays(arrays);
		destroy_string(&s);
		return print_error(errorMsg);
	}


	destroy_arrays(arrays);
	destroy_string(&s);
	return 0;
}


