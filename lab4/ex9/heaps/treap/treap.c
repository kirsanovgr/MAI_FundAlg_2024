#include "treap.h"

error_msg create_treap_node(TreapNode **node, Application *application) {
	if (node == NULL || application == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_treap_node", "get pointer tu null"};
	}
	TreapNode *tmp = (TreapNode *)calloc(1, sizeof(TreapNode));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_treap_node", "memory allocated in object"};
	}
	tmp->application = application;
	tmp->priority = rand();
	*node = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_treap_node_new(TreapNode *src, TreapNode **dst) {
	if (src == NULL || dst == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_treap_node_new", "get pointer to null"};
	}
	Application *f;
	error_msg errorMsg = copy_application_new(src->application, &f);
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = create_treap_node(dst, f);
	if (errorMsg.type) {
		destroy_application(f);
		return errorMsg;
	}
	(*dst)->priority = src->priority;
	return (error_msg){SUCCESS, "", ""};
}

void destroy_treap_node(TreapNode *node) {
	destroy_application(node->application);
	node->left = NULL;
	node->right = NULL;
	node->priority = 0;
	free(node);
}

error_msg copy_treap_r(TreapNode *src, TreapNode **dst) {
	if (src == NULL || dst == NULL) {
		return (error_msg){SUCCESS, "", ""};
	}
	error_msg errorMsg = copy_treap_node_new(src, dst);
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = copy_treap_r(src->left, &((*dst)->left));
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = copy_treap_r(src->right, &((*dst)->right));
	if (errorMsg.type) {
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_treap(Treap *src, Treap **dst) {
	if (src == NULL || dst == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_treap", "get pointer null"};
	}
	Treap *tmp;
	error_msg errorMsg = create_treap(&tmp);
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = copy_treap_r(src->head, &(tmp->head));
	if (errorMsg.type) {
		destroy_treap(tmp);
		return errorMsg;
	}

	tmp->size = src->size;
	*dst = tmp;
	return (error_msg){SUCCESS, "", ""};
}

// Время работы O(h) h - высота дерева
PairNode split(TreapNode *node, size_t key) {
	if (node == NULL) {
		return (PairNode){NULL, NULL};
	}
	if (node->application->key <= key) {
		PairNode p = split(node->right, key);
		node->right = p.first;
		return (PairNode){node, p.second};
	} else {
		PairNode p = split(node->left, key);
		node->left = p.second;
		return (PairNode){p.first, node};
	}
}

TreapNode *merge_treap_r(TreapNode *first, TreapNode *second) {
	if (first == NULL) {
		return second;
	}
	if (second == NULL) {
		return first;
	}
	if (first->priority > second->priority) {
		first->right = merge_treap_r(first->right, second);
		return first;
	} else {
		second->left = merge_treap_r(first, second->left);
		return second;
	}
}

error_msg merge_treap_with_destroy(Treap *first, Treap *second, Treap **result) {
	// Внимание все ключи в первом дереве должны быть меньше чем во втором
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_treap_with_destroy", "get pointer to null"};
	}

	Treap *tmp;
	error_msg errorMsg = create_treap(&tmp);
	if (errorMsg.type) {
		return errorMsg;
	}
	tmp->head = merge_treap_r(first->head, second->head);
	tmp->size = first->size + second->size;
	*result = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg merge_treap_without_destroy(Treap *first, Treap *second, Treap **result) {
	// Внимание все ключи в первом дереве должны быть меньше чем во втором
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_treap_without_destroy", "get pointer to null"};
	}

	Treap *tmp1, *tmp2;
	error_msg errorMsg = copy_treap(first, &tmp1);
	if (errorMsg.type) {
		return errorMsg;
	}

	errorMsg = copy_treap(second, &tmp2);
	if (errorMsg.type) {
		destroy_treap(tmp1);
		return errorMsg;
	}

	errorMsg = merge_treap_with_destroy(tmp1, tmp2, result);
	if (errorMsg.type) {
		destroy_treap(tmp1);
		destroy_treap(tmp2);
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg create_treap(Treap **treap) {
	if (treap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_treap", "get pointer to null"};
	}
	*treap = (Treap *)calloc(1, sizeof(Treap));
	if (!*treap) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_treap", "memory allocated in object"};
	}
	return (error_msg){SUCCESS, "", ""};
}

void destroy_treap_rek(TreapNode *node) {
	if (node == NULL) {
		return;
	}
    destroy_treap_rek(node->left);
    destroy_treap_rek(node->right);
	destroy_treap_node(node);
}

error_msg destroy_treap(Treap *treap) {
	if (treap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_treap", "get pointer to null"};
	}
    destroy_treap_rek(treap->head);
	treap->size = 0;
	free(treap);
	return (error_msg){SUCCESS, "", ""};
}

error_msg insert_treap(Treap *treap, Application *application) {
	if (treap == NULL || application == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "insert_treap", "get pointer to null"};
	}
	size_t t_size = treap->size;
	PairNode p1 = split(treap->head, application->key);
	TreapNode *node;
	error_msg errorMsg = create_treap_node(&node, application);
	if (errorMsg.type) {
		return errorMsg;
	}
	treap->head = merge_treap_r(merge_treap_r(p1.first, node), p1.second);
	treap->size = t_size + 1;

	return (error_msg){SUCCESS, "", ""};
}

Application *find_max_priority_elem_treap(const Treap *treap) {
	if (treap == NULL || treap->head == NULL) {
		return NULL;
	}
	TreapNode *cur = treap->head;
	while (cur->right) {
		cur = cur->right;
	}
	return cur->application;
}

error_msg delete_treap(Treap *treap, Application **result) {
	if (treap == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_treap", "get pointer to null"};
	}
	if (treap->size == 0) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_treap", "try delete from empty heap"};
	}
	TreapNode *cur = treap->head;
	while (cur->right) {
		cur = cur->right;
	}
	PairNode p = split(treap->head, cur->application->key - 1);
	PairNode p2 = split(p.second, cur->application->key);
	treap->head = merge_treap_r(p.first, p2.second);
	*result = cur->application;
	free(cur);
	treap->size -= 1;
	return (error_msg){SUCCESS, "", ""};
}

int is_empty_treap(const Treap *treap) { return treap->size == 0; }
size_t get_size_treap(const Treap *treap) { return treap->size; }