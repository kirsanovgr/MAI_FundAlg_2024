#include "application.h"

error_msg create_application(Application** app, Time time, size_t priority, size_t id_department, String* text,
                             size_t id_application) {
	Application * application = (Application*)calloc(1, sizeof(Application));
	application->time_create = time;
	application->key = priority;
	application->id_department = id_department;
	error_msg errorMsg = mstrcopynew(text, &(application->text));
	if(errorMsg.type){
		return errorMsg;
	}
	application->id_application = id_application;
	*app = application;
	return (error_msg){SUCCESS, "", ""};
}



void destroy_application(Application * application){
	destroy_string(&(application->text));
	free(application);
}

error_msg copy_application_new(Application * src, Application ** dst){
	error_msg errorMsg = create_application(dst, src->time_create, src->key, src->id_department, &(src->text), src->id_application);
	if(errorMsg.type){
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}

size_t DayInMonth(size_t month, size_t year) {
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
		return 29;
	}
	return days[month - 1];
}

int is_correct_time(const Time* time) {
	if (time->year > 9999 || time->month < 1 || time->month > 12 || time->day > DayInMonth(time->month, time->year))
		return 0;
	if (time->hour >= 24 || time->min >= 60) return 0;

	return 1;
}

int compare_time(const Time* t1, const Time* t2) {
	if (t1->year > t2->year || (t1->year == t2->year && t1->month > t2->month) ||
	    (t1->year == t2->year && t1->month == t2->month && t1->day > t2->day) ||
	    (t1->year == t2->year && t1->month == t2->month && t1->day == t2->day && t1->hour > t2->hour) ||
	    (t1->year == t2->year && t1->month == t2->month && t1->day == t2->day && t1->hour == t2->hour &&
	     t1->min > t2->min)){
		return 1;
	} else if (t1->year == t2->year && t1->month == t2->month && t1->day == t2->day && t1->hour == t2->hour &&
	           t1->min == t2->min) {
		return 0;
	}
	return -1;
}


void print_time(FILE* stream, const Time* t) {
	fprintf(stream, "%04zu-%02zu-%02zuT%02zu:%02zu", t->year, t->month, t->day, t->hour, t->min);
}

int is_leap_year(size_t year) {
	if (year % 4 != 0) return 0;
	if (year % 100 != 0) return 1;
	if (year % 400 == 0) return 1;
	return 0;
}

size_t days_in_month(size_t month, size_t year) {
	if (month == 2) {
		return is_leap_year(year) ? 29 : 28;
	}
	const size_t days[] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	return days[month - 1];
}

Time add_minutes(Time t, size_t minutes) {
	Time new_time = t;

	new_time.min += minutes;

	while (new_time.min >= 60) {
		new_time.min -= 60;
		new_time.hour += 1;

		if (new_time.hour >= 24) {
			new_time.hour -= 24;
			new_time.day += 1;

			if (new_time.day > days_in_month(new_time.month, new_time.year)) {
				new_time.day = 1;
				new_time.month += 1;

				if (new_time.month > 12) {
					new_time.month = 1;
					new_time.year += 1;
				}
			}
		}
	}

	return new_time;
}

error_msg read_time(FILE* stream, Time* t) {
	String tmp;
	error_msg errorMsg = create_string(&tmp, "");
	if (errorMsg.type) {
		return errorMsg;
	}

	clear_string(&tmp);
	int n = read_string(stream, &tmp);
	if (n == 0) {
		destroy_string(&tmp);
		return (error_msg){INCORRECT_OPTIONS_ERROR, "read_time", "not read string"};
	}
	if (n == -1) {
		destroy_string(&tmp);
		return (error_msg){MEMORY_ALLOCATED_ERROR, "read_time", "memory allocated"};
	}

	if (sscanf(tmp.arr, "%4zu-%2zu-%2zuT%2zu:%2zu", &t->year, &t->month, &t->day, &t->hour, &t->min) !=
	        5 ||
	    !is_correct_time(t)) {
		destroy_string(&tmp);
		return (error_msg){INCORRECT_OPTIONS_ERROR, "read_time", "not read all parameters"};
	}
	destroy_string(&tmp);
	return (error_msg){SUCCESS, "", ""};
}

Time generate_random_time() {
	Time t;

	t.year = START_YEAR + rand() % MAX_YEARS;
	t.month = 1 + rand() % 12;

	int max_day = 31;
	if (t.month == 4 || t.month == 6 || t.month == 9 || t.month == 11) {
		max_day = 30;
	} else if (t.month == 2) {
		max_day = 28;
		if ((t.year % 4 == 0 && t.year % 100 != 0) || t.year % 400 == 0) {
			max_day = 29;
		}
	}
	t.day = 1 + rand() % max_day;


	t.hour = rand() % 24;
	t.min = rand() % 60;

	return t;
}