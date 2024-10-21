#include "ex9.h"

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

error_msg prime_factors(int n, IntVector * factors) {
	error_msg errorMsg;
	while (n % 2 == 0) {
		errorMsg = push_end_intvector(factors, 2);
		if(errorMsg) return errorMsg;
		n = n / 2;
	}
	for (int i = 3; i <= sqrt(n); i += 2) {
		while (n % i == 0) {
			errorMsg = push_end_intvector(factors, i);
			if(errorMsg) return errorMsg;
			n = n / i;
		}
	}
	if (n > 2) {
		errorMsg = push_end_intvector(factors, n);
		if(errorMsg) return errorMsg;
	}
	return SUCCESS;
}


error_msg has_finite_representation(double fraction, int base, int* fl) {
	error_msg errorMsg;
	int denominator = 10;
	if(fraction >= 1 || fraction <= 0) return INCORRECT_OPTIONS_ERROR;

	IntVector * factors = create_int_vector(1);
	if(!factors) return MEMORY_ALLOCATED_ERROR;
	errorMsg = prime_factors(denominator, factors);
	if(errorMsg) {
		destroy_int_vector(factors);
		return errorMsg;
	}

	IntVector * base_factors = create_int_vector(1);
	if(!base_factors) {
		destroy_int_vector(factors);
		return MEMORY_ALLOCATED_ERROR;
	}
	errorMsg = prime_factors(base, base_factors);
	if(errorMsg) {
		destroy_int_vector(factors);
		destroy_int_vector(base_factors);
		return errorMsg;
	}
	int x, y;
	for (int i = 0; i < size_intvector(factors); i++) {
		int found = 0;
		for (int j = 0; j < size_intvector(base_factors); j++) {
			errorMsg = get_intvector(factors, i, &x);
			if(errorMsg){
				destroy_int_vector(factors);
				destroy_int_vector(base_factors);
				return errorMsg;
			}
			errorMsg = get_intvector(base_factors, j, &y);
			if(errorMsg){
				destroy_int_vector(factors);
				destroy_int_vector(base_factors);
				return errorMsg;
			}
			if (x == y) {
				found = 1;
				break;
			}
		}
		if(!found){
			*fl = 0;
			destroy_int_vector(factors);
			destroy_int_vector(base_factors);
			return SUCCESS;
		}
	}
	*fl = 1;
	destroy_int_vector(factors);
	destroy_int_vector(base_factors);
	return SUCCESS;
}




error_msg AreCorrectFractions(StringVector * vec, int base, int n, ...){
	if(base < 2 || base > 36) return NUMERAL_SYSTEM_ERROR;
	va_list factor;
	va_start(factor, n);
	int fl;
	error_msg errorMsg;
	vec->size = 0;
	for(int i = 0; i < n; ++i){
		double x = va_arg(factor, double);
		errorMsg = has_finite_representation(x, base, &fl);
		if(errorMsg){
			va_end(factor);
			return errorMsg;
		}
		if(fl){
			char msg[100];
			sprintf(msg,"Fraction %f has finite representation in base %d", x, base);
			errorMsg = push_end_string_vector(vec, msg);
			if(errorMsg){
				va_end(factor);
				return errorMsg;
			}
		}
		else{
			char msg[100];
			sprintf(msg,"Fraction %f hasn't finite representation in base %d", x, base);
			errorMsg = push_end_string_vector(vec, msg);
			if(errorMsg){
				va_end(factor);
				return errorMsg;
			}
		}
	}
	va_end(factor);
	return SUCCESS;
}