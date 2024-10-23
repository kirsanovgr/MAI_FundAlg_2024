#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUCCESS = 0,
    SUBSTRING_NOT_FOUND,
    ERROR_OPENING_FILE,
    ERROR_MEMORY_ALLOCATION
} Status;

int Find_substring(const char *line, const char *substring, int *position) {
    int line_len = 0, sub_len = 0;
    
    // Подсчет длины строки
    while (line[line_len] != '\0') { 
        line_len++; 
    }
    
    // Подсчет длины подстроки
    while (substring[sub_len] != '\0') { 
        sub_len++; 
    }

    if (sub_len == 0) {
        return SUCCESS; 
    }

    for (int i = *position; i <= line_len - sub_len; i++) {
        int match = 1;
        for (int j = 0; j < sub_len; j++) {
            if (line[i + j] != substring[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            *position = i;
            return SUBSTRING_NOT_FOUND;
        }
    }
    return SUCCESS;
}

int Process_file(const char *filepath, const char *substring) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Не могу открыть файл: %s\n", filepath);
        return ERROR_OPENING_FILE;
    }

    char line[1024];
    int line_number = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        int position = 0;

        while (Find_substring(line, substring, &position) == SUBSTRING_NOT_FOUND) {
            printf("Файл: %s, Строка: %d, Позиция: %d\n", filepath, line_number, position + 1);
            position++;  
        }

        line_number++;
    }

    fclose(file);
    return SUCCESS;
}

int Find_in_files(const char *substring, int file_count, const char *filepaths[]) {
    if (substring == NULL || substring[0] == '\0') {
        printf("Подстрока не может быть пустой.\n");
        return ERROR_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < file_count; i++) {
        int status = Process_file(filepaths[i], substring);
        if (status != SUCCESS) {
            return status;
        }
    }

    return SUCCESS;
}

int main() {
    char substring[256];
    int file_count;

    printf("Введите подстроку для поиска: ");
    scanf("%255s", substring);
    printf("\n");

    printf("Введите количество файлов: ");
    scanf("%d", &file_count);
    printf("\n");

    if (file_count <= 0) {
        printf("Количество файлов должно быть больше нуля.\n");
        return ERROR_MEMORY_ALLOCATION;
    }

    // Выделение памяти для хранения путей к файлам
    char **files = (char **)malloc(file_count * sizeof(char *));
    if (files == NULL) {
        printf("Ошибка выделения памяти.\n");
        return ERROR_MEMORY_ALLOCATION;
    }

    // Ввод имен файлов
    for (int i = 0; i < file_count; ++i) {
        files[i] = (char *)malloc(256 * sizeof(char));
        if (files[i] == NULL) {
            printf("Ошибка выделения памяти для имени файла.\n");
            
            // Очистка ранее выделенной памяти
            for (int j = 0; j < i; ++j) {
                free(files[j]);
            }
            free(files);
            
            return ERROR_MEMORY_ALLOCATION;
        }
        
        printf("Введите путь к файлу %d: ", i + 1);
        scanf("%255s", files[i]);
        printf("\n");
    }

    // Поиск подстроки в файлах
    int status = Find_in_files(substring, file_count, (const char **)files);
    if (status != SUCCESS) {
        printf("Ошибка при поиске подстроки.\n");
    }

    for (int i = 0; i < file_count; ++i) {
        free(files[i]);
    }
    free(files);

    return status;
}
