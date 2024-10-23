#pragma once

double derivative(int order, int n, double a, const double *coeff);
int transform_polynomial(double epsilon, double a, int n, double **result, ...);
void print_polynomial(const double *coeff, int n, double a);