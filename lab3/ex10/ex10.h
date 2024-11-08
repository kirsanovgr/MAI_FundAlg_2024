#ifndef LAB3_EX10_H
#define LAB3_EX10_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/vector/charvector.h"

#define DEFAULT_COUNT_CHILD 5

typedef struct Node {
	String data;
	struct Node **children;
	int count_children;
	int capacity_children;
} Node;

typedef struct NodeLL {
	struct NodeLL *next;
	Node *node;
} NodeLL;

#define max(a, b) (a > b) ? a : b

// Проверка совпадения имен файлов
int checks_names_files(int argc, char **argv);

// Функции для дерева
error_msg build_tree(String *expression, Node **root);
void destroy_tree(Node *head);
void print_tree(FILE *output, Node *root, int level);

error_msg create_node(Node **node, String *s);
void destroy_node(Node *node);
error_msg add_node(Node *father, Node *child);

// Односвязный список
error_msg create_node_ll(NodeLL **nodeLl, Node *node);
error_msg push_into_ll(NodeLL **head, Node *x);
void print_ll(FILE *stream, NodeLL *head);
NodeLL *find_prev_node(NodeLL *head, NodeLL *cur);

void delete_node_ll(NodeLL *prev, NodeLL *cur);
#endif  // LAB3_EX10_H
