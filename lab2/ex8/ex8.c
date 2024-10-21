#include "ex8.h"


int sequence_number(char c) {
	if (c >= 'A' && c <= 'Z') c = 'a' + c - 'A';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	else if (c >= '0' && c <= '9')
		return c - '0';
	else
		return -1;
}

char back_sequence_number(int x) {
	if (x < 10) return x + '0';
	return 'a' + (x - 10);
}


void StringWithoutLeadingZeros(const char *a, char *b){
	int fl = 0, j = 0;
	for(int i = 0; a[i] != '\0';++i){
		if(a[i] != '0' || fl == 1){
			fl = 1;
			b[j++] = a[i];
		}
	}
	b[j] = '\0';
}


error_msg AdditionNumbers(char *a, char *b, char *result, int base) {
	int next = 0;
	CharVector *tmp = create_char_vector(1);
	if(!tmp){
		return MEMORY_ALLOCATED_ERROR;
	}
	error_msg error;
	// Меняем a и b, так чтобы a было больше по размеру
	if (SizeString(a) < SizeString(b)) {
		char *c = a;
		a = b;
		b = c;
	}
	int i = SizeString(a) - 1, j = SizeString(b) - 1;
	for (; j >= 0; --j) {
		if (sequence_number(a[i]) == -1 || sequence_number(b[j]) == -1 || sequence_number(a[i]) >= base ||
		    sequence_number(b[j]) >= base) {
			destroy_char_vector(tmp);
			return UNRECOGNIZED_CHARACTER_ERROR;
		}
		int f = sequence_number(a[i]) + sequence_number(b[j]) + next;
		error = push_end_charvector(tmp, back_sequence_number(f % base));
		if (error) {
			destroy_char_vector(tmp);
			return error;
		}
		next = f / base;
		--i;
	}
	for (; i >= 0; --i) {
		if (sequence_number(a[i]) == -1 || sequence_number(a[i]) >= base) return UNRECOGNIZED_CHARACTER_ERROR;
		int f = sequence_number(a[i]) + next;
		error = push_end_charvector(tmp, back_sequence_number(f % base));
		if (error) {
			destroy_char_vector(tmp);
			return error;
		}
		next = f / base;
	}
	while (next > 0) {
		error = push_end_charvector(tmp, back_sequence_number(next % base));
		if (error) {
			destroy_char_vector(tmp);
			return error;
		}
		next /= base;
	}
	char x;
	i = 0;
	for (int k = size_charvector(tmp) - 1; k >= 0; --k) {
		error = get_charvector(tmp, k, &x);
		if (error) {
			destroy_char_vector(tmp);
			return error;
		}
		result[i++] = x;
	}
	result[i] = '\0';
	destroy_char_vector(tmp);
	return SUCCESS;
}

int max(int a, int b){
	if(a > b) return a;
	return b;
}

error_msg AdditionManyNumbers(char * result, int base, int n, ...){
	if(base < 2 || base > 36) return NUMERAL_SYSTEM_ERROR;
	error_msg errorMsg;
	va_list factor;
	va_start(factor, n);
	char * first = va_arg(factor, char*), *tmp;
	int size = SizeString(first) + 11;
	char * last = (char*)malloc(sizeof(char) * (size));
	if(!last){
		va_end(factor);
		return MEMORY_ALLOCATED_ERROR;
	}
	strcopy(first, last, 0, SizeString(first));
	for(int i = 1; i < n;++i){
		char* second = va_arg(factor, char*);
		if(size <= max(SizeString(last), SizeString(second))){
			tmp = (char*)realloc(last, max(SizeString(last), SizeString(second)) * 2);
			if(!tmp){
				free(last);
				va_end(factor);
				return MEMORY_ALLOCATED_ERROR;
			}
			last = tmp;
			size = max(SizeString(last), SizeString(second)) * 2;
		}
		errorMsg = AdditionNumbers(last, second, last, base);
		if(errorMsg) {
			free(last);
			va_end(factor);
			return errorMsg;
		}
//		printf("%s\n", last);
	}
	StringWithoutLeadingZeros(last, result);
	free(last);
	return SUCCESS;
}
