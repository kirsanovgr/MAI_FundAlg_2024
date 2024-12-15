

/*
 * Файл с описанием заявок
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../lib2/SystemErrors2/errors.h"
#include "../../lib2/vector/charvector.h"

typedef struct Time {
	size_t year;
	size_t month;
	size_t day;
	size_t hour;
	size_t min;
} Time;

typedef struct Application {
	Time time_create;
	size_t key;
	size_t id_department;
	String text;
	size_t id_application;
} Application;

#define START_YEAR 2024
#define MAX_YEARS 1

error_msg create_application(Application** application, Time time, size_t priority, size_t id_department, String* text,
                             size_t id_application);

error_msg copy_application_new(Application* src, Application** dst);

void destroy_application(Application* application);

int is_correct_time(const Time* time);
int compare_time(const Time* t1, const Time* t2);
void print_time(FILE* stream, const Time* t);
Time add_minutes(Time t, size_t minutes);
error_msg read_time(FILE* stream, Time* t);
Time generate_random_time();