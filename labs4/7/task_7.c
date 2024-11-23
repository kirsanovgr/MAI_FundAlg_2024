#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *name;
    int value;
} MemoryCell;

int compareMemoryCells(const void *a, const void *b) {
    return strcmp(((MemoryCell *)a)->name, ((MemoryCell *)b)->name);
}

MemoryCell *findMemoryCell(MemoryCell *cells, int size, const char *name) {
    MemoryCell key = { .name = (char *)name, .value = 0 };
    return (MemoryCell *)bsearch(&key, cells, size, sizeof(MemoryCell), compareMemoryCells);
}

int addMemoryCell(MemoryCell **cells, int *size, int *capacity, const char *name, int value) {
    MemoryCell *existingCell = findMemoryCell(*cells, *size, name);
    if (existingCell) {
        existingCell->value = value;
        return 0;
    }

    if (*size >= *capacity) {
        *capacity *= 2;
        MemoryCell *newCells = realloc(*cells, *capacity * sizeof(MemoryCell));
        if (!newCells) {
            free(*cells);
            return -1;
        }
        *cells = newCells;
    }
    (*cells)[*size].name = strdup(name);
    if (!(*cells)[*size].name) {
        free(*cells);
        return -1;
    }
    (*cells)[*size].value = value;
    (*size)++;
    qsort(*cells, *size, sizeof(MemoryCell), compareMemoryCells);
    return 0;
}

char *readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = malloc(length + 1);
    if (!content) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);
    return content;
}

int performOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                fprintf(stderr, "Error: division by zero\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        case '%':
            if (b == 0) {
                fprintf(stderr, "Error: modulo by zero\n");
                return 0;
            }
            return a % b;
        default: return 0;
    }
}

int isValidVariableName(const char *name) {
    if (!name || !*name) return 0;
    for (const char *p = name; *p; p++) {
        if (!(((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p == '_')))) {
            return 0;
        }
    }
    return 1;
}

int executeCommand(char *command, MemoryCell **cells, int *size, int *capacity) {
    char *token = strtok(command, " ");
    if (!token) {
        return -1;
    }

    if (strcmp(token, "print") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            MemoryCell *cell = findMemoryCell(*cells, *size, token);
            if (cell) {
                printf("%s = %d\n", cell->name, cell->value);
            } else {
                fprintf(stderr, "Error: variable '%s' not found\n", token);
                return -1;
            }
        } else {
            for (int i = 0; i < *size; i++) {
                printf("%s = %d\n", (*cells)[i].name, (*cells)[i].value);
            }
        }
    } else {
        char *name = strtok(token, "=");
        char *expression = strtok(NULL, "=");
        if (!name || !expression || !isValidVariableName(name)) {
            fprintf(stderr, "Error: invalid command '%s'\n", command);
            return -1;
        }

        char *op = strpbrk(expression, "+-*/%");
        char *endptr;
        if (op) {
            char operator = *op;
            *op = '\0';
            op++;
            int a = strtol(expression, &endptr, 10);
            if (*endptr != '\0') {
                MemoryCell *cellA = findMemoryCell(*cells, *size, expression);
                a = cellA ? cellA->value : 0;
            }
            int b = strtol(op, &endptr, 10);
            if (*endptr != '\0') {
                MemoryCell *cellB = findMemoryCell(*cells, *size, op);
                b = cellB ? cellB->value : 0;
            }
            int result = performOperation(a, b, operator);
            if (addMemoryCell(cells, size, capacity, name, result) != 0) {
                fprintf(stderr, "Error: could not add variable '%s'\n", name);
                return -1;
            }
        } else {
            int value = strtol(expression, &endptr, 10);
            if (*endptr != '\0') {
                MemoryCell *cell = findMemoryCell(*cells, *size, expression);
                value = cell ? cell->value : 0;
            }
            if (addMemoryCell(cells, size, capacity, name, value) != 0) {
                fprintf(stderr, "Error: could not add variable '%s'\n", name);
                return -1;
            }
        }
    }
    return 0;
}

void parseAndExecuteInstructions(const char *instructions, MemoryCell **cells, int *size, int *capacity) {
    char *instructionsCopy = strdup(instructions);
    if (!instructionsCopy) {
        perror("Memory allocation error");
        return;
    }

    char *line = instructionsCopy;
    char *semicolon;

    while ((semicolon = strchr(line, ';')) != NULL) {
        *semicolon = '\0';
        while (isspace(*line)) line++;
        char *lineEnd = line + strlen(line) - 1;
        while (lineEnd > line && isspace(*lineEnd)) *lineEnd-- = '\0';

        if (*line != '\0') {
            if (executeCommand(line, cells, size, capacity) != 0) {
                fprintf(stderr, "Error executing command: %s\n", line);
                break;
            }
        }

        line = semicolon + 1;
    }

    free(instructionsCopy);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <instructions_file>\n", argv[0]);
        return 1;
    }

    char *instructions = readFile(argv[1]);
    if (!instructions || instructions[0] == '\0') {
        fprintf(stderr, "Error: file is empty or could not read content.\n");
        return 1;
    }

    int size = 0;
    int capacity = 10;
    MemoryCell *cells = malloc(capacity * sizeof(MemoryCell));
    if (!cells) {
        perror("Memory allocation error");
        free(instructions);
        return 1;
    }

    parseAndExecuteInstructions(instructions, &cells, &size, &capacity);

    for (int i = 0; i < size; i++) {
        free(cells[i].name);
    }
    free(cells);
    free(instructions);

    return 0;
}