#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUCCESS = 0,
    MISSING_ARGUMENTS_ERROR,
    ERROR_INPUT,
    ERROR_INVALID_FLAG,
    ERROR_MEMORY_ALLOCATION
} Status;

size_t str_len(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Подсчёт длины строки для флага -l
int len_string(const char* str) {
    return str_len(str);
}

// Реверс строки для флага -r
char* reverse_string(const char* str) {
    size_t len = str_len(str);
    char* reversed = (char*)malloc((len + 1) * sizeof(char));
    if (reversed == NULL) {
        printf("Ошибка: Не удалось выделить память\n");
    }

    for (size_t i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    return reversed;
}

// Преобразование нечётных символов в верхний регистр для флага -u
char* uppercase_odd_positions(const char* str) {
    size_t len = str_len(str);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        printf("Ошибка: Не удалось выделить память\n");
    }

    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 1 && str[i] >= 'a' && str[i] <= 'z') {
            result[i] = str[i] - ('a' - 'A'); // Преобразуем символ в верхний регистр (было 32, потому что разница между ними 32)
        } else {
            result[i] = str[i];
        }
    }
    result[len] = '\0';
    return result;
}

// Сортировка строки: цифры, буквы, остальные символы для флага -n
char* sort_string(const char* str) {
    size_t len = str_len(str);
    char* sorted = (char*)malloc((len + 1) * sizeof(char));
    if (sorted == NULL) {
        printf("Ошибка: Не удалось выделить память\n");
    }

    size_t index = 0;

    // Добавляем цифры
    for (size_t i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            sorted[index++] = str[i];
        }
    }

    // Добавляем буквы
    for (size_t i = 0; i < len; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            sorted[index++] = str[i];
        }
    }

    // Добавляем остальные символы
    for (size_t i = 0; i < len; i++) {
        if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))) {
            sorted[index++] = str[i];
        }
    }

    sorted[len] = '\0';
    return sorted;
}

// Конкатенация строк в псевдослучайном порядке для флага -c
char* concatenate_random(int seed, int argc, char** argv) {
    srand(seed);

    // Количество строк для конкатенации
    int count = argc - 3;  // Учитываем три первых аргумента
    if (count < 2) {
        printf("Недостаточно строк для конкатенации\n");
        return NULL;
    }

    // Выделяем память для результата
    size_t total_length = 0;
    for (int i = 3; i < argc; i++) {
        total_length += str_len(argv[i]);
    }

    char* result = (char*)malloc((total_length + 1) * sizeof(char));
    if (result == NULL) {
        printf("Ошибка: Не удалось выделить память\n");
        return NULL;
    }

    // Конкатенируем строки в случайном порядке
    int* indices = (int*)malloc(count * sizeof(int));
    if (indices == NULL) {
        free(result);
        return NULL;
    }

    // Инициализация индексов
    for (int i = 0; i < count; i++) {
        indices[i] = i + 3;
    }

    // Перемешиваем индексы
    for (int i = 0; i < count; i++) {
        int j = rand() % count;
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Заполняем результирующую строку
    size_t current_position = 0;
    for (int i = 0; i < count; i++) {
        size_t len = str_len(argv[indices[i]]);
        for (size_t j = 0; j < len; j++) {
            result[current_position++] = argv[indices[i]][j];
        }
    }
    result[current_position] = '\0';  // Устанавливаем конец строки

    free(indices);
    return result;
}

// Преобразование строки в unsigned int
unsigned int string_to_uint(const char *str) {
    unsigned int result = 0;
    while (*str == ' ') str++;
    if (*str == '+' || *str == '-') {
        if (*str == '-') {
            return -1;
        } 
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

typedef Status (*FlagHandler)(int argc, char** argv);

Status handle_len(int argc, char** argv) {
    if (argc < 3) {
        return MISSING_ARGUMENTS_ERROR;
    }
    printf("Длина: %d\n", len_string(argv[2]));
    return SUCCESS;
}

Status handle_reverse(int argc, char** argv) {
    if (argc < 3) {
        return MISSING_ARGUMENTS_ERROR;
    } 
    char* reversed = reverse_string(argv[2]);
    if (reversed == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    printf("Реверс: %s\n", reversed);
    free(reversed);
    return SUCCESS;
}

Status handle_uppercase(int argc, char** argv) {
    if (argc < 3) {
        return MISSING_ARGUMENTS_ERROR;
    } 
    char* result = uppercase_odd_positions(argv[2]);
    if (result == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    } 
    printf("Верхний регистр на нечётных позициях: %s\n", result);
    free(result);
    return SUCCESS;
}

Status handle_sort(int argc, char** argv) {
    if (argc < 3) {
        return MISSING_ARGUMENTS_ERROR;
    } 
    char* sorted = sort_string(argv[2]);
    if (sorted == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    printf("Отсортировано: %s\n", sorted);
    free(sorted);
    return SUCCESS;
}

Status handle_concatenate(int argc, char** argv) {
    if (argc < 4) {
        return MISSING_ARGUMENTS_ERROR;
    }
    unsigned int seed = string_to_uint(argv[2]);
    char* concatenated = concatenate_random(seed, argc, argv);
    if (concatenated == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    printf("Конкатенация: %s\n", concatenated);
    free(concatenated);
    return SUCCESS;
}

typedef struct {
    const char* flag;
    FlagHandler handler;
} FlagCommand;

FlagCommand commands[] = {
    {"-l", handle_len},
    {"-r", handle_reverse},
    {"-u", handle_uppercase},
    {"-n", handle_sort},
    {"-c", handle_concatenate}
};

Status parse_flag(int argc, char** argv) {
    if (argc < 2) {
        return ERROR_INPUT;
    }
    
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        if (str_len(commands[i].flag) == 2 && argv[1][0] == '-' && argv[1][1] == commands[i].flag[1]) {
            return commands[i].handler(argc, argv);
        }
    }
    return ERROR_INVALID_FLAG;
}

int main(int argc, char** argv) {
    Status status = parse_flag(argc, argv);
    if (status != SUCCESS) {
        if (status == MISSING_ARGUMENTS_ERROR) {
            printf("Ошибка: Недостаточно аргументов\n");
        } else if (status == ERROR_INPUT) {
            printf("Ошибка: Неправильный ввод\n");
        } else if (status == ERROR_INVALID_FLAG) {
            printf("Ошибка: Неизвестный флаг %s\n", argv[1]);
        } else if (status == ERROR_MEMORY_ALLOCATION) {
            printf("Ошибка: Не удалось выделить память\n");
        }
        return status;
    }
    return 0;
}