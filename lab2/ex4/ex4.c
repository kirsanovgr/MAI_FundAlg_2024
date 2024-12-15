#include "ex4.h"

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

double cross_product(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }

int IsConvexPolygon(int n, ...) {
	va_list factor;
	va_start(factor, n);
	Point p[n];
	if(n <= 2 ) return 1;
	//	Считываем
	for (int i = 0; i < n; ++i) {
		p[i] = va_arg(factor, Point);
	}
	va_end(factor);
	int sign = 0;
	for (int i = 0; i < n; ++i) {
		double cp = cross_product(p[i], p[(i + 1) % n], p[(i + 2) % n]);
		if (!sign) sign = (cp > 0) ? 1 : -1;
		if (cp * sign <= 0) {
			return 0;
		}
	}
	return 1;
}

double ValueOfPolynomial(double x, int n, ...) {
	va_list factor;
	va_start(factor, n);
	double value = 0, coefficient = 0;
	for (int i = 0; i < n; ++i) {
		coefficient = va_arg(factor, double);
		value = value * x + coefficient;
	}
	va_end(factor);
	return value;
}

error_msg ProductNumbers(char *a, char *b, char *result, int base) {
	error_msg error;

	if (base < 2 || base > 36) return NUMERAL_SYSTEM_ERROR;
	int len1 = SizeString(a);
	int len2 = SizeString(b);
	CharVector *tmp = create_char_vector(1);
	if (!tmp) return MEMORY_ALLOCATED_ERROR;
	int k = 0;
	int x = 0;
	int next = 0;
	int index_tmp = 0;
	for (int i = len1 - 1; i >= 0; --i) {
		next = 0;
		index_tmp = k;
		for (int j = len2 - 1; j >= 0; --j) {
			if (sequence_number(a[i]) == -1 || sequence_number(b[j]) == -1 || sequence_number(a[i]) >= base ||
			    sequence_number(b[j]) >= base) {
				destroy_char_vector(tmp);
				return UNRECOGNIZED_CHARACTER_ERROR;
			}

			x = sequence_number(a[i]) * sequence_number(b[j]) + next;
			if (index_tmp < size_charvector(tmp)) {
				char value;
				error = get_charvector(tmp, index_tmp, &value);
				if (error) {
					destroy_char_vector(tmp);
					return error;
				}
				error = at_charvector(tmp, index_tmp, back_sequence_number((x + sequence_number(value)) % base));
				if (error) {
					destroy_char_vector(tmp);
					return error;
				}
				next = (x + sequence_number(value)) / base;
			} else {
				error = push_end_charvector(tmp, back_sequence_number(x % base));
				if (error) {
					destroy_char_vector(tmp);
					return error;
				}
				next = x / base;
			}
			++index_tmp;
		}
		while (next > 0) {
			if (index_tmp < size_charvector(tmp)) {
				char value;
				error = get_charvector(tmp, index_tmp, &value);
				if (error) {
					destroy_char_vector(tmp);
					return error;
				}
				error = at_charvector(tmp, index_tmp, back_sequence_number((next + (value - '0')) % base));
				if (error) {
					destroy_char_vector(tmp);
					return error;
				}
			} else {
				error = push_end_charvector(tmp, back_sequence_number(next % base));
				if (error) {
					destroy_char_vector(tmp);
					return error;
				}
			}
			++index_tmp;
			next /= base;
		}
		++k;
	}
	int j = 0;
	for (int i = size_charvector(tmp) - 1; i >= 0; --i, ++j) {
		char c;
		error = get_charvector(tmp, i, &c);
		if (error) {
			destroy_char_vector(tmp);
			return error;
		}
		result[j] = c;
	}
	result[j] = '\0';
	destroy_char_vector(tmp);
	return SUCCESS;
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

int strcmpInOurCase(char *a, char *b){
	int i;
	for (i = 0; a[i] != '\0' && b[i] != '\0'; ++i) {
		if (sequence_number(a[i]) != sequence_number(b[i]) || sequence_number(b[i]) == -1) return 0;
	}
	if (a[i] != b[i]) return 0;
	return 1;
}

void StringWithoutLeadingZeros(const char *a, char *b){
	int fl = 0;
	int j = 0;
	for(int i = 0; a[i] != '\0';++i){
		if(a[i] != '0' || fl == 1){
			fl = 1;
			b[j++] = a[i];
		}
	}
	b[j] = '\0';
}


error_msg FindNumbersKarper(StringVector *vec, int base, int n, ...) {
	vec->size = 0;
	if (base < 2 || base > 36) return NUMERAL_SYSTEM_ERROR;
	char * number;
	va_list factor;
	va_start(factor, n);
	int middle;
	error_msg error;
	for (int i = 0; i < n; ++i) {
		number = va_arg(factor, char *);
		char tmp[SizeString(number)];
		StringWithoutLeadingZeros(number, tmp);
		char tmp2[SizeString(tmp) * 2];

		error = ProductNumbers(tmp, tmp, tmp2, base);
		if (error) {
			va_end(factor);
			return error;
		}

		middle = SizeString(tmp2) / 2;
		if (SizeString(tmp2) % 2 == 0) {
			char left_half[middle], right_half[middle];
			error = strcopy(tmp2, left_half, 0, middle);
			if (error) {
				va_end(factor);
				return error;
			}
			error = strcopy(tmp2, right_half, middle, SizeString(tmp2));
			if (error) {
				va_end(factor);
				return error;
			}
			char addition_half[SizeString(tmp2)];
			error = AdditionNumbers(left_half, right_half, addition_half, base);
			if (error) {
				va_end(factor);
				return error;
			}
			if (strcmpInOurCase(tmp, addition_half)) {
				error = push_end_string_vector(vec, tmp);
				if (error) {
					va_end(factor);
					return error;
				}
			}
//			printf("%s %s %s %s %s\n", tmp, tmp2, left_half, right_half, addition_half);
		} else {
			char left_half[middle + 1], right_half[middle + 1];
			error = strcopy(tmp2, left_half, 0, middle + 1);
			if (error) {
				va_end(factor);
				return error;
			}
			error = strcopy(tmp2, right_half, middle + 1, SizeString(tmp2));
			if (error) {
				va_end(factor);
				return error;
			}
			char addition_half[SizeString(tmp2)];
			error = AdditionNumbers(left_half, right_half, addition_half, base);
			if (error) {
				va_end(factor);
				return error;
			}
			if (strcmpInOurCase(tmp, addition_half)) {
				error = push_end_string_vector(vec, tmp);
				if (error) {
					va_end(factor);
					return error;
				}
			}
//			printf("%s %s %s %s %s\n", tmp, tmp2, left_half, right_half, addition_half);
			error = strcopy(tmp2, left_half, 0, middle);
			if (error) {
				va_end(factor);
				return error;
			}
			error = strcopy(tmp2, right_half, middle, SizeString(tmp2));
			if (error) {
				va_end(factor);
				return error;
			}
			error = AdditionNumbers(left_half, right_half, addition_half, base);
			if (error) {
				va_end(factor);
				return error;
			}
			if (strcmpInOurCase(tmp, addition_half)) {
				error = push_end_string_vector(vec, tmp);
				if (error) {
					va_end(factor);
					return error;
				}
			}
//			printf("%s %s %s %s %s\n", tmp, tmp2, left_half, right_half, addition_half);
		}
	}
	va_end(factor);
	return SUCCESS;
}
