#include <stdio.h>
#include <stdarg.h>

typedef enum {
    SUCCESSFUL = 0,
    ERROR = -1
} Status;

void my_strcat(char *dest, const char *src) {
    while (*dest) {
        dest++;
    }
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

void int_to_roman(int num, char *result) {
    struct Roman {
        int value;
        const char *numeral;
    } roman[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"},
        {5, "V"}, {4, "IV"}, {1, "I"}, {0, NULL}
    };

    result[0] = '\0';

    for (struct Roman *r = roman; r->value > 0; r++) {
        while (num >= r->value) {
            my_strcat(result, r->numeral);
            num -= r->value;
        }
    }
}

void print_fibonacci_reverse(int n, FILE *stream) {
    if (n <= 0) return;

    int a = 0, b = 1, temp;
    int fib[100];
    int count = 0;

    for (int i = 0; i < n; i++) {
        fib[i] = a;
        temp = a + b;
        a = b;
        b = temp;
        count++;
    }

    for (int i = count - 1; i >= 0; i--) {
        fprintf(stream, "%d", fib[i]);
        if (i > 0) {
            fputc(' ', stream);
        }
    }
}

void print_in_base(int num, int base, FILE *stream, int is_upper) {
    if (base == 16) {
        if (is_upper) {
            fprintf(stream, "%X", num);
        } else {
            fprintf(stream, "%x", num);
        }
    } else if (base == 8) {
        fprintf(stream, "%o", num);
    } else {
        fprintf(stream, "%d", num);
    }
}

void print_memory_representation(const void *ptr, size_t size, FILE *stream) {
    const unsigned char *byte_ptr = (const unsigned char *)ptr;
    for (size_t i = 0; i < size; i++) {
        if (i > 0) fputc(' ', stream);
        fprintf(stream, "%02X", byte_ptr[i]);
    }
}

int overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    const char *p = format;
    char temp[100];

    while (*p) {
        if (*p == '%') {
            p++;
            if (*p == 'r' && *(p + 1) == 'O') {
                p += 2;
                int num = va_arg(args, int);
                int_to_roman(num, temp);
                fputs(temp, stream);
                fputc('\n', stream);
            } else if (*p == 'Z' && *(p + 1) == 'r') {
                p += 2;
                int n = va_arg(args, int);
                print_fibonacci_reverse(n, stream);
                fputc('\n', stream);
            } else if (*p == 'C') {
                p++;
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                print_in_base(num, base, stream, 0);
                fputc('\n', stream);
            } else if (*p == 'C' && *(p + 1) == 'V') {
                p += 2;
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                print_in_base(num, base, stream, 1);
                fputc('\n', stream);
            } else if (*p == 'o' && *(p + 1) == '%') {
                p += 2;
                int num = va_arg(args, int);
                print_in_base(num, 8, stream, 0);
                fputc('\n', stream);
            } else if (*p == 'T' && *(p + 1) == '0') {
                p += 2;
                int num = va_arg(args, int);
                fprintf(stream, "%d", num);
                fputc('\n', stream);
            } else if (*p == 'm' && *(p + 1) == 'i') {
                p += 2;
                int num = va_arg(args, int);
                print_memory_representation(&num, sizeof(num), stream);
                fputc('\n', stream);
            } else if (*p == 'm' && *(p + 1) == 'u') {
                p += 2;
                unsigned int num = va_arg(args, unsigned int);
                print_memory_representation(&num, sizeof(num), stream);
                fputc('\n', stream);
            } else if (*p == 'm' && *(p + 1) == 'd') {
                p += 2;
                double num = va_arg(args, double);
                print_memory_representation(&num, sizeof(num), stream);
                fputc('\n', stream);
            } else if (*p == 'm' && *(p + 1) == 'f') {
                p += 2;
                float num = va_arg(args, double);
                print_memory_representation(&num, sizeof(num), stream);
                fputc('\n', stream);
            }
        } else {
            fputc(*p, stream);
        }
        p++;
    }
    va_end(args);
    return SUCCESSFUL;
}

int main() {
    overfprintf(stdout, "Roman numeral of 69: %rO\n", 69);
    overfprintf(stdout, "Roman numeral of 228: %rO\n", 228);
    overfprintf(stdout, "Roman numeral of 999: %rO\n", 999);
    overfprintf(stdout, "Roman numeral of 2005: %rO\n", 2005);

    overfprintf(stdout, "Fibonacci (3 numbers) in reverse: %Zr\n", 3);
    overfprintf(stdout, "Fibonacci (5 numbers) in reverse: %Zr\n", 5);
    overfprintf(stdout, "Fibonacci (10 numbers) in reverse: %Zr\n", 10);

    overfprintf(stdout, "Number in hexadecimal: %C\n", 42, 16);
    overfprintf(stdout, "Number in octal: %o%\n", 52);
    overfprintf(stdout, "Number in decimal: %T0\n", 52);
    overfprintf(stdout, "Number in base 2: %C\n", 52, 2);

    overfprintf(stdout, "Memory representation of an int: %mi\n", 69);
    overfprintf(stdout, "Memory representation of an unsigned int: %mu\n", 42U);
    overfprintf(stdout, "Memory representation of a double: %md\n", 69.69);
    overfprintf(stdout, "Memory representation of a float: %mf\n", 42.42f);

    return SUCCESSFUL;
}