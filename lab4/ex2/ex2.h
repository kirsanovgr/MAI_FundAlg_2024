
#ifndef LAB4_EX2_H
#define LAB4_EX2_H

#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/vector/charvector.h"
#include "../lib/vector/intvector.h"

#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b

error_msg get_arr(IntVector** arrays, char c, IntVector** vec);
void destroy_arrays(IntVector** arrays);

error_msg read_command(FILE* stream, String* command);

error_msg read_instructions(IntVector** arrays, String* filename);

// Инструкции
error_msg load_arr(IntVector** arrays, char c, String* filename);
error_msg save_arr(IntVector** arrays, char c, String* filename);
error_msg rand_arr(IntVector** arrays, char c, int count_numbers, int left_border_numbers, int right_border_numbers);
error_msg concatenate_arrays(IntVector** arrays, char a, char b);
error_msg free_arr(IntVector** arrays, char name);
error_msg remove_arr(IntVector** arrays, char a, int start_index, int count);
error_msg copy_arr(IntVector** arrays, char name1, char name2, int start_index, int end_index);
error_msg sort_arr(IntVector** arrays, char name, char comp);
error_msg shuffle_arr(IntVector** arrays, char name);
error_msg stats_arr(IntVector** arrays, char name);
error_msg print_all(IntVector** array, char name);
error_msg print_section(IntVector** array, char name, int start_index, int end_index);
error_msg print_el(IntVector** array, char name, int index);

// Парсеры для инструкций
error_msg parser_for_save_arr(IntVector** array, String* instruction);
error_msg parser_for_load_arr(IntVector** array, String* instruction);
error_msg parser_for_rand_arr(IntVector** arrays, String* instruction);
error_msg parser_for_concatenate_arr(IntVector** arrays, String* instruction);
error_msg parser_for_free_arr(IntVector** arrays, String* instruction);
error_msg parser_for_remove_arr(IntVector** arrays, String* instruction);
error_msg parser_for_remove_arr(IntVector** arrays, String* instruction);
error_msg parser_for_copy_arr(IntVector** arrays, String* instruction);
error_msg parser_for_sort_arr(IntVector** arrays, String* instruction);
error_msg parser_for_shuffle_arr(IntVector** arrays, String* instruction);
error_msg parser_for_stats_arr(IntVector** arrays, String* instruction);
error_msg parser_for_print(IntVector** arrays, String* instruction);

// Компораторы
int cmp_greater(const void* a, const void* b);
int cmp_less(const void* a, const void* b);
int cmp_rand(const void* a, const void* b);

#endif  // LAB4_EX2_H
