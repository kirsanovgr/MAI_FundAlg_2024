
#include "department.h"

void generate_random_name(char* name, size_t max_name_length, const char* alphabet) {
	for (size_t i = 0; i < max_name_length; i++) {
		name[i] = alphabet[rand() % (SizeString(alphabet))];
	}
	name[max_name_length] = '\0';
}

error_msg create_departament(Departament** dep, size_t count_operators, size_t id, char what_queue){
	if(dep == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "create_departament", "get pointer to null"};
	}
	Departament * departament = (Departament*)calloc(1, sizeof(Departament));
	if(!departament){
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_departament", "memory allocated"};
	}
	departament->operators = (Operator**)calloc(count_operators, sizeof(Operator*));
	if(!departament->operators){
		return (error_msg){MEMORY_ALLOCATED_ERROR, "create_departament", "memory allocated"};
	}
	error_msg errorMsg;
	departament->id = id;
	departament->queue.v = heaps_functions[(int)what_queue];
	errorMsg = departament->queue.v.create_heap(&(departament->queue.q));
	if(errorMsg.type){
		free(departament->operators);
		free(departament);
		return errorMsg;
	}
	departament->id = id;
	char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for(size_t i = 0; i < count_operators; ++i){
		departament->operators[i] = (Operator*)calloc(1, sizeof(Operator));
		if(departament->operators[i] == NULL){
			destroy_departament(departament);
			return errorMsg;
		}
		departament->operators[i]->departament = departament;
		size_t len = rand() % MAX_LEN_NAME;
		char a[len + 1];
		generate_random_name(a, len, alphabet);

//		Псевдорандом зацикливается
//		int fl = 0;
//		while (!fl){
//			size_t j = 0;
//			for(; j < departament->count_operators;++j){
//				if(string_cmp(departament->operators[j]->name.arr, a)){
//					break;
//				}
//			}
//			if(j != departament->count_operators){
//				generate_random_name(a, len, alphabet);
//			} else{
//				fl = 1;
//			}
//		}

		errorMsg = create_string(&(departament->operators[i]->name), a);
		if(errorMsg.type){
			destroy_departament(departament);
		}
		departament->count_operators++;
	}
	*dep = departament;
	return (error_msg){SUCCESS, "", ""};
}


error_msg destroy_departament(Departament * departament){
	if(departament == NULL){
		return (error_msg){INCORRECT_ARG_FUNCTION, "destroy_departament", "get pointer to null"};
	}
	for(size_t i = 0; i < departament->count_operators; ++i){
		destroy_string(&(departament->operators[i]->name));
		if(departament->operators[i]->application != NULL){
			destroy_application(departament->operators[i]->application);
		}
		free(departament->operators[i]);
	}
	error_msg errorMsg = departament->queue.v.destroy_heap(departament->queue.q);
	if(errorMsg.type){
		free(departament->operators);
		free(departament);
		return errorMsg;
	}
	free(departament->operators);
	free(departament);
	return (error_msg){SUCCESS, "", ""};
}



void print_departament_condition(FILE* stream, const Departament * departament){
	fprintf(stream, "%zu\n", departament->id);
	fprintf(stream, "Count operators: %zu\nEmployed operators: %zu\n", departament->count_operators, departament->count_employed_operators);
	for(size_t i = 0; i < departament->count_operators;++i){
		fprintf(stream, "-------------------------------------\n");
		fprintf(stream, "Name: %s\nApplication: %p\n", departament->operators[i]->name.arr, departament->operators[i]->application);
		print_time(stream, &(departament->operators[i]->end_time));
		fprintf(stream, "\nDepartament: %p\n", departament->operators[i]->departament);
	}
}