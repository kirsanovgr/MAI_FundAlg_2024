#define _CRT_SECURE_NO_WARNINGS
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Search_In_File(const char* substring, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File %s isn't found!\n", filename);
        return;
    }

    int len_sub = strlen(substring);
    int line_number = 1;
    int match_count = 0;
    int position_in_line = 1;
    int buffer_size = 0;
    char c;

    char* buffer = (char*)malloc(1);
    if (!buffer) {
        printf("Memory allocation failed!\n");
        fclose(file);
        return;
    }

    printf("Searching in file: %s\n", filename);

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            line_number++;
            position_in_line = 1;
            buffer_size = 0;
            free(buffer);
            buffer = (char*)malloc(1);
            if (!buffer) {
                printf("Memory allocation failed!\n");
                fclose(file);
                return;
            }
            continue;
        }

        buffer_size++;
        char* temp_buffer = (char*)realloc(buffer, buffer_size);
        if (!temp_buffer) {
            printf("Memory allocation failed!\n");
            free(buffer);
            fclose(file);
            return;
        }
        buffer = temp_buffer;
        buffer[buffer_size - 1] = c;

        if (buffer_size >= len_sub) {
            int match = 1;

            for (int i = 0; i < len_sub; i++) {
                if (buffer[buffer_size - len_sub + i] != substring[i]) {
                    match = 0;
                    break;
                }
            }

            if (match) {
                match_count++;
                printf("Match #%d found at line %d, position %d\n", match_count, line_number, position_in_line - len_sub + 1);
            }
        }

        position_in_line++;
    }

    if (match_count == 0) {
        printf("No matches found in file %s\n", filename);
    }

    fclose(file);
    free(buffer);
}

void Search_from_files(int num_of_files, ...) {
    va_list file_list;
    va_start(file_list, num_of_files);

    const char* substring = va_arg(file_list, const char*);

    for (int i = 1; i < num_of_files; i++) {
        const char* filename = va_arg(file_list, const char*);
        Search_In_File(substring, filename);
    }

    va_end(file_list);
}

int main() {
    Search_from_files(4, "test", "1.txt", "2.txt", "3.txt");

    return 0;
}
