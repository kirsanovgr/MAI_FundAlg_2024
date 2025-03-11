#include <check.h>
#include "func.h"

// Test for Roman numeral conversion
START_TEST(test_int_to_roman) {
    char result[20];
    int_to_roman(42, result);
    ck_assert_str_eq(result, "XLII");
}
END_TEST

// Test for Fibonacci reverse printing
START_TEST(test_print_fibonacci_reverse) {
    FILE *stream = fopen("test_output.txt", "w");
    print_fibonacci_reverse(3, stream);
    fclose(stream);
    
    stream = fopen("test_output.txt", "r");
    char buffer[100];
    fgets(buffer, 100, stream);
    fclose(stream);
    
    ck_assert_str_eq(buffer, "1 1 0");
}
END_TEST

Suite *func_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Overfprintf (task 5)");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_int_to_roman);
    tcase_add_test(tc_core, test_print_fibonacci_reverse);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = func_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
