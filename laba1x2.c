#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415
#define MAX_INTERATION 47

long double BinPow(long double a, int n) {
    long double res = 1;
    while (n != 0) {
        if (n & 1)
            res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

long double factorial(int n) {
	long double res = 1.0;
	for (int i = 2; i <= n; i++) {
		res *= i;
	}
	return res;
}

// 1.1
long double ELimit(double epsilon) {
	long double e = 0.0;
	int n = 1;
	while (1) {
		long double term = BinPow(1.0 + 1.0 / n, n);
		if (fabs(term - e) < epsilon) {
			break;
		}
		e = term;
		n++;
	}
	return e;
}

// 1.2
long double ESeries(double epsilon) {
	long double e = 1.0;
	long double term = 1.0;
	int n = 1;
	while (fabs(term) > epsilon) {
		term /= n;
		e += term;
		n++;
	}
	return e;
}

// 1.3
long double EEquation(double epsilon) {
	long double x = 2.0;
	while (fabs(log(x) - 1.0) > epsilon) {
		x = x - (log(x) - 1.0) / (1.0 / x);
	}
	return x;
}

// 2.1
long double PiLimit(double epsilon) {
	long double pi = 4;
	long double prev_pi = 0.0;
	int n = 1;
	while (fabs(pi - prev_pi) > epsilon) {
		prev_pi = pi;
		pi *= 4.0 * ((n + 1) * n) / BinPow(2 * n + 1, 2);
		n++;
	}

	return pi;
}

// 2.2
long double PiSeries(double epsilon) {
	long double pi = 1.0;
	long double term = 1.0;
	int n = 2;
	while (fabsl(term) > epsilon) {
		term = ((n - 1) % 2 ? -1.0 : 1.0) / (2 * n - 1);
		pi += term;
		n++;
	}
	return pi * 4;
}

// 2.3
long double PiEquation(double epsilon) {
	long double x = 3.0;
	while (fabsl(cos(x) + 1.0) > epsilon) {
		x = x - (cos(x) + 1.0) / (-sin(x));
	}
	return x;
}

// 3.1
long double Ln2Limit(double epsilon) {
	long double ln2 = 0.0;
	long double term;
	int n = 1;
	while (1) {
		term = n * (powl(2, 1.0 / n) - 1);
		if (fabsl(term - ln2) < epsilon) {
			break;
		}
		ln2 = term;
		n++;
	}
	return ln2;
}

// 3.2
long double Ln2Series(double epsilon) {
	long double ln2 = 0.0;
    long double term = 1.0;
    int sign = 1;
    int n = 1;

    while (fabsl(term) > epsilon) {
        term = 1.0 / n;
        ln2 += sign * term;
        sign = -sign;
        n++;
    }

    return ln2;
}

// 3.3
long double Ln2Equation(double epsilon) {
	long double x = 1.0;
	while (fabsl(exp(x) - 2.0) > epsilon) {
		x = x - (exp(x) - 2.0) / exp(x);
	}
	return x;
}

// 4.1
long double Sqrt2Limit(double epsilon) {
	long double sqrt2 = -0.5;
	long double next = sqrt2 - (sqrt2 * sqrt2) / 2 + 1;
	while (fabs(sqrt2 - next) > epsilon) {
		sqrt2 = next;
		next = sqrt2 - (sqrt2 * sqrt2) / 2 + 1;
	}
	return next;
}

// 4.2
long double Sqrt2Series(double epsilon) {
	long double sqrt2 = 1.0;
	long double term;
	int k = 2;
	while (1) {
		term = powl(2, powl(2, -k));
		sqrt2 *= term;
		if (fabsl(term - 1) < epsilon) {
			break;
		}
		k++;
	}
	return sqrt2;
}

// 4.3
long double Sqrt2Equation(double epsilon) {
	long double x = 1.0;
	while (fabsl(x * x - 2.0) > epsilon) {
		x -= (x * x - 2.0) / (2 * x);
	}
	return x;
}

// 5.1
long double GammaLimit(double epsilon) {
	long double gamma = 0.0;
	long double prev_gamma = 0.0;
	int m = 1;
	long double fact_m = 1;
	while (1) {
		long double sum = 0.0;
		long double fact_k = 1;
		for (int k = 1; k <= m; k++) {
			fact_k *= k;
			long double binom = fact_m / (fact_k * factorial(m - k));
			sum += binom * (k % 2 ? -1.0 : 1.0) * log(fact_k) / k;

		}

		if (m == 1) {
			prev_gamma = -100;
		} else {
			prev_gamma = gamma;
		}

		gamma = sum;

		if (m >= MAX_INTERATION) {
			return gamma;
		}

		if (fabsl(gamma - prev_gamma) < epsilon) {
			break;
		}
		m++;
		fact_m *= m;
	}

	return gamma;
}

// 5.2
long double GammaSeries(double epsilon) {
	long double gamma = 0;
	long double term = 0;
	long double gamma_prev;
	int k = 2;

	while (1) {
		gamma_prev = gamma;
		term = (1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k);
		gamma += term;
		if (fabsl(term) < epsilon && term != 0) {
			break;
		}

		k++;
	}

	return gamma - PI * PI / 6.0;
}

// 5.3
bool IsPrime(int n) {
	if (n < 2) {
		return false;
	}
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

double ProdResult(int t) {
	double product = 1.0;
	for (int p = 2; p <= t; p++) {
		if (IsPrime(p)) {
			product *= (double)(p - 1) / p;
		}
	}
	return product;
}

long double GammaEquation(double epsilon) {
	double t = 2.0; 
	double prev_x = 0.0;

	for (int i = 0; i < 1000; i++) {
		double product = ProdResult((int)t);

		double current_x = log(t) * product;

		if (fabs(current_x - prev_x) < epsilon) {
			return current_x;
		}

		prev_x = current_x;
		t += 1;
	}

	return prev_x;
}

double MyStrtod(const char* str, char** end) {
	while (isspace((unsigned char)*str)) {
		str++;
	}

	int sign = 1;
	if (*str == '-') {
		sign = -1;
		str++;
	} else if (*str == '+') {
		str++;
	}

	double integer_part = 0.0;
	while (isdigit((unsigned char)*str)) {
		integer_part = integer_part * 10 + (*str - '0');
		str++;
	}

	double fraction_part = 0.0;
	if (*str == '.') {
		str++;
		double divisor = 10.0;
		while (isdigit((unsigned char)*str)) {
			fraction_part += (*str - '0') / divisor;
			divisor *= 10;
			str++;
		}
	}

	double result = sign * (integer_part + fraction_part);

	if (end) {
		*end = (char*)str;
	}

	return result;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Your programm must start with: %s <epsilon>", argv[0]);
		return 1;
	}

	char* end;
	double epsilon = MyStrtod(argv[1], &end);
	if (*end != '\0') {
		fprintf(stderr, "Incorrect epsilon.\n");
		return 1;
	}

	printf("e Const\n");
	printf("\tlimit: %Lf\n", ELimit(epsilon));
	printf("\trow: %Lf\n", ESeries(epsilon));
	printf("\tequation: %Lf\n", EEquation(epsilon));
	printf("pi Const\n");
	printf("\tlimit: %Lf\n", PiLimit(epsilon));
	printf("\trow: %Lf\n", PiSeries(epsilon));
	printf("\tequation: %Lf\n", PiEquation(epsilon));
	printf("ln of 2\n");
	printf("\tlimit: %Lf\n", Ln2Limit(epsilon));
	printf("\trow: %Lf\n", Ln2Series(epsilon));
	printf("\tequation: %Lf\n", Ln2Equation(epsilon));
	printf("sqrt of 2\n");
	printf("\tlimit: %Lf\n", Sqrt2Limit(epsilon));
	printf("\trow: %Lf\n", Sqrt2Series(epsilon));
	printf("\tequation: %Lf\n", Sqrt2Equation(epsilon));
	printf("Gamma\n");
	printf("\tlimit: %Lf\n", GammaLimit(epsilon));
	printf("\trow: %Lf\n", GammaSeries(epsilon));
	printf("\tequation: %Lf\n", GammaEquation(epsilon));

	return 0;
}