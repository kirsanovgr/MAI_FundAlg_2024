//
// Created by matvey on 10/17/24.
//

#include "test.h"


long double func1(long double x){
	return log(x) + 0.5;
}

long double func2(long double x){
	return tan(x) + x;
}

long double func3(long double x){
	return cos(x) + 1;
}



START_TEST(test_dichotomy){

		long double result = calculate_dichotomy(func1, 0, 5, 0.00001);
	    ck_assert_double_eq_tol(result, 0.60653, 0.00001);

	    result = calculate_dichotomy(func2, 1, 5, 0.000000001);
	    ck_assert_double_eq_tol(result, 2.02876, 0.0001);

	    result = calculate_dichotomy(func2, 3, 5, 0.000000001);
	    ck_assert_double_eq_tol(result, 5, 0.0001);

	    result = calculate_dichotomy(func3, 0, 5, 0.000000001);
	    ck_assert_double_eq_tol(result, 5, 0.0001);

	    result = calculate_dichotomy(func3, 0, 5, -0.000000001);
	    ck_assert_double_eq_tol(result, -404, 0.0001);
}
END_TEST

Suite* ex7_suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Ex7");

	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_dichotomy);
	suite_add_tcase(s, tc_core);

	return s;
}