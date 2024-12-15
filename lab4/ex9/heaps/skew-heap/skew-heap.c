#include "skew-heap.h"

error_msg create_skew_node(SkewNode** node, Application* application) {
	if (node == NULL || application == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_skew_node", "get pointer no null"};
	}
	*node = (SkewNode*)calloc(1, sizeof(SkewNode));
	if (!*node) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_skew_node", "memory allocated in object"};
	}
	(*node)->application = application;
	return (error_msg){SUCCESS, "", ""};
}

void destroy_skew_node(SkewNode* skewNode) {
	destroy_application(skewNode->application);
	skewNode->right = NULL;
	skewNode->left = NULL;
	free(skewNode);
}

error_msg copy_skew_node_new(SkewNode* src, SkewNode** dst) {
	if (src == NULL || dst == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_skew_node_new", "get pointer to null"};
	}
	Application* f;
	error_msg errorMsg = copy_application_new(src->application, &f);
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = create_skew_node(dst, f);
	if (errorMsg.type) {
		destroy_application(f);
		return errorMsg;
	}

	return (error_msg){SUCCESS, "", ""};
}

error_msg create_skew_heap(SkewHeap** heap) {
	if (heap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_skew_heap", "get pointer to null"};
	}
	*heap = (SkewHeap*)calloc(1, sizeof(SkewHeap));
	if (!*heap) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_skew_heap", "memory allocated in object"};
	}
	return (error_msg){SUCCESS, "", ""};
}

void destroy_skew_heap_r(SkewNode* node) {
	if (node == NULL) {
		return;
	}
	destroy_skew_heap_r(node->left);
	destroy_skew_heap_r(node->right);
	destroy_skew_node(node);
}

error_msg destroy_skew_heap(SkewHeap* heap) {
	if (heap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_skew_heap", "get pointer to null"};
	}
	destroy_skew_heap_r(heap->head);
	heap->head = NULL;
	heap->size = 0;
	free(heap);
	return (error_msg){SUCCESS, "", ""};
}

SkewNode* merge_with_destroy_heap_r(SkewNode* first, SkewNode* second) {
	if (first == NULL) {
		return second;
	}
	if (second == NULL) {
		return first;
	}

	if (first->application->key < second->application->key ||
	    (first->application->key == second->application->key &&
	     compare_time(&(first->application->time_create), &(second->application->time_create)) == 1)) {
		SkewNode* tmp = first;
		first = second;
		second = tmp;
	}

	SkewNode* tmp = first->left;
	first->left = first->right;
	first->right = tmp;

	first->left = merge_with_destroy_heap_r(second, first->left);
	return first;
}

error_msg copy_skew_heap_r(SkewNode * src, SkewNode ** dst){
	if(src == NULL || dst == NULL){
		return (error_msg){SUCCESS, "", ""};
	}
	error_msg errorMsg = copy_skew_node_new(src, dst);
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = copy_skew_heap_r(src->left, &((*dst)->left));
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = copy_skew_heap_r(src->right, &((*dst)->right));
	if(errorMsg.type){
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_skew_heap(SkewHeap * src, SkewHeap ** dst){
	if(src == NULL || dst == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "copy_skew_heap", "get pointer null"};
	}
	SkewHeap * tmp;
	error_msg errorMsg = create_skew_heap(&tmp);
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = copy_skew_heap_r(src->head, &(tmp->head));
	if(errorMsg.type){
		destroy_skew_heap(tmp);
		return errorMsg;
	}

	tmp->size = src->size;
	*dst = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg merge_skew_heap_with_destroy(SkewHeap* first, SkewHeap* second, SkewHeap** result) {
	if (first == NULL || second == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_skew_heap_with_destroy", "get pointer to null"};
	}

	SkewHeap* tmp;
	error_msg errorMsg = create_skew_heap(&tmp);
	if (errorMsg.type) {
		return errorMsg;
	}

	tmp->size = first->size + second->size;
	tmp->head = merge_with_destroy_heap_r(first->head, second->head);

	first->head = NULL;
	second->head = NULL;
	free(first);
	free(second);
	*result = tmp;
	return (error_msg){SUCCESS, "", ""};
}


error_msg merge_skew_heap_without_destroy(SkewHeap* first, SkewHeap* second, SkewHeap** result){
	SkewHeap * tmp1;
	SkewHeap * tmp2;
	error_msg errorMsg = copy_skew_heap(first, &tmp1);
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = copy_skew_heap(second, &tmp2);
	if(errorMsg.type){
		destroy_skew_heap(tmp1);
		return errorMsg;
	}
	errorMsg = merge_skew_heap_with_destroy(tmp1, tmp2, result);
	if(errorMsg.type){
		destroy_skew_heap(tmp1);
		destroy_skew_heap(tmp2);
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg insert_skew_heap(SkewHeap * heap, Application* application){
	if(heap == NULL || application == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "insert_skew_heap", "get pointer to null"};
	}
	SkewHeap * tmp;
	error_msg errorMsg = create_skew_heap(&tmp);
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = create_skew_node(&(tmp->head), application);
	if(errorMsg.type){
		free(tmp);
		return errorMsg;
	}
	tmp->size += 1;

	SkewHeap * res;
	errorMsg = merge_skew_heap_without_destroy(heap, tmp, &res);
	if(errorMsg.type){
		destroy_skew_node(tmp->head);
		free(tmp);
		return errorMsg;
	}
	destroy_skew_heap_r(heap->head);
	destroy_skew_heap(tmp);
	heap->head = res->head;
	heap->size = res->size;
	free(res);
	return (error_msg){SUCCESS, "", ""};
}




Application * find_max_priority_element_skew_heap(const SkewHeap * skewHeap){
	if(skewHeap == NULL || skewHeap->head == NULL){
		return NULL;
	}
	return skewHeap->head->application;
}


error_msg delete_skew_heap(SkewHeap * heap, Application ** result){
	if(heap == NULL || result == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_skew_heap", "get pointer to null"};
	}

	*result = heap->head->application;
	SkewHeap * tmp1;
	SkewHeap * tmp2;

	error_msg errorMsg = create_skew_heap(&tmp1);
	if(errorMsg.type){
		return errorMsg;
	}
	errorMsg = create_skew_heap(&tmp2);
	if(errorMsg.type){
		destroy_skew_heap(tmp1);
		return errorMsg;
	}
	tmp1->head = heap->head->left;
	tmp2->head = heap->head->right;

	SkewHeap * tmp3;

	size_t t_size = heap->size - 1;

	errorMsg = merge_skew_heap_without_destroy(tmp1, tmp2, &tmp3);
	if(errorMsg.type){
		destroy_skew_heap(tmp1);
		destroy_skew_heap(tmp2);
		return errorMsg;
	}

	destroy_skew_heap(tmp1);
	destroy_skew_heap(tmp2);
	free(heap->head);
	heap->head = tmp3->head;
	heap->size = t_size;
	free(tmp3);

	return (error_msg){SUCCESS, "", ""};
}

int is_empty_skew_heap(const SkewHeap* heap) { return heap->size == 0; }
size_t get_size_skew_heap(const SkewHeap* heap) { return heap->size; }
