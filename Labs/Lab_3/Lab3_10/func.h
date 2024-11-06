#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef enum Error {
    SUCCESS = 0,
    INPUT_ERROR = 1
} Status;

typedef struct Node {
    char data;          // Значение узла (символ)
    struct Node** children; // Массив потомков
    int child_count;    // Количество потомков
} Node;

typedef struct Stack {
    Node** data;
    int top;
    int capacity;
} Stack;

Node* ParseExpression(const char* str);
void PrintTree(FILE* output, Node* root, int level);
void FreeTree(Node* root);