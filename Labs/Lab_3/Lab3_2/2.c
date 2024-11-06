#include "func.h"

double infinity_norm(const Vector *v) {
    if (v == NULL || v->data == NULL) return 0.0;
    double max = fabs(v->data[0]);
    for (int i = 1; i < v->size; i++) {
        if (fabs(v->data[i]) > max) {
            max = fabs(v->data[i]);
        }
    }
    return max;
}

double p_norm(const Vector *v, double p) {
    if (v == NULL || v->data == NULL) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < v->size; i++) {
        sum += pow(fabs(v->data[i]), p);
    }
    return pow(sum, 1.0 / p);
}

double a_norm(const Vector *v, const Matrix *A) {
    if (v == NULL || A == NULL || v->data == NULL || A->data == NULL) return 0.0;
    double norm = 0.0;
    for (int i = 0; i < A->rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < A->cols; j++) {
            sum += A->data[i][j] * v->data[j];
        }
        norm += fabs(sum);
    }
    return norm;
}

int main() {
    Vector v;
    Matrix A;

    printf("Введите размер вектора: ");
    if (scanf("%d", &v.size) != 1 || v.size <= 0) {
        printf("Некорректный размер вектора.\n");
        return INCORRECT_OPTIONS;
    }

    v.data = (double *)malloc(v.size * sizeof(double));
    if (v.data == NULL) {
        printf("Ошибка выделения памяти для вектора.\n");
        return INCORRECT_OPTIONS;
    }

    printf("Введите %d элементов вектора:\n", v.size);
    for (int i = 0; i < v.size; i++) {
        if (scanf("%lf", &v.data[i]) != 1) {
            printf("Некорректный ввод элемента вектора.\n");
            free(v.data);
            return INCORRECT_OPTIONS;
        }
    }

    // очищаем всё, что ввели лешнего
    while (getchar() != '\n');

    // Ввод размеров матрицы
    printf("Введите количество строк матрицы: ");
    if (scanf("%d", &A.rows) != 1 || A.rows <= 0) {
        printf("Некорректное количество строк.\n");
        free(v.data);
        return INCORRECT_OPTIONS;
    }
    printf("Введите количество столбцов матрицы: ");
    if (scanf("%d", &A.cols) != 1 || A.cols <= 0) {
        printf("Некорректное количество столбцов.\n");
        free(v.data);
        return INCORRECT_OPTIONS;
    }

    // проверяем совместимость размеров матрицы и вектора
    if (A.cols != v.size) {
        printf("Количество столбцов матрицы должно совпадать с размером вектора.\n");
        free(v.data);
        return INCORRECT_OPTIONS;
    }

    A.data = (double **)malloc(A.rows * sizeof(double *));
    if (A.data == NULL) {
        printf("Ошибка выделения памяти для матрицы.\n");
        free(v.data);
        return INCORRECT_OPTIONS;
    }
    for (int i = 0; i < A.rows; i++) {
        A.data[i] = (double *)malloc(A.cols * sizeof(double));
        if (A.data[i] == NULL) {
            printf("Ошибка выделения памяти для строки матрицы.\n");
            for (int j = 0; j < i; j++) {
                free(A.data[j]);
            }
            free(A.data);
            free(v.data);
            return INCORRECT_OPTIONS;
        }
    }

    printf("Введите %d элементов матрицы построчно:\n", A.rows * A.cols);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            if (scanf("%lf", &A.data[i][j]) != 1) {
                printf("Некорректный ввод элемента матрицы.\n");
                for (int k = 0; k < A.rows; k++) {
                    free(A.data[k]);
                }
                free(A.data);
                free(v.data);
                return INCORRECT_OPTIONS;
            }
        }
    }

    // очищаем всё, что ввели лешнего
    while (getchar() != '\n');

    double inf_norm = infinity_norm(&v);
    double p2_norm = p_norm(&v, 2.0);
    double a_norm_value = a_norm(&v, &A);

    printf("Бесконечная норма: %f\n", inf_norm);
    printf("2-норма: %f\n", p2_norm);
    printf("a-норма: %f\n", a_norm_value);

    free(v.data);
    for (int i = 0; i < A.rows; i++) {
        free(A.data[i]);
    }
    free(A.data);

    return SUCCESS;
}
