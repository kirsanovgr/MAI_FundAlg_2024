#include "errors.h"

int print_error(error_msg error) {
	if (error.type) {
		fprintf(stderr, "Error - %s: %s\n", error.func, error.msg);
		return error.type;
	}
	return 0;
}