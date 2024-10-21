#include <check.h>
#include "func.h"

START_TEST(test_finite_representation) {
    int base = 10;
    ck_assert_int_eq(has_finite_representation(base, 3, 0.5, 0.333, 0.2), SUCCESS);
}
END_TEST

Suite *finite_representation_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Finite Representation (task 9)");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_finite_representation);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = finite_representation_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
