
#include "bin-tree.h"

error_msg create_bin_tree_node(BinTreeNode** node, size_t id_department, size_t count_operators, char what_queue) {
	if (node == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_bin_tree_node", "get pointer to null"};
	}
	BinTreeNode* tmp = (BinTreeNode*)calloc(1, sizeof(BinTreeNode));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_bin_tree_node", "memory allocated in object"};
	}
	error_msg errorMsg = create_departament(&(tmp->departament), count_operators, id_department, what_queue);
	if (errorMsg.type) {
		free(tmp);
		return errorMsg;
	}
	*node = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg destroy_bin_tree_node(BinTreeNode* node) {
	if (node == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_bin_tree_node", "get pointer to null"};
	}
	destroy_departament(node->departament);
	node->right = NULL;
	node->left = NULL;
	free(node);
	return (error_msg){SUCCESS, "", ""};
}

void destroy_bin_tree_r(BinTreeNode* node) {
	if (node == NULL) {
		return;
	}
	destroy_bin_tree_r(node->left);
	destroy_bin_tree_r(node->right);
	destroy_bin_tree_node(node);
}

error_msg destroy_bin_tree(BinTree* tree) {
	if (tree == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_bin_tree", "get pointer to null"};
	}
	destroy_bin_tree_r(tree->head);
	tree->head = NULL;
	tree->size = 0;
	return (error_msg){SUCCESS, "", ""};
}

error_msg create_bin_tree(BinTree* tree) {
	if (tree == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_bin_tree", "get pointer to null"};
	}
	tree->size = 0;
	tree->head = NULL;
	return (error_msg){SUCCESS, "", ""};
}

error_msg push_into_bin_tree(BinTree* tree, size_t id_department, size_t count_operators, char what_queue) {
	if (tree == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "push_into_bin_tree", "get pointer to null"};
	}
	error_msg errorMsg;
	if (tree->head == NULL) {
		errorMsg = create_bin_tree_node(&(tree->head), id_department, count_operators, what_queue);
		if (errorMsg.type) {
			return errorMsg;
		}
		tree->size += 1;
		return (error_msg){SUCCESS, "", ""};
	}
	BinTreeNode* moving = tree->head;
	BinTreeNode* prev;
	while (moving) {
		prev = moving;
		if (moving->departament->id > id_department) {
			moving = moving->left;
		} else {
			moving = moving->right;
		}
	}
	errorMsg = create_bin_tree_node(&moving, id_department, count_operators, what_queue);
	if (errorMsg.type) {
		return errorMsg;
	}
	if (id_department >= prev->departament->id) {
		prev->right = moving;
	} else {
		prev->left = moving;
	}
	tree->size += 1;
	return (error_msg){SUCCESS, "", ""};
}

error_msg get_bin_tree(BinTree* tree, size_t id, Departament** dep) {
	if (tree == NULL || dep == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "get_into_bin_tree", "get pointer to null"};
	}
	BinTreeNode* current = tree->head;
	while (current && current->departament->id != id) {
		if (current->departament->id > id) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	if (current == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "get_into_bin_tree", "this idea doesn't exist"};
	}
	*dep = current->departament;
	return (error_msg){SUCCESS, "", ""};
}