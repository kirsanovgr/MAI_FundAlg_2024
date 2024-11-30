#include <check.h>
#include "func.h"
#include <math.h>

double test_function(double x) {
    return x * x - 2.0;
}

START_TEST(test_dychotomy_success) {
    double root;
    StatusCode status = Dychotomy(0, 2, test_function, 1e-6, &root);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert(fabs(root - sqrt(2)) < 1e-6);
}
END_TEST

START_TEST(test_dychotomy_invalid_bounds) {
    double root;
    StatusCode status = Dychotomy(2, 2, test_function, 1e-6, &root);
    ck_assert_int_eq(status, ERROR_NO_ROOT);
}
END_TEST

Suite *dychotomy_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Dychotomy (task 7)");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_dychotomy_success);
    tcase_add_test(tc_core, test_dychotomy_invalid_bounds);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = dychotomy_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}