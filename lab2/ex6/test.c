#include "test.h"

// Тест для функции overfscanf
START_TEST(test_overfscanf)
{
	FILE *file;
	int res_int;
	unsigned int res_uint;
	int count;

	file = fopen("ex6/test_input.txt", "w");
	if (!file) {
		ck_abort_msg("Failed to open file for writing");
	}

	// Записываем данные в файл
	fprintf(file, "Roman: MCMLXXXIV\n");
	fprintf(file, "Zr: 010001\n");
	fprintf(file, "Base 16: ff\n");
	fprintf(file, "Base 16 Upper: FF\n");
	fprintf(file, "|||12|||13()12.24343\n");
	fprintf(file, "|||12|||13()12.24343 sdf\n");
	fclose(file);

	// Открываем файл для чтения
	file = fopen("ex6/test_input.txt", "r");
	if (!file) {
		ck_abort_msg("Failed to open file for reading");
	}

	// Тест 1: Римские числа
	count = overfscanf(file, "Roman: %Ro", &res_int);
	ck_assert_int_eq(count, 1);
	ck_assert_int_eq(res_int, 1984);

	// Тест 2: Числа Фибоначчи
	count = overfscanf(file, "Zr: %Zr", &res_uint);
	ck_assert_int_eq(count, 1);
	ck_assert_int_eq(res_uint, 9);

	// Тест 3: Преобразование в другую систему счисления
	count = overfscanf(file, "Base 16: %Cv", &res_int, 16);
	ck_assert_int_eq(count, 1);
	ck_assert_int_eq(res_int, 255);

	// Тест 4: Преобразование в другую систему счисления с верхним регистром
	count = overfscanf(file, "Base 16 Upper: %CV", &res_int, 16);
	ck_assert_int_eq(count, 1);
	ck_assert_int_eq(res_int, 255);

	int x = 0;
	int y = 0;
	double s = 0;
	count = overfscanf(file, "|||%d|||%d()%lf", &x, &y, &s);
	ck_assert_int_eq(count, 3);
	ck_assert_int_eq(x, 12);
	ck_assert_int_eq(y, 13);

	x = 0;
	y = 0;
	char ss[100];
	ss[0] = '\0';
	count = overfscanf(file, "|||%d|||%d()%lf %s", &x, &y, &s, ss);
	ck_assert_int_eq(count, 4);
	ck_assert_int_eq(x, 12);
	ck_assert_int_eq(y, 13);
	ck_assert_str_eq(ss, "sdf");

	fclose(file);
	remove("test_input.txt");
}
END_TEST


START_TEST(test_oversscanf)
{
	char buffer[256];
	int res_int;
	unsigned int res_uint;
	int count;

	// Тест 1: Римские числа
	strcpy(buffer, "Roman: MCMLXXXIV");
	count = oversscanf(buffer, "Roman: %Ro", &res_int);
	ck_assert_int_eq(count, 1);
	ck_assert_int_eq(res_int, 1984);

	// Тест 2: Числа Фибоначчи
	strcpy(buffer, "Zr: 010001");
	count = oversscanf(buffer, "Zr: %Zr", &res_uint);
	ck_assert_int_eq(count, 1);
	ck_assert_int_eq(res_uint, 9);

	// Тест 3: Преобразование в другую систему счисления
	strcpy(buffer, "Base 16: ff");
	count = oversscanf(buffer, "Base 16: %Cv", &res_int, 16);
	ck_assert_int_eq(count, 1);
	ck_assert_int_eq(res_int, 255);

	// Тест 4: Преобразование в другую систему счисления с верхним регистром
	strcpy(buffer, "Base 16 Upper: FF");
	count = oversscanf(buffer, "Base 16 Upper: %CV", &res_int, 16);
	ck_assert_int_eq(count, 1);
	ck_assert_int_eq(res_int, 255);

}
END_TEST

Suite* ex6_suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Ex6");

	// Core test case
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_overfscanf);
	tcase_add_test(tc_core, test_oversscanf);
	suite_add_tcase(s, tc_core);

	return s;
}

