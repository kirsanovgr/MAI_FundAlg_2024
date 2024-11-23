#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_PATH_LENGTH 260
#define BUFFER_SIZE 1024

typedef enum {
    SUCCESS,
    ERROR_INVALID_ARGUMENTS,
    ERROR_FILE_NOT_FOUND,
    ERROR_MEMORY_ALLOCATION,
    ERROR_SYNTAX,
    ERROR_INVALID_OPERATION
} StatusCode;

typedef struct {
    char name;
    unsigned int value;
} Variable;

typedef enum {
    OP_ASSIGN,
    OP_NOT,
    OP_READ,
    OP_WRITE,
    OP_INVALID
} OperationType;

typedef struct {
    OperationType type;
    char var1;
    char var2;
    char var3;
    char op[3];
    int base;
} ParsedOperation;

void initialize_variables(Variable variables[]) {
    for (int i = 0; i < 26; i++) {
        variables[i].name = 'A' + i;
        variables[i].value = 0;
    }
}

Variable* get_variable(Variable variables[], char name) {
    if (name >= 'A' && name <= 'Z') {
        return &variables[name - 'A'];
    }
    return NULL;
}

StatusCode validate_arguments(int argc, char *argv[], char *input_file, char *trace_file, bool *trace_enabled) {
    if (argc < 2 || argc > 4) {
        return ERROR_INVALID_ARGUMENTS;
    }

    strcpy(input_file, argv[1]);

    if (argc == 4 && strcmp(argv[2], "/trace") == 0) {
        *trace_enabled = true;
        strcpy(trace_file, argv[3]);
    } else {
        *trace_enabled = false;
    }

    return SUCCESS;
}

void remove_comments(const char *source, char *destination) {
    bool in_single_line_comment = false;
    bool in_multi_line_comment = false;
    
    while (*source) {
        if (in_single_line_comment) {
            if (*source == '\n') {
                in_single_line_comment = false;
            }
        } else if (in_multi_line_comment) {
            if (*source == '}') {
                in_multi_line_comment = false;
            }
        } else {
            if (*source == '%' && !in_multi_line_comment) {
                in_single_line_comment = true;
            } else if (*source == '{' && !in_single_line_comment) {
                in_multi_line_comment = true;
            } else {
                *destination++ = *source;
            }
        }
        source++;
    }
    *destination = '\0';
}

char* read_file(FILE *file) {
    char *content = NULL;
    size_t content_size = 0;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, file)) {
        size_t buffer_length = strlen(buffer);
        char *new_content = realloc(content, content_size + buffer_length + 1);
        if (!new_content) {
            free(content);
            return NULL;
        }
        content = new_content;
        strcpy(content + content_size, buffer);
        content_size += buffer_length;
    }

    return content;
}

OperationType parse_operation(const char *operator, ParsedOperation *parsed_op) {
    if (sscanf(operator, " %c := %c %2s %c ", &parsed_op->var1, &parsed_op->var2, parsed_op->op, &parsed_op->var3) == 4) {
        parsed_op->type = OP_ASSIGN;
        return OP_ASSIGN;
    }
    if (sscanf(operator, " %c := \\%c ", &parsed_op->var1, &parsed_op->var2) == 2) {
        parsed_op->type = OP_NOT;
        return OP_NOT;
    }
    if (sscanf(operator, " read ( %c , %d ) ", &parsed_op->var1, &parsed_op->base) == 2) {
        parsed_op->type = OP_READ;
        return OP_READ;
    }
    if (sscanf(operator, " write ( %c , %d ) ", &parsed_op->var1, &parsed_op->base) == 2) {
        parsed_op->type = OP_WRITE;
        return OP_WRITE;
    }
    return OP_INVALID;
}

void log_operation(const ParsedOperation *parsed_op, FILE *trace_fp, const char *message) {
    if (trace_fp) {
        fprintf(trace_fp, "Operation: ");
        switch (parsed_op->type) {
            case OP_ASSIGN:
                fprintf(trace_fp, "%c := %c %s %c\n", parsed_op->var1, parsed_op->var2, parsed_op->op, parsed_op->var3);
                break;
            case OP_NOT:
                fprintf(trace_fp, "%c := \\%c\n", parsed_op->var1, parsed_op->var2);
                break;
            case OP_READ:
                fprintf(trace_fp, "read(%c, %d)\n", parsed_op->var1, parsed_op->base);
                break;
            case OP_WRITE:
                fprintf(trace_fp, "write(%c, %d)\n", parsed_op->var1, parsed_op->base);
                break;
            default:
                fprintf(trace_fp, "Invalid operation\n");
                break;
        }
        fprintf(trace_fp, "Message: %s\n", message);
    }
}

unsigned int perform_binary_operation(unsigned int a, unsigned int b, const char *op) {
    if (strcmp(op, "+") == 0) return a | b;
    if (strcmp(op, "&") == 0) return a & b;
    if (strcmp(op, "->") == 0) return ~a | b;
    if (strcmp(op, "<-") == 0) return a | ~b;
    if (strcmp(op, "~") == 0) return ~(a ^ b);
    if (strcmp(op, "<>") == 0) return a ^ b;
    if (strcmp(op, "+>") == 0) return ~(a & b);
    if (strcmp(op, "?") == 0) return ~(a & b);
    if (strcmp(op, "!") == 0) return ~(a | b);
    return 0;
}

StatusCode execute_operation(const ParsedOperation *parsed_op, Variable variables[], FILE *trace_fp) {
    Variable *var1 = get_variable(variables, parsed_op->var1);
    Variable *var2 = get_variable(variables, parsed_op->var2);
    Variable *var3 = get_variable(variables, parsed_op->var3);

    switch (parsed_op->type) {
        case OP_ASSIGN:
            if (var1 && var2 && var3) {
                var1->value = perform_binary_operation(var2->value, var3->value, parsed_op->op);
                log_operation(parsed_op, trace_fp, "Assignment executed");
            } else {
                log_operation(parsed_op, trace_fp, "Invalid variables for ASSIGN operation");
                return ERROR_INVALID_OPERATION;
            }
            break;
        case OP_NOT:
            if (var1 && var2) {
                var1->value = ~var2->value;
                log_operation(parsed_op, trace_fp, "Bitwise NOT executed");
            } else {
                log_operation(parsed_op, trace_fp, "Invalid variables for NOT operation");
                return ERROR_INVALID_OPERATION;
            }
            break;
        case OP_READ:
            if (var1) {
                char input[BUFFER_SIZE];
                if (fgets(input, BUFFER_SIZE, stdin)) {
                    var1->value = strtoul(input, NULL, parsed_op->base);
                    log_operation(parsed_op, trace_fp, "Read executed");
                } else {
                    log_operation(parsed_op, trace_fp, "Failed to read input");
                    return ERROR_INVALID_OPERATION;
                }
            } else {
                log_operation(parsed_op, trace_fp, "Invalid variable for READ operation");
                return ERROR_INVALID_OPERATION;
            }
            break;
        case OP_WRITE:
            if (var1) {
                char output[BUFFER_SIZE];
                snprintf(output, BUFFER_SIZE, "%u", var1->value);
                unsigned int value = var1->value;
                char binary_output[BUFFER_SIZE];
                itoa(value, binary_output, 2);
                printf("%s\n", binary_output);
                log_operation(parsed_op, trace_fp, "Write executed");
            } else {
                log_operation(parsed_op, trace_fp, "Invalid variable for WRITE operation");
                return ERROR_INVALID_OPERATION;
            }
            break;
        default:
            fprintf(stderr, "Invalid operation.\n");
            log_operation(parsed_op, trace_fp, "Invalid operation");
            return ERROR_INVALID_OPERATION;
    }
    return SUCCESS;
}

int main(int argc, char *argv[]) {
    char input_file[MAX_PATH_LENGTH];
    char trace_file[MAX_PATH_LENGTH];
    bool trace_enabled;
    StatusCode status;

    status = validate_arguments(argc, argv, input_file, trace_file, &trace_enabled);
    if (status != SUCCESS) {
        fprintf(stderr, "Invalid arguments.\n");
        return status;
    }

    FILE *input_fp = fopen(input_file, "r");
    if (!input_fp) {
        fprintf(stderr, "Error opening input file.\n");
        return ERROR_FILE_NOT_FOUND;
    }

    FILE *trace_fp = NULL;
    if (trace_enabled) {
        trace_fp = fopen(trace_file, "w");
        if (!trace_fp) {
            fprintf(stderr, "Error opening trace file.\n");
            fclose(input_fp);
            return ERROR_FILE_NOT_FOUND;
        }
    }

    char *file_content = read_file(input_fp);
    if (!file_content) {
        fprintf(stderr, "Error reading input file.\n");
        fclose(input_fp);
        if (trace_fp) {
            fclose(trace_fp);
        }
        return ERROR_MEMORY_ALLOCATION;
    }

    char *cleaned_content = malloc(strlen(file_content) + 1);
    if (!cleaned_content) {
        fprintf(stderr, "Memory allocation error.\n");
        free(file_content);
        fclose(input_fp);
        if (trace_fp) {
            fclose(trace_fp);
        }
        return ERROR_MEMORY_ALLOCATION;
    }

    remove_comments(file_content, cleaned_content);
    free(file_content);

    Variable variables[26];
    initialize_variables(variables);

    char *operator = strtok(cleaned_content, ";");
    while (operator != NULL) {
        while (isspace(*operator)) operator++;
        if (*operator == '\0') {
            operator = strtok(NULL, ";");
            continue;
        }

        ParsedOperation parsed_op;
        if (parse_operation(operator, &parsed_op) != OP_INVALID) {
            status = execute_operation(&parsed_op, variables, trace_fp);
            if (status != SUCCESS) {
                fprintf(stderr, "Error executing operation: %s\n", operator);
                if (trace_fp) {
                    fprintf(trace_fp, "Error executing operation: %s\n", operator);
                }
            }
        } else {
            fprintf(stderr, "Syntax error in operator: %s\n", operator);
            if (trace_fp) {
                fprintf(trace_fp, "Syntax error in operator: %s\n", operator);
            }
        }
        operator = strtok(NULL, ";");
    }

    free(cleaned_content);
    fclose(input_fp);
    if (trace_fp) {
        fclose(trace_fp);
    }

    return SUCCESS;
}