#include "intarray.h"
#include "../error_handler.h"

int create_intarr(unsigned int length, IntArray* arr) {
    arr->capacity = length;
    arr->length = 0;
    arr->val = (int*) malloc(length * sizeof(int));

    if (!arr->val)
        return throw_err(MEMORY_NOT_ALLOCATED);

    return 0;
}

int append_int(IntArray* arr, int value) {
    if (arr->length >= arr->capacity) {
        int err = extend_int(arr);
        if (err)
            return err;
    }

    arr->val[arr->length++] = value;
    return 0;
}

int resize_int(IntArray* arr, int size_delta) {
    int* new_addr = (int*) realloc(arr->val, (arr->capacity + size_delta) * sizeof(int));

    if (!new_addr) {
        free(arr->val);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    arr->val = new_addr;
    arr->capacity += size_delta;
    return 0;
}

// Double array length.
int extend_int(IntArray* arr) {
    return resize_int(arr, arr->capacity);
}

void destroy_int(IntArray* arr) {
    if (arr->val)
        free(arr->val);
    arr->val = NULL;
    arr->length = 0;
    arr->capacity = 0;
}

void print_intarr(const IntArray arr) {
    for (int i = 0; i < arr.length; ++i) {
        printf("%d ", arr.val[i]);
    }
    printf("\n");
}

//int copy(IntArray* dst, IntArray* src) {
//    destroy_int(dst);
//    dst->val = calloc(src->capacity, sizeof(char));
//    dst->length = src->length;
//    dst->capacity = src->capacity;
//
//    char* tempdst = dst->val, *tempsrc = src->val;
//    while ((*dst->val++ = *src->val++));
//    dst->val = tempdst;
//    src->val = tempsrc;
//    return 0;
//}
//
int reverse_int(IntArray* arr) {
    int size = arr->length;
    for (int i = 0; i < size / 2; ++i) {
        char temp = arr->val[i];
        arr->val[i] = arr->val[size - i - 1];
        arr->val[size - i - 1] = temp;
    }

    return 0;
}