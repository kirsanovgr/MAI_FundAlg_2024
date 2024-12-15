
#include "test.h"


START_TEST(test_overfprintf) {
	FILE *file = fopen("test_output.txt", "w");
	if (!file) {
		ck_abort_msg("Failed to open file for writing");
	}

	// Тест 1: Римские числа
	int count = overfprintf(file, "Roman: %Ro\n", 1984);
	ck_assert_int_eq(count, 17);  // "Roman: MCMLXXXIV"

	// Тест 2: Числа Фибоначчи
	count = overfprintf(file, "Zr: %Zr\n", 100);
	ck_assert_int_eq(count, 16);  // "Zr: 00010100001"

	// Тест 3: Преобразование в другую систему счисления
	count = overfprintf(file, "Base 16: %Cv\n", 255, 16);
	ck_assert_int_eq(count, 12);  // "Base 16: ff"

	// Тест 4: Преобразование в другую систему счисления с верхним регистром
	count = overfprintf(file, "Base 16 Upper: %CV\n", 255, 16);
	ck_assert_int_eq(count, 18);  // "Base 16 Upper: FF"

	// Тест 5: Преобразование из другой системы счисления в десятичную
	count = overfprintf(file, "From Base 16: %to\n", "ff", 16);
	ck_assert_int_eq(count, 18);  // "From Base 16: 255"

	// Тест 6: Дамп памяти для int32_t
	int32_t value = -1234567890;
	count = overfprintf(file, "Memory Dump: %mi\n", value);
	ck_assert_int_eq(count, 50);  // "Memory Dump: 00101110 11111101 01101001 10110110"

	fclose(file);

}
END_TEST

START_TEST(test_oversprintf) {
	char buffer[256];

	// Тест 1: Римские числа
	int count = oversprintf(buffer, "Roman: %Ro", 1984);
	ck_assert_int_eq(count, 16);  // "Roman: MCMLXXXIV"
	ck_assert_str_eq(buffer, "Roman: MCMLXXXIV");

	// Тест 2: Числа Фибоначчи
	count = oversprintf(buffer, "Zr: %Zr", 100);
	ck_assert_int_eq(count, 15);  // "Zr: 00010100001"
	ck_assert_str_eq(buffer, "Zr: 00010100001");

	// Тест 3: Преобразование в другую систему счисления
	count = oversprintf(buffer, "Base 16: %Cv", 255, 16);
	ck_assert_int_eq(count, 11);  // "Base 16: ff"
	ck_assert_str_eq(buffer, "Base 16: ff");

	// Тест 4: Преобразование в другую систему счисления с верхним регистром
	count = oversprintf(buffer, "Base 16 Upper: %CV", 255, 16);
	ck_assert_int_eq(count, 17);  // "Base 16 Upper: FF"
	ck_assert_str_eq(buffer, "Base 16 Upper: FF");

	// Тест 5: Преобразование из другой системы счисления в десятичную
	count = oversprintf(buffer, "From Base 16: %to", "ff", 16);
	ck_assert_int_eq(count, 17);  // "From Base 16: 255"
	ck_assert_str_eq(buffer, "From Base 16: 255");

	// Тест 6: Дамп памяти для int32_t
	int32_t value = -1234567890;
	count = oversprintf(buffer, "Memory Dump: %mi", value);
	ck_assert_int_eq(count, 49);  // "Memory Dump: 00101110 11111101 01101001 10110110 "
	ck_assert_str_eq(buffer, "Memory Dump: 00101110 11111101 01101001 10110110 ");
}
END_TEST


Suite *overloads_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("Ex5");


	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_overfprintf);
	tcase_add_test(tc_core, test_oversprintf);
	suite_add_tcase(s, tc_core);

	return s;
}
