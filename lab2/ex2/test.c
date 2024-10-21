#include <check.h>
#include <math.h>
#include "ex2.h"


START_TEST(test_geometric_mean)
{
	double result;
	error_msg err;


	err = geometric_mean(&result, 3, 2.0, 4.0, 8.0);
	ck_assert_int_eq(err, NORMAL);
	ck_assert_double_eq_tol(result, 4.0, 1e-6);


	err = geometric_mean(&result, 3, 2.0, 1e-17, 8.0);
	ck_assert_int_eq(err, INCORRECT_OPTIONS_ERROR);


	err = geometric_mean(&result, 1, 2.0);
	ck_assert_int_eq(err, NORMAL);
	ck_assert_double_eq_tol(result, 2.0, 1e-6);


	err = geometric_mean(&result, 0);
	ck_assert_int_eq(err, NORMAL);
	ck_assert_double_eq_tol(result, 1.0, 1e-6);
}
END_TEST

// Тест для функции QuitPow
START_TEST(test_quit_pow)
{
	// Тест 1: Возведение в степень 0
	ck_assert_double_eq_tol(QuitPow(2.0, 0), 1.0, 1e-6);


	ck_assert_double_eq_tol(QuitPow(2.0, 3), 8.0, 1e-6);


	ck_assert_double_eq_tol(QuitPow(2.0, -3), 0.125, 1e-6);


	ck_assert_double_eq_tol(QuitPow(2.0, 1), 2.0, 1e-6);


	ck_assert_double_eq_tol(QuitPow(2.0, -1), 0.5, 1e-6);
}
END_TEST

Suite* ex2_suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Ex2");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_geometric_mean);
	tcase_add_test(tc_core, test_quit_pow);
	suite_add_tcase(s, tc_core);

	return s;
}
