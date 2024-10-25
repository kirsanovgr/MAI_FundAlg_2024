#ifndef LAB1T1_INTARRAY_H
#define LAB1T1_INTARRAY_H

typedef struct IntArray {
    int* val;
    unsigned int length;
    unsigned int capacity;
} IntArray;

int create_intarr(unsigned int length, IntArray* arr);
int append_int(IntArray* arr, int value);
int resize_int(IntArray* arr, int size_delta);
int extend_int(IntArray* arr);
void destroy_int(IntArray* arr);
//int copy(IntArray* dst, IntArray* src);
int reverse_int(IntArray* arr);
void print_intarr(IntArray arr);
int base_char_to_dec(char x);

#endif //LAB1T1_INTARRAY_H