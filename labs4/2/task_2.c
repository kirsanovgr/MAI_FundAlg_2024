#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#define MAX_ARRAYS 26
#define MAX_COMMAND_LENGTH 256

typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_COMMAND,
    ERROR_INVALID_ARGUMENTS,
    ERROR_MEMORY_ALLOCATION,
    ERROR_FILE_IO,
    ERROR_OUT_OF_BOUNDS,
    ERROR_UNKNOWN
} StatusCode;

typedef struct {
    int *data;
    size_t size;
} Array;

Array arrays[MAX_ARRAYS];

void init_array(char name) {
    if (name < 'A' || name > 'Z') return;
    int index = name - 'A';
    arrays[index].data = NULL;
    arrays[index].size = 0;
}

void free_array(char name) {
    if (name < 'A' || name > 'Z') return;
    int index = name - 'A';
    free(arrays[index].data);
    arrays[index].data = NULL;
    arrays[index].size = 0;
}

StatusCode load_array(char name, const char *filename) {
    if (name < 'A' || name > 'Z') return ERROR_INVALID_ARGUMENTS;
    int index = name - 'A';

    FILE *file = fopen(filename, "r");
    if (!file) return ERROR_FILE_IO;

    int *temp_data = NULL;
    size_t temp_size = 0;
    int value;

    while (fscanf(file, "%d", &value) == 1) {
        int *new_data = realloc(temp_data, (temp_size + 1) * sizeof(int));
        if (!new_data) {
            free(temp_data);
            fclose(file);
            return ERROR_MEMORY_ALLOCATION;
        }
        temp_data = new_data;
        temp_data[temp_size++] = value;
    }

    fclose(file);

    free_array(name);
    arrays[index].data = temp_data;
    arrays[index].size = temp_size;

    return SUCCESS;
}

StatusCode save_array(char name, const char *filename) {
    if (name < 'A' || name > 'Z') return ERROR_INVALID_ARGUMENTS;
    int index = name - 'A';

    FILE *file = fopen(filename, "w");
    if (!file) return ERROR_FILE_IO;

    for (size_t i = 0; i < arrays[index].size; ++i) {
        fprintf(file, "%d%c", arrays[index].data[i], (i == arrays[index].size - 1) ? '\n' : ' ');
    }

    fclose(file);
    return SUCCESS;
}

StatusCode rand_array(char name, size_t count, int lb, int rb) {
    if (name < 'A' || name > 'Z') return ERROR_INVALID_ARGUMENTS;
    if (count == 0 || lb > rb) return ERROR_INVALID_ARGUMENTS;

    int index = name - 'A';

    int *new_data = malloc(count * sizeof(int));
    if (!new_data) return ERROR_MEMORY_ALLOCATION;

    for (size_t i = 0; i < count; ++i) {
        new_data[i] = lb + rand() % (rb - lb + 1);
    }

    free_array(name);
    arrays[index].data = new_data;
    arrays[index].size = count;

    return SUCCESS;
}

StatusCode concat_arrays(char name_a, char name_b) {
    if (name_a < 'A' || name_a > 'Z' || name_b < 'A' || name_b > 'Z') return ERROR_INVALID_ARGUMENTS;

    int index_a = name_a - 'A';
    int index_b = name_b - 'A';

    size_t new_size = arrays[index_a].size + arrays[index_b].size;
    int *new_data = realloc(arrays[index_a].data, new_size * sizeof(int));
    if (!new_data) return ERROR_MEMORY_ALLOCATION;

    memcpy(new_data + arrays[index_a].size, arrays[index_b].data, arrays[index_b].size * sizeof(int));
    arrays[index_a].data = new_data;
    arrays[index_a].size = new_size;

    return SUCCESS;
}

StatusCode remove_elements(char name, size_t start, size_t count) {
    if (name < 'A' || name > 'Z') return ERROR_INVALID_ARGUMENTS;

    int index = name - 'A';

    if (start >= arrays[index].size || count == 0) return ERROR_OUT_OF_BOUNDS;
    if (start + count > arrays[index].size) count = arrays[index].size - start;

    memmove(arrays[index].data + start, arrays[index].data + start + count, (arrays[index].size - start - count) * sizeof(int));
    arrays[index].size -= count;

    int *new_data = realloc(arrays[index].data, arrays[index].size * sizeof(int));
    if (!new_data && arrays[index].size > 0) return ERROR_MEMORY_ALLOCATION;

    arrays[index].data = new_data;

    return SUCCESS;
}

StatusCode copy_elements(char name_a, size_t start, size_t end, char name_b) {
    if (name_a < 'A' || name_a > 'Z' || name_b < 'A' || name_b > 'Z') return ERROR_INVALID_ARGUMENTS;

    int index_a = name_a - 'A';
    int index_b = name_b - 'A';

    if (start > end || end >= arrays[index_a].size) return ERROR_OUT_OF_BOUNDS;

    size_t new_size = end - start + 1;
    int *new_data = malloc(new_size * sizeof(int));
    if (!new_data) return ERROR_MEMORY_ALLOCATION;

    memcpy(new_data, arrays[index_a].data + start, new_size * sizeof(int));
    free_array(name_b);
    arrays[index_b].data = new_data;
    arrays[index_b].size = new_size;

    return SUCCESS;
}

int compare_ascending(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int compare_descending(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

StatusCode sort_array(char name, char order) {
    if (name < 'A' || name > 'Z') return ERROR_INVALID_ARGUMENTS;

    int index = name - 'A';
    if (arrays[index].size == 0) return ERROR_OUT_OF_BOUNDS;

    if (order == '+') {
        qsort(arrays[index].data, arrays[index].size, sizeof(int), compare_ascending);
    } else if (order == '-') {
        qsort(arrays[index].data, arrays[index].size, sizeof(int), compare_descending);
    } else {
        return ERROR_INVALID_ARGUMENTS;
    }

    return SUCCESS;
}

StatusCode shuffle_array(char name) {
    if (name < 'A' || name > 'Z') return ERROR_INVALID_ARGUMENTS;

    int index = name - 'A';
    if (arrays[index].size == 0) return ERROR_OUT_OF_BOUNDS;

    for (size_t i = 0; i < arrays[index].size; ++i) {
        size_t j = i + rand() / (RAND_MAX / (arrays[index].size - i) + 1);
        int temp = arrays[index].data[i];
        arrays[index].data[i] = arrays[index].data[j];
        arrays[index].data[j] = temp;
    }

    return SUCCESS;
}

StatusCode stats_array(char name) {
    if (name < 'A' || name > 'Z') return ERROR_INVALID_ARGUMENTS;

    int index = name - 'A';
    if (arrays[index].size == 0) return ERROR_OUT_OF_BOUNDS;

    int min = arrays[index].data[0], max = arrays[index].data[0];
    size_t min_index = 0, max_index = 0;
    double sum = 0;

    for (size_t i = 0; i < arrays[index].size; ++i) {
        if (arrays[index].data[i] < min) {
            min = arrays[index].data[i];
            min_index = i;
        }
        if (arrays[index].data[i] > max) {
            max = arrays[index].data[i];
            max_index = i;
        }
        sum += arrays[index].data[i];
    }

    double mean = sum / arrays[index].size;

    int *frequency = calloc(arrays[index].size, sizeof(int));
    if (!frequency) return ERROR_MEMORY_ALLOCATION;

    int most_frequent = arrays[index].data[0], max_count = 0;
    for (size_t i = 0; i < arrays[index].size; ++i) {
        for (size_t j = i; j < arrays[index].size; ++j) {
            if (arrays[index].data[i] == arrays[index].data[j]) {
                frequency[i]++;
            }
        }
        if (frequency[i] > max_count || (frequency[i] == max_count && arrays[index].data[i] > most_frequent)) {
            max_count = frequency[i];
            most_frequent = arrays[index].data[i];
        }
    }

    free(frequency);

    double max_deviation = 0;
    for (size_t i = 0; i < arrays[index].size; ++i) {
        double deviation = fabs(arrays[index].data[i] - mean);
        if (deviation > max_deviation) {
            max_deviation = deviation;
        }
    }

    printf("Array %c Stats:\n", name);
    printf("Size: %zu\n", arrays[index].size);
    printf("Min: %d (Index: %zu)\n", min, min_index);
    printf("Max: %d (Index: %zu)\n", max, max_index);
    printf("Mean: %.2f\n", mean);
    printf("Most Frequent: %d (Count: %d)\n", most_frequent, max_count);
    printf("Max Deviation: %.2f\n", max_deviation);

    return SUCCESS;
}

StatusCode print_array(char name, size_t start, size_t end) {
    if (name < 'A' || name > 'Z') return ERROR_INVALID_ARGUMENTS;

    int index = name - 'A';
    if (arrays[index].size == 0 || start > end || end >= arrays[index].size) return ERROR_OUT_OF_BOUNDS;

    for (size_t i = start; i <= end; ++i) {
        printf("%d%c", arrays[index].data[i], (i == end) ? '\n' : ' ');
    }

    return SUCCESS;
}

StatusCode process_command(const char *command) {
    char cmd[MAX_COMMAND_LENGTH];
    strncpy(cmd, command, MAX_COMMAND_LENGTH);
    cmd[MAX_COMMAND_LENGTH - 1] = '\0';

    char *token = strtok(cmd, " ,;");
    if (!token) return ERROR_INVALID_COMMAND;

    if (strcasecmp(token, "Load") == 0) {
        char *array_name = strtok(NULL, " ,;");
        char *filename = strtok(NULL, " ,;");
        if (!array_name || !filename || strlen(array_name) != 1) 
            return ERROR_INVALID_ARGUMENTS;
        return load_array(toupper(array_name[0]), filename);
    }

    if (strcasecmp(token, "Save") == 0) {
        char *array_name = strtok(NULL, " ,;");
        char *filename = strtok(NULL, " ,;");
        if (!array_name || !filename || strlen(array_name) != 1) 
            return ERROR_INVALID_ARGUMENTS;
        return save_array(toupper(array_name[0]), filename);
    }

    if (strcasecmp(token, "Rand") == 0) {
        char *array_name = strtok(NULL, " ,;");
        char *count_str = strtok(NULL, " ,;");
        char *lb_str = strtok(NULL, " ,;");
        char *rb_str = strtok(NULL, " ,;");
        if (!array_name || !count_str || !lb_str || !rb_str || strlen(array_name) != 1)
            return ERROR_INVALID_ARGUMENTS;

        size_t count = strtoul(count_str, NULL, 10);
        int lb = strtol(lb_str, NULL, 10);
        int rb = strtol(rb_str, NULL, 10);

        return rand_array(toupper(array_name[0]), count, lb, rb);
    }

    if (strcasecmp(token, "Free") == 0) {
        char *array_name = strtok(NULL, " ,;");
        if (!array_name || strlen(array_name) != 1) 
            return ERROR_INVALID_ARGUMENTS;
        free_array(toupper(array_name[0]));
        return SUCCESS;
    }

    if (strcasecmp(token, "Concat") == 0) {
        char *array_a = strtok(NULL, " ,;");
        char *array_b = strtok(NULL, " ,;");
        if (!array_a || !array_b || strlen(array_a) != 1 || strlen(array_b) != 1) 
            return ERROR_INVALID_ARGUMENTS;
        return concat_arrays(toupper(array_a[0]), toupper(array_b[0]));
    }

    if (strcasecmp(token, "Remove") == 0) {
        char *array_name = strtok(NULL, " ,;");
        char *start_str = strtok(NULL, " ,;");
        char *count_str = strtok(NULL, " ,;");
        if (!array_name || !start_str || !count_str || strlen(array_name) != 1)
            return ERROR_INVALID_ARGUMENTS;

        size_t start = strtoul(start_str, NULL, 10);
        size_t count = strtoul(count_str, NULL, 10);
        return remove_elements(toupper(array_name[0]), start, count);
    }

    if (strcasecmp(token, "Copy") == 0) {
        char *array_a = strtok(NULL, " ,;");
        char *start_str = strtok(NULL, " ,;");
        char *end_str = strtok(NULL, " ,;");
        char *array_b = strtok(NULL, " ,;");
        if (!array_a || !start_str || !end_str || !array_b || strlen(array_a) != 1 || strlen(array_b) != 1)
            return ERROR_INVALID_ARGUMENTS;

        size_t start = strtoul(start_str, NULL, 10);
        size_t end = strtoul(end_str, NULL, 10);
        return copy_elements(toupper(array_a[0]), start, end, toupper(array_b[0]));
    }

    if (strcasecmp(token, "Sort") == 0) {
        char *array_name = strtok(NULL, " ,;");
        char *order = strtok(NULL, " ,;");
        if (!array_name || !order || strlen(array_name) != 1 || strlen(order) != 1)
            return ERROR_INVALID_ARGUMENTS;
        return sort_array(toupper(array_name[0]), order[0]);
    }

    if (strcasecmp(token, "Shuffle") == 0) {
        char *array_name = strtok(NULL, " ,;");
        if (!array_name || strlen(array_name) != 1)
            return ERROR_INVALID_ARGUMENTS;
        return shuffle_array(toupper(array_name[0]));
    }

    if (strcasecmp(token, "Stats") == 0) {
        char *array_name = strtok(NULL, " ,;");
        if (!array_name || strlen(array_name) != 1)
            return ERROR_INVALID_ARGUMENTS;
        return stats_array(toupper(array_name[0]));
    }

    if (strcasecmp(token, "Print") == 0) {
        char *array_name = strtok(NULL, " ,;");
        char *start_str = strtok(NULL, " ,;");
        char *end_str = strtok(NULL, " ,;");

        if (!array_name || strlen(array_name) != 1) 
            return ERROR_INVALID_ARGUMENTS;

        if (strcasecmp(start_str, "all") == 0) {
            return print_array(toupper(array_name[0]), 0, arrays[toupper(array_name[0]) - 'A'].size - 1);
        }
        else {
            size_t start = strtoul(start_str, NULL, 10);
            size_t end = (end_str) ? strtoul(end_str, NULL, 10) : start;
            if (start > end || start >= arrays[toupper(array_name[0]) - 'A'].size) 
                return ERROR_INVALID_ARGUMENTS;

            return print_array(toupper(array_name[0]), start, end);
        }
    }

    return ERROR_INVALID_COMMAND;
}

StatusCode process_file(const char *filename) {
    if (!filename) return ERROR_INVALID_ARGUMENTS;

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return ERROR_FILE_IO;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *newline = strchr(line, '\n');
        if (newline) *newline = '\0';

        if (strlen(line) == 0) continue;

        StatusCode result = process_command(line);
        if (result != SUCCESS) {
            fprintf(stderr, "Error processing command: %s\n", line);
            fclose(file);
            return result;
        }
    }

    fclose(file);
    return SUCCESS;
}

int main(int argc, char *argv[]) {
    srand((unsigned)time(NULL));

    for (char name = 'A'; name <= 'Z'; ++name) {
        init_array(name);
    }

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <instructions.txt>\n", argv[0]);
        return ERROR_UNKNOWN;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return ERROR_FILE_IO;
    }

    char line[MAX_COMMAND_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = '\0';

        StatusCode status = process_command(line);
        if (status != SUCCESS) {
            fprintf(stderr, "Error processing command: %s (code: %d)\n", line, status);
        }
    }

    fclose(file);

    for (char name = 'A'; name <= 'Z'; ++name) {
        free_array(name);
    }

    return SUCCESS;
}