#include "func.h"

Node* CreateNode(char data) {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }
    newNode->data = data;
    newNode->children = NULL;
    newNode->child_count = 0;
    return newNode;
}

void AddChild(Node* parent, Node* child) {
    parent->children = (Node**)realloc(parent->children, (parent->child_count + 1) * sizeof(Node*));
    if (parent->children == NULL) {
        printf("Ошибка выделения памяти для потомков\n");
        return;
    }
    parent->children[parent->child_count++] = child;
}

Stack* CreateStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        return NULL;
    }
    stack->data = (Node**)malloc(capacity * sizeof(Node*));
    if (!stack->data) {
        free(stack);
        return NULL;
    }
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void Push(Stack* stack, Node* node) {
    if (stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = node;
    }
}

Node* Pop(Stack* stack) {
    return (stack->top >= 0) ? stack->data[stack->top--] : NULL;
}

Node* Peek(Stack* stack) {
    return (stack->top >= 0) ? stack->data[stack->top] : NULL;
}

void FreeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

Node* ParseExpression(const char* str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    Stack* stack = CreateStack(MAX_STACK_SIZE); // глубина дерева 100 узлов max
    if (!stack) {
        return NULL;
    }

    Node* root = NULL;
    Node* current = NULL;

    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {  // Обрабатываем узел
            Node* newNode = CreateNode(*str);
            if (newNode == NULL) {
                FreeStack(stack);
                return NULL;
            }
            if (!root) {
                root = newNode;  // Первый узел становится корнем
            } else {
                // Добавляем потомка текущему узлу
                AddChild(Peek(stack), newNode);
            }
            current = newNode;  // Обновляем текущий узел
        } else if (*str == '(') {
            Push(stack, current);  // Сохраняем текущий узел в стек
        } else if (*str == ')') {
            Pop(stack);            // Закрывающая скобка — возвращаемся к родителю
        }
        str++;
    }

    FreeStack(stack);
    return root;
}

void PrintTree(FILE* output, Node* root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) {
        fprintf(output, "\t"); 
    }
    fprintf(output, "%c\n", root->data);

    for (int i = 0; i < root->child_count; i++) {
        PrintTree(output, root->children[i], level + 1);
    }
}

void FreeTree(Node* root) {
    if (root == NULL) return;
    for (int i = 0; i < root->child_count; i++) {
        FreeTree(root->children[i]);  // Освобождаем каждого потомка
    }
    free(root->children);  // Освобождаем массив потомков
    free(root);  // Освобождаем память текущего узла
}
