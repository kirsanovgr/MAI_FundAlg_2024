#include "ex10.h"

int main(int argc, char ** argv){
	if(checks_names_files(argc, argv)){
		return print_error(INCORRECT_OPTIONS_ERROR);
	}
	FILE * in = fopen(argv[1], "r");
	if(!in){
		return print_error(INPUT_FILE_ERROR);
	}
	FILE * out = fopen(argv[2], "w");
	if(!out){
		fclose(in);
		return print_error(OUTPUT_FILE_ERROR);
	}

	String expression;
	error_msg errorMsg = create_string(&expression, "");
	if(errorMsg){
		fclose(in);
		fclose(out);
		return print_error(errorMsg);
	}

	int n;
	Node *head;
	while ((n = read_line(in, &expression)) > 0){
		head = NULL;
		errorMsg = build_tree(&expression,  &head);
		if(errorMsg){
			return print_error(errorMsg);
		}
		print_tree(out, head, 0);
		destroy_tree(head);
		clear_string(&expression);
		fprintf(out, "------------------------------------------\n");
	}

	destroy_string(&expression);
	fclose(in);
	fclose(out);
}