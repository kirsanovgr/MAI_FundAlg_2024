#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "task_3.c"

Employee* create_test_data(int* count) {
    *count = 5;
    Employee* employees = malloc(*count * sizeof(Employee));
    
    employees[0].id = 1;
    employees[0].name = strdup("John");
    employees[0].surname = strdup("Doe");
    employees[0].salary = 50000;

    employees[1].id = 2;
    employees[1].name = strdup("Alice");
    employees[1].surname = strdup("Smith");
    employees[1].salary = 60000;

    employees[2].id = 3;
    employees[2].name = strdup("Bob");
    employees[2].surname = strdup("Johnson");
    employees[2].salary = 50000;

    employees[3].id = 4;
    employees[3].name = strdup("Charlie");
    employees[3].surname = strdup("Brown");
    employees[3].salary = 70000;

    employees[4].id = 5;
    employees[4].name = strdup("Eve");
    employees[4].surname = strdup("Davis");
    employees[4].salary = 60000;

    return employees;
}

START_TEST(test_compare_employees) {
    Employee emp1 = {1, "John", "Doe", 50000};
    Employee emp2 = {2, "Alice", "Smith", 60000};
    
    ck_assert_int_lt(compareEmployees(&emp1, &emp2), 0);
    ck_assert_int_gt(compareEmployees(&emp2, &emp1), 0);
}

START_TEST(test_sort_employees) {
    int count;
    Employee* employees = create_test_data(&count);
    sortEmployees(employees, count, 1);

    ck_assert_str_eq(employees[0].name, "John");
    ck_assert_str_eq(employees[1].name, "Bob");
    ck_assert_str_eq(employees[2].name, "Alice");
    ck_assert_str_eq(employees[3].name, "Eve");
    ck_assert_str_eq(employees[4].name, "Charlie");

    free(employees);
}

START_TEST(test_read_employees) {
    FILE* f = fopen("test_input.txt", "w");
    fprintf(f, "1 John Doe 50000\n2 Alice Smith 60000\n3 Bob Johnson 50000\n4 Charlie Brown 70000\n5 Eve Davis 60000\n");
    fclose(f);

    FILE* input_file = fopen("test_input.txt", "r");
    ck_assert_ptr_nonnull(input_file);

    int employeeCount = 0;
    Employee* employees = NULL;
    char bufName[BUFSIZ], bufSurname[BUFSIZ];
    int id;
    float salary;

    while (fscanf(input_file, "%d %s %s %f", &id, bufName, bufSurname, &salary) == 4) {
        Employee* temp = (Employee*)realloc(employees, (employeeCount + 1) * sizeof(Employee));
        employees = temp;
        employees[employeeCount].id = id;
        employees[employeeCount].name = strdup(bufName);
        employees[employeeCount].surname = strdup(bufSurname);
        employees[employeeCount].salary = salary;
        employeeCount++;
    }
    fclose(input_file);

    ck_assert_int_eq(employees[0].id, 1);
    ck_assert_str_eq(employees[0].name, "John");
    ck_assert_str_eq(employees[0].surname, "Doe");
    ck_assert_float_eq(employees[0].salary, 50000);

    for (int i = 0; i < employeeCount; i++) {
        free(employees[i].name);
        free(employees[i].surname);
    }
    free(employees);
    remove("test_input.txt");
}

int main(void) {
    Suite* s;
    SRunner* sr;

    s = suite_create("Employee Tests");

    TCase* tc1 = tcase_create("Employee Comparison");
    tcase_add_test(tc1, test_compare_employees);
    suite_add_tcase(s, tc1);

    TCase* tc2 = tcase_create("Employee Sorting");
    tcase_add_test(tc2, test_sort_employees);
    suite_add_tcase(s, tc2);

    TCase* tc3 = tcase_create("Employee Reading");
    tcase_add_test(tc3, test_read_employees);
    suite_add_tcase(s, tc3);

    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
