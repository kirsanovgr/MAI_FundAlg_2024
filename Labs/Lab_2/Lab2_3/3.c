#include "func.h"

int len(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int Shift_Table(const char *template, int n, int *result) {
    if (n == 0)
        return -1;

    int i = 1, j = 0;
    result[0] = 0;
    while (i < n) {
        if (template[i] != template[j]) {
            if (j == 0) {
                result[i] = 0;
                i++;
            } else {
                j = result[j - 1];
            }
        } else {
            j++;
            result[i] = j;
            i++;
        }
    }
    return 0;
}

int Substr(const char* str, int n, const char* key, int m) {
    n--; // уменьшаем, чтобы не выходить за пределы
    m--; // уменьшаем, чтобы не выходить за пределы
    int table[m], i = 0, j = 0;

    Shift_Table(key, m, table);

    while (i < n) {
        if (str[i] == key[j]) {
            i++;
            j++;
            if (j == m) {
                return i - j; // Нашли первое вхождение
            }
        } else {
            if (j > 0) {
                j = table[j - 1];
            } else {
                i++;
            }
        }
    }
    return FILE_ERROR;
}

int Line_Counter(const char *str, int size) {
    int count = 1;
    for (int i = 0; i < size; ++i) {
        if (str[i] == '\n')
            count++;
    }
    return count;
}

int Pos_In_Line(const char *str, int size) {
    if (str[size - 1] == '\n')
        return 1;
    for (int i = size - 2; i >= 0; --i) {
        if (str[i] == '\n')
            return size - i - 1;
    }
    return size;
}

int File_Handler(char *key, int m, char *filename) {
    FILE* stream = fopen(filename, "r");
    if (!stream)
        return FILE_ERROR;

    fseek(stream, 0, SEEK_END);
    int size = ftell(stream);
    fseek(stream, 0, SEEK_SET);

    char content[size + 1]; // +1 для нуль-терминатора
    fread(content, sizeof(char), size, stream);
    content[size] = '\0'; // Добавляем нуль-терминатор

    int i = 0, ind = 0;

    while (1) {
        i = Substr(content + ind, size - ind, key, m);
        if (i == FILE_ERROR) break;
        ind += i + 1;
        printf("Найдено вхождение в файле %s, строка %d, символ %d\n", filename, Line_Counter(content, ind), Pos_In_Line(content, ind));
    }

    fclose(stream);
    return SUCCESS;
}

void Process_Newline_In_Substring(char *substr) {
    int i = 0;
    while (substr[i] != '\0') {
        if (substr[i] == '\\' && substr[i + 1] == 'n') {
            // Заменяем "\n" на '\n'
            substr[i] = '\n';
            // Сдвигаем строку влево
            int j = i + 1;
            while (substr[j] != '\0') {
                substr[j] = substr[j + 1];
                j++;
            }
        } else {
            i++;
        }
    }
}