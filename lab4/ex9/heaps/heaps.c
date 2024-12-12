#include "heaps.h"

V_table_queue heaps_functions[] = {
    {
        create_binary,
        insert_binary,
        delete_binary,
        merge_binary_with_destroy,
        merge_binary_without_destroy,
        destroy_binary,
        find_max_priority_elem_binary,
        is_empty_binary,
        get_size_bin
    },
    {
        create_binomial,
        insert_binomial,
        delete_binomial,
        merge_binomial_with_destroy,
        merge_binomial_without_destroy,
        destroy_binomial,
        find_max_priority_elem_binomial,
        is_empty_binomial,
        get_size_binomial
    },
    {
        create_fibonacci,
        insert_fibonacci,
        delete_fibonacci,
        merge_fibonacci_with_destroy,
        merge_fibonacci_without_destroy,
        destroy_fibonacci,
        find_max_priority_elem_fibonacci,
        is_empty_fibonacci,
        get_size_fibonacci
    },
    {
        create_skew,
        insert_skew,
        delete_skew,
        merge_skew_with_destroy,
        merge_skew_without_destroy,
        destroy_skew,
        find_max_priority_elem_skew,
        is_empty_skew,
        get_size_skew
    },
    {
        create_leftist,
        insert_leftist,
        delete_leftist,
        merge_leftist_with_destroy,
        merge_leftist_without_destroy,
        destroy_leftist,
        find_max_priority_elem_leftist,
        is_empty_leftist,
        get_size_leftist
    },
    {
        create_treap_r,
        insert_treap_r,
        delete_treap_r,
        merge_treap_with_destroy_r,
        merge_treap_without_destroy_r,
        destroy_treap_r,
        find_max_priority_elem_treap_r,
        is_empty_tr,
        get_size_tr
    }
};

error_msg create_binary(Q_queue **queue) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "create_binary", "get pointer to null"};
    }
    BinaryHeap *binaryHeap = &((*queue)->bin_h);
    error_msg errorMsg = create_binary_heap(&binaryHeap);
    *queue = (Q_queue *)binaryHeap;
    return errorMsg;
}

int is_empty_binary(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return binary_queue_is_empty(&(queue->bin_h));
}

int is_empty_binomial(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return is_empty_binomial_heap(&(queue->binomial_h));
}

int is_empty_fibonacci(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return is_empty_fibonacci_heap(&(queue->fibonacci_h));
}

int is_empty_leftist(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return is_empty_leftist_heap(&(queue->leftist_h));
}

int is_empty_skew(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return is_empty_skew_heap(&(queue->skew_h));
}

int is_empty_tr(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return is_empty_treap(&(queue->treap));
}

size_t get_size_bin(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return get_size_binary_queue(&(queue->bin_h));
}

size_t get_size_binomial(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return get_size_binomial_heap(&(queue->binomial_h));
}

size_t get_size_fibonacci(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return get_size_fibonacci_heap(&(queue->fibonacci_h));
}

size_t get_size_leftist(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return get_size_leftist_heap(&(queue->leftist_h));
}

size_t get_size_skew(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return get_size_skew_heap(&(queue->skew_h));
}

size_t get_size_tr(Q_queue *queue) {
	if (queue == NULL) {
		return -1;
	}
	return get_size_treap(&(queue->treap));
}


error_msg insert_binary(Q_queue *queue, Application *application) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "insert_binary", "get pointer to null"};
    }
    return insert_binary_heap(&(queue->bin_h), application);
}

error_msg destroy_binary(Q_queue *queue) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_binary", "get pointer to null"};
    }
    return destroy_binary_heap(&(queue->bin_h));
}

error_msg delete_binary(Q_queue *queue, Application **result) {
    if (queue == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "delete_binary", "get pointer to null"};
    }
    return delete_binary_heap(&(queue->bin_h), result);
}

error_msg merge_binary_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binary_without_destroy", "get pointer to null"};
    }

    BinaryHeap *res = &((*result)->bin_h);
    error_msg errorMsg = merge_binary_heaps_without_destroy(&(first->bin_h), &(second->bin_h), &res);
    *result = (Q_queue *)res;
    return errorMsg;
}

error_msg merge_binary_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binary_with_destroy", "get pointer to null"};
    }
    BinaryHeap *res = &((*result)->bin_h);
    error_msg errorMsg = merge_binary_heaps_with_destroy(&(first->bin_h), &(second->bin_h), &res);
    *result = (Q_queue *)res;
    return errorMsg;
}

Application *find_max_priority_elem_binary(const Q_queue *queue) {
    if (queue == NULL) {
        return NULL;
    }
    return find_max_priority_elem_binary_heap(&(queue->bin_h));
}

error_msg create_binomial(Q_queue **queue) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "create_binomial", "get pointer to null"};
    }
    BinomialHeap *binomialHeap = &((*queue)->binomial_h);
    error_msg errorMsg = create_binomial_heap(&binomialHeap);
    *queue = (Q_queue *)binomialHeap;
    return errorMsg;
}

error_msg insert_binomial(Q_queue *queue, Application *application) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "insert_binomial", "get pointer to null"};
    }
    return insert_binomial_heap(&(queue->binomial_h), application);
}

error_msg delete_binomial(Q_queue *queue, Application **result) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "delete_binomial", "get pointer to null"};
    }
    return delete_binomial_heap(&(queue->binomial_h), result);
}

error_msg merge_binomial_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binomial_with_destroy", "get pointer to null"};
    }
    BinomialHeap *res = &((*result)->binomial_h);
    error_msg errorMsg = merge_binomial_heap_with_destroy(&(first->binomial_h), &(second->binomial_h), &res);
    *result = (Q_queue *)res;
    return errorMsg;
}
error_msg merge_binomial_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "merge_binomial_without_destroy", "get pointer to null"};
    }
    BinomialHeap *res = &((*result)->binomial_h);
    error_msg errorMsg = merge_binomial_heap_without_destroy(&(first->binomial_h), &(second->binomial_h), &res);
    *result = (Q_queue *)res;
    return errorMsg;
}

Application *find_max_priority_elem_binomial(const Q_queue *queue) {
    if (queue == NULL) {
        return NULL;
    }
    return find_max_priority_elem_binomial_heap(&(queue->binomial_h));
}

error_msg destroy_binomial(Q_queue *queue) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_binomial", "get pointer to null"};
    }
    return destroy_binomial_heap(&(queue->binomial_h));
}

error_msg create_fibonacci(Q_queue **queue) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "create_fibonacci", "get pointer to null"};
    }

    FibonacciHeap *fibonacciHeap = &((*queue)->fibonacci_h);
    error_msg errorMsg = create_fibonacci_heap(&fibonacciHeap);
    *queue = (Q_queue *)fibonacciHeap;
    return errorMsg;
}

error_msg insert_fibonacci(Q_queue *queue, Application *application) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "insert_fibonacci", "get pointer to null"};
    }
    return insert_fibonacci_heap(&(queue->fibonacci_h), application);
}

error_msg delete_fibonacci(Q_queue *queue, Application **result) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "delete_fibonacci", "get pointer to null"};
    }
    return delete_fibonacci_heap(&(queue->fibonacci_h), result);
}

error_msg merge_fibonacci_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "merge_fibonacci_with_destroy", "get pointer to null"};
    }
    FibonacciHeap *res = &((*result)->fibonacci_h);
    error_msg errorMsg = merge_fibonacci_heap_with_destroy(&(first->fibonacci_h), &(second->fibonacci_h), &res);
    *result = (Q_queue *)res;
    return errorMsg;
}

error_msg merge_fibonacci_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "merge_fibonacci_with_destroy", "get pointer to null"};
    }
    FibonacciHeap *res = &((*result)->fibonacci_h);
    error_msg errorMsg = merge_fibonacci_heap_without_destroy(&(first->fibonacci_h), &(second->fibonacci_h), &res);
    *result = (Q_queue *)res;
    return errorMsg;
}

Application *find_max_priority_elem_fibonacci(const Q_queue *queue) {
    if (queue == NULL) {
        return NULL;
    }
    return find_max_priority_element_fibonacci_heap(&(queue->fibonacci_h));
}

error_msg destroy_fibonacci(Q_queue *queue) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_fibonacci", "get pointer "};
    }
    return destroy_fibonacci_heap(&(queue->fibonacci_h));
}

error_msg create_skew(Q_queue **queue) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "create_skew", "get pointer nu null"};
    }
    SkewHeap *r = &((*queue)->skew_h);
    error_msg errorMsg = create_skew_heap(&r);
    *queue = (Q_queue *)r;
    return errorMsg;
}

error_msg insert_skew(Q_queue *queue, Application *application) {
    if (queue == NULL || application == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "insert_skew", "get pointer to null"};
    }
    return insert_skew_heap(&(queue->skew_h), application);
}

error_msg delete_skew(Q_queue *queue, Application **result) {
    if (queue == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "delete_skew", "get pointer to null"};
    }
    return delete_skew_heap(&(queue->skew_h), result);
}

error_msg merge_skew_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "merge_skew_with_destroy", "get pointer to null"};
    }
    SkewHeap *res = &((*result)->skew_h);
    error_msg errorMsg = merge_skew_heap_with_destroy(&(first->skew_h), &(second->skew_h), &res);
    *result = (Q_queue *)res;
    return errorMsg;
}

error_msg merge_skew_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "merge_skew_without_destroy", "get pointer to null"};
    }
    SkewHeap *res = &((*result)->skew_h);
    error_msg errorMsg = merge_skew_heap_without_destroy(&(first->skew_h), &(second->skew_h), &res);
    *result = (Q_queue *)res;
    return errorMsg;
}

Application *find_max_priority_elem_skew(const Q_queue *queue) {
    if (queue == NULL) {
        return NULL;
    }
    return find_max_priority_element_skew_heap(&(queue->skew_h));
}

error_msg destroy_skew(Q_queue *queue) {
    if (queue == NULL) {
        return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_skew", "get pointer to null"};
    }
    return destroy_skew_heap(&(queue->skew_h));
}

error_msg create_leftist(Q_queue **queue) {
    if (queue == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "create_leftist", "get pointer to null"};
    }
    LeftistHeap *leftist_heap = &((*queue)->leftist_h);
    error_msg errorMsg = create_leftist_heap(&leftist_heap);
    *queue = (Q_queue *) leftist_heap;
    return errorMsg;
}

error_msg insert_leftist(Q_queue *queue, Application *application) {
    if (queue == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "insert_leftist", "get pointer to null"};
    }
    return insert_leftist_heap(&(queue->leftist_h), application);
}

error_msg delete_leftist(Q_queue *queue, Application **result) {
    if (queue == NULL || result == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "delete_leftist", "get pointer to null"};
    }
    return delete_leftist_heap(&(queue->leftist_h), result);
}

error_msg merge_leftist_with_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "merge_leftist_with_destroy", "get pointer to null"};
    }
    LeftistHeap *res = &((*result)->leftist_h);
    error_msg errorMsg = merge_leftist_heap_with_destroy(&(first->leftist_h), &(second->leftist_h), &res);
    *result = (Q_queue *) res;
    return errorMsg;
}

error_msg merge_leftist_without_destroy(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "merge_leftist_without_destroy", "get pointer to null"};
    }
    LeftistHeap *res = &((*result)->leftist_h);
    error_msg errorMsg = merge_leftist_heap_without_destroy(&(first->leftist_h), &(second->leftist_h), &res);
    *result = (Q_queue *) res;
    return errorMsg;
}

Application *find_max_priority_elem_leftist(const Q_queue *queue) {
    if (queue == NULL) {
        return NULL;
    }
    return find_max_priority_elem_leftist_heap(&(queue->leftist_h));
}

error_msg destroy_leftist(Q_queue *queue) {
    if (queue == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "destroy_leftist", "get pointer to null"};
    }
    return destroy_leftist_heap(&(queue->leftist_h));
}

error_msg create_treap_r(Q_queue **queue) {
    if (queue == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "create_treap_r", "get pointer to null"};
    }
    Treap *treap = &((*queue)->treap);
    error_msg errorMsg = create_treap(&treap);
    *queue = (Q_queue *) treap;
    return errorMsg;
}

error_msg destroy_treap_r(Q_queue *queue) {
    if (queue == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "destroy_treap_rek", "get pointer to null"};
    }
    return destroy_treap(&(queue->treap));
}

error_msg insert_treap_r(Q_queue *queue, Application *application) {
    if (queue == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "insert_treap_r", "get pointer to null"};
    }
    return insert_treap(&(queue->treap), application);
}


error_msg delete_treap_r(Q_queue *queue, Application **result) {
    if (queue == NULL || result == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "delete_treap_r", "get pointer to null"};
    }
    return delete_treap(&(queue->treap), result);
}


error_msg merge_treap_with_destroy_r(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "merge_treap_with_destroy_r", "get pointer to null"};
    }
    Treap *res = &((*result)->treap);
    error_msg errorMsg = merge_treap_with_destroy(&(first->treap), &(second->treap), &res);
    *result = (Q_queue *) res;
    return errorMsg;
}

error_msg merge_treap_without_destroy_r(Q_queue *first, Q_queue *second, Q_queue **result) {
    if (first == NULL || second == NULL || result == NULL) {
        return (error_msg) {INCORRECT_ARG_FUNCTION, "merge_treap_without_destroy_r", "get pointer to null"};
    }
    Treap *res = &((*result)->treap);
    error_msg errorMsg = merge_treap_without_destroy(&(first->treap), &(second->treap), &res);
    *result = (Q_queue *) res;
    return errorMsg;
}


Application *find_max_priority_elem_treap_r(const Q_queue *queue) {
    if (queue == NULL) {
        return NULL;
    }
    return find_max_priority_elem_treap(&(queue->treap));

}
