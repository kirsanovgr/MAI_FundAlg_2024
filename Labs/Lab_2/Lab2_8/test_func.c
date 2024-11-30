#include <check.h>
#include "func.h"


START_TEST(test_sum_in_base_with_zero) {
    char* result = sum_in_base(10, 3, "0", "0", "0");
    ck_assert_str_eq(result, "0"); // 0 + 0 + 0 = 0
    free(result);
}

START_TEST(test_sum_in_base_large_numbers) {
    char* result = sum_in_base(36, 2, "Z", "Z"); // Z (35) + Z (35) = 70
    ck_assert_str_eq(result, "1Y"); // 70 в 36-й системе = 1Y
    free(result);
}

Suite* sum_suite(void) {
    Suite* s;
    TCase* tc_core;

    s = suite_create("Sum (task 8)");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_sum_in_base_with_zero);
    tcase_add_test(tc_core, test_sum_in_base_large_numbers);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = sum_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
