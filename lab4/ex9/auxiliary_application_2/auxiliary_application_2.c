#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib2/SystemErrors2/errors.h"
#include "../../lib2/vector/charvector.h"
#include "../application/application.h"

#define MAX_COUNT_FILES 50
#define MAX_COUNT_APPLICATIONS 100
#define MAX_LENGTH_TEXT 100

void generate_random_text(char* buffer) {
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	size_t charset_length = sizeof(charset) - 1;

	size_t length = 1 + rand() % MAX_LENGTH_TEXT;

	for (size_t i = 0; i < length; i++) {
		buffer[i] = charset[rand() % charset_length];
	}
	buffer[length] = '\0';
}

error_msg generate_file(const char* filename, size_t count_departments, size_t max_priority) {
	FILE* f = fopen(filename, "w");
	if (!f) {
		return (error_msg){OUTPUT_FILE_ERROR, "generate_file", "file didn't open"};
	}

	size_t dep, pr;
	size_t count_application = rand() % MAX_COUNT_APPLICATIONS + 1;
	for (size_t i = 0; i < count_application; ++i) {
		Time create = generate_random_time();
		dep = rand() % count_departments + 1;
		pr = rand() % max_priority + 1;

		char text[MAX_LENGTH_TEXT + 1];
		generate_random_text(text);

		print_time(f, &create);
		fprintf(f, " %zu %zu %s\n", pr, dep, text);
	}

	fclose(f);
	return (error_msg){SUCCESS, "", ""};
}

int main(int argc, char** argv) {
	if (argc != 3) {
		return print_error(
		    (error_msg){INCORRECT_OPTIONS_ERROR, "main", "must be 3 arg: max_priority and count_departments"});
	}
	char* pEnd;
	size_t max_priority = strtoul(argv[1], &pEnd, 10);
	size_t count_departments = strtoul(argv[2], &pEnd, 10);
	if (count_departments == 0 || count_departments > 100 || max_priority == 0) {
		return print_error(
		    (error_msg){INCORRECT_OPTIONS_ERROR, "main", "count departments [1, 100], max_priority [1;inf)"});
	}

	char default_filename[100] = "test_file_";
	char id_file[MAX_COUNT_FILES + 1];
	size_t count_files = rand() % MAX_COUNT_FILES + 1;
	printf("Generate files: %zu\n", count_files);
	error_msg errorMsg;
	for (size_t i = 0; i < count_files; ++i) {
		memset(id_file, '\0', MAX_COUNT_FILES + 1);
		default_filename[10] = '\0';

		u_long_to_s(i + 1, id_file);
		my_strcat(default_filename, id_file);

		errorMsg = generate_file(default_filename, count_departments, max_priority);
		if (errorMsg.type) {
			return print_error(errorMsg);
		}
	}
	return 0;
}