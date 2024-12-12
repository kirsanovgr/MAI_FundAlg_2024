#include "leftist-heap.h"

error_msg create_leftist_node(LeftistNode** node, Application* application) {
	if (node == NULL || application == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_leftist_node", "get pointer to null"};
	}
	LeftistNode* tmp = (LeftistNode*)calloc(1, sizeof(LeftistNode));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_leftist_node", "memory allocated in object"};
	}
	tmp->application = application;
	*node = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_leftist_node_new(LeftistNode* src, LeftistNode** dst) {
	if (src == NULL || dst == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_leftist_node_new", "get pointer to null"};
	}
	Application* r;
	error_msg errorMsg = copy_application_new(src->application, &r);
	if (errorMsg.type) {
		return errorMsg;
	}

	errorMsg = create_leftist_node(dst, r);
	if (errorMsg.type) {
		destroy_application(r);
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

void destroy_leftist_node(LeftistNode* node) {
	destroy_application(node->application);
	node->left = NULL;
	node->right = NULL;
	free(node);
}

error_msg create_leftist_heap(LeftistHeap** heap) {
	if (heap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_leftist_heap", "get pointer to null"};
	}
	*heap = (LeftistHeap*)calloc(1, sizeof(LeftistHeap));
	if (!*heap) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_leftist_heap", "memory allocated in object"};
	}
	return (error_msg){SUCCESS, "", ""};
}

void destroy_leftist_heap_r(LeftistNode * node){
	if(node == NULL){
		return;
	}
	destroy_leftist_heap_r(node->left);
	destroy_leftist_heap_r(node->right);
	destroy_leftist_node(node);
}

error_msg destroy_leftist_heap(LeftistHeap * heap){
	if(heap == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_leftist_heap", "get pointer to null"};
	}
	destroy_leftist_heap_r(heap->head);
	heap->head = NULL;
	heap->size = 0;
	free(heap);
	return (error_msg){SUCCESS, "", ""};
}


error_msg copy_leftist_heap_r(LeftistNode * src, LeftistNode ** dst){
	if(src == NULL || dst == NULL){
		return (error_msg){SUCCESS, "", ""};
	}
	error_msg errorMsg = copy_leftist_node_new(src, dst);
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = copy_leftist_heap_r(src->left, &((*dst)->left));
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = copy_leftist_heap_r(src->right, &((*dst)->right));
	if(errorMsg.type){
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_leftist_heap(LeftistHeap * src, LeftistHeap ** dst){
	if(src == NULL || dst == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_leftist_heap", "get pointer null"};
	}
	LeftistHeap * tmp;
	error_msg errorMsg = create_leftist_heap(&tmp);
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = copy_leftist_heap_r(src->head, &(tmp->head));
	if(errorMsg.type){
		destroy_leftist_heap(tmp);
		return errorMsg;
	}

	tmp->size = src->size;
	*dst = tmp;
	return (error_msg){SUCCESS, "", ""};
}

void swap_leftist_node(LeftistNode ** x, LeftistNode ** y){
	LeftistNode * t = *x;
	*x = *y;
	*y = t;
}

LeftistNode * merge_leftist_heap_with_destroy_r(LeftistNode * x, LeftistNode *y){
	if(x == NULL){
		return y;
	}

	if(y == NULL){
		return x;
	}

	if (x->application->key < y->application->key ||
	    (x->application->key == y->application->key &&
	     compare_time(&(x->application->time_create), &(y->application->time_create)) == 1)) {
		swap_leftist_node(&x, &y);
	}

	x->right = merge_leftist_heap_with_destroy_r(x->right, y);
	if(x->right && x->left){
		if(x->right->dist > x->left->dist){
			swap_leftist_node(&(x->left), &(x->right));
		}
	} else if(x->right && !x->left){
		swap_leftist_node(&(x->left), &(x->right));
	}

	if(x->right){
		x->dist = x->right->dist + 1;
	} else {
		x->dist = 0;
	}
	return x;
}


error_msg merge_leftist_heap_with_destroy(LeftistHeap * first, LeftistHeap * second, LeftistHeap ** result){
	if(first == NULL || second == NULL || result == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_leftist_heap_with_destroy", "get pointer to null"};
	}
	LeftistHeap * tmp;
	error_msg errorMsg = create_leftist_heap(&tmp);
	if(errorMsg.type){
		return errorMsg;
	}
	tmp->head = merge_leftist_heap_with_destroy_r(first->head, second->head);
	tmp->size = first->size + second->size;
	*result = tmp;
	free(first);
	free(second);
	return (error_msg){SUCCESS, "", ""};
}


error_msg merge_leftist_heap_without_destroy(LeftistHeap * first, LeftistHeap * second, LeftistHeap ** result){
	if(first == NULL || second == NULL || result == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_leftist_heap_without_destroy", "get pointer to null"};
	}
	LeftistHeap * tmp1;
	LeftistHeap * tmp2;
	error_msg errorMsg = copy_leftist_heap(first, &tmp1);
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = copy_leftist_heap(second, &tmp2);
	if(errorMsg.type){
		destroy_leftist_heap(tmp1);
		return errorMsg;
	}
	errorMsg = merge_leftist_heap_with_destroy(tmp1, tmp2, result);
	if(errorMsg.type){
		destroy_leftist_heap(tmp1);
		destroy_leftist_heap(tmp2);
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}


error_msg insert_leftist_heap(LeftistHeap * heap, Application * application){
	if(heap == NULL || application == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "insert_leftist_heap", "get pointer to null"};
	}
	LeftistHeap * tmp;
	error_msg errorMsg = create_leftist_heap(&tmp);
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = create_leftist_node(&(tmp->head), application);
	if(errorMsg.type){
		destroy_leftist_heap(tmp);
		return errorMsg;
	}
	tmp->size = 1;
	size_t t_size = tmp->size + heap->size;

	LeftistHeap * result;
	errorMsg = merge_leftist_heap_without_destroy(heap, tmp, &result);
	if(errorMsg.type){
		destroy_leftist_heap(tmp);
		return errorMsg;
	}
	destroy_leftist_heap_r(heap->head);
	heap->head = result->head;
	heap->size = t_size;
	free(result);
	destroy_leftist_heap(tmp);
	return (error_msg){SUCCESS, "", ""};
}


Application * find_max_priority_elem_leftist_heap(const LeftistHeap* leftistHeap){
	if(leftistHeap == NULL || leftistHeap->head == NULL){
		return NULL;
	}
	return leftistHeap->head->application;
}



error_msg delete_leftist_heap(LeftistHeap * heap, Application ** result){
	if(heap == NULL || result == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_leftist_heap", "get pointer to null"};
	}
	if(heap->head == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_leftist_heap", "try delete from empty head"};
	}
	LeftistHeap * tmp1;
	error_msg errorMsg = create_leftist_heap(&tmp1);
	if(errorMsg.type){
		return errorMsg;
	}

	tmp1->head = heap->head->left;

	LeftistHeap * tmp2;
	errorMsg = create_leftist_heap(&tmp2);
	if(errorMsg.type){
		return errorMsg;
	}

	tmp2->head = heap->head->right;
	size_t t_size = heap->size - 1;
	LeftistHeap * res;
	*result = heap->head->application;
	free(heap->head);

	errorMsg = merge_leftist_heap_with_destroy(tmp1, tmp2, &res);
	if(errorMsg.type){
		destroy_leftist_heap(tmp1);
		destroy_leftist_heap(tmp2);
		return errorMsg;
	}

	heap->head = res->head;
	heap->size = t_size;
	free(res);
	return (error_msg){SUCCESS, "", ""};
}

int is_empty_leftist_heap(const LeftistHeap* heap) { return heap->size == 0; }
size_t get_size_leftist_heap(const LeftistHeap* heap) { return heap->size; }