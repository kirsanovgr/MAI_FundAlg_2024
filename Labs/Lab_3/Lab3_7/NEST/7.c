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

// Структура для хранения истории изменений (Undo)
typedef struct History {
    char action;  // 'A' - добавление, 'D' - удаление, 'M' - изменение
    Liver* liver; // Структура данных жителя, который был изменен
    struct History* next;
} History;

// Функция для сравнения дат рождения
int compare_birth_dates(const char* date1, const char* date2) {
    int day1, month1, year1, day2, month2, year2;
    sscanf(date1, "%d.%d.%d", &day1, &month1, &year1);
    sscanf(date2, "%d.%d.%d", &day2, &month2, &year2);

    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}

// Функция для вставки в упорядоченный список
void insert_sorted(Liver** head, Liver* new_liver) {
    if (*head == NULL || compare_birth_dates(new_liver->birth_date, (*head)->birth_date) < 0) {
        new_liver->next = *head;
        *head = new_liver;
        return;
    }

    Liver* current = *head;
    while (current->next && compare_birth_dates(new_liver->birth_date, current->next->birth_date) > 0) {
        current = current->next;
    }

    new_liver->next = current->next;
    current->next = new_liver;
}

// Функция для добавления в историю
void add_to_history(History** history, char action, Liver* liver) {
    History* new_history = (History*)malloc(sizeof(History));
    if (!new_history) return; // Ошибка выделения памяти

    new_history->action = action;
    new_history->liver = liver;
    new_history->next = *history;
    *history = new_history;
}

// Функция для отмены последнего действия
// Функция для отмены последнего действия
int undo(History** history, Liver** head) {
    if (*history == NULL) {
        return -1; // История пуста
    }

    History* last_action = *history;
    *history = last_action->next;

    if (last_action->action == 'A') {
        // Отменяем добавление, удаляем последнего жителя
        Liver* current = *head;
        if (current == last_action->liver) {
            *head = current->next;
            free(current);
        } else {
            while (current->next && current->next != last_action->liver) {
                current = current->next;
            }
            if (current->next) {
                Liver* to_delete = current->next;
                current->next = current->next->next;
                free(to_delete);
            }
        }
    } else if (last_action->action == 'D') {
        // Отменяем удаление, добавляем назад
        insert_sorted(head, last_action->liver);
    } else if (last_action->action == 'M') {
        // Отменяем изменение, возвращаем старые данные
        // Восстановим данные из прошлого состояния
        // Возвращаем старые значения
        char temp_name[MAX_NAME_LEN];
        strncpy(temp_name, last_action->liver->name, MAX_NAME_LEN);
        strncpy(last_action->liver->name, last_action->liver->patronymic, MAX_NAME_LEN); // Восстановить прежние данные
        //last_action->liver->income = 2000.00; // Восстановить прежний доход (пример)
    }

    free(last_action);
    return 0;
}


// Функция для чтения данных из файла// Чтение данных из файла
int read_from_file(const char* filename, Liver** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return -1; // Ошибка открытия файла
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Парсим строку в структуру
        Liver* new_liver = (Liver*)malloc(sizeof(Liver));
        if (!new_liver) {
            fclose(file);
            return -2; // Ошибка выделения памяти
        }

        // Проверим формат и корректность данных
        if (sscanf(buffer, "%s %s %s %s %c %lf", new_liver->surname,
            new_liver->name, new_liver->patronymic, new_liver->birth_date,
            &new_liver->gender, &new_liver->income) != 6) {
            free(new_liver);
            continue; // Пропускаем строку, если она не полная или содержит ошибку
        }

        insert_sorted(head, new_liver); // Вставляем в отсортированный список
    }

    fclose(file);
    return 0;
}


// Функция для добавления жителя в список
int add_liver(Liver** head, Liver* new_liver, History** history) {
    insert_sorted(head, new_liver);
    add_to_history(history, 'A', new_liver);
    return 0;
}

// Функция для удаления жителя из списка
int delete_liver(Liver** head, const char* surname, History** history) {
    Liver* current = *head;
    Liver* prev = NULL;

    while (current) {
        if (strcmp(current->surname, surname) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            add_to_history(history, 'D', current); // Добавляем в историю удаления
            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return -1; // Житель не найден
}

// Функция для модификации данных жителя
// Функция для модификации данных жителя
int modify_liver(Liver* head, const char* surname, const char* new_name, double new_income, History** history) {
    Liver* current = head;
    while (current) {
        if (strcmp(current->surname, surname) == 0) {
            // Добавляем в историю изменения
            add_to_history(history, 'M', current);
            printf("Изменение данных для %s\n", current->surname); // Отладочная информация
            strncpy(current->name, new_name, MAX_NAME_LEN);
            current->income = new_income;
            return 0;
        }
        current = current->next;
    }
    return -1; // Житель не найден
}


// Функция для сохранения данных в файл
int save_to_file(const char* filename, Liver* head) {
    char save_filename[100];
    printf("Введите путь к файлу для сохранения данных: ");
    scanf("%s", save_filename);

    FILE* file = fopen(filename, "w");
    if (!file) {
        return -1;
    }

    Liver* current = head;
    while (current) {
        fprintf(file, "%s %s %s %s %c %.2f\n", current->surname, current->name,
                current->patronymic, current->birth_date, current->gender, current->income);
        current = current->next;
    }

    fclose(file);
    return 0;
}

// Функция для отображения данных всех жителей
void print_residents(Liver* head) {
    Liver* current = head;
    while (current) {
        printf("Фамилия: %s, Имя: %s, Отчество: %s, Дата рождения: %s, Пол: %c, Доход: %.2f\n",
               current->surname, current->name, current->patronymic, current->birth_date,
               current->gender, current->income);
        current = current->next;
    }
}

int main() {
    Liver* residents = NULL;
    History* history = NULL;

    const char* filename = "residents.txt";

    // Чтение данных из файла
    if (read_from_file(filename, &residents) != 0) {
        printf("Ошибка при чтении файла.\n");
        return 1;
    }

    // Главный цикл программы
    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Добавить жителя\n");
        printf("2. Удалить жителя\n");
        printf("3. Изменить данные жителя\n");
        printf("4. Показать всех жителей\n");
        printf("5. Отмена последнего действия (Undo)\n");
        printf("6. Сохранить в файл\n");
        printf("7. Выйти\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Добавление нового жителя
            Liver* new_liver = (Liver*)malloc(sizeof(Liver));
            if (!new_liver) {
                printf("Ошибка выделения памяти.\n");
                continue;
            }

            printf("Введите фамилию: ");
            scanf("%s", new_liver->surname);
            printf("Введите имя: ");
            scanf("%s", new_liver->name);
            printf("Введите отчество: ");
            scanf("%s", new_liver->patronymic);
            printf("Введите дату рождения (dd.mm.yyyy): ");
            scanf("%s", new_liver->birth_date);
            printf("Введите пол (M/W): ");
            scanf(" %c", &new_liver->gender);
            printf("Введите доход: ");
            scanf("%lf", &new_liver->income);

            add_liver(&residents, new_liver, &history);
            printf("Житель добавлен.\n");
        } else if (choice == 2) {
            // Удаление жителя
            char surname[MAX_NAME_LEN];
            printf("Введите фамилию жителя для удаления: ");
            scanf("%s", surname);
            if (delete_liver(&residents, surname, &history) != 0) {
                printf("Житель не найден.\n");
            } else {
                printf("Житель удалён.\n");
            }
        } else if (choice == 3) {
            // Изменение данных жителя
            char surname[MAX_NAME_LEN], new_name[MAX_NAME_LEN];
            double new_income;
            printf("Введите фамилию жителя для изменения: ");
            scanf("%s", surname);
            printf("Введите новое имя: ");
            scanf("%s", new_name);
            printf("Введите новый доход: ");
            scanf("%lf", &new_income);

            if (modify_liver(residents, surname, new_name, new_income, &history) != 0) {
                printf("Житель не найден.\n");
            } else {
                printf("Данные изменены.\n");
            }
        } else if (choice == 4) {
            // Показать всех жителей
            print_residents(residents);
        } else if (choice == 5) {
            // Отмена последнего действия
            if (undo(&history, &residents) == 0) {
                printf("Последнее изменение отменено.\n");
            } else {
                printf("Невозможно отменить изменение.\n");
            }
        } else if (choice == 6) {
            // Сохранение в файл
            if (save_to_file(filename, residents) == 0) {
                printf("Данные успешно сохранены в файл.\n");
            } else {
                printf("Ошибка при сохранении файла.\n");
            }
        }
    } while (choice != 7);

    return 0;
}
