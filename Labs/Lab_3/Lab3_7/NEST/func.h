#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_DATE_LEN 11  // Формат: dd.mm.yyyy

typedef struct Liver {
    char surname[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char patronymic[MAX_NAME_LEN];
    char birth_date[MAX_DATE_LEN]; // в формате "dd.mm.yyyy"
    char gender;  // 'M' или 'W'
    double income;
    struct Liver* next;
} Liver;

typedef enum Errors {
    SUCCESS = 0,
    NOT_HISTORY = -1,
    ERROR_FILE = -2,
    NOT_HUMAN = -3,
    ERROR_MEMORY = -4
} Errors;

typedef enum Menu {
    ADDING_RESIDENT = 1,
    REMOVE_RESIDENT = 2,
    CHANGE_DATA = 3,
    SHOW_ALL = 4,
    UNDO = 5,
    SAVE_TO_FILE = 6,
    END = 7
} Menu;

// Структура для хранения истории изменений (Undo)
typedef struct History {
    char action;  // 'A' - добавление, 'D' - удаление, 'M' - изменение
    Liver* liver; // Структура данных жителя, который был изменен
    struct History* next;
} History;

// для сравнения дат рождения
int compare_birth_dates(const char* date1, const char* date2) {
    int day1, month1, year1, day2, month2, year2;
    sscanf(date1, "%d.%d.%d", &day1, &month1, &year1);
    sscanf(date2, "%d.%d.%d", &day2, &month2, &year2);

    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}
