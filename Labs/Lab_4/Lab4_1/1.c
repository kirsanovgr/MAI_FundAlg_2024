#include "func.h"

// Глобальные переменные
Macro **hashtable = NULL;
unsigned int HASHSIZE = INITIAL_HASHSIZE;
unsigned int macro_count = 0;

// Реализация хеш-функции
unsigned int hash(const char *str) {
    unsigned long hash = 0;
    while (*str) {
        char c = *str++;
        int value;

        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            value = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'z') {
            value = c - 'a' + 36;
        } else {
            return 0; // неправильный символ
        }

        hash = hash * 62 + value;
    }
    return hash % HASHSIZE;
}

char *strdup(const char *str) {
	size_t len = strlen(str) + 1; // Длина строки + символ окончания
	char *copy = malloc(len);    // Выделение памяти
	if (copy) {
		memcpy(copy, str, len);  // Копирование строки
	}
	return copy;
}

// Функция для перераспределения хеш-таблицы
void rehash(unsigned int new_size) {
    Macro **new_table = (Macro **)calloc(new_size, sizeof(Macro *));
    if (!new_table) {
        fprintf(stderr, "Ошибка выделения памяти для новой таблицы.\n");
        return;
    }

    for (unsigned int i = 0; i < HASHSIZE; i++) {
        Macro *macro = hashtable[i];
        while (macro) {
            Macro *next = macro->next;
            unsigned int new_index = hash(macro->name) % new_size;

            macro->next = new_table[new_index];
            new_table[new_index] = macro;

            macro = next;
        }
    }

    free(hashtable);
    hashtable = new_table;
    HASHSIZE = new_size;
}

// Добавление макроса
int add_macro(const char *name, const char *value) {
    if ((double)macro_count / HASHSIZE > 0.75) {
        rehash(HASHSIZE * 2);
    }

    unsigned int index = hash(name);
    Macro *new_macro = (Macro *)malloc(sizeof(Macro));
    if (!new_macro) {
        return ERROR_MEMORY;
    }

    new_macro->name = strdup(name);
    new_macro->value = strdup(value);
    new_macro->next = hashtable[index];
    hashtable[index] = new_macro;

    macro_count++;
    return SUCCESS;
}

// Поиск макроса по имени
const char *find_macro(const char *name) {
    unsigned int index = hash(name);
    Macro *macro = hashtable[index];
    while (macro) {
        if (strcmp(macro->name, name) == 0) {
            return macro->value;
        }
        macro = macro->next;
    }
    return NULL;
}

// Освобождение памяти хеш-таблицы
void free_hashtable() {
    for (unsigned int i = 0; i < HASHSIZE; i++) {
        Macro *macro = hashtable[i];
        while (macro) {
            Macro *temp = macro;
            macro = macro->next;
            free(temp->name);
            free(temp->value);
            free(temp);
        }
        hashtable[i] = NULL;
    }
    free(hashtable);
    hashtable = NULL;
    macro_count = 0;
}

// Обработка файла и замена макросов
int process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return ERROR_FILE_OPEN;
    }

    char line[1024];
    int reading_defines = 1;

    while (fgets(line, sizeof(line), file)) {
        if (reading_defines && strncmp(line, "#define", 7) == 0) {
            char name[256], value[256];
            if (sscanf(line, "#define %255s %255[^\n]", name, value) == 2) {
                if (add_macro(name, value) != 0) {
                    fprintf(stderr, "Ошибка добавления макроса: %s\n", name);
                    fclose(file);
                    return ERROR_WITH_MACROS;
                }
            }
        } else {
            reading_defines = 0;
            char *start = line;

            while (*start) {
                char *end = start;
                while (*end && !isspace(*end) && *end != ',' && *end != '.' && *end != '!' && *end != '?') {
                    end++;
                }

                char temp = *end;
                *end = '\0';

                const char *replacement = find_macro(start);
                if (replacement) {
                    printf("%s", replacement);
                } else {
                    printf("%s", start);
                }

                *end = temp;
                start = end;

                if (*start && isspace(*start)) {
                    printf(" ");
                    start++;
                } else if (*start) {
                    printf("%c", *start);
                    start++;
                }
            }
            printf("\n");
        }
    }

    fclose(file);
    return SUCCESS;
}

// Тестирование
void run_tests() {
    printf("Тесты:\n");

    add_macro("PI", "3.14");
    add_macro("E", "2.71");
    printf("PI = %s\n", find_macro("PI"));
    printf("E = %s\n", find_macro("E"));

    rehash(256);
    printf("После рехэша: PI = %s\n", find_macro("PI"));
    printf("После рехэша: E = %s\n", find_macro("E"));
}

// Точка входа
int main(int argc, char *argv[]) {
    hashtable = (Macro **)calloc(INITIAL_HASHSIZE, sizeof(Macro *));
    if (!hashtable) {
        fprintf(stderr, "Ошибка выделения памяти для хеш-таблицы.\n");
        return ERROR_MEMORY;
    }

    if (argc != 2) {
        fprintf(stderr, "Использование: %s <файл>\n", argv[0]);
        free_hashtable();
        return INCORRECT_OPTIONS;
    }

    if (process_file(argv[1]) != SUCCESS) {
        free_hashtable();
        return ERROR_WITH_MACROS;
    }

    free_hashtable();
    return SUCCESS;
}
