#include "data-storages.h"

V_table_data_storages data_storages_functions[] = {
    {
        create_hash_t,
        push_into_hash_t,
        get_hash_t,
        destroy_hast_t
    },
    {
        create_dynamic_arr,
        push_into_dynamic_arr,
        get_dynamic_arr,
        destroy_dynamic_arr
    },
    {
        create_bin_t,
        push_into_bin_t,
        get_bin_t,
        destroy_bin_t
    },
    {
        create_trie_t,
        push_into_trie_t,
        get_trie_t,
        destroy_trie_t
    }
};

error_msg create_hash_t(Data_storages *storages, size_t size) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_hash_t", "get pointer to null"};
	}
	return create_hash_table(&(storages->hash_t), size);
}

error_msg push_into_hash_t(Data_storages *storages, size_t id_department, size_t count_operators, char what_queue) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "push_into_hash_t", "get pointer to null"};
	}
	return push_into_hash_table(&(storages->hash_t), id_department, count_operators, what_queue);
}

error_msg get_hash_t(Data_storages *storages, size_t id, Departament **departament) {
	if (storages == NULL || departament == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "get_hash_t", "get pointer to null"};
	}
	return get_hash_table(&(storages->hash_t), id, departament);
}

error_msg destroy_hast_t(Data_storages *storages) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_hast_t", "get pointer to null"};
	}
	return destroy_hash_table(&(storages->hash_t));
}

error_msg create_dynamic_arr(Data_storages *storages, size_t capacity) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_dynamic_arr", "get pointer to null"};
	}
	return create_dynamic_array_departments(&(storages->dynamic_arr), capacity);
}

error_msg push_into_dynamic_arr(Data_storages *storages, size_t id_department, size_t count_operators,
                                char what_queue) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "push_into_dynamic_arr", "get pointer to null"};
	}
	return push_into_dynamic_array(&(storages->dynamic_arr), id_department, count_operators, what_queue);
}

error_msg get_dynamic_arr(Data_storages *storages, size_t id, Departament **departament) {
	if (storages == NULL || departament == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "get_dynamic_arr", "get pointer to null"};
	}
	return get_dynamic_array(&(storages->dynamic_arr), id, departament);
}

error_msg destroy_dynamic_arr(Data_storages *storages) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_dynamic_arr", "get pointer to null"};
	}
	return destroy_dynamic_array(&(storages->dynamic_arr));
}

error_msg create_bin_t(Data_storages *storages, [[maybe_unused]] size_t capacity) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_bin_t", "get pointer to null"};
	}
	return create_bin_tree(&(storages->bin_tree));
}

error_msg push_into_bin_t(Data_storages *storages, size_t id_department, size_t count_operators, char what_queue) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "push_into_bin_t", "get pointer to null"};
	}
	return push_into_bin_tree(&(storages->bin_tree), id_department, count_operators, what_queue);
}

error_msg get_bin_t(Data_storages *storages, size_t id, Departament **departament) {
	if (storages == NULL || departament == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "get_bin_t", "get pointer to null"};
	}
	return get_bin_tree(&(storages->bin_tree), id, departament);
}

error_msg destroy_bin_t(Data_storages *storages) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_bin_t", "get pointer to null"};
	}
	return destroy_bin_tree(&(storages->bin_tree));
}

error_msg create_trie_t(Data_storages *storages,  [[maybe_unused]] size_t capacity) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_trie_t", "get pointer to null"};
	}
	return create_trie(&(storages->trie));
}

error_msg push_into_trie_t(Data_storages *storages, size_t id_department, size_t count_operators, char what_queue) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "push_into_trie_t", "get pointer to null"};
	}
	return push_into_trie(&(storages->trie), id_department, count_operators, what_queue);
}

error_msg get_trie_t(Data_storages *storages, size_t id, Departament **departament) {
	if (storages == NULL || departament == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "get_trie_t", "get pointer to null"};
	}
	return get_trie(&(storages->trie), id, departament);
}

error_msg destroy_trie_t(Data_storages *storages) {
	if (storages == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_trie_t", "get pointer to null"};
	}
	return destroy_trie(&(storages->trie));
}