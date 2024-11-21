#include "func.h"

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

int add_macro(const char *name, const char *value) {
    unsigned int index = hash(name);
    Macro *new_macro = (Macro *)malloc(sizeof(Macro));
    if (!new_macro) {
        return ERROR_MEMORY;
    }

    new_macro->name = strdup(name);
    new_macro->value = strdup(value);
    new_macro->next = hashtable[index];
    hashtable[index] = new_macro;

    return SUCCESS;
}

// поиск макроса по имени
const char* find_macro(const char *name) {
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

void free_hashtable() {
    for (int i = 0; i < HASHSIZE; i++) {
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
}

// для обработки файла и замены макросов в тексте
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
            // Обработка define
            char name[256], value[256];
            if (sscanf(line, "#define %255s %255[^\n]", name, value) == 2) {
                if (add_macro(name, value) != 0) {
                    fprintf(stderr, "Ошибка добавления макроса: %s\n", name);
                    fclose(file);
                    return ERROR_WITH_MACROS;
                }
            }
        } else {
            // Переход к основной части текста
            reading_defines = 0;

            // Обработка строки с заменой макросов
            char *start = line;
            while (*start) {
                // Находим конец текущего слова
                char *end = start;
                while (*end && !isspace(*end) && *end != ',' && *end != '.' && *end != '!' && *end != '?') {
                    end++;
                }

                // Временное сохранение символа
                char temp = *end;
                *end = '\0';

                // Ищем макрос в таблице
                const char *replacement = find_macro(start);
                if (replacement) {
                    printf("%s", replacement);  // Выводим только значение макроса
                } else {
                    printf("%s", start);  // Выводим слово, если оно не является макросом
                }

                // Восстанавливаем символ и двигаемся дальше
                *end = temp;
                start = end;

                // Печатаем разделительный символ (например, пробел или пунктуацию)
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Ввод: %s <файл>\n", argv[0]);
        return INCORRECT_OPTIONS;
    }

    if (process_file(argv[1]) != 0) {
        free_hashtable();
        return INCORRECT_OPTIONS;
    }

    free_hashtable();
    return SUCCESS;
}
