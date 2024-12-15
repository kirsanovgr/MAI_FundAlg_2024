#include "ex10.h"

int checks_names_files(int argc, char **argv) {
	if(argc != 3){
		return INCORRECT_OPTIONS_ERROR;
	}
	char *realnames[2] = {};
	for (int i = 0; i < 2; ++i) {
		realnames[i] = malloc(sizeof(char) * 4096);
	}

	realpath(argv[1], realnames[0]);
	realpath(argv[2], realnames[1]);

	if (string_cmp(realnames[0], realnames[1])) {
		for (int i = 0; i < 2; ++i) {
			free(realnames[i]);
		}
		return INCORRECT_OPTIONS_ERROR;
	}

	for (int i = 0; i < 2; ++i) {
		free(realnames[i]);
	}
	return SUCCESS;
}

error_msg to_linked_list(String *expression, NodeLL **linked_list_nodes) {
	NodeLL *nodes = *linked_list_nodes;
	nodes = NULL;
	String tmp;
	error_msg errorMsg = create_string(&tmp, "");
	if (errorMsg) {
		return errorMsg;
	}

	// Вспомогательные, где хранятся скобки
	String s1;
	errorMsg = create_string(&s1, "(");
	if (errorMsg) {
		destroy_string(&tmp);
		return errorMsg;
	}
	String s2;
	errorMsg = create_string(&s2, ")");
	if (errorMsg) {
		destroy_string(&tmp);
		destroy_string(&s1);
		return errorMsg;
	}

	String s3;
	errorMsg = create_string(&s3, ",");
	if (errorMsg) {
		destroy_string(&tmp);
		destroy_string(&s1);
		destroy_string(&s3);
		return errorMsg;
	}

	for (int i = 0; i < expression->size; ++i) {
		if((expression->arr[i] == '(' ||expression->arr[i] == ')' || expression->arr[i] == ',' || i == expression->size - 1) && tmp.size > 0) {
			Node *word;
			errorMsg = create_node(&word, &tmp);
			if (errorMsg) {
				destroy_string(&tmp);
				destroy_string(&s1);
				destroy_string(&s2);
				destroy_string(&s3);
			}
			clear_string(&tmp);
			errorMsg = push_into_ll(&nodes, word);
			if (errorMsg) {
				destroy_string(&tmp);
				destroy_string(&s1);
				destroy_string(&s2);
				destroy_string(&s3);
				return errorMsg;
			}
			clear_string(&tmp);
		}
		if (expression->arr[i] == '(' ||expression->arr[i] == ')' ||expression->arr[i] == ',' ){
			Node *node;
			if(expression->arr[i] == '(')
				errorMsg = create_node(&node, &s1);
			else if(expression->arr[i] == ')')
				errorMsg = create_node(&node, &s2);
			else
				errorMsg = create_node(&node, &s3);
			if (errorMsg) {
				destroy_string(&tmp);
				destroy_string(&s1);
				destroy_string(&s2);
				destroy_string(&s3);
				return errorMsg;
			}
			errorMsg = push_into_ll(&nodes, node);
			if (errorMsg) {
				destroy_string(&tmp);
				destroy_string(&s1);
				destroy_string(&s2);
				destroy_string(&s3);
				return errorMsg;
			}
			clear_string(&tmp);
		}else if(expression->arr[i] != ' ' && expression->arr[i] != ','){
			errorMsg = push_end_string(&tmp, expression->arr[i]);
			if(errorMsg){
				destroy_string(&tmp);
				destroy_string(&s1);
				destroy_string(&s2);
				destroy_string(&s3);
				return errorMsg;
			}
		}
	}
	*linked_list_nodes = nodes;
	destroy_string(&tmp);
	destroy_string(&s1);
	destroy_string(&s2);
	destroy_string(&s3);
	return SUCCESS;
}

NodeLL * find_max_level(NodeLL * nodeLl){
	NodeLL * node = NULL;
	while (nodeLl->next){
		if(string_cmp(nodeLl->node->data.arr, "(")){
			node = nodeLl;
		}
		nodeLl = nodeLl->next;
	}
	return node;
}

error_msg build_tree(String *expression, Node **root) {
	NodeLL *linked_list_nodes;
	error_msg errorMsg = to_linked_list(expression, &linked_list_nodes);
	if (errorMsg) {
		return errorMsg;
	}
	NodeLL * x;
	NodeLL * main_nodell;
	while ((x = find_max_level(linked_list_nodes))){
		// Находим элемент на который потом будем опираться
		main_nodell = find_prev_node(linked_list_nodes, x);
		if(!main_nodell || string_cmp(main_nodell->node->data.arr, ",") || string_cmp(main_nodell->node->data.arr, "(")){
			main_nodell = x;
			while (main_nodell && !string_cmp(main_nodell->node->data.arr, ")")) main_nodell = main_nodell->next;
			main_nodell = main_nodell->next;
		}

		// Добавляем выражения из скобок в детей главного узла(main_nodell)
		NodeLL * tmp = x->next;
		while (tmp && !string_cmp(tmp->node->data.arr, ")")){
			if(!string_cmp(tmp->node->data.arr, ",")){
				errorMsg = add_node(main_nodell->node, tmp->node);
				if(errorMsg){
					return errorMsg;
				}
			}
			tmp = tmp->next;
		}
		// Удаляем уже добавленные узлы и оставляем только главный

		// Случай если скобки стоят первые например (A, B) C - надо оставить только C
		if(x == linked_list_nodes){
			while (x && !string_cmp(x->node->data.arr, ")")) {
				linked_list_nodes = linked_list_nodes->next;
				if(string_cmp(x->node->data.arr, ",") || string_cmp(x->node->data.arr, "(") || string_cmp(x->node->data.arr, ")")){
					destroy_node(x->node);
				}
				free(x);
				x = linked_list_nodes;
			}
			linked_list_nodes = linked_list_nodes->next;
			destroy_node(x->node);
			free(x);

		} else{
			NodeLL * prev = find_prev_node(linked_list_nodes, x);
			x = prev->next;
			NodeLL *t;
			while (x && !string_cmp(x->node->data.arr, ")")){
				t = x;
				x = x->next;
				if(string_cmp(t->node->data.arr, ",") || string_cmp(t->node->data.arr, "(") || string_cmp(t->node->data.arr, ")")){
					destroy_node(t->node);
				}
				free(t);
			}
			t = x;
			x = x->next;
			destroy_node(t->node);
			free(t);
			prev->next = x;
		}

	}
	*root = linked_list_nodes->node;

	free(linked_list_nodes);
	return SUCCESS;
}

error_msg create_node(Node **node, String *s) {
	Node *tmp_node;
	tmp_node = (Node *)calloc(1, sizeof(Node));
	if (!tmp_node) {
		return MEMORY_ALLOCATED_ERROR;
	}
	tmp_node->capacity_children = DEFAULT_COUNT_CHILD;
	tmp_node->children = (Node **)calloc(tmp_node->capacity_children, sizeof(Node));
	if (!tmp_node->children) {
		free(tmp_node);
		return MEMORY_ALLOCATED_ERROR;
	}
	error_msg errorMsg = mstrcopynew(s, &(tmp_node->data));
	if (errorMsg) {
		free(tmp_node->children);
		free(tmp_node);
		return errorMsg;
	}
	*node = tmp_node;
	return SUCCESS;
}

void destroy_node(Node *node) {
	node->capacity_children = 0;
	node->count_children = 0;
	destroy_string(&(node->data));
	free(node->children);
	free(node);
}

error_msg add_node(Node *father, Node *child) {
	if (father->capacity_children == father->count_children) {
		Node **tmp = (Node **)realloc(father->children, father->capacity_children * 2 * sizeof(Node *));
		if (!tmp) {
			return MEMORY_ALLOCATED_ERROR;
		}
		father->children = tmp;
		father->capacity_children *= 2;
	}
	father->children[father->count_children++] = child;
	return SUCCESS;
}

void destroy_tree(Node *head) {
	for (int i = 0; i < head->count_children; ++i) {
		destroy_tree(head->children[i]);
	}
	destroy_node(head);
}

void print_tree(FILE *output, Node *root, int level) {
	for (int i = 0; i < level; i++) {
		fprintf(output, "\t");
	}
	print_string(output, &root->data, "");
	fprintf(output, "\n");

	for (int i = 0; i < root->count_children; i++) {
		print_tree(output, root->children[i], level + 1);
	}
}

error_msg create_node_ll(NodeLL **nodeLl, Node *node) {
	*nodeLl = (NodeLL *)calloc(1, sizeof(NodeLL));
	if (!*nodeLl) {
		return MEMORY_ALLOCATED_ERROR;
	}
	(*nodeLl)->node = node;
	(*nodeLl)->next = NULL;
	return SUCCESS;
}

void add_node_ll(NodeLL *prev, NodeLL *nodeLl) {
	nodeLl->next = prev->next;
	prev->next = nodeLl;
}

void delete_node_ll(NodeLL *prev, NodeLL *cur) {
	prev->next = cur->next;
	free(cur);
}

error_msg push_into_ll(NodeLL **head, Node *x) {
	if (*head) {
		NodeLL *tmp = *head;
		while (tmp->next) {
			tmp = tmp->next;
		}
		NodeLL *real;
		error_msg errorMsg = create_node_ll(&real, x);
		if (errorMsg) {
			return errorMsg;
		}
		add_node_ll(tmp, real);
	} else {
		NodeLL *real;
		error_msg errorMsg = create_node_ll(&real, x);
		if (errorMsg) {
			return errorMsg;
		}
		*head = real;
	}
	return SUCCESS;
}

void print_ll(FILE * stream, NodeLL * head){
	while(head){
		print_string(stream, &(head->node->data), "");
		head = head->next;
		putc(' ', stream);
	}
}

NodeLL *  find_prev_node(NodeLL * head, NodeLL * cur){
	while (head->next){
		if(head->next == cur){
			return head;
		}
		head = head->next;
	}
	return NULL;
}