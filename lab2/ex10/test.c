#include "test.h"

START_TEST(decompositionpolynomial){
	double* res;
	double correct_res1[] = {64.0, 79.0, 34.0, 5.0};
	int n = 3;
	double a = 2.0;
	error_msg errorMsg = DecompositionPolynomial(1e-16, a, &res, n, 2.0, 3.0, 4.0, 5.0);
	ck_assert_int_eq(errorMsg, NORMAL);
	for(int i = 0; i <= n;++i){
		ck_assert_double_eq(correct_res1[i], res[i]);
	}

	free(res);
	double correct_res2[] = {11.0, 9.0, 2.0};
	n = 2;
	a = 2.0;
	errorMsg = DecompositionPolynomial(1e-16, a, &res, n, 1.0, 1.0, 2.0);
	ck_assert_int_eq(errorMsg, NORMAL);
	for (int i = 0; i <= n; ++i) {
		ck_assert_double_eq(correct_res2[i], res[i]);
	}
	free(res);

	double correct_res3[] = {6298.800000, 16535.000000, 18580.400000, 11706.100000, 4568.100000, 1138.300000, 172.000000, 12.200000};
	n = 7;
	errorMsg =
	    DecompositionPolynomial(1e-16, 2.0, &res, n, 12.0, 13.0, -4.2, 5.3, 89.1, 99.1, 1.2, 12.2);
	ck_assert_int_eq(errorMsg, NORMAL);
	for (int i = 0; i <= n; ++i) {
		ck_assert_double_eq_tol(correct_res3[i], res[i], 1e-10);
	}
	free(res);

//	double correct_res4[] = {6298.800000, 16535.000000, 18580.400000, 11706.100000, 4568.100000, 1138.300000, 172.000000, 12.200000};
	n = 7;
	errorMsg =
	    DecompositionPolynomial(-1e-16, 2.0, &res, n, 12.0, 13.0, -4.2, 5.3, 89.1, 99.1, 1.2, 12.2);
	ck_assert_int_eq(errorMsg, INCORRECT_OPTIONS_ERROR);
}

Suite* ex10_quite(){
	Suite *s;
	s = suite_create("ex10");
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, decompositionpolynomial);

	suite_add_tcase(s, tc_core);
	return s;
}