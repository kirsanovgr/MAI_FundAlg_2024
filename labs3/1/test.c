#include <check.h>
#include <stdlib.h>
#include "task_1.c"

START_TEST(test_addition) {
    ck_assert_int_eq(add(5, 10), 15);
    ck_assert_int_eq(add(-5, 5), 0);
}
END_TEST

START_TEST(test_intToChar) {
    ck_assert_int_eq(intToChar(0), '0');
    ck_assert_int_eq(intToChar(10), 'A');
    ck_assert_int_eq(intToChar(15), 'F');
    ck_assert_int_eq(intToChar(-1), -1);
}
END_TEST

START_TEST(test_reverseString) {
    char str[] = "12345";
    reverseString(str);
    ck_assert_str_eq(str, "54321");
}
END_TEST

START_TEST(test_decimalToBase) {
    char result[BUFSIZ];
    decimalToBase(10, 1, result);
    ck_assert_str_eq(result, "1010");

    decimalToBase(255, 4, result);
    ck_assert_str_eq(result, "FF");
}
END_TEST

Suite *create_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Core");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_addition);
    tcase_add_test(tc_core, test_intToChar);
    tcase_add_test(tc_core, test_reverseString);
    tcase_add_test(tc_core, test_decimalToBase);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = create_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}