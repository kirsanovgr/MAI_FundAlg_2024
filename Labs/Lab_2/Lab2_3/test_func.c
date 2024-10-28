#include <check.h>
#include "func.h"

START_TEST(test_len) {
    char test_str[] = "Hello, World!";
    ck_assert_int_eq(len(test_str), 13);
}

START_TEST(test_shift_table) {
    int result[256];
    char pattern[] = "ABABCA";
    ck_assert_int_eq(Shift_Table(pattern, len(pattern), result), 0);
    ck_assert_int_eq(result[0], 0);
    ck_assert_int_eq(result[1], 0);
    ck_assert_int_eq(result[2], 1);
    ck_assert_int_eq(result[3], 2);
}

START_TEST(test_substr) {
    char str[] = "abcabcabcd";
    char key[] = "abc";
    ck_assert_int_eq(Substr(str, len(str), key, len(key)), 0);
    ck_assert_int_eq(Substr(str, len(str), "xyz", len("xyz")), FILE_ERROR);
}

START_TEST(test_line_counter) {
    char str[] = "Line 1\nLine 2\nLine 3\n";
    ck_assert_int_eq(Line_Counter(str, len(str)), 4);
}

START_TEST(test_process_newline_in_substring) {
    char test_substr[MAX_SUBSTRING_LENGTH];
    snprintf(test_substr, sizeof(test_substr), "Hello\\nWorld");
    Process_Newline_In_Substring(test_substr);
    ck_assert_str_eq(test_substr, "Hello\nWorld");
}

Suite* create_suite(void) {
    Suite* s;
    TCase* tc_core;

    s = suite_create("Substring Tests (task 3)");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_len);
    tcase_add_test(tc_core, test_shift_table);
    tcase_add_test(tc_core, test_substr);
    tcase_add_test(tc_core, test_line_counter);
    tcase_add_test(tc_core, test_process_newline_in_substring);
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
