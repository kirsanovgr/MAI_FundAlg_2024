#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double *data; // Указатель на массив данных вектора
    int size;     // Размер вектора
} Vector;

typedef struct Matrix {
    double **data; // Указатель на массив данных матрицы
    int rows;      // Кол-во строк
    int cols;      // Кол-во столбцов
} Matrix;

typedef enum Error {
    SUCCESS = 0,
    INCORRECT_OPTIONS = -1
} Status;