#pragma once

#include <stdlib.h>

#include "../../lib2/SystemErrors2/errors.h"
#include "../../lib2/vector/charvector.h"
#include "../heaps/heaps.h"

#define MAX_LEN_NAME 20

typedef struct Department Departament;

typedef struct Operator {
	String name;
	Application* application;
	Time end_time;
	size_t processing_time_in_minutes;
	Departament* departament;
	char is_busy;
} Operator;

struct Department {
	size_t id;
	size_t count_operators;
	size_t count_employed_operators;
	Operator** operators;
	Queue queue;
};

error_msg create_departament(Departament** departament, size_t count_operators, size_t id, char what_queue);
void print_departament_condition(FILE* stream, const Departament* departament);
error_msg destroy_departament(Departament* departament);
