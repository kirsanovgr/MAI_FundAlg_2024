#include "fibonacci-heap.h"

error_msg create_fibonacci_node(FibonacciNode** fibonacciNode, Application* application) {
	if (fibonacciNode == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_fibonacci_node", "get pointer to null"};
	}
	FibonacciNode* tmp = (FibonacciNode*)calloc(1, sizeof(FibonacciNode));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_fibonacci_node", "memory allocated in object"};
	}
	tmp->application = application;
	*fibonacciNode = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_fibonacci_node_new(FibonacciNode* src, FibonacciNode** dst) {
	if (src == NULL || dst == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, " copy_fibonacci_node_new", "get pointer to null"};
	}
	Application* tmp;
	error_msg errorMsg = copy_application_new(src->application, &tmp);
	if (errorMsg.type) {
		return errorMsg;
	}

	errorMsg = create_fibonacci_node(dst, tmp);
	if (errorMsg.type) {
		destroy_application(tmp);
		return errorMsg;
	}
	(*dst)->marked = src->marked;
	return (error_msg){SUCCESS, "", ""};
}

void destroy_fibonacci_node(FibonacciNode* fibonacciNode) {
	destroy_application(fibonacciNode->application);
	fibonacciNode->child = NULL;
	fibonacciNode->left = NULL;
	fibonacciNode->parent = NULL;
	fibonacciNode->right = NULL;
	free(fibonacciNode);
}

error_msg create_fibonacci_heap(FibonacciHeap** fibonacciHeap) {
	if (fibonacciHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_fibonacci_heap", "get pointer to null"};
	}
	FibonacciHeap* tmp = (FibonacciHeap*)calloc(1, sizeof(FibonacciHeap));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_fibonacci_heap", "memory allocated in object"};
	}
	*fibonacciHeap = tmp;
	return (error_msg){SUCCESS, "", ""};
}


error_msg insert_fibonacci_heap(FibonacciHeap* fibonacciHeap, Application* application) {
	FibonacciNode* new;
	error_msg errorMsg = create_fibonacci_node(&new, application);
	if (errorMsg.type) {
		return errorMsg;
	}
	if (fibonacciHeap->size == 0) {
		fibonacciHeap->size = 1;
		fibonacciHeap->head = new;
		new->right = new;
		new->left = new;
		return (error_msg){SUCCESS, "", ""};
	}
	FibonacciNode* prev_right = fibonacciHeap->head->right;
	fibonacciHeap->head->right = new;
	new->left = fibonacciHeap->head;
	new->right = prev_right;
	prev_right->left = new;

	if (new->application->key > fibonacciHeap->head->application->key ||
	    (new->application->key ==
	     fibonacciHeap->head->application->key&& compare_time(
	         &(new->application->time_create), &(fibonacciHeap->head->application->time_create)) == -1)) {
		fibonacciHeap->head = new;
	}
	fibonacciHeap->size += 1;
	return (error_msg){SUCCESS, "", ""};
}

Application* find_max_priority_element_fibonacci_heap(const FibonacciHeap* fibonacciHeap) {
	if (fibonacciHeap == NULL) {
		return NULL;
	}
	return fibonacciHeap->head->application;
}



error_msg copy_sub_heap(FibonacciNode* node, FibonacciNode** new) {
	if (node == NULL) {
		return (error_msg){SUCCESS, "", ""};
	}

	// Копирование текущего узла
	error_msg errorMsg = copy_fibonacci_node_new(node, new);
	if (errorMsg.type) {
		return errorMsg;
	}

	// Копирование детей
	FibonacciNode* child = node->child;
	FibonacciNode* new_child = NULL;
	FibonacciNode* prev_new_child = NULL;

	if (child != NULL) {
		do {
			FibonacciNode* new_child_node;
			errorMsg = copy_sub_heap(child, &new_child_node);
			if (errorMsg.type) {
				destroy_fibonacci_node(*new);
				return errorMsg;
			}
			new_child_node->parent = *new;

			if (new_child == NULL) {
				new_child = new_child_node;
				(*new)->child = new_child;
			} else {
				prev_new_child->right = new_child_node;
				new_child_node->left = prev_new_child;
			}

			prev_new_child = new_child_node;
			child = child->right;
		} while (child != node->child);

		// Замыкаем список детей
		prev_new_child->right = new_child;
		new_child->left = prev_new_child;
	}

	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_fibonacci_heap_new(FibonacciHeap* src, FibonacciHeap** dst) {
	if(src == NULL || dst == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_fibonacci_heap", "get pointer to null"};
	}

	FibonacciHeap * tmp;
	error_msg errorMsg = create_fibonacci_heap(&tmp);
	if(errorMsg.type){
		return errorMsg;
	}

	if (src->size == 0) {
		*dst = tmp;
		return (error_msg){SUCCESS, "", ""};
	}
	tmp->head = NULL;
	FibonacciNode * cur_src = src->head;
	FibonacciNode* prev_new = NULL;
	FibonacciNode* new_max = NULL;
	FibonacciNode* new;
	do {
		errorMsg = copy_sub_heap(cur_src, &new);
		if(errorMsg.type){
			destroy_fibonacci_heap(tmp);
			return errorMsg;
		}
		if (new_max == NULL) {
			new_max = new;
			new_max->right = new_max;
			new_max->left = new_max;
		} else {
			new->left = prev_new;
			new->right = prev_new->right;
			prev_new->right->left = new;
			prev_new->right->left = new;
			prev_new->right = new;
		}
		if (new_max->application->key < new->application->key) {
			new_max = new;
		}
		prev_new = new;
		cur_src = cur_src->right;

	} while (cur_src != src->head);
	tmp->head = new_max;
	tmp->size = src->size;
	*dst = tmp;
	return (error_msg){SUCCESS, "", ""};
}

void destroy_subheap(FibonacciNode* node) {
	if (node == NULL) return;

	FibonacciNode* current = node;
	do {
		FibonacciNode* next = current->right;
		destroy_subheap(current->child);
		destroy_fibonacci_node(current);
		current = next;
	} while (current != node);

}

// Уничтожение фибоначчиевой кучи
error_msg destroy_fibonacci_heap(FibonacciHeap* heap) {
	if (heap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_fibonacci_heap", "heap pointer is NULL"};
	}

	// Уничтожаем все узлы в куче
	if (heap->head != NULL) {
		destroy_subheap(heap->head);
	}

	// Обнуляем поля кучи
	heap->head = NULL;
	heap->size = 0;

	free(heap);

	return (error_msg){SUCCESS, "", ""};
}

error_msg merge_fibonacci_heap_with_destroy(FibonacciHeap* first, FibonacciHeap* second, FibonacciHeap** result) {
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_fibonacci_heap_with_destroy", "get pointer to null"};
	}

	if (first == second) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_fibonacci_heap_with_destroy", "merge by itself"};
	}

	FibonacciHeap* tmp;
	error_msg errorMsg = create_fibonacci_heap(&tmp);
	if (errorMsg.type) {
		return errorMsg;
	}

	if (second->size == 0) {
		tmp->size = first->size;
		tmp->head = first->head;
		first->size = 0;
		first->head = NULL;
		*result = tmp;
		free(first);
		free(second);
		return (error_msg){SUCCESS, "", ""};
	}

	if (first->size == 0) {
		tmp->size = second->size;
		tmp->head = second->head;
		second->size = 0;
		second->head = NULL;
		*result = tmp;
		free(first);
		free(second);
		return (error_msg){SUCCESS, "", ""};
	}

	FibonacciNode* left = first->head->left;
	FibonacciNode* right = second->head->right;
	second->head->right = first->head;
	first->head->left = second->head;
	left->right = right;
	right->left = left;

	tmp->size = first->size + second->size;
	tmp->head = first->head;
	if (first->head->application->key < second->head->application->key) {
		tmp->head = second->head;
	}

	*result = tmp;

	// Уничтожаем исходные кучи
	free(first);
	free(second);

	return (error_msg){SUCCESS, "", ""};
}

error_msg merge_fibonacci_heap_without_destroy(FibonacciHeap* first, FibonacciHeap* second, FibonacciHeap** result) {
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_fibonacci_heap_without_destroy", "get pointer to null"};
	}

	FibonacciHeap *tmp1, *tmp2;
	error_msg errorMsg = copy_fibonacci_heap_new(first, &tmp1);
	if (errorMsg.type) {
		return errorMsg;
	}

	errorMsg = copy_fibonacci_heap_new(second, &tmp2);
	if (errorMsg.type) {
		destroy_fibonacci_heap(tmp1);
		return errorMsg;
	}

	errorMsg = merge_fibonacci_heap_with_destroy(tmp1, tmp2, result);
	if (errorMsg.type) {
		destroy_fibonacci_heap(tmp1);
		destroy_fibonacci_heap(tmp2);
		return errorMsg;
	}

	return (error_msg){SUCCESS, "", ""};
}

void union_(FibonacciNode* x, FibonacciNode* y) {
	if (x == NULL) {
		return;
	}
	//	if(x->application->key > y->application->key){
	//		FibonacciNode * t = y;
	//		y = x;
	//		x = t;
	//	}

	y->left->right = y->right;
	y->right->left = y->left;

	y->parent = x;
	if (x->child == NULL) {
		x->child = y;
		y->left = y;
		y->right = y;
	} else {
		y->left = x->child;
		y->right = x->child->right;
		x->child->right->left = y;
		x->child->right = y;
	}
	x->degree++;
	y->marked = 0;
}

void union_lists(FibonacciNode** f, FibonacciNode* second) {
	if (second == NULL || f == NULL) {
		return;
	}

	FibonacciNode* t_L = second->left;
	FibonacciNode* t_R = second->right;
	t_L->right = t_R;
	t_R->left = t_L;
	if (second->parent) {
		second->parent->child = NULL;
	}

	FibonacciNode* first = *f;
	if (first == NULL) {
		first = second;
		first->right = first;
		first->left = first;
		*f = first;
		return;
	}

	FibonacciNode* R = first->right;
	first->right = second;
	second->left = first;
	R->left = second;
	second->right = R;

	if (first->application->key < second->application->key) {
		*f = second;
	} else {
		*f = first;
	}
}

void add_root_list(FibonacciHeap* heap, FibonacciNode* node) {
	if (heap->head == NULL) {
		heap->head = node;
		node->left = node;
		node->right = node;
	} else {
		FibonacciNode* L = heap->head->left;
		FibonacciNode* R = heap->head;
		L->right = node;
		node->left = L;
		node->right = R;
		R->left = node;

		if (node->application->key > heap->head->application->key ||
		    (node->application->key == heap->head->application->key &&
		     compare_time(&(node->application->time_create), &(heap->head->application->time_create)) == -1)) {
			heap->head = node;
		}
	}
}

error_msg consolidate(FibonacciHeap* heap) {
	size_t max_degree = (size_t)(log((double)heap->size) / log(2)) + 1;
	FibonacciNode** A = (FibonacciNode**)calloc(max_degree, sizeof(FibonacciNode*));
	if (!A) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "consolidate", "memory allocated"};
	}

	FibonacciNode* current = heap->head;
	if (current == NULL) {
		free(A);
		return (error_msg){SUCCESS, "", ""};
	}

	FibonacciNode* last = current->left;
	A[current->degree] = current;
	current = current->right;

	while (current != last) {
		FibonacciNode* next = current->right;
		size_t d = current->degree;
		while (A[d] != NULL) {
			FibonacciNode* conflict = A[d];
			if (current->application->key < conflict->application->key) {
				FibonacciNode* temp = current;
				current = conflict;
				conflict = temp;
			}
			union_(current, conflict);
			A[d] = NULL;
			d++;
		}
		A[d] = current;
		current = next;
	}

	heap->head = NULL;
	for (size_t i = 0; i < max_degree; ++i) {
		if (A[i] != NULL) {
			add_root_list(heap, A[i]);
		}
	}
	free(A);
	return (error_msg){SUCCESS, "", ""};
}

error_msg delete_fibonacci_heap(FibonacciHeap* heap, Application** result) {
	if (heap == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_fibonacci_heap", "get pointer to null"};
	}
	if (heap->size == 0) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_fibonacci_heap", "try delete from empty heap"};
	}

	FibonacciNode* prev_max = heap->head;
	if (prev_max->child) {
		FibonacciNode* child = prev_max->child;
		FibonacciNode* last_child = child->left;
		FibonacciNode* R = prev_max->right;

		prev_max->right = child;
		child->left = prev_max;
		last_child->right = R;
		R->left = last_child;
	}

	FibonacciNode* L = prev_max->left;
	FibonacciNode* R = prev_max->right;
	L->right = R;
	R->left = L;

	if (prev_max->right == prev_max) {
		heap->size = 0;
		heap->head = NULL;
	} else {
		heap->head = R;
		error_msg errorMsg = consolidate(heap);
		if (errorMsg.type) {
			*result = prev_max->application;
			free(prev_max);
			return errorMsg;
		}
		heap->size -= 1;
	}

	*result = prev_max->application;
	free(prev_max);
	return (error_msg){SUCCESS, "", ""};
}

int is_empty_fibonacci_heap(const FibonacciHeap* heap) { return heap->size == 0; }

size_t get_size_fibonacci_heap(const FibonacciHeap* heap) { return heap->size; }