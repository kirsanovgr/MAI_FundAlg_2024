#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
    int n;
    double* coords;
} Vector;

struct ArrayVectors {
    int size;
    int capacity;
    Vector* vectors;
};

typedef struct ArrayVectors ArrayVectors;

typedef enum {
    SUCCESS = 0,
    MEMORY_ALLOCATED_ERROR = 1
} Status;

typedef double (*norm_func)(Vector, va_list);

ArrayVectors* create_array_vector_array(int capacity) {
    ArrayVectors* vector = (ArrayVectors*)malloc(sizeof(ArrayVectors));
    if (!vector) {
        return NULL;
    }
    vector->vectors = (Vector*)malloc(sizeof(Vector) * capacity);
    if (!(vector->vectors)) {
        free(vector);
        return NULL;
    }
    vector->size = 0;
    vector->capacity = capacity;
    return vector;
}

int resize_array_vector(ArrayVectors* arrayVectors, int new_capacity) {
    Vector* new_vectors = (Vector*)realloc(arrayVectors->vectors, sizeof(Vector) * new_capacity);
    if (!new_vectors) {
        return MEMORY_ALLOCATED_ERROR;
    }
    arrayVectors->vectors = new_vectors;
    arrayVectors->capacity = new_capacity;
    return SUCCESS;
}

Status push_array_vector(ArrayVectors* vector, Vector new_element) {
    if (vector->size == vector->capacity) {
        Status error = resize_array_vector(vector, vector->capacity * 2);
        if (error) return error;
    }
    vector->vectors[vector->size] = new_element;
    vector->size += 1;
    return SUCCESS;
}

void destroy_array_vector(ArrayVectors* vector) {
    free(vector->vectors);
    free(vector);
}

void print_array_vector(ArrayVectors* vector) {
    for (int i = 0; i < vector->size; ++i) {
        printf("vector:\t");
        for (int j = 0; j < vector->vectors[i].n; ++j) {
            printf("%f\t", vector->vectors[i].coords[j]);
        }
        putchar('\n');
    }
}

double norm1(Vector x, va_list factor) {
    double max_x = fabs(x.coords[0]);
    for (int i = 0; i < x.n; ++i) {
        if (fabs(x.coords[i]) > max_x) {
            max_x = fabs(x.coords[i]);
        }
    }
    return max_x;
}

double norm2(Vector x, va_list factor) {
    int p = va_arg(factor, int);
    if (p < 1) p = 1;
    double sum = 0.0;
    for (int i = 0; i < x.n; i++) {
        sum += pow(fabs(x.coords[i]), p);
    }
    return pow(sum, 1.0 / p);
}

double norm3(Vector x, va_list factor) {
    double** matrix = va_arg(factor, double**);
    double sum = 0.0;
    for (int i = 0; i < x.n; i++) {
        for (int j = 0; j < x.n; j++) {
            sum += matrix[i][j] * x.coords[j] * x.coords[i];
        }
    }
    return sqrt(sum);
}

Status MaxVectors(ArrayVectors*** array_vectors, int count_vectors, int count_norms, ...) {
    va_list factor;
    va_start(factor, count_norms);

    Vector* vectors = (Vector*)malloc(sizeof(Vector) * count_vectors);
    if (!vectors) {
        va_end(factor);
        return MEMORY_ALLOCATED_ERROR;
    }

    for (int i = 0; i < count_vectors; ++i) {
        vectors[i] = va_arg(factor, Vector);
    }

    double vector_len;
    double max_vector_len;
    ArrayVectors** array_array_vectors = (ArrayVectors**)malloc(sizeof(ArrayVectors*) * count_norms);
    if (!array_array_vectors) {
        free(vectors);
        va_end(factor);
        return MEMORY_ALLOCATED_ERROR;
    }

    for (int i = 0; i < count_norms; ++i) {
        array_array_vectors[i] = create_array_vector_array(1);
        if (!array_array_vectors[i]) {
            free(vectors);
            free(array_array_vectors);
            va_end(factor);
            return MEMORY_ALLOCATED_ERROR;
        }
    }

    va_list copy_factor;
    for (int i = 0; i < count_norms; ++i) {
        norm_func norm = va_arg(factor, norm_func);
        max_vector_len = -1.0;
        for (int j = 0; j < count_vectors; ++j) {
            if (j != count_vectors - 1) {
                va_copy(copy_factor, factor);
                vector_len = norm(vectors[j], copy_factor);
                va_end(copy_factor);
            } else {
                vector_len = norm(vectors[j], factor);
            }

            if (vector_len > max_vector_len) {
                max_vector_len = vector_len;
                array_array_vectors[i]->size = 0;
                push_array_vector(array_array_vectors[i], vectors[j]);
            } else if (vector_len == max_vector_len) {
                push_array_vector(array_array_vectors[i], vectors[j]);
            }
        }
    }

    va_end(factor);
    *array_vectors = array_array_vectors;
    free(vectors);
    return SUCCESS;
}

int main() {
    Status errorMsg;
    int n = 3;
    Vector vectors[15];

    double coords[15][3] = {
        {3.0, 4.0, 0.0},
        {-1.0, 5.0, 2.0},
        {-3.0, -4.0, -5.0},
        {0.0, 0.0, 0.0},
        {1.0, -1.0, 3.0},
        {-3.0, 2.0, -2.0},
        {4.0, -3.0, 5.0},
        {1.5, 2.5, 0.5},
        {2.2, 3.3, -1.1},
        {-1.0, -1.0, 4.0},
        {1.0, 2.0, 2.0},
        {3.0, 4.0, 5.0},
        {-1.0, -1.0, -1.0},
        {0.0, 0.0, 0.0},
        {1.0, -1.0, 1.0},
    };

    for (int i = 0; i < 15; ++i) {
        vectors[i].n = 3;
        vectors[i].coords = (double*)malloc(sizeof(double) * 3);
        for (int j = 0; j < 3; ++j) {
            vectors[i].coords[j] = coords[i][j];
        }
    }

    double** A = (double**)malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(sizeof(double) * n);
        if (i == 0) {
            A[i][0] = 1; A[i][1] = -2; A[i][2] = 3;
        } else if (i == 1) {
            A[i][0] = 4; A[i][1] = 5; A[i][2] = -6;
        } else {
            A[i][0] = -7; A[i][1] = 8; A[i][2] = 9;
        }
    }

    int count_vectors = 15;
    int count_norms = 3;
    int p = 2;
    ArrayVectors** result_vectors = NULL;

    errorMsg = MaxVectors(&result_vectors, count_vectors, count_norms,
        vectors[0], vectors[1], vectors[2], vectors[3], vectors[4],
        vectors[5], vectors[6], vectors[7], vectors[8], vectors[9],
        vectors[10], vectors[11], vectors[12], vectors[13], vectors[14],
        norm1, norm2, p, norm3, A);

    if (errorMsg) {
        for (int i = 0; i < count_norms; ++i) {
            destroy_array_vector(result_vectors[i]);
        }
        free(result_vectors);
        return errorMsg;
    }

    for (int i = 0; i < count_norms; ++i) {
        printf("Норма %d:\n", i + 1);
        print_array_vector(result_vectors[i]);
        destroy_array_vector(result_vectors[i]);
    }

    free(result_vectors);
    for (int i = 0; i < 15; ++i) {
        free(vectors[i].coords);
    }
    for (int i = 0; i < n; ++i) {
        free(A[i]);
    }
    free(A);

    return SUCCESS;
}
