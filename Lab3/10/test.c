#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "task_10.c"

START_TEST(test_create_node) {
    Node *node = create_node('A');
    ck_assert_ptr_nonnull(node);
    ck_assert_int_eq(node->label, 'A');
    ck_assert_int_eq(node->child_count, 0);
    free_tree(node);
}
END_TEST

START_TEST(test_add_child) {
    Node *parent = create_node('A');
    Node *child = create_node('B');
    StatusCode status = add_child(parent, child);

    ck_assert_int_eq(status, SUCCESS);
    ck_assert_int_eq(parent->child_count, 1);
    ck_assert_ptr_eq(parent->children[0], child);

    free_tree(parent);
}
END_TEST

START_TEST(test_parse_expression) {
    const char *expr = "A(B,C(D,E))";
    Node *root = parse_expression(expr);
    ck_assert_ptr_nonnull(root);
    ck_assert_int_eq(root->label, 'A');
    ck_assert_int_eq(root->child_count, 2);
    ck_assert_int_eq(root->children[0]->label, 'B');
    ck_assert_int_eq(root->children[1]->label, 'C');
    free_tree(root);
}
END_TEST

Suite *tree_suite(void) {
    Suite *s = suite_create("Tree");

    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_create_node);
    tcase_add_test(tc_core, test_add_child);
    tcase_add_test(tc_core, test_parse_expression);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s = tree_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}