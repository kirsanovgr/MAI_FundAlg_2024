#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
    SUCCESS,
    ERROR_INVALID_DIMENSION,
    ERROR_MEMORY_ALLOCATION_FAILED
} StatusCode;

typedef struct {
    double* coordinates;
    int dimension;
} Vector;

double maxNorm(Vector* v) {
    double max = fabs(v->coordinates[0]);
    for (int i = 1; i < v->dimension; i++) {
        if (fabs(v->coordinates[i]) > max) {
            max = fabs(v->coordinates[i]);
        }
    }
    return max;
}

double l1Norm(Vector* v) {
    double sum = 0;
    for (int i = 0; i < v->dimension; i++) {
        sum += fabs(v->coordinates[i]);
    }
    return sum;
}

double lpNorm(Vector* v, double p) {
    double sum = 0;
    for (int i = 0; i < v->dimension; i++) {
        sum += pow(fabs(v->coordinates[i]), p);
    }
    return pow(sum, 1.0 / p);
}

StatusCode findLongestVectors(int n, Vector* vectors, int vectorCount, double (*normFunc)(Vector*), Vector*** longestVectors, int* longestCount) {
    if (n <= 0 || vectorCount <= 0) {
        return ERROR_INVALID_DIMENSION;
    }
    
    double maxLength = 0;
    *longestCount = 0;
    *longestVectors = NULL;

    for (int i = 0; i < vectorCount; i++) {
        double length = normFunc(&vectors[i]);
        if (length > maxLength) {
            maxLength = length;
            *longestCount = 1;
            *longestVectors = realloc(*longestVectors, sizeof(Vector*) * (*longestCount));
            if (*longestVectors == NULL) {
                return ERROR_MEMORY_ALLOCATION_FAILED;
            }
            (*longestVectors)[0] = &vectors[i];
        } else if (length == maxLength) {
            (*longestCount)++;
            *longestVectors = realloc(*longestVectors, sizeof(Vector*) * (*longestCount));
            if (*longestVectors == NULL) {
                return ERROR_MEMORY_ALLOCATION_FAILED;
            }
            (*longestVectors)[*longestCount - 1] = &vectors[i];
        }
    }
    return SUCCESS;
}

void freeVectors(Vector* vectors, int vectorCount) {
    for (int i = 0; i < vectorCount; i++) {
        free(vectors[i].coordinates);
    }
    free(vectors);
}

int main() {
    int n, vectorCount;
    printf("Enter the dimension of space (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid dimension entered.\n");
        return ERROR_INVALID_DIMENSION;
    }

    printf("Enter the number of vectors: ");
    if (scanf("%d", &vectorCount) != 1 || vectorCount <= 0) {
        printf("Invalid vector count entered.\n");
        return ERROR_INVALID_DIMENSION;
    }

    Vector* vectors = malloc(sizeof(Vector) * vectorCount);
    if (vectors == NULL) {
        printf("Memory allocation failed for vectors.\n");
        return ERROR_MEMORY_ALLOCATION_FAILED;
    }

    for (int i = 0; i < vectorCount; i++) {
        vectors[i].coordinates = malloc(sizeof(double) * n);
        if (vectors[i].coordinates == NULL) {
            freeVectors(vectors, i);
            printf("Memory allocation failed for vector coordinates.\n");
            return ERROR_MEMORY_ALLOCATION_FAILED;
        }
        
        printf("Enter coordinates for vector %d:\n", i + 1);
        for (int j = 0; j < n; j++) {
            if (scanf("%lf", &vectors[i].coordinates[j]) != 1) {
                freeVectors(vectors, vectorCount);
                printf("Invalid input for coordinates.\n");
                return ERROR_MEMORY_ALLOCATION_FAILED;
            }
        }
        vectors[i].dimension = n;
    }

    Vector** longestVectors = NULL;
    int longestCount = 0;

    StatusCode status = findLongestVectors(n, vectors, vectorCount, maxNorm, &longestVectors, &longestCount);
    if (status != SUCCESS) {
        freeVectors(vectors, vectorCount);
        printf("Error occurred: %d\n", status);
        return status;
    }

    printf("Longest vectors (max norm):\n");
    for (int i = 0; i < longestCount; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", longestVectors[i]->coordinates[j]);
        }
        printf("\n");
    }

    free(longestVectors);
    freeVectors(vectors, vectorCount);

    return SUCCESS;
}
