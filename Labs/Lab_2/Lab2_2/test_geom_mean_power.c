#include <check.h>
#include <math.h>
#include "geom_mean_power.h" 

typedef enum {
    EXIT_SUCCESS = 0,
    EXIT_FAILURE
} Status;

START_TEST(test_geometric_mean_success) {
    double result;
    int status = geometric_mean(&result, 3, 4.0, 8.0, 16.0);
    ck_assert_int_eq(status, EXIT_SUCCESS);
    ck_assert(fabs(result - 8.0) < 1e-6);
}
END_TEST

START_TEST(test_geometric_mean_invalid_argument) {
    double result;
    int status = geometric_mean(&result, 2, 0.0, 8.0);
    ck_assert_int_eq(status, EXIT_FAILURE);
}
END_TEST

// Тесты для функции power
START_TEST(test_power_positive_exponent) {
    double result = power(2.0, 10);
    ck_assert(fabs(result - 1024.0) < 1e-6);
}
END_TEST

START_TEST(test_power_negative_exponent) {
    double result = power(2.0, -2);
    ck_assert(fabs(result - 0.25) < 1e-6);
}
END_TEST

START_TEST(test_power_zero_exponent) {
    double result = power(5.0, 0);
    ck_assert(fabs(result - 1.0) < 1e-6);
}
END_TEST

// Создание тестовой группы
Suite *geom_mean_power_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Geometric Mean and Power (task 2)");

    // Добавляем тесты для геометрического среднего
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_geometric_mean_success);
    tcase_add_test(tc_core, test_geometric_mean_invalid_argument);

    // Добавляем тесты для возведения в степень
    tcase_add_test(tc_core, test_power_positive_exponent);
    tcase_add_test(tc_core, test_power_negative_exponent);
    tcase_add_test(tc_core, test_power_zero_exponent);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = geom_mean_power_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
