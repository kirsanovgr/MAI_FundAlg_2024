#include "func.h"

int main() {
    char substring[256];
    int file_count;

    printf("Введите подстроку для поиска: ");
    fgets(substring, sizeof(substring), stdin);
    // Убираем символ новой строки в конце
    int length = len(substring);
    if (substring[length - 1] == '\n') {
        substring[length - 1] = '\0';
    }
    Process_Newline_In_Substring(substring); // Обрабатываем подстроку

    printf("Введите количество файлов: ");
    if (scanf("%d", &file_count) != 1 || file_count <= 0) {
        printf("Количество файлов должно быть больше нуля.\n");
        return 1;
    }

    char **files = (char **)malloc(file_count * sizeof(char *));
    if (files == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    getchar(); // Чтобы убрать оставшийся символ новой строки
    for (int i = 0; i < file_count; ++i) {
        files[i] = (char *)malloc(256 * sizeof(char));
        if (files[i] == NULL) {
            printf("Ошибка выделения памяти для имени файла.\n");
            for (int j = 0; j < i; ++j) {
                free(files[j]);
            }
            free(files);
            return 1;
        }

        printf("Введите путь к файлу %d: ", i + 1);
        fgets(files[i], 256, stdin);
        // Убираем символ новой строки
        length = len(files[i]);
        if (files[i][length - 1] == '\n') {
            files[i][length - 1] = '\0';
        }
    }

    for (int i = 0; i < file_count; i++) {
        File_Handler(substring, len(substring), files[i]);
    }

    for (int i = 0; i < file_count; ++i) {
        free(files[i]);
    }
    free(files);

    return 0;
}
