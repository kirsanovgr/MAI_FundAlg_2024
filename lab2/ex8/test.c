#include "test.h"

START_TEST(test_addition_numbers) {
	char result1[100];
	error_msg error1 = AdditionManyNumbers(result1, 10, 3, "0000000000000000000000000000000123", "456", "789");

	ck_assert_int_eq(error1, SUCCESS);
	ck_assert_str_eq(result1, "1368");

	char result2[100];
	error_msg error2 = AdditionManyNumbers(result2, 16, 4, "1a", "2b", "3c", "4d");
	ck_assert_int_eq(error2, SUCCESS);
	ck_assert_str_eq(result2, "ce");

	char result3[100];
	error_msg error3 = AdditionManyNumbers(result3, 10, 5, "123", "456", "789", "1011", "2345");
	ck_assert_int_eq(error3, SUCCESS);
	ck_assert_str_eq(result3, "4724");

	char result4[100];
	error_msg error4 = AdditionManyNumbers(result4, 16, 3, "ffff", "1", "1");
	ck_assert_int_eq(error4, SUCCESS);
	ck_assert_str_eq(result4, "10001");

	char result5[100];
	error_msg error5 = AdditionManyNumbers(result5, 8, 3, "777", "1", "1");
	ck_assert_int_eq(error5, SUCCESS);
	ck_assert_str_eq(result5, "1001");


	char result6[100];
	error_msg error6 = AdditionManyNumbers(result6, 2, 3, "1;11", "1", "1");
	ck_assert_int_eq(error6, UNRECOGNIZED_CHARACTER_ERROR);

	char result7[100];
	error_msg error7 = AdditionManyNumbers(result7, 10, 2, "000123", "000456");
	ck_assert_int_eq(error7, SUCCESS);
	ck_assert_str_eq(result7, "579");

	char result8[100];
	error_msg error8 = AdditionManyNumbers(result8, 10, 2, "999", "1");
	ck_assert_int_eq(error8, SUCCESS);
	ck_assert_str_eq(result8, "1000");

	char result9[100];
	error_msg error9 = AdditionManyNumbers(result9, -2, 2, "999", "1");
	ck_assert_int_eq(error9, NUMERAL_SYSTEM_ERROR);


}
END_TEST

Suite *ex8_quite() {
	Suite *s;
	s = suite_create("ex8");
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_addition_numbers);

	suite_add_tcase(s, tc_core);
	return s;
}