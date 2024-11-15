#include "ex2.h"

error_msg get_arr(IntVector **arrays, char c, IntVector **vec) {
	if (c < 'A' || c > 'Z') {
		return INCORRECT_OPTIONS_ERROR;
	}
	int index = c - 'A';
	if (arrays[index]) {
		*vec = arrays[index];
	} else {
		error_msg errorMsg = create_int_vector(vec, 1);
		arrays[index] = *vec;
		if (errorMsg) {
			return errorMsg;
		}
	}
	return SUCCESS;
}

void destroy_arrays(IntVector **arrays) {
	for (int i = 0; i < 26; ++i) {
		if (arrays[i]) {
			destroy_int_vector(arrays[i]);
		}
	}
}

error_msg load_arr(IntVector **arrays, char c, String *filename) {
	IntVector *vector;
	error_msg errorMsg = get_arr(arrays, c, &vector);
	if (errorMsg) {
		return errorMsg;
	}

	FILE *stream = fopen(filename->arr, "r");
	if (!stream) {
		return INPUT_FILE_ERROR;
	}

	int d;
	String tmp;
	errorMsg = create_string(&tmp, "");
	if (errorMsg) {
		fclose(stream);
		return errorMsg;
	}
	int n;
	while (!feof(stream)) {
		clear_string(&tmp);
		n = read_string(stream, &tmp);
		if (n == 0) {
			break;
		}
		errorMsg = string_to_int(&tmp, &d);
		if (errorMsg) {
			fclose(stream);
			destroy_string(&tmp);
			return errorMsg;
		}

		errorMsg = push_end_intvector(vector, d);
		if (errorMsg) {
			fclose(stream);
			destroy_string(&tmp);
			return errorMsg;
		}
	}

	destroy_string(&tmp);
	fclose(stream);
	return SUCCESS;
}

error_msg save_arr(IntVector **arrays, char c, String *filename) {
	FILE *output = fopen(filename->arr, "w");
	if (!output) {
		return OUTPUT_FILE_ERROR;
	}

	IntVector *vector;
	error_msg errorMsg = get_arr(arrays, c, &vector);
	if (errorMsg) {
		fclose(output);
		return errorMsg;
	}

	print_intvector(output, vector, " ");
	fclose(output);
	return SUCCESS;
}

error_msg rand_arr(IntVector **arrays, char c, int count_numbers, int left_border_numbers, int right_border_numbers) {
	error_msg errorMsg;

	if (left_border_numbers > right_border_numbers || count_numbers < 0) {
		return INCORRECT_OPTIONS_ERROR;
	}

	IntVector *vector;
	errorMsg = get_arr(arrays, c, &vector);
	if (errorMsg) {
		return errorMsg;
	}
	for (int i = 0; i < count_numbers; ++i) {
		errorMsg =
		    push_end_intvector(vector, rand() % (right_border_numbers - left_border_numbers + 1) + left_border_numbers);
		if (errorMsg) {
			destroy_int_vector(vector);
			return errorMsg;
		}
	}

	return SUCCESS;
}

error_msg concatenate_arrays(IntVector **arrays, char a, char b) {
	IntVector *first;
	IntVector *second;
	error_msg errorMsg = get_arr(arrays, a, &first);
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = get_arr(arrays, b, &second);
	if (errorMsg) {
		return errorMsg;
	}
	for (int i = 0; i < second->size; ++i) {
		errorMsg = push_end_intvector(first, second->arr[i]);
		if (errorMsg) {
			return errorMsg;
		}
	}
	return SUCCESS;
}

error_msg free_arr(IntVector **arrays, char name) {
	IntVector *vector;
	error_msg errorMsg = get_arr(arrays, name, &vector);
	if (errorMsg) {
		return errorMsg;
	}
	vector->size = 0;
	return SUCCESS;
}

error_msg remove_arr(IntVector **arrays, char a, int start_index, int count) {
	if (start_index < 0 || count < 0) {
		return INCORRECT_OPTIONS_ERROR;
	}
	IntVector *arr;
	error_msg errorMsg = get_arr(arrays, a, &arr);
	if (errorMsg) {
		return errorMsg;
	}
	for (int i = start_index; i - start_index < count; ++i) {
		errorMsg = remove_int_vector(arr, start_index);
		if (errorMsg == INDEX_VECTOR_ERROR) {
			break;
		} else if (errorMsg) {
			return errorMsg;
		}
	}
	return SUCCESS;
}

error_msg copy_arr(IntVector **arrays, char name1, char name2, int start_index, int end_index) {
	if (start_index < 0 || start_index > end_index) {
		return INCORRECT_OPTIONS_ERROR;
	}
	IntVector *first;
	IntVector *second;
	error_msg errorMsg = get_arr(arrays, name1, &first);
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = get_arr(arrays, name2, &second);
	if (errorMsg) {
		return errorMsg;
	}
	second->size = 0;
	for (int i = start_index; i < first->size && i < end_index; ++i) {
		errorMsg = push_end_intvector(second, first->arr[i]);
		if (errorMsg) {
			return errorMsg;
		}
	}
	return SUCCESS;
}

int cmp_greater(const void *a, const void *b) { return (*((int *)a) - *((int *)b)); }

int cmp_less(const void *a, const void *b) { return -(*((int *)a) - *((int *)b)); }

int cmp_rand(const void *a, const void *b) { return (*((int *)a) - *((int *)b)) * (rand() % 3 - 1); }

error_msg sort_arr(IntVector **arrays, char name, char comp) {
	IntVector *vector;
	error_msg errorMsg = get_arr(arrays, name, &vector);
	if (errorMsg) {
		return errorMsg;
	}
	switch (comp) {
		case '+':
			qsort(vector->arr, vector->size, sizeof(int), cmp_greater);
			break;
		case '-':
			qsort(vector->arr, vector->size, sizeof(int), cmp_less);
			break;
		default:
			return INCORRECT_OPTIONS_ERROR;
	}
	return SUCCESS;
}

error_msg shuffle_arr(IntVector **arrays, char name) {
	IntVector *vector;
	error_msg errorMsg = get_arr(arrays, name, &vector);
	if (errorMsg) {
		return errorMsg;
	}

	qsort(vector->arr, vector->size, sizeof(int), cmp_rand);
	return SUCCESS;
}

error_msg stats_arr(IntVector **arrays, char name) {
	IntVector *vector;
	error_msg errorMsg = get_arr(arrays, name, &vector);
	if (errorMsg) {
		return errorMsg;
	}
	int index_max = find_max(vector);
	int value_max;
	if (index_max == -1) {
		value_max = -1;
	} else {
		value_max = vector->arr[index_max];
	}
	int index_min = find_min(vector);
	int value_min;
	if (index_min == -1) {
		value_min = -1;
	} else {
		value_min = vector->arr[index_min];
	}
	int index_most_frequent_value = find_most_frequent_value(vector);
	int value_most_frequent;
	if (index_most_frequent_value == -1) {
		value_most_frequent = -1;
	} else {
		value_most_frequent = vector->arr[index_most_frequent_value];
	}
	double average_value = find_average_value(vector);
	double max_deviation;
	if (vector->size > 0) {
		if (vector->arr[index_max] > abs(vector->arr[index_min])) {
			max_deviation = vector->arr[index_max] - average_value;
		} else {
			max_deviation = average_value - abs(vector->arr[index_min]);
		}
	} else {
		max_deviation = -1;
	}
	printf(
	    "arr %c:\nSize: %d\nMax %i: %d\nMin %i: %d\nThe most_frequent_value: %d\nAverage_value: %f\nMax_deviation: "
	    "%f\n",
	    name, vector->size, index_max, value_max, index_min, value_min, value_most_frequent, average_value,
	    max_deviation);

	return SUCCESS;
}

error_msg print_all(IntVector ** array, char name){
	IntVector * vector;
	error_msg errorMsg = get_arr(array, name, &vector);
	if(errorMsg){
		return errorMsg;
	}
	print_intvector(stdout, vector, " ");
	putc('\n', stdout);
	return SUCCESS;
}

error_msg print_section(IntVector ** array, char name, int start_index, int end_index){
	if(start_index < 0 || start_index > end_index){
		return INCORRECT_OPTIONS_ERROR;
	}
	IntVector * vector;
	error_msg errorMsg = get_arr(array, name, &vector);
	if(errorMsg){
		return errorMsg;
	}
	for(int i = start_index; i < end_index && i < vector->size; ++i){
		printf("%d ", vector->arr[i]);
	}
	putc('\n', stdout);
	return SUCCESS;
}

error_msg print_el(IntVector ** array, char name, int index){
	if(index < 0){
		return INCORRECT_OPTIONS_ERROR;
	}
	IntVector * vector;
	error_msg errorMsg = get_arr(array, name, &vector);
	if(errorMsg){
		return errorMsg;
	}
	if(vector->size > index){
		printf("%d\n", vector->arr[index]);
	}
	return SUCCESS;
}

error_msg read_command(FILE *stream, String *command) {
	clear_string(command);
	char c;
	while ((c = getc(stream)) != EOF && c != ';' && (c == ' ' || c == '\t' || c == '\n'))
		;
	if (c == EOF) {
		return SUCCESS;
	}
	error_msg errorMsg;
	do {
		errorMsg = push_end_string(command, c);
		if (errorMsg) {
			return errorMsg;
		}
	} while ((c = getc(stream)) != EOF && c != ';');
	if (c == EOF && command->size > 0) {
		return INCORRECT_OPTIONS_ERROR;
	}
	return SUCCESS;
}

error_msg parser_for_load_arr(IntVector **array, String *instruction) {
	int index_name_arr = find_index_string_with_start_index(instruction, ',', 4);
	if (index_name_arr == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}

	// обработка имени массива
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String arr_name_string;
	error_msg errorMsg = create_string(&arr_name_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &arr_name_string, index_first_space + 1, index_name_arr);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	strip(&arr_name_string);
	if (arr_name_string.size != 1) {
		destroy_string(&arr_name_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	char arr_name = arr_name_string.arr[0];
	if (arr_name >= 'a' && arr_name <= 'z') {
		arr_name = (char)(arr_name - 'a' + 'A');
	}

	String filename;
	errorMsg = create_string(&filename, "");
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &filename, index_name_arr + 1, instruction->size);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&filename);
		return errorMsg;
	}

	strip(&filename);

	errorMsg = load_arr(array, arr_name, &filename);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&filename);
		return errorMsg;
	}

	destroy_string(&arr_name_string);
	destroy_string(&filename);
	return SUCCESS;
}

error_msg parser_for_save_arr(IntVector **array, String *instruction) {
	int index_name_arr = find_index_string_with_start_index(instruction, ',', 4);
	if (index_name_arr == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	// обработка имени массива
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String arr_name_string;
	error_msg errorMsg = create_string(&arr_name_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &arr_name_string, index_first_space + 1, index_name_arr);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	strip(&arr_name_string);
	if (arr_name_string.size != 1) {
		destroy_string(&arr_name_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	char arr_name = arr_name_string.arr[0];
	if (arr_name >= 'a' && arr_name <= 'z') {
		arr_name = (char)(arr_name - 'a' + 'A');
	}

	String filename;
	errorMsg = create_string(&filename, "");
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &filename, index_name_arr + 1, instruction->size);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&filename);
		return errorMsg;
	}

	strip(&filename);

	errorMsg = save_arr(array, arr_name, &filename);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&filename);
		return errorMsg;
	}

	destroy_string(&arr_name_string);
	destroy_string(&filename);
	return SUCCESS;
}

error_msg parser_for_rand_arr(IntVector **arrays, String *instruction) {
	int index_name_arr = find_index_string_with_start_index(instruction, ',', 4);
	if (index_name_arr == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	// обработка имени массива
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String arr_name_string;
	error_msg errorMsg = create_string(&arr_name_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &arr_name_string, index_first_space + 1, index_name_arr);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	strip(&arr_name_string);
	if (arr_name_string.size != 1) {
		destroy_string(&arr_name_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	char arr_name = arr_name_string.arr[0];
	if (arr_name >= 'a' && arr_name <= 'z') {
		arr_name = (char)(arr_name - 'a' + 'A');
	}

	// Count выделяем
	String count;
	errorMsg = create_string(&count, "");
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	int index_count = find_index_string_with_start_index(instruction, ',', index_name_arr + 1);
	errorMsg = mstrcopy(instruction, &count, index_name_arr + 1, index_count);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&count);
		return errorMsg;
	}
	strip(&count);

	// lb выделяем
	String left_border;
	errorMsg = create_string(&left_border, "");
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&count);
		return errorMsg;
	}
	int index_left_border = find_index_string_with_start_index(instruction, ',', index_count + 1);
	errorMsg = mstrcopy(instruction, &left_border, index_count + 1, index_left_border);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&left_border);
		destroy_string(&count);
		return errorMsg;
	}
	strip(&left_border);

	// rb выделяем
	String right_border;
	errorMsg = create_string(&right_border, "");
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&count);
		destroy_string(&left_border);
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &right_border, index_left_border + 1, instruction->size);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&left_border);
		destroy_string(&right_border);
		destroy_string(&count);
		return errorMsg;
	}
	strip(&right_border);

	// Выделяем значения
	int count_numbers, left_border_numbers, right_border_numbers;
	errorMsg = string_to_int(&count, &count_numbers);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&left_border);
		destroy_string(&right_border);
		destroy_string(&count);
		return errorMsg;
	}

	errorMsg = string_to_int(&left_border, &left_border_numbers);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&left_border);
		destroy_string(&right_border);
		destroy_string(&count);
		return errorMsg;
	}

	errorMsg = string_to_int(&right_border, &right_border_numbers);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		destroy_string(&left_border);
		destroy_string(&right_border);
		destroy_string(&count);
		return errorMsg;
	}
	destroy_string(&arr_name_string);
	destroy_string(&left_border);
	destroy_string(&right_border);
	destroy_string(&count);

	errorMsg = rand_arr(arrays, arr_name, count_numbers, left_border_numbers, right_border_numbers);
	if (errorMsg) {
		return errorMsg;
	}
	return SUCCESS;
}

error_msg parser_for_concatenate_arr(IntVector **arrays, String *instruction) {
	int index_name_arr1 = find_index_string_with_start_index(instruction, ',', 4);
	if (index_name_arr1 == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}

	// обработка имени массива1
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String arr_name1_string;
	error_msg errorMsg = create_string(&arr_name1_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &arr_name1_string, index_first_space + 1, index_name_arr1);
	if (errorMsg) {
		destroy_string(&arr_name1_string);
		return errorMsg;
	}
	strip(&arr_name1_string);
	if (arr_name1_string.size != 1) {
		destroy_string(&arr_name1_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	char arr_name1 = arr_name1_string.arr[0];
	if (arr_name1 >= 'a' && arr_name1 <= 'z') {
		arr_name1 = (char)(arr_name1 - 'a' + 'A');
	}

	// Обработка имени массива 2
	String arr_name2_string;
	errorMsg = create_string(&arr_name2_string, "");
	if (errorMsg) {
		destroy_string(&arr_name1_string);
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &arr_name2_string, index_name_arr1 + 1, instruction->size);
	if (errorMsg) {
		destroy_string(&arr_name1_string);
		destroy_string(&arr_name2_string);
		return errorMsg;
	}
	strip(&arr_name2_string);
	if (arr_name2_string.size != 1) {
		destroy_string(&arr_name2_string);
		destroy_string(&arr_name2_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	char arr_name2 = arr_name2_string.arr[0];
	if (arr_name2 >= 'a' && arr_name2 <= 'z') {
		arr_name2 = (char)(arr_name2 - 'a' + 'A');
	}

	errorMsg = concatenate_arrays(arrays, arr_name1, arr_name2);
	if (errorMsg) {
		destroy_string(&arr_name2_string);
		destroy_string(&arr_name1_string);
		return errorMsg;
	}

	destroy_string(&arr_name2_string);
	destroy_string(&arr_name1_string);
	return SUCCESS;
}

error_msg parser_for_free_arr(IntVector **arrays, String *instruction) {
	// Получаем имя массива
	int index_arr_name = find_index_string(instruction, ')');
	if (index_arr_name == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String arr_name_string;
	error_msg errorMsg = create_string(&arr_name_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &arr_name_string, 5, index_arr_name);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}

	strip(&arr_name_string);
	char arr_name = arr_name_string.arr[0];
	if (arr_name >= 'a' && arr_name <= 'z') {
		arr_name = (char)(arr_name - 'a' + 'A');
	}

	errorMsg = free_arr(arrays, arr_name);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}

	destroy_string(&arr_name_string);
	return SUCCESS;
}

error_msg parser_for_remove_arr(IntVector **arrays, String *instruction) {
	// обработка имени массива
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String arr_name_string;
	error_msg errorMsg = create_string(&arr_name_string, "");
	if (errorMsg) {
		return errorMsg;
	}

	int index_name_arr = find_index_string(instruction, ',');
	if (index_name_arr == -1) {
		destroy_string(&arr_name_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	errorMsg = mstrcopy(instruction, &arr_name_string, index_first_space + 1, index_name_arr);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	strip(&arr_name_string);
	if (arr_name_string.size != 1) {
		destroy_string(&arr_name_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	char arr_name = arr_name_string.arr[0];
	if (arr_name >= 'a' && arr_name <= 'z') {
		arr_name = (char)(arr_name - 'a' + 'A');
	}
	destroy_string(&arr_name_string);

	// Считаем индекс с которого удалять
	int index_second_comma = find_index_string_with_start_index(instruction, ',', index_name_arr + 1);
	if (index_second_comma == -1) {
		return -1;
	}
	int remove_index_start = 0;
	String remove_index_start_string;
	errorMsg = create_string(&remove_index_start_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &remove_index_start_string, index_name_arr + 1, index_second_comma);
	if (errorMsg) {
		destroy_string(&remove_index_start_string);
		return errorMsg;
	}
	strip(&remove_index_start_string);
	errorMsg = string_to_int(&remove_index_start_string, &remove_index_start);
	if (errorMsg) {
		destroy_string(&remove_index_start_string);
		return errorMsg;
	}
	destroy_string(&remove_index_start_string);

	// Считаем сколько индексов удалять
	String remove_count_string;
	errorMsg = create_string(&remove_count_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &remove_count_string, index_second_comma + 1, instruction->size);
	if (errorMsg) {
		destroy_string(&remove_count_string);
		return errorMsg;
	}
	strip(&remove_count_string);
	int remove_count = 0;
	errorMsg = string_to_int(&remove_count_string, &remove_count);
	if (errorMsg) {
		destroy_string(&remove_count_string);
		return errorMsg;
	}

	destroy_string(&remove_count_string);

	errorMsg = remove_arr(arrays, arr_name, remove_index_start, remove_count);
	if (errorMsg) {
		return errorMsg;
	}

	return SUCCESS;
}

error_msg parser_for_copy_arr(IntVector **arrays, String *instruction) {
	// Получаем имя массива
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}

	int index_first_comma = find_index_string(instruction, ',');
	if (index_first_comma == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String arr_name_string;
	error_msg errorMsg = create_string(&arr_name_string, " ");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &arr_name_string, index_first_space + 1, index_first_comma);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	strip(&arr_name_string);
	if (arr_name_string.size != 1) {
		destroy_string(&arr_name_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	char arr_name = arr_name_string.arr[0];
	if (arr_name >= 'a' && arr_name <= 'z') {
		arr_name = (char)(arr_name - 'a' + 'A');
	}
	destroy_string(&arr_name_string);

	// Ищем Начальный индекс
	int index_second_comma = find_index_string_with_start_index(instruction, ',', index_first_comma + 1);
	if (index_second_comma == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}

	String copy_start_index_string;
	errorMsg = create_string(&copy_start_index_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &copy_start_index_string, index_first_comma + 1, index_second_comma);
	if (errorMsg) {
		destroy_string(&copy_start_index_string);
		return errorMsg;
	}
	strip(&copy_start_index_string);
	int copy_start_index = 0;
	errorMsg = string_to_int(&copy_start_index_string, &copy_start_index);
	if (errorMsg) {
		destroy_string(&copy_start_index_string);
		return errorMsg;
	}
	destroy_string(&copy_start_index_string);

	// Ищем конечный индекс
	String copy_end_index_string;
	errorMsg = create_string(&copy_end_index_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	int index_third_comma = find_index_string_with_start_index(instruction, ',', index_second_comma + 1);
	if (index_third_comma == -1) {
		destroy_string(&copy_end_index_string);
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &copy_end_index_string, index_second_comma + 1, index_third_comma);
	if (errorMsg) {
		destroy_string(&copy_end_index_string);
		return errorMsg;
	}
	strip(&copy_end_index_string);
	int copy_end_index = 0;
	errorMsg = string_to_int(&copy_end_index_string, &copy_end_index);
	if (errorMsg) {
		destroy_string(&copy_end_index_string);
		return errorMsg;
	}
	destroy_string(&copy_end_index_string);

	// Получаем имя второго массива

	String name_second_arr_string;
	errorMsg = create_string(&name_second_arr_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &name_second_arr_string, index_third_comma + 1, instruction->size);
	if (errorMsg) {
		destroy_string(&name_second_arr_string);
		return errorMsg;
	}
	strip(&name_second_arr_string);
	if (name_second_arr_string.size != 1) {
		destroy_string(&name_second_arr_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	char second_arr_name = name_second_arr_string.arr[0];
	if (second_arr_name >= 'a' && second_arr_name <= 'z') {
		second_arr_name = (char)(second_arr_name - 'a' + 'A');
	}
	destroy_string(&name_second_arr_string);

	errorMsg = copy_arr(arrays, arr_name, second_arr_name, copy_start_index, copy_end_index + 1);
	if (errorMsg) {
		return errorMsg;
	}

	return SUCCESS;
}

error_msg parser_for_sort_arr(IntVector **arrays, String *instruction) {
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}

	String name_arr_string;
	error_msg errorMsg = create_string(&name_arr_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &name_arr_string, index_first_space + 1, instruction->size);
	if (errorMsg) {
		destroy_string(&name_arr_string);
		return errorMsg;
	}
	strip(&name_arr_string);
	if (name_arr_string.size != 2) {
		destroy_string(&name_arr_string);
		return INCORRECT_OPTIONS_ERROR;
	}

	char arr_name = name_arr_string.arr[0];
	char comp = name_arr_string.arr[1];
	destroy_string(&name_arr_string);
	if (arr_name >= 'a' && arr_name <= 'z') {
		arr_name = (char)(arr_name - 'a' + 'A');
	}

	errorMsg = sort_arr(arrays, arr_name, comp);
	if (errorMsg) {
		return errorMsg;
	}

	return SUCCESS;
}

error_msg parser_for_shuffle_arr(IntVector **arrays, String *instruction) {
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String name_arr_string;
	error_msg errorMsg = create_string(&name_arr_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &name_arr_string, index_first_space + 1, instruction->size);
	if (errorMsg) {
		destroy_string(&name_arr_string);
		return errorMsg;
	}
	strip(&name_arr_string);
	if (name_arr_string.size != 1) {
		destroy_string(&name_arr_string);
		return INCORRECT_OPTIONS_ERROR;
	}
	char name_arr = name_arr_string.arr[0];
	if (name_arr >= 'a' && name_arr <= 'z') {
		name_arr = (char)(name_arr - 'a' + 'A');
	}
	destroy_string(&name_arr_string);

	errorMsg = shuffle_arr(arrays, name_arr);
	if (errorMsg) {
		return errorMsg;
	}

	return SUCCESS;
}

error_msg parser_for_stats_arr(IntVector **arrays, String *instruction) {
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String arr_name_string;
	error_msg errorMsg = create_string(&arr_name_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &arr_name_string, index_first_space + 1, instruction->size);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	strip(&arr_name_string);
	if (arr_name_string.size != 1) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	char name_arr = arr_name_string.arr[0];
	if (name_arr >= 'a' && name_arr <= 'z') {
		name_arr = (char)(name_arr - 'a' + 'A');
	}
	destroy_string(&arr_name_string);

	errorMsg = stats_arr(arrays, name_arr);
	if (errorMsg) {
		return errorMsg;
	}
	return SUCCESS;
}

error_msg parser_for_print(IntVector **arrays, String *instruction) {
	// Получаем имя
	int index_first_space = find_index_string(instruction, ' ');
	if (index_first_space == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	int index_first_comma = find_index_string(instruction, ',');
	if (index_first_comma == -1) {
		return INCORRECT_OPTIONS_ERROR;
	}
	String arr_name_string;
	error_msg errorMsg = create_string(&arr_name_string, "");
	if (errorMsg) {
		return errorMsg;
	}
	errorMsg = mstrcopy(instruction, &arr_name_string, index_first_space + 1, index_first_comma);
	if (errorMsg) {
		destroy_string(&arr_name_string);
		return errorMsg;
	}
	strip(&arr_name_string);
	char name_arr = arr_name_string.arr[0];
	if (name_arr >= 'a' && name_arr <= 'z') {
		name_arr = (char)(name_arr - 'a' + 'A');
	}
	destroy_string(&arr_name_string);

	int index_second_comma = find_index_string_with_start_index(instruction, ',', index_first_comma + 1);
	if (index_second_comma == -1) {
		String second_arg;
		errorMsg = create_string(&second_arg, "");
		if (errorMsg) {
			return errorMsg;
		}
		errorMsg = mstrcopy(instruction, &second_arg, index_first_comma + 1, instruction->size);
		if (errorMsg) {
			destroy_string(&second_arg);
			return errorMsg;
		}
		strip(&second_arg);
		string_to_upper(&second_arg);
		if (string_cmp(second_arg.arr, "ALL")) {
			errorMsg = print_all(arrays, name_arr);
			if(errorMsg){
				destroy_string(&second_arg);
				return errorMsg;
			}
		} else {
			int find_index;
			errorMsg = string_to_int(&second_arg, &find_index);
			if (errorMsg) {
				destroy_string(&second_arg);
				return errorMsg;
			}
			errorMsg = print_el(arrays, name_arr, find_index);
			if(errorMsg){
				destroy_string(&second_arg);
				return errorMsg;
			}
		}
		destroy_string(&second_arg);
	} else {
		String second_arg;
		errorMsg = create_string(&second_arg, "");
		if(errorMsg){
			return errorMsg;
		}
		errorMsg = mstrcopy(instruction, &second_arg, index_first_comma + 1, index_second_comma);
		if(errorMsg){
			destroy_string(&second_arg);
			return errorMsg;
		}
		strip(&second_arg);
		int start_index = 0;
		errorMsg = string_to_int(&second_arg, &start_index);
		if(errorMsg){
			destroy_string(&second_arg);
			return errorMsg;
		}
		destroy_string(&second_arg);
		String third_arg;
		errorMsg = create_string(&third_arg, "");
		if(errorMsg){
			return errorMsg;
		}
		errorMsg = mstrcopy(instruction, &third_arg, index_second_comma + 1, instruction->size);
		if(errorMsg){
			destroy_string(&third_arg);
			return errorMsg;
		}
		strip(&third_arg);
		int end_index = 0;
		errorMsg = string_to_int(&third_arg, &end_index);
		if(errorMsg){
			destroy_string(&third_arg);
			return errorMsg;
		}
		destroy_string(&third_arg);

		errorMsg = print_section(arrays, name_arr, start_index, end_index + 1);
		if(errorMsg){
			return errorMsg;
		}
	}
	return SUCCESS;
}

int instruction_recognition(String *instruction) {
	String name_instruction;
	error_msg errorMsg = create_string(&name_instruction, "");
	int index_instruction = -1;
	if (errorMsg) {
		return -1;
	}
	int index_space = find_index_string(instruction, ' ');
	if (find_index_string(instruction, '(') < index_space && find_index_string(instruction, '(') != -1)
		index_space = find_index_string(instruction, '(');
	if (index_space == -1) {
		destroy_string(&name_instruction);
		return -1;
	}
	errorMsg = mstrcopy(instruction, &name_instruction, 0, index_space);
	if (errorMsg) {
		destroy_string(&name_instruction);
		return -1;
	}

	string_to_upper(&name_instruction);

	if (string_cmp(name_instruction.arr, "LOAD")) {
		index_instruction = 0;
	} else if (string_cmp(name_instruction.arr, "SAVE")) {
		index_instruction = 1;
	} else if (string_cmp(name_instruction.arr, "RAND")) {
		index_instruction = 2;
	} else if (string_cmp(name_instruction.arr, "CONCAT")) {
		index_instruction = 3;
	} else if (string_cmp(name_instruction.arr, "FREE")) {
		index_instruction = 4;
	} else if (string_cmp(name_instruction.arr, "REMOVE")) {
		index_instruction = 5;
	} else if (string_cmp(name_instruction.arr, "COPY")) {
		index_instruction = 6;
	} else if (string_cmp(name_instruction.arr, "SORT")) {
		index_instruction = 7;
	} else if (string_cmp(name_instruction.arr, "SHUFFLE")) {
		index_instruction = 8;
	} else if (string_cmp(name_instruction.arr, "STATS")) {
		index_instruction = 9;
	} else if (string_cmp(name_instruction.arr, "PRINT")) {
		index_instruction = 10;
	} else {
		index_instruction = -1;
	}

	destroy_string(&name_instruction);
	return index_instruction;
}

error_msg read_instructions(IntVector **arrays, String *filename) {
	error_msg errorMsg;

	FILE *file_with_instructions = fopen(filename->arr, "r");
	if (!file_with_instructions) {
		return INDEX_VECTOR_ERROR;
	}

	String instruction;
	errorMsg = create_string(&instruction, "");
	if (errorMsg) {
		fclose(file_with_instructions);
		return errorMsg;
	}

	error_msg (*possible_instructions[11])(IntVector **arrays, String *instruction) = {
	    parser_for_load_arr,    parser_for_save_arr,   parser_for_rand_arr, parser_for_concatenate_arr,
	    parser_for_free_arr,    parser_for_remove_arr, parser_for_copy_arr, parser_for_sort_arr,
	    parser_for_shuffle_arr, parser_for_stats_arr,  parser_for_print};

	int index_instruction;
	while (!feof(file_with_instructions)) {
		errorMsg = read_command(file_with_instructions, &instruction);
		if (errorMsg) {
			fclose(file_with_instructions);
			destroy_string(&instruction);
			return errorMsg;
		}
		if (instruction.size == 0) {
			break;
		}

		// Ищем индекс команды
		index_instruction = instruction_recognition(&instruction);
		if (index_instruction == -1) {
			fclose(file_with_instructions);
			destroy_string(&instruction);
			return INCORRECT_OPTIONS_ERROR;
		}

		// Запускаем действие
		errorMsg = possible_instructions[index_instruction](arrays, &instruction);
		if (errorMsg) {
			fclose(file_with_instructions);
			destroy_string(&instruction);
			return errorMsg;
		}
	}

	fclose(file_with_instructions);
	destroy_string(&instruction);
	return SUCCESS;
}