#include <check.h>
#include "func.h"
#include <stdlib.h>

START_TEST(test_transform_polynomial_basic) {
    double epsilon = 1e-5; // Allowable error
    double *new_coeff = NULL;

    int n = 2; 
    double a = 2.0;
    int res = transform_polynomial(epsilon, a, n, &new_coeff, 1.0, 2.0, 3.0);
    
    ck_assert_int_eq(res, 0);

    ck_assert(fabsl(17.0 - new_coeff[0]) < epsilon);  // g0 = 17
    ck_assert(fabsl(14.0 - new_coeff[1]) < epsilon);  // g1 = 14
    ck_assert(fabsl(3.0 - new_coeff[2]) < epsilon);   //  g2 = 3

    free(new_coeff);
}
END_TEST

Suite *polynomial_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Polynomial (task 10)");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_transform_polynomial_basic);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = polynomial_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
