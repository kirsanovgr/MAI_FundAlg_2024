#include "mstring.h"


error_msg str_to_k(const char **string, char *separator, char *result) {
	error_msg error;
	int len_string = SizeString(*string);
	int len_separator = SizeString(separator);
	char b[len_separator + 1];
	if (len_string == 0) {
		result = NULL;
		return SUCCESS;
	}
	for (int i = 0; i < len_string; ++i) {
		//        printf("%s\n", *string);
		error = strcopy(*string, b, 0, len_separator);
		if (error) return error;
		if (string_cmp(b, separator)) {
			result[i] = '\0';
			*string += len_separator;
			break;
		}
		if (len_separator == SizeString(*string)) {
			result[i] = '\0';
			error = my_strcat(result, *string);
			if (error) return error;
			*string = "\0";
			break;
		}
		result[i] = **string;
		*string += 1;
	}
	return SUCCESS;
}

error_msg my_strcat(char *a, const char *b) {
	int i = SizeString(a);
	for (int j = 0; j < SizeString(b); ++i, ++j) {
		a[i] = b[j];
	}
	a[i] = '\0';
	return SUCCESS;
}

int string_cmp(const char *a, const char *b) {
	int i;
	for (i = 0; a[i] != '\0' && b[i] != '\0'; ++i) {
		if (a[i] != b[i]) return 0;
	}
	if (a[i] != b[i]) return 0;
	return 1;
}

error_msg strcopy(const char *a, char *result, int start, int end) {
	int i = 0;
	int end_for = end - start;
	if (start > 0) end_for++;
	for (; i < end_for && i + start < SizeString(a); ++i) {
		result[i] = a[i + start];
	}
	result[i] = '\0';
	return SUCCESS;
}

int SizeString(const char *a) {
	int i = 0;
	for (; a[i] != '\0'; ++i)
		;
	return i;
}

int string_compare(const char *s1, const char*s2){
	int i = 0;
	for(; s1[i] && s2[i]; ++i){
		if(s1[i] - s2[i] != 0) return s1[i] - s2[i];
	}
	return s1[i] - s2[i];
}


int strtoint(const char * a){
	int sum = 0;
	while (*a){
		sum *= 10 + (*a - '0');
		a++;
	}
	return sum;
}