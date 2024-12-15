
#include "binary-heap.h"

void swap(Application **ap1, Application **ap2) {
	Application *t = *ap1;
	*ap1 = *ap2;
	*ap2 = t;
}

error_msg create_binary_heap(BinaryHeap **binaryHeap) {
	if (binaryHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_binary_heap", "get pointer to null"};
	}
	BinaryHeap *tmp = NULL;
	tmp = (BinaryHeap *)calloc(1, sizeof(BinaryHeap));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_binary_heap", "Memory allocated: pointer to object"};
	}
	tmp->size = 0;
	tmp->capacity = DEFAULT_CAPACITY_BINARY_HEAP;
	tmp->data = (Application **)calloc(tmp->capacity, sizeof(Application *));
	if (!tmp->data) {
		free(tmp);
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_binary_heap", "Memory allocated: pointer to data"};
	}
	*binaryHeap = tmp;
	return (error_msg){SUCCESS, "", ""};
}

error_msg destroy_binary_heap(BinaryHeap *binaryHeap) {
	if (binaryHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_binary_heap", "get pointer to null"};
	}
	for (size_t i = 0; i < binaryHeap->size; ++i) {
		destroy_application(binaryHeap->data[i]);
	}
	free(binaryHeap->data);
	binaryHeap->data = NULL;
	binaryHeap->size = 0;
	binaryHeap->capacity = 0;
	free(binaryHeap);
	return (error_msg){SUCCESS, "", ""};
}

error_msg resize_binary_heap(BinaryHeap *binaryHeap, size_t new_capacity) {
	if (binaryHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "resize_binary_heap", "get pointer to null"};
	}
	Application **tmp = (Application **)realloc(binaryHeap->data, new_capacity * sizeof(Application *));
	if (!tmp) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, "resize_binary_heap", "memory allocated: realloc"};
	}
	binaryHeap->capacity = new_capacity;
	binaryHeap->data = tmp;
	return (error_msg){SUCCESS, "", ""};
}

size_t get_parent_index(const size_t i) {
	if (i % 2) {
		return (i - 1) / 2;
	}
	return (i - 2) / 2;
}

error_msg sift_down_binary_heap(BinaryHeap *binaryHeap, size_t index) {
	if (binaryHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "sift_down_binary_heap", "get pointer to null"};
	}

	size_t left_child = 2 * index + 1;
	size_t right_child = 2 * index + 2;
	size_t largest = index;

	error_msg errorMsg;

	if (left_child < binaryHeap->size && binaryHeap->data[left_child] > binaryHeap->data[largest]) {
		largest = left_child;
	}
	if (right_child < binaryHeap->size && binaryHeap->data[right_child] > binaryHeap->data[largest]) {
		largest = right_child;
	}

	if (largest != index) {
		swap(&(binaryHeap->data[index]), &(binaryHeap->data[largest]));

		errorMsg = sift_down_binary_heap(binaryHeap, largest);
		if (errorMsg.type) {
			return errorMsg;
		}
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg sift_up_binary_heap(BinaryHeap *binaryHeap) {
	if (binaryHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "sift_up_binary_heap", "get pointer to null"};
	}

	size_t j = get_parent_index(binaryHeap->size - 1);
	size_t i = binaryHeap->size - 1;
	while (i > 0 && (binaryHeap->data[i]->key > binaryHeap->data[j]->key ||
	                 (binaryHeap->data[i]->key == binaryHeap->data[j]->key &&
	                  compare_time(&(binaryHeap->data[i]->time_create), &(binaryHeap->data[j]->time_create)) == -1))) {
		swap(&(binaryHeap->data[i]), &(binaryHeap->data[j]));
		i = j;
		j = get_parent_index(j);
	}

	return (error_msg){SUCCESS, "", ""};
}

error_msg insert_binary_heap(BinaryHeap *binaryHeap, Application *application) {
	if (binaryHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "insert_binary_heap", "get pointer to null"};
	}
	error_msg errorMsg;
	if (binaryHeap->size == binaryHeap->capacity) {
		errorMsg = resize_binary_heap(binaryHeap, binaryHeap->capacity * 2);
		if (errorMsg.type) {
			return errorMsg;
		}
	}

	// Вставляем в корень, если куча пустая
	if (binaryHeap->size == 0) {
		binaryHeap->data[0] = application;
		binaryHeap->size += 1;
		return (error_msg){SUCCESS, "", ""};
	}

	binaryHeap->data[binaryHeap->size] = application;
	binaryHeap->size += 1;
	errorMsg = sift_up_binary_heap(binaryHeap);
	if (errorMsg.type) {
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg delete_binary_heap(BinaryHeap *binaryHeap, Application **result) {
	if (binaryHeap == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "delete_binary_heap", "get pointer to null"};
	}

	if (binaryHeap->size == 0) {
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "delete_binary_heap",
                            "attempt to delete an item from binary head"};
	}
	*result = binaryHeap->data[0];
	binaryHeap->size -= 1;
	binaryHeap->data[0] = binaryHeap->data[binaryHeap->size];

	error_msg errorMsg = sift_down_binary_heap(binaryHeap, 0);
	if (errorMsg.type) {
		return errorMsg;
	}

	return (error_msg){SUCCESS, "", ""};
}

error_msg merge_binary_heaps_without_destroy(const BinaryHeap *first, const BinaryHeap *second, BinaryHeap **res) {
	if (first == NULL || second == NULL || res == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binary_heaps_without_destroy", "get pointer to null"};
	}
	if (first == second) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binary_heaps_without_destroy", "merge by itself"};
	}

	BinaryHeap *result;
	error_msg errorMsg = create_binary_heap(&result);
	if (errorMsg.type) {
		return errorMsg;
	}
	errorMsg = resize_binary_heap(result, first->capacity + second->capacity + 1);
	if (errorMsg.type) {
		destroy_binary_heap(result);
		return errorMsg;
	}

	// Копируем из первой
	for (size_t i = 0; i < first->size; ++i) {
		Application *new;
		errorMsg = copy_application_new(first->data[i], &(new));
		if (errorMsg.type) {
			destroy_binary_heap(result);
			return errorMsg;
		}
		result->data[i] = new;
	}
	result->size = first->size;

	// Из второй
	for (size_t i = 0; i < second->size; ++i) {
		Application *new;
		errorMsg = copy_application_new(second->data[i], &(new));
		if (errorMsg.type) {
			destroy_binary_heap(result);
			return errorMsg;
		}
		errorMsg = insert_binary_heap(result, new);
		if (errorMsg.type) {
			destroy_binary_heap(result);
			return errorMsg;
		}
	}

	*res = result;

	return (error_msg){SUCCESS, "", ""};
}

error_msg merge_binary_heaps_with_destroy(BinaryHeap *first, BinaryHeap *second, BinaryHeap **res) {
	error_msg errorMsg = merge_binary_heaps_without_destroy(first, second, res);
	if (errorMsg.type) {
		destroy_binary_heap(first);
		destroy_binary_heap(second);
		return errorMsg;
	}
	destroy_binary_heap(first);
	destroy_binary_heap(second);
	return (error_msg){SUCCESS, "", ""};
}

Application *find_max_priority_elem_binary_heap(const BinaryHeap *binaryHeap) {
	if(binaryHeap == NULL){
		return NULL;
	}
	return binaryHeap->data[0];
}


void print_binary_queue(const BinaryHeap *binaryHeap) {
	for (size_t i = 0; i < binaryHeap->size; ++i) {
		printf("%zu ", binaryHeap->data[i]->key);
    }
    printf("\n");
}

int binary_queue_is_empty(const BinaryHeap *binaryHeap) { return binaryHeap->size == 0; }

size_t get_size_binary_queue(const BinaryHeap *binaryHeap) { return binaryHeap->size; }