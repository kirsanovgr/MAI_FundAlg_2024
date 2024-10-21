#include "ex10.h"

/**
 * f = 1 + 2x + 3x^2 + 4x^3 \n
 * f' = 2 + 6x + 12x^2 \n
 * f'' = 6 + 24x \n
 * f''' = 24 \n
 * g''' = 4 * n! \n
 * g''' = 4 * n! \n
 * g'' = 4 * n! *(x - a) + A = 6 + 24x \n
 * g' = (4 * n! / 2) * (x - a)^2 + A(x - a) + B = 2 + 6x + 12x^2 \n
 * g = (4 * n! / 2 / 3) * (x - a)^3 + A / 2 *(x - a)^2 + B(x - a) + C \n
 */

error_msg DecompositionPolynomial(double eps, double a, double **result, int n, ...) {
	if (eps < 1e-40) return INCORRECT_OPTIONS_ERROR;
	va_list factor;
	va_start(factor, n);
	*result = (double *)calloc(n + 1, sizeof(double));
	double coefficients[n + 1];
	if (!*result) {
		va_end(factor);
		return MEMORY_ALLOCATED_ERROR;
	}
	double x;
	for (int i = 0; i <= n; ++i) {
		x = va_arg(factor, double);
		coefficients[i] = x;
	}
	(*result)[n] = coefficients[n];
	for (int i = n - 1, count_derivative = n - 1; i >= 0; --i, count_derivative--) {
		for (int j = i, k = 0; j <= n; ++j, ++k) {
			if ((fabsl((long double)special_product(count_derivative, j) * coefficients[j]) * pow(a, k) -
			     (long double)DBL_MAX) >= eps)
				return OVERFLOW_ERROR;
			(*result)[i] += (double)special_product(count_derivative, j) * coefficients[j] * pow(a, k);
		}
		(*result)[i] /= (double)fac(i);
	}
	return NORMAL;
}

int compare(double a, double b, double eps) {
	if ((a - b) >= eps) return 1;
	if ((b - a) >= eps) return -1;
	return 0;
}

long long int special_product(int n, int p) {
	long long int x = 1;
	for (int i = 0; i < n; ++i) {
		x *= p;
		p -= 1;
	}
	return x;
}

long long int fac(int x) {
	long long int s = 1;
	for (int i = 2; i <= x; ++i) {
		s *= i;
	}
	return s;
}