#include <check.h>
#include "func.h"

START_TEST(test_oversscanf_roman) {
    int roman;
    ck_assert_int_eq(oversscanf("XIII", "%Ro", &roman), 0);
    ck_assert_int_eq(roman, 13);
}

START_TEST(test_oversscanf_zeckendorf) {
    int zeckendorf;
    ck_assert_int_eq(oversscanf("100101", "%Zg", &zeckendorf), 0);
    ck_assert_int_eq(zeckendorf, 31); 
}

START_TEST(test_oversscanf_base8) {
    int base8;
    ck_assert_int_eq(oversscanf("12345", "%Cv", &base8, 8), 0);
    ck_assert_int_eq(base8, 5349); 
}

Suite *create_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Function Tests (task 6)");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_oversscanf_roman);
    tcase_add_test(tc_core, test_oversscanf_zeckendorf);
    tcase_add_test(tc_core, test_oversscanf_base8);
    
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

    return (number_failed == 0) ? 0 : 1;
}
