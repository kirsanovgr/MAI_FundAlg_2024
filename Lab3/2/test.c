#define _CRT_SECURE_NO_WARNINGS
#include <check.h>
#include <stdlib.h>
#include <math.h>
#include "task_2.c"

START_TEST(test_max_norm) {
    Vector vectors[2];
    double coords1[] = {1.0, -2.0, 3.0};
    double coords2[] = {4.0, 5.0, -6.0};

    vectors[0].coordinates = coords1;
    vectors[0].dimension = 3;
    vectors[1].coordinates = coords2;
    vectors[1].dimension = 3;

    double norm1 = maxNorm(&vectors[0]);
    double norm2 = maxNorm(&vectors[1]);

    ck_assert_double_eq(norm1, 3.0);
    ck_assert_double_eq(norm2, 6.0);
}
END_TEST

START_TEST(test_l1_norm) {
    Vector vectors[2];
    double coords1[] = {1.0, -2.0, 3.0};
    double coords2[] = {4.0, -5.0, -6.0};

    vectors[0].coordinates = coords1;
    vectors[0].dimension = 3;
    vectors[1].coordinates = coords2;
    vectors[1].dimension = 3;

    double norm1 = l1Norm(&vectors[0]);
    double norm2 = l1Norm(&vectors[1]);

    ck_assert_double_eq(norm1, 6.0);
    ck_assert_double_eq(norm2, 15.0);
}
END_TEST

START_TEST(test_find_longest_vectors) {
    Vector vectors[3];
    double coords1[] = {1.0, -2.0, 3.0};
    double coords2[] = {4.0, 5.0, -6.0};
    double coords3[] = {2.0, 2.0, 2.0};

    vectors[0].coordinates = coords1;
    vectors[0].dimension = 3;
    vectors[1].coordinates = coords2;
    vectors[1].dimension = 3;
    vectors[2].coordinates = coords3;
    vectors[2].dimension = 3;

    Vector** longestVectors;
    int longestCount;

    StatusCode status = findLongestVectors(3, vectors, 3, maxNorm, &longestVectors, &longestCount);

    ck_assert_int_eq(status, SUCCESS);
    ck_assert_int_eq(longestCount, 1);
    ck_assert_double_eq(maxNorm(longestVectors[0]), 6.0);
    free(longestVectors);
}
END_TEST

Suite* vectors_suite(void) {
    Suite* s;
    TCase* tc_core;

    s = suite_create("Vectors");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_max_norm);
    tcase_add_test(tc_core, test_l1_norm);
    tcase_add_test(tc_core, test_find_longest_vectors);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = vectors_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
