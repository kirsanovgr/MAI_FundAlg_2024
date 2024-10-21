#include "ex1.h"

int main(int argc, char **argv) {
	error_msg error;
	kOpts opt;

	error = GetOpts(argc, argv, &opt);
	if(error) return print_error(error);
	char * new_string;
	int size;
	switch (opt) {
		case 0:
			error = HandlerOptL(argv, &size);
			if(error) return print_error(error);
			printf("%d\n", size);
			break;
		case 1:
			error = HandlerOptR(argv, &new_string);
			if(error) {
				free(new_string);
				return print_error(error);
			}
			printf("%s\n", new_string);
			free(new_string);
			break;
		case 2:
			error = HandlerOptU(argv, &new_string);
			if(error) {
				free(new_string);
				return print_error(error);
			}
			printf("%s\n", new_string);
			free(new_string);
			break;
		case 3:
			error = HandlerOptN(argv, &new_string);
			if(error) {
				free(new_string);
				return print_error(error);
			}
			printf("%s\n", new_string);
			free(new_string);
			break;
		case 4:
			error = HandlerOptC(argc, argv, &new_string);
			if(error) {
				free(new_string);
				return print_error(error);
			}
			printf("%s\n", new_string);
			free(new_string);
			break;
	}


	return 0;
}