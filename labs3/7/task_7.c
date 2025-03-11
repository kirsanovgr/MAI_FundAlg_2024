#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Liver {
    char surname[50];
    char name[50];
    char patronymic[50];
    int day, month, year;
    char gender;
    double income;
    struct Liver* next;
} Liver;

typedef struct History {
    Liver* state;
    char type;
    struct History* next;
} History;

Liver* head = NULL;
History* historyHead = NULL;
int modificationCount = 0;

bool isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2024) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) return false;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return day <= 29;
        }
        return day <= 28;
    }
    return true;
}

bool isValidIncome(double income) {
    return income >= 0;
}

bool isValidString(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) return false;
    }
    return true;
}

bool isValidGender(char gender) {
    return gender == 'M' || gender == 'W';
}

void addLiver(Liver newLiver) {
    Liver* newNode = malloc(sizeof(Liver));
    if (!newNode) {
        return;
    }
    *newNode = newLiver;
    newNode->next = NULL;

    if (!head || (newNode->year < head->year) || 
        (newNode->year == head->year && newNode->month < head->month) ||
        (newNode->year == head->year && newNode->month == head->month && newNode->day < head->day)) {
        newNode->next = head;
        head = newNode;
    } else {
        Liver* current = head;
        while (current->next && 
              (newNode->year > current->next->year || 
              (newNode->year == current->next->year && newNode->month > current->next->month) ||
              (newNode->year == current->next->year && newNode->month == current->next->month && newNode->day > current->next->day))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    History* newHistory = malloc(sizeof(History));
    newHistory->state = newNode;
    newHistory->type = 'A';
    newHistory->next = historyHead;
    historyHead = newHistory;

    modificationCount++;
}

void printLivers() {
    Liver* current = head;
    while (current) {
        printf("%s %s %s %02d/%02d/%04d %c %.2f\n",
               current->surname, current->name, current->patronymic,
               current->day, current->month, current->year,
               current->gender, current->income);
        current = current->next;
    }
}

Liver* findLiver(const char* surname) {
    Liver* current = head;
    while (current) {
        if (strcmp(current->surname, surname) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modifyLiver(Liver* liver) {
    if (!liver) {
        printf("Resident not found.\n");
        return;
    }

    // Print current details
    printf("Current details: %s %s %s %02d/%02d/%04d %c %.2f\n",
           liver->surname, liver->name, liver->patronymic,
           liver->day, liver->month, liver->year,
           liver->gender, liver->income);
    
    printf("Enter new surname, name, patronymic, birth date (dd/mm/yyyy), gender (M/W), income:\n");
    
    Liver newLiver;
    scanf("%s %s %s %d/%d/%d %c %lf", newLiver.surname, newLiver.name, newLiver.patronymic,
          &newLiver.day, &newLiver.month, &newLiver.year, &newLiver.gender, &newLiver.income);
    
    // Validation
    if (!isValidDate(newLiver.day, newLiver.month, newLiver.year)) {
        printf("Invalid date. Please enter a valid date.\n");
        return;
    }
    if (!isValidGender(newLiver.gender)) {
        printf("Invalid gender. Please enter 'M' or 'W'.\n");
        return;
    }
    if (!isValidIncome(newLiver.income)) {
        printf("Invalid income. Please enter a positive income.\n");
        return;
    }
    if (!isValidString(newLiver.surname) || !isValidString(newLiver.name) || !isValidString(newLiver.patronymic)) {
        printf("Invalid input. Please use letters only for names and surname.\n");
        return;
    }

    History* newHistory = malloc(sizeof(History));
    newHistory->state = malloc(sizeof(Liver));
    *newHistory->state = *liver;
    newHistory->type = 'M';
    newHistory->next = historyHead;
    historyHead = newHistory;

    strcpy(liver->surname, newLiver.surname);
    strcpy(liver->name, newLiver.name);
    strcpy(liver->patronymic, newLiver.patronymic);
    liver->day = newLiver.day;
    liver->month = newLiver.month;
    liver->year = newLiver.year;
    liver->gender = newLiver.gender;
    liver->income = newLiver.income;

    modificationCount++;
    printf("Resident modified successfully.\n");
}


void deleteLiver(const char* surname) {
    Liver* current = head;
    Liver* previous = NULL;

    while (current) {
        if (strcmp(current->surname, surname) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next;
            }

            History* newHistory = malloc(sizeof(History));
            newHistory->state = malloc(sizeof(Liver));
            *newHistory->state = *current;
            newHistory->type = 'D';
            newHistory->next = historyHead;
            historyHead = newHistory;

            free(current);
            printf("Resident %s deleted.\n", surname);
            modificationCount++;
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Resident not found.\n");
}

void undo() {
    if (!historyHead) {
        printf("No modifications to undo.\n");
        return;
    }

    History* lastHistory = historyHead;
    historyHead = historyHead->next;

    if (lastHistory->state) {
        if (lastHistory->type == 'D') {
            addLiver(*(lastHistory->state));
        } else if (lastHistory->type == 'M') {
            Liver* current = head;
            while (current) {
                if (strcmp(current->surname, lastHistory->state->surname) == 0) {
                    *current = *(lastHistory->state);
                    break;
                }
                current = current->next;
            }
        }
    }

    free(lastHistory->state);
    free(lastHistory);
    modificationCount--;
    printf("Last modification undone.\n");
}

void saveToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    Liver* current = head;
    while (current) {
        fprintf(file, "%s %s %s %02d/%02d/%04d %c %.2f\n",
                current->surname, current->name, current->patronymic,
                current->day, current->month, current->year,
                current->gender, current->income);
        current = current->next;
    }
    
    fclose(file);
}

void loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }

    while (head) {
        Liver* temp = head;
        head = head->next;
        free(temp);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Liver newLiver;
        if (sscanf(line, "%49s %49s %49s %d/%d/%d %c %lf",
                   newLiver.surname, newLiver.name, newLiver.patronymic,
                   &newLiver.day, &newLiver.month, &newLiver.year,
                   &newLiver.gender, &newLiver.income) == 8) {
            addLiver(newLiver);
        }
    }

    fclose(file);
}

int main() {
    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. Add resident\n");
        printf("2. Modify resident\n");
        printf("3. Delete resident\n");
        printf("4. Print residents\n");
        printf("5. Undo last operation\n");
        printf("6. Save to file\n");
        printf("7. Load from file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                Liver newLiver;
                printf("Enter surname, name, patronymic, birth date (dd/mm/yyyy), gender (M/W), income:\n");
                scanf("%s %s %s %d/%d/%d %c %lf", newLiver.surname, newLiver.name, newLiver.patronymic,
                      &newLiver.day, &newLiver.month, &newLiver.year, &newLiver.gender, &newLiver.income);
                if (isValidDate(newLiver.day, newLiver.month, newLiver.year) &&
                    isValidGender(newLiver.gender) &&
                    isValidIncome(newLiver.income) &&
                    isValidString(newLiver.surname) &&
                    isValidString(newLiver.name) &&
                    isValidString(newLiver.patronymic)) {
                    addLiver(newLiver);
                    printf("Resident added.\n");
                } else {
                    printf("Invalid input. Please try again.\n");
                }
                break;
            }
            case 2: {
                char surname[50];
                printf("Enter surname of the resident to modify:\n");
                scanf("%s", surname);
                Liver* liver = findLiver(surname);
                modifyLiver(liver);
                break;
            }
            case 3: {
                char surname[50];
                printf("Enter surname of the resident to delete:\n");
                scanf("%s", surname);
                deleteLiver(surname);
                break;
            }
            case 4:
                printLivers();
                break;
            case 5:
                undo();
                break;
            case 6: {
                char filename[100];
                printf("Enter filename to save:\n");
                scanf("%s", filename);
                saveToFile(filename);
                break;
            }
            case 7: {
                char filename[100];
                printf("Enter filename to load:\n");
                scanf("%s", filename);
                loadFromFile(filename);
                break;
            }
            case 0:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
