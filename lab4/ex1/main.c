#include "ex1.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		return print_error(INCORRECT_OPTIONS_ERROR);
	}
	FILE* stream = fopen(argv[1], "r");
	if (!stream) {
		return print_error(INPUT_FILE_ERROR);
	}


	// Создаем строку вывода
	String result;
	error_msg errorMsg = create_string(&result, "");
	if (errorMsg) {
		fclose(stream);
		return errorMsg;
	}
	errorMsg = read_instruction(stream, &result);
	if (errorMsg) {
		destroy_string(&result);
		return print_error(errorMsg);
	}
	fclose(stream);

	// Записываем
//	stream = fopen(argv[1], "w");
//	if(!stream){
//		destroy_string(&result);
//		return print_error(OUTPUT_FILE_ERROR);
//	}
//	fprintf(stream, "%s", result.arr);
//		fclose(stream);

	printf("%s", result.arr);

	destroy_string(&result);
	return 0;
}
