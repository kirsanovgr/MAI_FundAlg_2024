#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_HASHSIZE 128
#define RESIZE_FACTOR 2

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **buckets;
    size_t size;
} HashTable;

Node *create_node(const char *key, const char *value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Error: Not enough memory to create node.\n");
        return NULL;
    }

    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;

    if (!node->key || !node->value) {
        fprintf(stderr, "Error: Not enough memory for key or value.\n");
        free(node->key);
        free(node->value);
        free(node);
        return NULL;
    }

    return node;
}

HashTable *create_table(size_t size) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (!table) {
        fprintf(stderr, "Error: Not enough memory to create hash table.\n");
        return NULL;
    }

    table->buckets = (Node **)calloc(size, sizeof(Node *));
    if (!table->buckets) {
        fprintf(stderr, "Error: Not enough memory for hash table buckets.\n");
        free(table);
        return NULL;
    }

    table->size = size;
    return table;
}

void free_table(HashTable *table) {
    if (!table) return;

    for (size_t i = 0; i < table->size; ++i) {
        Node *current = table->buckets[i];
        while (current) {
            Node *temp = current;
            current = current->next;

            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }

    free(table->buckets);
    free(table);
}

size_t hash_function(const char *key, size_t table_size) {
    size_t hash = 0;
    size_t base = 62;

    for (size_t i = 0; key[i] != '\0'; ++i) {
        char c = key[i];
        size_t value;

        if (c >= '0' && c <= '9') value = c - '0';
        else if (c >= 'A' && c <= 'Z') value = c - 'A' + 10;
        else if (c >= 'a' && c <= 'z') value = c - 'a' + 36;
        else continue;

        hash = hash * base + value;
    }

    return hash % table_size;
}

int add_to_table(HashTable *table, const char *key, const char *value) {
    if (!table || !key || !value) return -1;

    size_t index = hash_function(key, table->size);
    Node *current = table->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            return 0;
        }
        current = current->next;
    }

    Node *new_node = create_node(key, value);
    if (!new_node) return -2;

    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;

    return 0;
}

const char *find_in_table(const HashTable *table, const char *key) {
    if (!table || !key) return NULL;

    size_t index = hash_function(key, table->size);
    Node *current = table->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

int rebuild_table(HashTable *table) {
    if (!table) return -1;

    size_t new_size = table->size * RESIZE_FACTOR;
    Node **new_buckets = (Node **)calloc(new_size, sizeof(Node *));
    if (!new_buckets) {
        fprintf(stderr, "Error: Not enough memory to rebuild hash table.\n");
        return -2;
    }

    for (size_t i = 0; i < table->size; ++i) {
        Node *current = table->buckets[i];
        while (current) {
            Node *next = current->next;

            size_t new_index = hash_function(current->key, new_size);

            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;

            current = next;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->size = new_size;

    return 0;
}

size_t chain_length(Node *chain) {
    size_t length = 0;
    while (chain) {
        ++length;
        chain = chain->next;
    }
    return length;
}

int check_and_rebuild_table(HashTable *table) {
    if (!table) return -1;

    size_t min_length = SIZE_MAX;
    size_t max_length = 0;

    for (size_t i = 0; i < table->size; ++i) {
        size_t length = chain_length(table->buckets[i]);
        if (length < min_length) min_length = length;
        if (length > max_length) max_length = length;
    }

    if (max_length >= 2 * min_length) {
        return rebuild_table(table);
    }

    return 0;
}

char *process_line(const char *line, const HashTable *table) {
    if (!line || !table) return NULL; 

    size_t buffer_size = strlen(line) + 1;
    char *result = (char *)malloc(buffer_size);
    if (!result) {
        fprintf(stderr, "Error: Not enough memory to process string.\n");
        return NULL;
    }

    result[0] = '\0';

    const char *current = line;
    while (*current) {
        if ((*current >= 'A' && *current <= 'Z') || 
            (*current >= 'a' && *current <= 'z') || 
            (*current >= '0' && *current <= '9')) {

            const char *start = current;
            while ((*current >= 'A' && *current <= 'Z') || 
                   (*current >= 'a' && *current <= 'z') || 
                   (*current >= '0' && *current <= '9')) {
                ++current;
            }

            size_t macro_length = current - start;
            char *macro = (char *)malloc(macro_length + 1);
            if (!macro) {
                fprintf(stderr, "Error: Not enough memory for macro.\n");
                free(result);
                return NULL;
            }
            strncpy(macro, start, macro_length);
            macro[macro_length] = '\0';

            const char *replacement = find_in_table(table, macro);
            free(macro);

            if (replacement) {
                size_t new_length = strlen(result) + strlen(replacement) + 1;
                if (new_length > buffer_size) {
                    buffer_size = new_length * 2;
                    char *temp = realloc(result, buffer_size);
                    if (!temp) {
                        fprintf(stderr, "Error: Not enough memory to expand result.\n");
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                strcat(result, replacement);
            } else {
                size_t new_length = strlen(result) + macro_length + 1;
                if (new_length > buffer_size) {
                    buffer_size = new_length * 2;
                    char *temp = realloc(result, buffer_size);
                    if (!temp) {
                        fprintf(stderr, "Error: Not enough memory to expand result.\n");
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                strncat(result, start, macro_length);
            }
        } else {
            size_t current_length = strlen(result);
            if (current_length + 2 > buffer_size) {
                buffer_size *= 2;
                char *temp = realloc(result, buffer_size);
                if (!temp) {
                    fprintf(stderr, "Error: Not enough memory to expand result.\n");
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            result[current_length] = *current;
            result[current_length + 1] = '\0';
            ++current;
        }
    }

    return result;
}

int process_file(const char *input_path, const char *output_path, HashTable *table) {
    if (!input_path || !output_path || !table) return -1;

    FILE *input_file = fopen(input_path, "r");
    if (!input_file) {
        fprintf(stderr, "Error: Could not open file %s for reading.\n", input_path);
        return -2;
    }

    FILE *output_file = fopen(output_path, "w");
    if (!output_file) {
        fprintf(stderr, "Error: Could not open file %s for writing.\n", output_path);
        fclose(input_file);
        return -3;
    }

    char *line = NULL;
    size_t line_capacity = 0;
    ssize_t line_length;

    while ((line_length = getline(&line, &line_capacity, input_file)) != -1) {
        if (line_length > 0 && line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
        }

        if (strncmp(line, "#define ", 8) == 0) {
            char *key = strtok(line + 8, " ");
            char *value = strtok(NULL, "");

            if (key && value) {
                if (add_to_table(table, key, value) != 0) {
                    fprintf(stderr, "Error: Failed to add macro %s to table.\n", key);
                }
            }

            fprintf(output_file, "#define %s %s\n", key, value);
        } else {
            char *processed_line = process_line(line, table);
            if (!processed_line) {
                fprintf(stderr, "Error: String processing failed.\n");
                free(line);
                fclose(input_file);
                fclose(output_file);
                return -4;
            }

            fprintf(output_file, "%s\n", processed_line);

            free(processed_line);
        }
    }

    free(line);
    fclose(input_file);
    fclose(output_file);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    const char *input_path = argv[1];
    const char *output_path = argv[2];

    HashTable *table = create_table(INITIAL_HASHSIZE);
    if (!table) {
        fprintf(stderr, "Error: Failed to create hash table.\n");
        return 2;
    }

    FILE *input_file = fopen(input_path, "r");
    if (!input_file) {
        fprintf(stderr, "Error: Could not open file %s for reading.\n", input_path);
        free_table(table);
        return 3;
    }

    char *line = NULL;
    size_t line_capacity = 0;
    ssize_t line_length;

    while ((line_length = getline(&line, &line_capacity, input_file)) != -1) {
        if (line_length == 0 || line[0] == '\n') continue;

        if (line[line_length - 1] == '\n') line[line_length - 1] = '\0';

        if (strncmp(line, "#define", 7) == 0) {
            char *key = strtok(line + 7, " \t");
            char *value = strtok(NULL, "\0");

            if (key && value) {
                if (add_to_table(table, key, value) != 0) {
                    fprintf(stderr, "Error: Failed to add macro %s.\n", key);
                    free(line);
                    fclose(input_file);
                    free_table(table);
                    return 4;
                }

                if (check_and_rebuild_table(table) != 0) {
                    fprintf(stderr, "Error: Failed to rebuild hash table.\n");
                    free(line);
                    fclose(input_file);
                    free_table(table);
                    return 5;
                }
            } else {
                fprintf(stderr, "Error: Invalid #define directive.\n");
            }
        } else {
            fseek(input_file, -line_length, SEEK_CUR);
            break;
        }
    }

    free(line);
    fclose(input_file);

    if (process_file(input_path, output_path, table) != 0) {
        fprintf(stderr, "Error: Failed to process file %s.\n", input_path);
        free_table(table);
        return 6;
    }

    free_table(table);
    return 0;
}