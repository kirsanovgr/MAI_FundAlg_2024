#include "ex3.h"

error_msg computeLPSArray(const char *pat, int M, int *lps) {
	int j = 0;
	lps[0] = 0;
	int i = 1;
	while (i < M) {
		if (pat[i] == pat[j]) {
			j++;
			lps[i] = j;
			i++;
		} else {
			if (j != 0) {
				j = lps[j - 1];
			} else {
				lps[i] = 0;
				i++;
			}
		}
	}
	return NORMAL;
}

error_msg KMPSearch(char *substring, FILE *f, IntVector *vec) {
	int M = SizeString(substring);

	int lps[M];

	error_msg error = computeLPSArray(substring, M, lps);
	if(error) return error;
	int i = 0;
	int j = 0;
	char c = getc(f);
	while (!feof(f)) {
		//		printf("%c", c);
		if (substring[j] == c) {
			j++;
			i++;
			c = getc(f);
		}
		if (j == M) {
			error = push_end_intvector(vec, i - j);
			if (error) return error;
			j = lps[j - 1];
		} else if (!feof(f) && substring[j] != c) {
			if (j != 0) {
				j = lps[j - 1];
			} else {
				i = i + 1;
				c = getc(f);
			}
		}
	}
	return NORMAL;
}

error_msg print_result(StringVector *result, char *string, char *filename, IntVector *vec, FILE *f) {
	rewind(f);
	int i = 0, column = 1, row = 1, val;
	char c;
	error_msg error;
	for (int j = 0; j < size_intvector(vec); ++j) {
		error = get_intvector(vec, j, &val);
		if (error) return error;
		while (!feof(f)) {
			c = getc(f);
			if (c == '\n') {
				row++;
				column = 0;
			}
			++column;
			++i;
			if (i == val) break;
		}
		char msg[SizeString(string) + SizeString(filename) + 7 + 7];
		sprintf(msg, "%s%s    %d %d\n", string, filename, row, column);
		error = push_end_string_vector(result, msg);
		if(error){
			return error;
		}
	}
	return NORMAL;
}

error_msg FilesStrStr(int n, StringVector * result, char *string, ...) {
	error_msg error;
	va_list factor;
	va_start(factor, string);
	char *file_name;
	FILE *f;

	IntVector *pos = create_int_vector(1);
	if(!pos) return MEMORY_ALLOCATED_ERROR;
	for (int i = 0; i < n; ++i) {
		file_name = va_arg(factor, char *);
		f = fopen(file_name, "r");
		if (!f) {
			destroy_int_vector(pos);
			va_end(factor);
			return INPUT_FILE_ERROR;
		}
		error = KMPSearch(string, f, pos);
		if (error) {
			destroy_int_vector(pos);
			fclose(f);
			va_end(factor);
			return error;
		}
		error = print_result(result, "Find in:", file_name, pos, f);
		if (error) {
			destroy_int_vector(pos);
			fclose(f);
			va_end(factor);
			return error;
		}
		pos->size = 0;
		fclose(f);
	}
	va_end(factor);
	destroy_int_vector(pos);
	return NORMAL;
}