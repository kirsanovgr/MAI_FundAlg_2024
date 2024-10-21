#include <check.h>
#include "test_func.h"

START_TEST(test_is_convex_polygon) {
    double epsilon = 1e-6;
    ck_assert_int_eq(is_convex_polygon(epsilon, 4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0), 1);
}
END_TEST

START_TEST(test_evaluate_polynomial) {
    double epsilon = 1e-6;
    double result = evaluate_polynomial(epsilon, 2.0, 2, 1.0, -3.0, 2.0); // x^2 - 3x + 2
    ck_assert_double_eq(result, 0.0);
}
END_TEST

START_TEST(test_is_kaprekar_number_in_base) {
    // Здесь вы можете добавить более детальные проверки чисел Капрекара
    // Поскольку функция печатает результат, можно сделать отдельные проверки
    is_kaprekar_number_in_base(10, 3, "1", "9", "45"); // Проверка 1, 9, 45 в десятичной системе
}
END_TEST

Suite *polygon_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Polygon (task 4)");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_convex_polygon);
    tcase_add_test(tc_core, test_evaluate_polynomial);
    tcase_add_test(tc_core, test_is_kaprekar_number_in_base);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = polygon_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
