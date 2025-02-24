#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char label;
    struct Node** children;
    int child_count;
} Node;

typedef struct StackNode {
    Node* treeNode;
    struct StackNode* next;
} StackNode;

typedef enum {
    SUCCESS = 0,
    ERROR_MEMORY_ALLOCATION = -1,
    ERROR_FILE_OPERATION = -2,
    ERROR_INVALID_INPUT = -3
} StatusCode;

Node* create_node(char label) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->label = label;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

StatusCode add_child(Node* parent, Node* child) {
    if (parent == NULL || child == NULL) return ERROR_INVALID_INPUT;
    Node** new_children = realloc(parent->children, sizeof(Node*) * (parent->child_count + 1));
    if (new_children == NULL) return ERROR_MEMORY_ALLOCATION;
    parent->children = new_children;
    parent->children[parent->child_count++] = child;
    return SUCCESS;
}

void free_tree(Node* node) {
    if (node == NULL) return;
    for (int i = 0; i < node->child_count; i++) {
        free_tree(node->children[i]);
    }
    free(node->children);
    free(node);
}

StatusCode write_tree_to_file(const Node* node, FILE* file, int level) {
    if (node == NULL || file == NULL) return ERROR_INVALID_INPUT;
    for (int i = 0; i < level; i++) {
        if (fprintf(file, "  ") < 0) return ERROR_FILE_OPERATION;
    }
    if (fprintf(file, "%c\n", node->label) < 0) return ERROR_FILE_OPERATION;
    for (int i = 0; i < node->child_count; i++) {
        StatusCode result = write_tree_to_file(node->children[i], file, level + 1);
        if (result != SUCCESS) return result;
    }
    return SUCCESS;
}

StackNode* push(StackNode* stack, Node* treeNode) {
    StackNode* new_top = malloc(sizeof(StackNode));
    if (!new_top) return NULL;
    new_top->treeNode = treeNode;
    new_top->next = stack;
    return new_top;
}

StackNode* pop(StackNode** stack) {
    if (!(*stack)) return NULL;
    StackNode* top = *stack;
    *stack = (*stack)->next;
    return top;
}

Node* parse_expression(const char* expr) {
    StackNode* stack = NULL;
    Node* root = NULL;
    Node* current = NULL;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isalpha((unsigned char)expr[i])) {
            Node* new_node = create_node(expr[i]);
            if (new_node == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return NULL;
            }
            if (current == NULL) {
                root = new_node;
            } else {
                if (add_child(current, new_node) != SUCCESS) {
                    free_tree(new_node);
                    return NULL;
                }
            }
            current = new_node;
        } else if (expr[i] == '(') {
            stack = push(stack, current);
        } else if (expr[i] == ',') {
            current = stack->treeNode;
        } else if (expr[i] == ')') {
            StackNode* temp = pop(&stack);
            current = temp ? temp->treeNode : NULL;
            free(temp);
        }
    }

    while (stack) {
        StackNode* temp = pop(&stack);
        free(temp);
    }
    return root;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return ERROR_INVALID_INPUT;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Error opening input file");
        return ERROR_FILE_OPERATION;
    }

    FILE* output = fopen(argv[2], "w");
    if (output == NULL) {
        perror("Error opening output file");
        fclose(input);
        return ERROR_FILE_OPERATION;
    }

    char line[1024];
    while (fgets(line, sizeof(line), input) != NULL) {
        Node* tree = parse_expression(line);
        if (tree == NULL) {
            fprintf(stderr, "Failed to parse expression\n");
            continue;
        }

        StatusCode result = write_tree_to_file(tree, output, 0);
        if (result != SUCCESS) {
            fprintf(stderr, "Error writing tree to file\n");
            free_tree(tree);
            break;
        }
        fprintf(output, "\n");
        free_tree(tree);
    }

    fclose(input);
    fclose(output);
    return SUCCESS;
}
