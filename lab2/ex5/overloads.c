#include "overloads.h"

error_msg int_to_roman(int num, char *roman) {
	const char *roman_numerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	roman[0] = '\0';
	for (int i = 0; i < 13; i++) {
		while (num >= values[i]) {
			my_strcat(roman, roman_numerals[i]);
			num -= values[i];
		}
	}
	roman[SizeString(roman)] = '\0';
	return SUCCESS;
}

error_msg int_to_zeckendorf(unsigned int num, char *zeckendorf) {
	unsigned int fib[33];
	fib[0] = 1;
	fib[1] = 1;
	for (int i = 2; i < 33; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	zeckendorf[0] = '1';
	zeckendorf[1] = '\0';
	for (int i = 31; i >= 0; i--) {
		if (num >= fib[i]) {
			zeckendorf[i] = '1';
			num -= fib[i];
		} else {
			zeckendorf[i] = '0';
		}
	}
	zeckendorf[32] = '\0';
	int i = 31;
	while (zeckendorf[i] == '0') {
		zeckendorf[i] = '\0';
		i -= 1;
	}
	return SUCCESS;
}

void From10to(int number, char *result, int based) {
	char tmp[sizeof(int) * 8 + 1];
	int index = 0;
	int fl = 0;
	if (number < 0) {
		fl = 1;
		number *= -1;
	}
	while (number > 0) {
		if (number % based < 10)
			tmp[index] = '0' + number % based;
		else
			tmp[index] = 'a' + (number % based - 10);
		index++;
		number /= based;
	}
	if (fl) {
		tmp[index++] = '-';
	}
	for (int i = 0; i < index; i++) {
		result[i] = tmp[index - i - 1];
	}
	result[index] = '\0';
}

void ToUpper(char *s) {
	for (int i = 0; s[i] != '\0'; ++i) {
		if (s[i] >= 'a' && s[i] <= 'z') s[i] = 'A' + s[i] - 'a';
	}
}

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

int IsLower(const char *s) {
	for (int i = 0; s[i] != '\0'; ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z') return 0;
	}
	return 1;
}

int IsUpper(const char *s) {
	for (int i = 0; s[i] != '\0'; ++i) {
		if (s[i] >= 'a' && s[i] <= 'z') return 0;
	}
	return 1;
}

int FromXTo10(char *original, int based, long int *result) {
	*result = 0;
	int fl = 0;
	for (int i = 0; i < SizeString(original); ++i) {
		if (original[i] == '-') {
			fl = 1;
		} else {
			if (sequence_number(original[i]) == -1 || sequence_number(original[i]) >= based) return 1;
			*result = (*result) * based + sequence_number(original[i]);
		}
	}
	if (fl) *result *= -1;
	return 0;
}

void memory_dump(void *ptr, size_t size, char *result) {
	unsigned char *bytes = (unsigned char *)ptr;
	for (size_t i = 0; i < size; i++) {
		char tmp[10];
		tmp[0] = '\0';
		for (int j = 7; j >= 0; --j) {
			sprintf(tmp + SizeString(tmp), "%u", (bytes[i] >> j) & 1);
		}
		my_strcat(tmp, " ");
		my_strcat(result, tmp);
	}
}

int overfprintf(FILE *restrict stream, const char *format, ...) {
	if (!stream) return INPUT_FILE_ERROR;
	int count = 0;
	const char *p = format;
	va_list factor;
	va_start(factor, format);
	while (*p) {
		if (*p == '%') {
			p++;
			if (*p == '%') {
				count++;
			} else if (SizeString(p) >= 2 && *p == 'R' && *(p + 1) == 'o') {
				// Римские числа
				p += 2;
				int x = va_arg(factor, int);
				if (x <= 0) return -1;
				char vec[100];
				int_to_roman(x, vec);
				fprintf(stream, "%s", vec);
				count += SizeString(vec);
			} else if (SizeString(p) >= 2 && *p == 'Z' && *(p + 1) == 'r') {
				p += 2;
				unsigned int x = va_arg(factor, unsigned int);
				char vec[34];
				int_to_zeckendorf(x, vec);
				fprintf(stream, "%s", vec);
				count += SizeString(vec);
			} else if (SizeString(p) >= 2 && *p == 'C' && *(p + 1) == 'v') {
				p += 2;
				int x = va_arg(factor, int);
				int base = va_arg(factor, int);
				if (base < 2 || base > 36) base = 10;
				char vec[(sizeof(int) + 1) * 8];
				From10to(x, vec, base);
				fprintf(stream, "%s", vec);
				count += SizeString(vec);
			} else if (SizeString(p) >= 2 && *p == 'C' && *(p + 1) == 'V') {
				p += 2;
				int x = va_arg(factor, int);
				int base = va_arg(factor, int);
				if (base < 2 || base > 36) base = 10;
				char vec[(sizeof(int) + 1) * 8];
				From10to(x, vec, base);
				ToUpper(vec);
				fprintf(stream, "%s", vec);
				count += SizeString(vec);
			} else if (SizeString(p) >= 2 && *p == 't' && *(p + 1) == 'o') {
				p += 2;
				char *str = va_arg(factor, char *);
				int base = va_arg(factor, int);
				if (base < 2 || base > 36) base = 10;
				long int number;
				if (FromXTo10(str, base, &number) || !IsLower(str)) {
					va_end(factor);
					return -1;
				}
				int n = fprintf(stream, "%ld", number);
				count += n;
			} else if (SizeString(p) >= 2 && *p == 'T' && *(p + 1) == 'O') {
				p += 2;
				char *str = va_arg(factor, char *);
				int base = va_arg(factor, int);
				if (base < 2 || base > 36) base = 10;
				long int number;
				if (FromXTo10(str, base, &number) || !IsUpper(str)) {
					va_end(factor);
					return -1;
				}
				int n = fprintf(stream, "%ld", number);
				count += n;
			} else if (SizeString(p) >= 2 && *p == 'm' && *(p + 1) == 'i') {
				p += 2;
				int32_t value = va_arg(factor, int32_t);
				char result[8 * (sizeof(value) + 1)];
				result[0] = '\0';
				memory_dump(&value, sizeof(value), result);
				fprintf(stream, "%s", result);
				count += SizeString(result);
			} else if (SizeString(p) >= 2 && *p == 'm' && *(p + 1) == 'u') {
				p += 2;
				uint32_t value = va_arg(factor, uint32_t);
				char result[8 * (sizeof(value) + 1)];
				result[0] = '\0';
				memory_dump(&value, sizeof(value), result);
				fprintf(stream, "%s", result);
				count += SizeString(result);
			} else if (SizeString(p) >= 2 && *p == 'm' && *(p + 1) == 'd') {
				p += 2;
				double value = va_arg(factor, double);
				char result[8 * (sizeof(value) + 1)];
				result[0] = '\0';
				memory_dump(&value, sizeof(value), result);
				fprintf(stream, "%s", result);
				count += SizeString(result);
			} else if (SizeString(p) >= 2 && *p == 'm' && *(p + 1) == 'f') {
				p += 2;
				float value = va_arg(factor, double);
				char result[8 * (sizeof(value) + 1)];
				result[0] = '\0';
				memory_dump(&value, sizeof(value), result);
				fprintf(stream, "%s", result);
				count += SizeString(result);
			} else {
				char tmp[SizeString(format)];
				if (str_to_k(&p, "%", tmp)) {
					va_end(factor);
					return -1;
				}
				char tmp_str[SizeString(format)];
				tmp_str[0] = '\0';
				my_strcat(tmp_str, "%");
				my_strcat(tmp_str, tmp);
				int n = vfprintf(stream, tmp_str, factor);
				if (n < 0) {
					va_end(factor);
					return -1;
				}
				count += n;
				--p;
			}
		} else {
			fputc(*p, stream);
			count++;
			p++;
		}
	}
	va_end(factor);
	return count;
}

int oversprintf(char string[], const char *format, ...) {
	int count = 0;
	const char *p = format;
	va_list factor;
	string[0] = '\0';
	va_start(factor, format);
	while (*p) {
		if (*p == '%') {
			p++;
			if (*p == '%') {
				count++;
			} else if (SizeString(p) >= 2 && *p == 'R' && *(p + 1) == 'o') {
				// Римские числа
				p += 2;
				int x = va_arg(factor, int);
				if (x <= 0) return -1;
				// размер = 2 ^ (бит в int) / M(1000 в Римской сс)
				char vec[1000];
				int_to_roman(x, vec);
				my_strcat(string, vec);
				count += SizeString(vec);
			} else if (SizeString(p) >= 2 && *p == 'Z' && *(p + 1) == 'r') {
				p += 2;
				unsigned int x = va_arg(factor, unsigned int);
				char vec[34];
				int_to_zeckendorf(x, vec);
				my_strcat(string, vec);
				count += SizeString(vec);
			} else if (SizeString(p) >= 2 && *p == 'C' && *(p + 1) == 'v') {
				p += 2;
				int x = va_arg(factor, int);
				int base = va_arg(factor, int);
				if (base < 2 || base > 36) base = 10;
				char vec[sizeof(int) * 8];
				From10to(x, vec, base);
				my_strcat(string, vec);
				count += SizeString(vec);
			} else if (SizeString(p) >= 2 && *p == 'C' && *(p + 1) == 'V') {
				p += 2;
				int x = va_arg(factor, int);
				int base = va_arg(factor, int);
				if (base < 2 || base > 36) base = 10;
				char vec[sizeof(int) * 8];
				From10to(x, vec, base);
				ToUpper(vec);
				my_strcat(string, vec);
				count += SizeString(vec);
			} else if (SizeString(p) >= 2 && *p == 't' && *(p + 1) == 'o') {
				p += 2;
				char *str = va_arg(factor, char *);
				int base = va_arg(factor, int);
				if (base < 2 || base > 36) base = 10;
				long int number;
				if (FromXTo10(str, base, &number) || !IsLower(str)) {
					va_end(factor);
					return -1;
				}
				int n = sprintf(string + SizeString(string), "%ld", number);
				count += n;
			} else if (SizeString(p) >= 2 && *p == 'T' && *(p + 1) == 'O') {
				p += 2;
				char *str = va_arg(factor, char *);
				int base = va_arg(factor, int);
				if (base < 2 || base > 36) base = 10;
				long int number;
				if (FromXTo10(str, base, &number) || !IsUpper(str)) {
					va_end(factor);
					return -1;
				}
				int n = sprintf(string + SizeString(string), "%ld", number);
				count += n;
			} else if (SizeString(p) >= 2 && *p == 'm' && *(p + 1) == 'i') {
				p += 2;
				int32_t value = va_arg(factor, int32_t);
				char result[8 * (sizeof(value) + 1)];
				result[0] = '\0';
				memory_dump(&value, sizeof(value), result);
				my_strcat(string, result);
				count += SizeString(result);
			} else if (SizeString(p) >= 2 && *p == 'm' && *(p + 1) == 'u') {
				p += 2;
				uint32_t value = va_arg(factor, uint32_t);
				char result[8 * (sizeof(value) + 1)];
				result[0] = '\0';
				memory_dump(&value, sizeof(value), result);
				my_strcat(string, result);
				count += SizeString(result);
			} else if (SizeString(p) >= 2 && *p == 'm' && *(p + 1) == 'd') {
				p += 2;
				double value = va_arg(factor, double);
				char result[8 * (sizeof(value) + 1)];
				result[0] = '\0';
				memory_dump(&value, sizeof(value), result);
				my_strcat(string, result);
				count += SizeString(result);
			} else if (SizeString(p) >= 2 && *p == 'm' && *(p + 1) == 'f') {
				p += 2;
				float value = va_arg(factor, double);
				char result[8 * (sizeof(value) + 1)];
				result[0] = '\0';
				memory_dump(&value, sizeof(value), result);
				my_strcat(string, result);
				count += SizeString(result);
			} else {
				char tmp[SizeString(format)];
				tmp[0] = '\0';
				if (str_to_k(&p, "%", tmp)) {
					va_end(factor);
					return -1;
				}
				char tmp_str[SizeString(format)];
				tmp_str[0] = '\0';
				my_strcat(tmp_str, "%");
				my_strcat(tmp_str, tmp);
				int n = vsprintf(string + SizeString(string), tmp_str, factor);
				if (n < 0) {
					va_end(factor);
					return -1;
				}
				count += n;
				--p;
			}
		} else {
			string[SizeString(string)] = *p;
			count++;
			string[count] = '\0';
			p++;
		}
	}
	va_end(factor);
	return count;
}