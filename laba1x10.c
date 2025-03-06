#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef enum Errors {
    sep_sign = 0,
    end,
    sign_error,
    input_error,
    memory_error
} Errors;

int errors(int key) {
    switch (key) {
        case input_error:
            printf("Mistake with input");
            return 1;
        case sign_error:
            printf("Mistake -");
            return 1;
        default:
            printf("%d", key);
    }
}


int put_to_Array(char** array, char c, int* size, int* i) {
    if (*i < *size) {
        (*array)[*i] = c;
        (*i)++;
        return 0;
    }
    else {
        *size *= 2;
        char* yu = (char*)realloc(*array, *size);
        if (yu == NULL) {
            free(*array);
            return memory_error;
        }
        *array = yu;
        (*array)[*i] = c;
        (*i)++;
        return 0;
    }
}

int separation(char c) {
    return ((c == ' ') || (c == '\n') || (c == '\t'));
}

int correct_input(char symbol) {
    if (((symbol <= 'Z') && (symbol >= 'A')) || ((symbol >= '0') && (symbol <= '9'))) {
        return 1;
    }
    return 0;
}

int is_stop(char* last_symbols) {
    char* prefix = "Stop";
    int k = 1;
    for (int i = 0; i < 4; i++) {
        k *= (last_symbols[i] == prefix[i]);
    }
    return k;
}

int analyze_end(FILE* file, char current, char last) {
    char stop[5];
    stop[0] = last;
    for (int i = 1; i < 4; i++) {
        stop[i] = current;
        if (separation(current)) {
            return input_error;
        }
        current = getc(file);
    }
    if (is_stop(stop)) {
        return end;
    }
    return input_error;
}

int is_end_of_number(char last) {
    return correct_input(last);
}

int analyze_size(char* str) {
    int k = 0;
    while (str[k] != '\0') {
        k++;
    }
    return k;
}

int find_index(char symbol, char* alphabet) {
    for (int i = 0; alphabet[i] != '\0'; i++) {
        if (alphabet[i] == symbol) {
            return i;
        }
    }
}

int to_dec(char* str, int size, int base, long int * dec) {
    char* alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    double answer = 0.0;
    int k = size - 1;
    for (int i = 0; str[i] != '\0'; i++, k--) {
        int index = find_index(str[i], alphabet);
        if (index >= base){
            return input_error;
        }
        answer += index * pow(base * 1.0, k * 1.0);
    }
    *dec = (long int) answer;
    return 0;
}

int find_max(long int current, long int* max) {
    if (*max < current) {
        *max = current;
        return 1;
    }
    return 0;
}

int parse_number(FILE* file, char* last, char** str, int* size, int* i, int base, long int* max, int * sign, int* amount) {
    char current = getc(file);
    if ((*sign)&&(!(correct_input(current)))){
        return sign_error;
    }
    else if (*sign){
        *sign = 0;
    }
    if ((separation(current) && (is_end_of_number(*last)))) {
        *amount = 1;
        int number;
        int result = put_to_Array(str, '\0', size, i);
        if (result) {
            return result;
        }
        int filled_size = analyze_size(*str);
        long int dec;
        result = to_dec(*str, filled_size, base, &dec);
        if (result){
            return result;
        }
        *i = 0;
        *last = current;
        find_max(dec, max);
        return sep_sign;
    }
    else if (separation(current)) {
        return sep_sign;
    }
    else if (correct_input(current)) {
        int result = put_to_Array(str, current, size, i);
        if (result) {
            return result;
        }
        *last = current;
    }
    else if (current == '-'){
        *sign = 1;
    }
    else if (*last == 'S') {
        int result = analyze_end(stdin, current, *last);
        return result;
    }
    else {
        return input_error;
    }
    return 0;
}

void delete_zeros(char* str, char* answer) {
    int i = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] != '0') {
            break;
        }
    }
    if (str[i] == '\0') {
        int j = 0;
        for (; str[j] != '\0'; j++) {
            answer[j] = '0';
        }
        answer[j] = '\0';
        return;
    }
    int j = i;
    for (; str[j] != '\0'; j++) {
        answer[j - i] = str[j];
    }
    answer[j - i] = '\0';
}

int is_digit(char c) {
    return ((c <= '9') && (c >= '0'));
}

int my_atof(FILE* file, char last, int* base) {
    char symb = last;
    while (symb != '\n') {
        if (is_digit(symb)) {
            *base *= 10;
            *base += symb - '0';
        }
        else {
            return input_error;
        }
        symb = getc(file);
    }
    return 0;
}

int translate_from_dec(int dec, int base, char** answer, int* size){
    int number = dec;
    int i = 0;
    char* alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (number > 0){
        char current = alphabet[(number % base)];
        number /= base;
        put_to_Array(answer, current, size, &i);
    }
    return 0;
}

void print_number(int Max_number, int base){
    int k = 2;
    char* answer = (char *)malloc(k);
    translate_from_dec(Max_number, base, &answer, &k);
    printf("\n%d:", base);
    for (int i = k - 1; answer[i] != '\0'; i--) {
        if (correct_input(answer[i])) {
            printf("%c", answer[i]);
        }
    }
    free(answer);
}

int main() {
    int base_system;
    int base = 0;
    char last = getc(stdin);
    if (my_atof(stdin, last, &base)) {
        return errors(input_error);
    }
    if ((base < 2) || (base > 36)) {
        return errors(input_error);
    }
    long int Max_number = 0;
    int key;
    int size = 2;
    int i = 0;
    char* str = (char*)malloc(2 * sizeof(char));
    int sign = 0;
    int amount = 0;
    while (1) {
        key = parse_number(stdin, &last, &str, &size, &i, base, &Max_number, &sign, &amount);
        if (key == sep_sign) {
            continue;
        }
        else if (key == end) {
            printf("Program is finished");
            break;
        }
        else {
            return errors(key);
        }
    }
    if (amount){
        // print_number(Max_number, base);
        print_number(Max_number, 9);
        print_number(Max_number, 18);
        print_number(Max_number, 27);
        print_number(Max_number, 36);
        printf("\n");
    }
    else{
        printf("No numbers");
    }
    free(str);
    return 0;
}