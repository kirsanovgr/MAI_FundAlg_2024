#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char** read_tokens(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open input file '%s'.\n", filename);
        return NULL;
    }

    char** tokens = NULL;
    char buffer[BUFFER_SIZE];
    *count = 0;

    while (fscanf(file, "%1023s", buffer) == 1) {
        char** temp = realloc(tokens, (*count + 1) * sizeof(char*));
        if (!temp) {
            printf("Error: Memory allocation error while reading tokens.\n");
            for (int k = 0; k < *count; k++) free(tokens[k]);
            free(tokens);
            fclose(file);
            return NULL;
        }
        tokens = temp;

        tokens[*count] = strdup(buffer);
        if (!tokens[*count]) {
            printf("Error: Memory allocation error while duplicating token.\n");
            for (int k = 0; k < *count; k++) free(tokens[k]);
            free(tokens);
            fclose(file);
            return NULL;
        }
        (*count)++;
    }

    fclose(file);
    return tokens;
}

void write_tokens(const char* filename, char** tokens, int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to open output file '%s' for writing.\n", filename);
        return;
    }

    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s", tokens[i]);
        if (i < count - 1) {
            fprintf(file, " ");
        }
    }

    fclose(file);
}

int file_exists(const char* filename) {
    struct stat buffer;   
    return (stat(filename, &buffer) == 0);
}

char* get_absolute_path(const char* path) {
    char* absolute_path = malloc(PATH_MAX);
    if (realpath(path, absolute_path) == NULL) {
        free(absolute_path);
        return NULL;
    }
    return absolute_path;
}

int paths_are_equal(const char* file1, const char* file2) {
    char* abs_file1 = get_absolute_path(file1);
    char* abs_file2 = get_absolute_path(file2);
    
    if (!abs_file1 || !abs_file2) {
        free(abs_file1);
        free(abs_file2);
        return 0;
    }
    
    int result = strcmp(abs_file1, abs_file2) == 0;
    free(abs_file1);
    free(abs_file2);
    return result;
}

void process_r_flag(const char* file1, const char* file2, const char* output_file) {
    if (paths_are_equal(file1, output_file) || paths_are_equal(file2, output_file)) {
        printf("Error: Input and output file paths must be different.\n");
        return;
    }

    if (!file_exists(file1) || !file_exists(file2)) {
        printf("Error: One or both input files do not exist.\n");
        return;
    }

    int count1, count2;
    char** tokens1 = read_tokens(file1, &count1);
    char** tokens2 = read_tokens(file2, &count2);

    if (!tokens1 || !tokens2) {
        return;
    }

    int total_count = count1 + count2;
    char** result = malloc(total_count * sizeof(char*));
    if (!result) {
        printf("Error: Memory allocation error for result tokens.\n");
        for (int k = 0; k < count1; ++k) free(tokens1[k]);
        for (int k = 0; k < count2; ++k) free(tokens2[k]);
        free(tokens1);
        free(tokens2);
        return;
    }

    int idx = 0, i = 0, j = 0;

    while (i < count1 && j < count2) {
        result[idx++] = tokens1[i++];
        result[idx++] = tokens2[j++];
    }

    while (i < count1) {
        result[idx++] = tokens1[i++];
    }

    while (j < count2) {
        result[idx++] = tokens2[j++];
    }

    write_tokens(output_file, result, idx);

    for (int k = 0; k < count1; ++k) free(tokens1[k]);
    for (int k = 0; k < count2; ++k) free(tokens2[k]);
    free(tokens1);
    free(tokens2);
    free(result);
}

void convert_to_base4(char* token) {
    char buffer[BUFFER_SIZE] = "";
    char temp[16];

    for (int i = 0; token[i]; ++i) {
        token[i] = tolower(token[i]);
        int ascii_value = (int)token[i];

        sprintf(temp, "%d", ascii_value);
        char base4[32] = "";
        int index = 0;

        while (ascii_value > 0) {
            if (index >= (int)sizeof(base4) - 1) {
                printf("Error: Buffer overflow in base4 conversion.\n");
                return;
            }
            base4[index++] = '0' + (ascii_value % 4);
            ascii_value /= 4;
        }
        base4[index] = '\0';

        if (strlen(buffer) + strlen(base4) >= BUFFER_SIZE) {
            printf("Error: Buffer overflow while converting to base4.\n");
            return;
        }

        strcat(buffer, base4);
    }

    strcpy(token, buffer);
}

void convert_to_base8(char* token) {
    char buffer[BUFFER_SIZE] = "";
    char temp[16];

    for (int i = 0; token[i]; ++i) {
        int ascii_value = (int)token[i];

        sprintf(temp, "%o", ascii_value);

        if (strlen(buffer) + strlen(temp) >= BUFFER_SIZE) {
            printf("Error: Buffer overflow while converting to base8.\n");
            return;
        }

        strcat(buffer, temp);
    }

    strcpy(token, buffer);
}

void process_a_flag(const char* input_file, const char* output_file) {
    if (paths_are_equal(input_file, output_file)) {
        printf("Error: Input and output file paths must be different.\n");
        return;
    }

    if (!file_exists(input_file)) {
        printf("Error: Input file does not exist.\n");
        return;
    }

    int count;
    char** tokens = read_tokens(input_file, &count);

    if (!tokens) {
        return;
    }

    for (int i = 0; i < count; ++i) {
        if ((i + 1) % 10 == 0) {
            convert_to_base4(tokens[i]);
        } else if ((i + 1) % 2 == 0) {
            for (int j = 0; tokens[i][j]; ++j) {
                tokens[i][j] = tolower(tokens[i][j]);
            }
        } else if ((i + 1) % 5 == 0) {
            convert_to_base8(tokens[i]);
        }
    }

    write_tokens(output_file, tokens, count);

    for (int i = 0; i < count; ++i) free(tokens[i]);
    free(tokens);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: %s [-r or /r] | [-a or /a] <file1> <file2> <output_file>\n", argv[0]);
        return 1;
    }

    if (strncmp(argv[1], "-r", 2) == 0 || strncmp(argv[1], "/r", 2) == 0) {
        if (argc != 5) {
            printf("Error: Invalid number of arguments for -r or /r\n");
            return 1;
        }
        process_r_flag(argv[2], argv[3], argv[4]);
    } else if (strncmp(argv[1], "-a", 2) == 0 || strncmp(argv[1], "/a", 2) == 0) {
        if (argc != 4) {
            printf("Error: Invalid number of arguments for -a or /a\n");
            return 1;
        }
        process_a_flag(argv[2], argv[3]);
    } else {
        printf("Error: Invalid flag %s\n", argv[1]);
        return 1;
    }

    return 0;
}
