#include "ex6.h"

error_msg RomanTOInt(char *s, int *res) {
	int map[256] = {0};
	map['I'] = 1;
	map['V'] = 5;
	map['X'] = 10;
	map['L'] = 50;
	map['C'] = 100;
	map['D'] = 500;
	map['M'] = 1000;
	*res = 0;
	for (int i = 0; i < SizeString(s); ++i) {
		if (map[(int)s[i]] < map[(int)s[i + 1]]) {
			if (labs(*res - map[(int)s[i]]) >= INT_MAX) return OVERFLOW_ERROR;
			*res -= map[(int)s[i]];
		} else {
			if (labs(*res + map[(int)s[i]]) >= INT_MAX) return OVERFLOW_ERROR;
			*res += map[(int)s[i]];
		}
	}
	return NORMAL;
}

error_msg ZeckendorfTOUInt(char *s, unsigned int *res) {
	unsigned int fib[33];
	*res = 0;
	fib[0] = 1;
	fib[1] = 1;
	for (int i = 2; i < 33; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	for (int i = 0; s[i]; ++i) {
		if (s[i] == '1') {
			if ((*res + fib[i]) >= INT_MAX) return OVERFLOW_ERROR;
			*res += fib[i];
		}
	}

	return NORMAL;
}

int sequence_number(char c) {
	if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	else if (c >= '0' && c <= '9')
		return c - '0';
	else
		return -1;
}

error_msg FromXTo10(char *original, int based, int *result) {
	*result = 0;
	int fl = 0;
	for (int i = 0; i < SizeString(original); ++i) {
		if (original[i] == '-')
			fl = 1;
		else {
			if (sequence_number(original[i]) == -1 || sequence_number(original[i]) >= based)
				return NUMERAL_SYSTEM_ERROR;
			*result = (*result) * based + sequence_number(original[i]);
		}
	}
	if (fl) *result *= -1;
	return 0;
}

int IsNotUpper(char c) {
	if (c < 'A' || c > 'Z') return 1;
	return 0;
}

int IsNotLow(char c) {
	if (c < 'a' || c > 'z') return 1;
	return 0;
}

int overfscanf(FILE *restrict stream, char *format, ...) {
	va_list factor;
	error_msg errorMsg;
	va_start(factor, format);
	if (!stream) {
		return INPUT_FILE_ERROR;
	}
	int count = 0;
	char c;
	const char *p = format;
	while (p) {
		if (*p == '%') {
			++p;
			if (*p == '%') {
				++p;
			} else if (*p == 'R' && *(p + 1) == 'o') {
				int *res = va_arg(factor, int *);
				int i = 0;
				char input_char;
				char input_str[(int)pow(2, sizeof(int) * 8) / 1000 + 1];
				while ((input_char = getc(stream)) &&
				       (input_char == 'M' || input_char == 'D' || input_char == 'C' || input_char == 'L' ||
				        input_char == 'V' || input_char == 'I' || input_char == 'X')) {
					input_str[i++] = input_char;
				}
				fseek(stream, -1, SEEK_CUR);
				input_str[i] = '\0';
				errorMsg = RomanTOInt(input_str, res);
				if (errorMsg) {
					va_end(factor);
					return count;
				}
				count++;
				p += 2;
			} else if (*p == 'Z' && *(p + 1) == 'r') {
				unsigned int *res = va_arg(factor, unsigned int *);
				char input_char;
				char input_str[50];
				int i = 0;
				while ((input_char = getc(stream)) && (input_char == '0' || input_char == '1')) {
					input_str[i++] = input_char;
				}
				errorMsg = ZeckendorfTOUInt(input_str, res);
				fseek(stream, -1, SEEK_CUR);
				if (errorMsg) {
					va_end(factor);
					return count;
				}
				count++;
				p += 2;
			} else if (*p == 'C' && *(p + 1) == 'v') {
				int *res = va_arg(factor, int *);
				int base = va_arg(factor, int);
				if(base < 2 || base > 36) base = 10;
				*res = 0;
				char str[100], input_char;
				int i = 0;
				while (((input_char = getc(stream)) && sequence_number(input_char) != -1 &&
				       sequence_number(input_char) < base && IsNotUpper(input_char)) || input_char == '-') {
					str[i++] = input_char;
				}
				str[i] = '\0';
				errorMsg = FromXTo10(str, base, res);
				if (errorMsg || i == 0 || (str[0] == '-' && i == 1))  {
					va_end(factor);
					return count;
				}
				count += 1;
				fseek(stream, -1, SEEK_CUR);
				p += 2;
			} else if ((*p == 'C' && *(p + 1) == 'V')) {
				int *res = va_arg(factor, int *);
				int base = va_arg(factor, int);
				if(base < 2 || base > 36) base = 10;
				*res = 0;
				char str[100], input_char;
				int i = 0;
				while (((input_char = getc(stream)) && sequence_number(input_char) != -1 &&
				       sequence_number(input_char) < base && IsNotLow(input_char)) || input_char == '-') {
					str[i++] = input_char;
				}
				str[i] = '\0';
				errorMsg = FromXTo10(str, base, res);
				if (errorMsg || i == 0 || (str[0] == '-' && i == 1)) {
					va_end(factor);
					return count;
				}
				count += 1;
				fseek(stream, -1, SEEK_CUR);
				p += 2;
			} else {
				char tmp[SizeString(format)];
				if (str_to_k(&p, "%", tmp)) {
					va_end(factor);
					return count;
				}
				char tmp_str[SizeString(format)];
				tmp_str[0] = '\0';
				my_strcat(tmp_str, "%");
				my_strcat(tmp_str, tmp);
				int n = vfscanf(stream, tmp_str, factor);
				va_arg(factor, void *);
				if (n == 0) {
					va_end(factor);
					return count;
				}
				count += n;
				--p;
			}

		} else {
			c = getc(stream);
			if (c != *p || feof(stream)) {
				va_end(factor);
				return count;
			}
			p++;
		}
	}
	va_end(factor);
	return 0;
}

int oversscanf(char *buffer, char *format, ...) {
	va_list factor;
	error_msg errorMsg;
	va_start(factor, format);
	int count = 0;
	char c;
	const char *p = format;
	while (p) {
		if (*p == '%') {
			++p;
			if (*p == '%') {
				++p;
			} else if (*p == 'R' && *(p + 1) == 'o') {
				int *res = va_arg(factor, int *);
				int i = 0;
				char input_char;
				char input_str[(int)pow(2, sizeof(int) * 8) / 1000 + 1];
				while ((input_char = *buffer) &&
				       (input_char == 'M' || input_char == 'D' || input_char == 'C' || input_char == 'L' ||
				        input_char == 'V' || input_char == 'I' || input_char == 'X')) {
					input_str[i++] = input_char;
					buffer++;
				}
				buffer--;
				input_str[i] = '\0';
				errorMsg = RomanTOInt(input_str, res);
				if (errorMsg) {
					va_end(factor);
					return count;
				}
				count++;
				p += 2;
			} else if (*p == 'Z' && *(p + 1) == 'r') {
				unsigned int *res = va_arg(factor, unsigned int *);
				char input_char;
				char input_str[50];
				int i = 0;
				while ((input_char = *buffer) && (input_char == '0' || input_char == '1')) {
					input_str[i++] = input_char;
					buffer++;
				}
				errorMsg = ZeckendorfTOUInt(input_str, res);
				buffer--;
				if (errorMsg) {
					va_end(factor);
					return count;
				}
				count++;
				p += 2;
			} else if (*p == 'C' && *(p + 1) == 'v') {
				int *res = va_arg(factor, int *);
				int base = va_arg(factor, int);
				if(base < 2 || base > 36) base = 10;
				*res = 0;
				char str[100], input_char;
				int i = 0;
				while (((input_char = *buffer) && sequence_number(input_char) != -1 &&
				        sequence_number(input_char) < base && IsNotUpper(input_char)) || input_char == '-') {
					str[i++] = input_char;
					buffer++;
				}
				str[i] = '\0';
				errorMsg = FromXTo10(str, base, res);
				if (errorMsg || i == 0 || (str[0] == '-' && i == 1))  {
					va_end(factor);
					return count;
				}
				count += 1;
				buffer--;
				p += 2;
			} else if ((*p == 'C' && *(p + 1) == 'V')) {
				int *res = va_arg(factor, int *);
				int base = va_arg(factor, int);
				if(base < 2 || base > 36) base = 10;
				*res = 0;
				char str[100], input_char;
				int i = 0;
				while (((input_char = *buffer) && sequence_number(input_char) != -1 &&
				        sequence_number(input_char) < base && IsNotLow(input_char)) || input_char == '-') {
					str[i++] = input_char;
					buffer++;
				}
				str[i] = '\0';
				errorMsg = FromXTo10(str, base, res);
				if (errorMsg || i == 0 || (str[0] == '-' && i == 1)) {
					va_end(factor);
					return count;
				}
				count += 1;
				buffer--;
				p += 2;
			} else {
				char tmp[SizeString(format)];
				if (str_to_k(&p, "%", tmp)) {
					va_end(factor);
					return count;
				}
				char tmp_str[SizeString(format)];
				tmp_str[0] = '\0';
				my_strcat(tmp_str, "%");
				my_strcat(tmp_str, tmp);
				int n = vsscanf(buffer, tmp_str, factor);
				va_arg(factor, void *);
				if (n == 0) {
					va_end(factor);
					return count;
				}
				const char *cc = tmp_str;

				while (*cc != 'c' && *cc != 's' && *cc != 'd' && *cc != 'i' &&
				       *cc != 'u' && *cc != 'o' && *cc != 'x' && *cc != 'X' &&
				       *cc != 'n' && *cc != 'a' && *cc != 'A' && *cc != 'e' &&
				       *cc != 'E' && *cc != 'f' && *cc != 'F' && *cc != 'g' &&
				       *cc != 'G' && *cc != 'p'){
					cc += 1;
				}
				cc++;
				while(*buffer != *cc) buffer++;
				buffer += SizeString(cc);
				count += n;
				--p;
			}

		} else {
			c = *buffer; ;
			buffer++;
			if (c != *p || c == '\0') {
				va_end(factor);
				return count;
			}
			p++;
		}
	}
	va_end(factor);
	return 0;
}