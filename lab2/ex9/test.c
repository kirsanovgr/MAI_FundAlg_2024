#include "test.h"

START_TEST(test_corect_fraction_in_different){
	StringVector * vec = create_string_vector(1);
	error_msg errorMsg = AreCorrectFractions(vec, 10, 3, 0.15, 0.18, 0.2);
	ck_assert_int_eq(errorMsg, SUCCESS);
	ck_assert_str_eq(vec->data[0],"Fraction 0.150000 has finite representation in base 10");
	ck_assert_str_eq(vec->data[1],"Fraction 0.180000 has finite representation in base 10");
	ck_assert_str_eq(vec->data[2],"Fraction 0.200000 has finite representation in base 10");

	errorMsg = AreCorrectFractions(vec, 10, 3, 3.15, 0.18, 0.2);
	ck_assert_int_eq(errorMsg, INCORRECT_OPTIONS_ERROR);

	errorMsg = AreCorrectFractions(vec, -2, 3, 3.15, 0.18, 0.2);
	ck_assert_int_eq(errorMsg, NUMERAL_SYSTEM_ERROR);

	errorMsg = AreCorrectFractions(vec, 37, 3, 3.15, 0.18, 0.2);
	ck_assert_int_eq(errorMsg, NUMERAL_SYSTEM_ERROR);

	errorMsg = AreCorrectFractions(vec, 8, 3, 0.125, 0.18, 0.2);
	ck_assert_int_eq(errorMsg, SUCCESS);
	ck_assert_str_eq(vec->data[0],"Fraction 0.125000 has finite representation in base 8");
	ck_assert_str_eq(vec->data[1],"Fraction 0.180000 hasn't finite representation in base 8");
	ck_assert_str_eq(vec->data[2],"Fraction 0.200000 hasn't finite representation in base 8");


	errorMsg = AreCorrectFractions(vec, 17, 3, 0.66666666666666666667, 0.13538, 0.2);
	ck_assert_int_eq(errorMsg, SUCCESS);
	ck_assert_str_eq(vec->data[0],"Fraction 0.666667 hasn't finite representation in base 17");
	ck_assert_str_eq(vec->data[1],"Fraction 0.135380 hasn't finite representation in base 17");
	ck_assert_str_eq(vec->data[2],"Fraction 0.200000 hasn't finite representation in base 17");

	errorMsg = AreCorrectFractions(vec, 2, 1, 0.5);
	ck_assert_int_eq(errorMsg, SUCCESS);
	ck_assert_str_eq(vec->data[0],"Fraction 0.500000 has finite representation in base 2");

	errorMsg = AreCorrectFractions(vec, 30, 7, 0.45, 0.18, 0.2, 0.122111, 0.1111110, 0.123456, 0.101010);
	ck_assert_int_eq(errorMsg, SUCCESS);
	ck_assert_str_eq(vec->data[0],"Fraction 0.450000 has finite representation in base 30");
	ck_assert_str_eq(vec->data[1],"Fraction 0.180000 has finite representation in base 30");
	ck_assert_str_eq(vec->data[2],"Fraction 0.200000 has finite representation in base 30");
	ck_assert_str_eq(vec->data[3],"Fraction 0.122111 has finite representation in base 30");
	ck_assert_str_eq(vec->data[4],"Fraction 0.111111 has finite representation in base 30");
	ck_assert_str_eq(vec->data[5],"Fraction 0.123456 has finite representation in base 30");
	ck_assert_str_eq(vec->data[6],"Fraction 0.101010 has finite representation in base 30");

	errorMsg = AreCorrectFractions(vec, 16, 2, 0.125, 0.25);
	ck_assert_int_eq(errorMsg, SUCCESS);
	ck_assert_str_eq(vec->data[0],"Fraction 0.125000 has finite representation in base 16");

	ck_assert_str_eq(vec->data[1],"Fraction 0.250000 has finite representation in base 16");
	destroy_string_vector(vec);


}
END_TEST

Suite* ex9_quite(){
	Suite *s;
	s = suite_create("ex9");
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_corect_fraction_in_different);

	suite_add_tcase(s, tc_core);
	return s;
}