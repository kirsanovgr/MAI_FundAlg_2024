#include "errors.h"


int print_error(error_msg error){
    switch (error) {
        case INPUT_FILE_ERROR:
            printf("Input file didnt open\n");
            return 1;
        case OUTPUT_FILE_ERROR:
            printf("Output file didnt open\n");
            return 2;
        case MEMORY_ALLOCATED_ERROR:
            printf("Memory allocated\n");
            return 3;
        case INDEX_VECTOR_ERROR:
            printf("Handling outside the array index\n");
            return 4;
        case OVERFLOW_ERROR:
            printf("Overflow error\n");
            return 5;
        case INCORRECT_OPTIONS_ERROR:
            printf("Incorrect options\n");
            return 6;
        case UNRECOGNIZED_CHARACTER_ERROR:
            printf("Unrecognized character\n");
            return 7;
		case NUMERAL_SYSTEM_ERROR:
			printf("This numeral system doesn't exist\n");
			return 8;
        default:
            return 0;
    }
}