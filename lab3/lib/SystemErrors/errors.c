#include "errors.h"


int print_error(error_msg error){
    switch (error) {
        case INPUT_FILE_ERROR:
            fprintf(stderr, "Input file didnt open\n");
            return 1;
        case OUTPUT_FILE_ERROR:
			fprintf(stderr, "Output file didnt open\n");
            return 2;
        case MEMORY_ALLOCATED_ERROR:
			fprintf(stderr, "Memory allocated\n");
            return 3;
        case INDEX_VECTOR_ERROR:
			fprintf(stderr, "Handling outside the array index\n");
            return 4;
        case OVERFLOW_ERROR:
			fprintf(stderr, "Overflow error\n");
            return 5;
        case INCORRECT_OPTIONS_ERROR:
			fprintf(stderr, "Incorrect options\n");
            return 6;
        case UNRECOGNIZED_CHARACTER_ERROR:
			fprintf(stderr, "Unrecognized character\n");
            return 7;
		case NUMERAL_SYSTEM_ERROR:
			fprintf(stderr, "This numeral system doesn't exist\n");
			return 8;
        default:
            return 0;
    }
}