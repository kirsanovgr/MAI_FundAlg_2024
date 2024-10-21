#include "ex1.h"

error_msg GetOpts(int argc, char **argv, kOpts *opt) {
	if(argc == 1)
		return INCORRECT_OPTIONS_ERROR;
	const char *proceeding_option = argv[1];
	if ((proceeding_option[0] == '/' || proceeding_option[0] == '-') && SizeString(proceeding_option) == 2) {
		switch (proceeding_option[1]) {
			case 'l':
				*opt = OPT_L;
				if (argc != 3) return INCORRECT_OPTIONS_ERROR;
				break;
			case 'r':
				*opt = OPT_R;
				if (argc != 3) return INCORRECT_OPTIONS_ERROR;
				break;
			case 'u':
				*opt = OPT_U;
				if (argc != 3) return INCORRECT_OPTIONS_ERROR;
				break;
			case 'n':
				*opt = OPT_N;
				if (argc != 3) return INCORRECT_OPTIONS_ERROR;
				break;
			case 'c':
				*opt = OPT_C;
				if (argc < 4) return INCORRECT_OPTIONS_ERROR;
				break;
			default:
				return INCORRECT_OPTIONS_ERROR;
		}
	} else {
		return INCORRECT_OPTIONS_ERROR;
	}
	return SUCCESS;
}


error_msg CharToUInt(const char *string, unsigned int *x) {
	*x = 0;
	for (int i = 0; string[i] != '\0'; ++i) {
		if (string[i] >= '0' && string[i] <= '9') {
			if ((unsigned long int)*x * 10 + (string[i] - '0') > UINT_MAX) {
				return OVERFLOW_ERROR;
			}
			*x = *x * 10 + (string[i] - '0');
		} else {
			return UNRECOGNIZED_CHARACTER_ERROR;
		}
	}
	return 0;
}

error_msg HandlerOptL(char **argv, int *size) {
	*size = SizeString(argv[2]);
	return SUCCESS;
}

error_msg HandlerOptR(char **argv, char **new_string) {
	*new_string = (char *)malloc(sizeof(char) * (SizeString(argv[2]) + 1));
	if (!*new_string) return MEMORY_ALLOCATED_ERROR;
    char * tmp_new_string = *new_string;
	char *old_string = argv[2];
	for (int i = SizeString(old_string) - 1, j = 0; i >= 0; --i, ++j) {
        tmp_new_string[j] = old_string[i];
	}
    tmp_new_string[SizeString(argv[2])] = '\0';
	return SUCCESS;
}

error_msg HandlerOptU(char **argv, char **new_string) {
	*new_string = (char *)malloc(sizeof(char) * (SizeString(argv[2]) + 1));
	if (!*new_string) return MEMORY_ALLOCATED_ERROR;
    char * tmp_new_string = *new_string;
	char *old_string = argv[2];
	int i;
	for (i = 0; i < SizeString((old_string)); ++i) {
		if (i % 2 && old_string[i] >= 'a' && old_string[i] <= 'z') {
            tmp_new_string[i] = 'A' + old_string[i] - 'a';
		} else {
            tmp_new_string[i] = old_string[i];
		}
	}
    tmp_new_string[i] = '\0';
	return SUCCESS;
}

error_msg HandlerOptN(char **argv, char **new_string) {
	error_msg error;
	*new_string = (char *)malloc(sizeof(char) * (SizeString(argv[2]) + 1));
	if (!*new_string) return MEMORY_ALLOCATED_ERROR;
    char * tmp_new_string = *new_string;
	char *old_string = argv[2];
	int index_new_string = 0;
	CharVector *letters = create_char_vector(1);
	if (!letters) {
		return MEMORY_ALLOCATED_ERROR;
	}
	CharVector *others = create_char_vector(1);
	if (!others) {
		destroy_char_vector(letters);
		return MEMORY_ALLOCATED_ERROR;
	}
	for (int i = 0; i < SizeString(old_string); ++i) {
		if (old_string[i] >= '0' && old_string[i] <= '9')
			tmp_new_string[index_new_string++] = old_string[i];
		else if ((old_string[i] >= 'a' && old_string[i] <= 'z') || (old_string[i] >= 'A' && old_string[i] <= 'Z')) {
			error = push_end_charvector(letters, old_string[i]);
			if (error) {
				destroy_char_vector(letters);
				destroy_char_vector(others);
				return error;
			}
		} else {
			error = push_end_charvector(others, old_string[i]);
			if (error) {
				destroy_char_vector(letters);
				destroy_char_vector(others);
				return error;
			}
		}
	}
	char x;
	for (int i = 0; i < size_charvector(letters); ++i) {
		error = get_charvector(letters, i, &x);
		if (error) {
			destroy_char_vector(letters);
			destroy_char_vector(others);
			return error;
		}
		tmp_new_string[index_new_string++] = x;
	}
	for (int i = 0; i < size_charvector(others); ++i) {
		error = get_charvector(others, i, &x);
		if (error) {
			destroy_char_vector(letters);
			destroy_char_vector(others);
			return error;
		}
		tmp_new_string[index_new_string++] = x;
	}
	tmp_new_string[index_new_string] = '\0';
	destroy_char_vector(letters);
	destroy_char_vector(others);
	return SUCCESS;
}

error_msg HandlerOptC(int argc, char **argv, char **new_string) {
	unsigned int seed;
	error_msg error = CharToUInt(argv[3], &seed);
	if (error) return error;
	srand(seed);
	int sum_size = SizeString(argv[2]);
	// Находим суммарный размер всех строчек
	for (int i = 4; i < argc; ++i) {
		sum_size += SizeString(argv[i]);
	}
	*new_string = (char *)malloc(sum_size + 1);
	if (!*new_string) return MEMORY_ALLOCATED_ERROR;
    char * tmp_new_string = *new_string;
	tmp_new_string[0] = '\0';
	for (int j = 3; j < argc - 1; ++j) {
		argv[j] = argv[j + 1];
	}
	int size = argc - 3, random_index;
	for (int i = 0; i < argc - 3; ++i) {
		random_index = rand() % size + 2;
		error = my_strcat(tmp_new_string, argv[random_index]);
		if (error) return error;
		for (int j = random_index; j < argc - 1; ++j) {
			argv[j] = argv[j + 1];
		}
		--size;
	}

	return SUCCESS;
}