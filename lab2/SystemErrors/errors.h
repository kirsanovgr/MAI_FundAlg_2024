
#ifndef LAB2_ERRORS_H
#define LAB2_ERRORS_H

#include <stdio.h>


typedef enum error_msg{
    SUCCESS,
    INPUT_FILE_ERROR,
    OUTPUT_FILE_ERROR,
    MEMORY_ALLOCATED_ERROR,
    INDEX_VECTOR_ERROR,
    OVERFLOW_ERROR,
    INCORRECT_OPTIONS_ERROR,
    UNRECOGNIZED_CHARACTER_ERROR,
	NUMERAL_SYSTEM_ERROR
} error_msg;

int print_error(error_msg error);


#endif
