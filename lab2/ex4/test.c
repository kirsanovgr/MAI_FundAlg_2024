#include "test.h"

START_TEST(test_is_convex_polygon) {
	Point p1 = {0.0, 0.0};
	Point p2 = {4.0, 0.0};
	Point p3 = {4.0, 4.0};
	Point p4 = {0.0, 4.0};

	ck_assert_int_eq(IsConvexPolygon(4, p1, p2, p3, p4), 1);

	Point p5 = {2.0, 2.0};
	ck_assert_int_eq(IsConvexPolygon(4, p1, p2, p5, p4), 0);

	ck_assert_int_eq(IsConvexPolygon(3, p1, p2, p3), 1);

	ck_assert_int_eq(IsConvexPolygon(1, p1), 1);

	ck_assert_int_eq(IsConvexPolygon(2, p1, p2), 1);
}
END_TEST

START_TEST(test_value_of_polynomial) {
	ck_assert_double_eq_tol(ValueOfPolynomial(2.0, 3, 2.0, 3.0, 1.0), 15.0, 1e-6);

	ck_assert_double_eq_tol(ValueOfPolynomial(5.0, 1, 1.0), 1.0, 1e-6);

	ck_assert_double_eq_tol(ValueOfPolynomial(10.0, 1, 0.0), 0.0, 1e-6);

	ck_assert_double_eq_tol(ValueOfPolynomial(0.0, 1, 3.0), 3.0, 1e-6);

	ck_assert_double_eq_tol(ValueOfPolynomial(1.0, 4, 5.0, 4.0, 3.0, 2.0), 14.0, 1e-6);
}
END_TEST

START_TEST(test_find_numbers_karper) {
	StringVector *vec = create_string_vector(1);
	error_msg error;

	error = FindNumbersKarper(vec, -1, 2, "12", "1234");
	ck_assert_int_eq(error, NUMERAL_SYSTEM_ERROR);

	error = FindNumbersKarper(vec, 10, 2, "a", "1234");
	ck_assert_int_eq(error, UNRECOGNIZED_CHARACTER_ERROR);

	error = FindNumbersKarper(vec, 10, 3, "123", "456", "789");
	ck_assert_int_eq(error, NORMAL);
	ck_assert_int_eq(vec->size, 0);

	error = FindNumbersKarper(vec, 16, 2, "1A", "2B");
	ck_assert_int_eq(error, NORMAL);
	ck_assert_int_eq(vec->size, 0);

	error = FindNumbersKarper(vec, 1, 1, "1");
	ck_assert_int_eq(error, NUMERAL_SYSTEM_ERROR);


	error = FindNumbersKarper(vec, 37, 1, "1");
	ck_assert_int_eq(error, NUMERAL_SYSTEM_ERROR);

	error = FindNumbersKarper(vec, 2, 2, "101", "110");
	ck_assert_int_eq(error, NORMAL);
	ck_assert_int_eq(vec->size, 0);

	error = FindNumbersKarper(vec, 16, 7, "0001745E", "13", "23", "7FE00", "80200", "fedacb", "85BD9");
	ck_assert_int_eq(error, NORMAL);
	ck_assert_int_eq(vec->size, 4);
	ck_assert_str_eq("1745E", vec->data[0]);

	destroy_string_vector(vec);
}
END_TEST

Suite *ex4_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("Ex4");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_is_convex_polygon);
	tcase_add_test(tc_core, test_value_of_polynomial);
	tcase_add_test(tc_core, test_find_numbers_karper);
	suite_add_tcase(s, tc_core);

	return s;
}
