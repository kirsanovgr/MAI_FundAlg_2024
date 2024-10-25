#include <check.h>
#include "main.h" // Include your main header file here

START_TEST(test_overfscanf_valid_input_fn) {
    FILE* stream = fopen("test_valid_input.txt", "w+");
    int res0, res1, res2;

    // Write test data to the file
    fprintf(stream, "   10 20 30\n");

    // Reset the file pointer to the beginning
    rewind(stream);
    
    // Call your function
    int err = overfscanf(stream, "%d %d %d", &res0, &res1, &res2);
    
    // Check results
    ck_assert_int_eq(err, 0); // Ensure no error
    ck_assert_int_eq(res0, 10); // Ensure first value is correct
    ck_assert_int_eq(res1, 20); // Ensure second value is correct
    ck_assert_int_eq(res2, 30); // Ensure third value is correct

    fclose(stream);
}
END_TEST

START_TEST(test_overfscanf_invalid_input_fn) {
    FILE* stream = fopen("test_invalid_input.txt", "w+");
    int res0, res1, res2;

    // Write invalid test data to the file
    fprintf(stream, "abc def ghi\n");

    // Reset the file pointer to the beginning
    rewind(stream);
    
    // Call your function
    int err = overfscanf(stream, "%d %d %d", &res0, &res1, &res2);
    
    // Check results
    ck_assert_int_eq(err, INCORRECT_ARGUMENTS); // Ensure the correct error is returned

    fclose(stream);
}
END_TEST

Suite* overfscanf_suite(void) {
    Suite* s;
    TCase* tc_core;

    s = suite_create("OverFscanf");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_overfscanf_valid_input_fn);
    tcase_add_test(tc_core, test_overfscanf_invalid_input_fn);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = overfscanf_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? 0 : 1;
}
