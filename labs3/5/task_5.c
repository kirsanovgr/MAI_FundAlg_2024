#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define MAX_GROUP_LENGTH 10
#define NUM_EXAMS 5
#define EPSILON 0.01

typedef struct {
    unsigned int id;
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char group[MAX_GROUP_LENGTH];
    unsigned char* grades;
} Student;

int isValidId(unsigned int id) {
    return id > 0;
}

int isValidName(const char* name) {
    return strlen(name) > 0 && strlen(name) < MAX_NAME_LENGTH;
}

int isValidGroup(const char* group) {
    return strlen(group) > 0 && strlen(group) < MAX_GROUP_LENGTH;
}

int readStudentsFromFile(const char* filename, Student** students, size_t* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Unable to open file\n");
        return -1;
    }

    *count = 0;
    *students = NULL;

    while (!feof(file)) {
        Student student;
        student.grades = malloc(NUM_EXAMS * sizeof(unsigned char));
        if (!student.grades) {
            fclose(file);
            return -2;
        }

        if (fscanf(file, "%u %s %s %s %hhu %hhu %hhu %hhu %hhu",
                   &student.id, student.name, student.surname,
                   student.group, &student.grades[0], &student.grades[1],
                   &student.grades[2], &student.grades[3], &student.grades[4]) == 9) {
            if (isValidId(student.id) && 
                isValidName(student.name) &&
                isValidName(student.surname) &&
                isValidGroup(student.group)) {
                (*count)++;
                Student* temp = realloc(*students, (*count) * sizeof(Student));
                if (!temp) {
                    free(student.grades);
                    fclose(file);
                    return -2;
                }
                *students = temp;
                (*students)[*count - 1] = student;
            } else {
                printf("Invalid data found in file: ID: %u, Name: %s, Surname: %s, Group: %s\n",
                       student.id, student.name, student.surname, student.group);
                free(student.grades);
            }
        } else {
            free(student.grades);
        }
    }

    fclose(file);
    return 0;
}

int compareById(const void* a, const void* b) {
    return ((Student*)a)->id - ((Student*)b)->id;
}

float calculateAverageGrade(const Student* student) {
    float sum = 0;
    for (int i = 0; i < NUM_EXAMS; i++) {
        sum += student->grades[i];
    }
    return sum / NUM_EXAMS;
}

void writeTraceFile(const char* traceFile, const Student* student) {
    FILE* file = fopen(traceFile, "a");
    if (!file) {
        printf("Unable to open trace file\n");
        return;
    }
    fprintf(file, "ID: %u, Name: %s %s, Group: %s, Average Grade: %.2f\n",
            student->id, student->name, student->surname,
            student->group, calculateAverageGrade(student));
    fclose(file);
}

void writeHighAchieversToTraceFile(const char* traceFile, const Student* students, size_t count) {
    FILE* file = fopen(traceFile, "a");
    if (!file) {
        printf("Unable to open trace file\n");
        return;
    }

    float totalSum = 0;
    for (size_t i = 0; i < count; i++) {
        totalSum += calculateAverageGrade(&students[i]);
    }
    float overallAverage = totalSum / count;

    fprintf(file, "Students with average grade above %.2f:\n", overallAverage);
    for (size_t i = 0; i < count; i++) {
        if (calculateAverageGrade(&students[i]) > overallAverage + EPSILON) {
            fprintf(file, "%s %s\n", students[i].name, students[i].surname);
        }
    }
    fclose(file);
}

void freeStudents(Student* students, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(students[i].grades);
    }
    free(students);
}

void searchStudentById(const Student* students, size_t count, unsigned int id, const char* traceFile) {
    if (!isValidId(id)) {
        printf("Invalid ID provided.\n");
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (students[i].id == id) {
            writeTraceFile(traceFile, &students[i]);
            printf("Student found: %s %s, Group: %s, Average Grade: %.2f\n", 
                   students[i].name, students[i].surname, students[i].group,
                   calculateAverageGrade(&students[i]));
            return;
        }
    }
    printf("Student with ID %u not found.\n", id);
}

void searchStudentBySurname(const Student* students, size_t count, const char* surname, const char* traceFile) {
    if (!isValidName(surname)) {
        printf("Invalid surname provided.\n");
        return;
    }

    for (size_t i = 0; i < count; i++) {
        if (strcmp(students[i].surname, surname) == 0) {
            writeTraceFile(traceFile, &students[i]);
            printf("Student found: %s %s, Group: %s, Average Grade: %.2f\n", 
                   students[i].name, students[i].surname, students[i].group,
                   calculateAverageGrade(&students[i]));
            return;
        }
    }
    printf("Student with surname %s not found.\n", surname);
}

void searchStudentByName(const Student* students, size_t count, const char* name, const char* traceFile) {
    if (!isValidName(name)) {
        printf("Invalid name provided.\n");
        return;
    }

    for (size_t i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            writeTraceFile(traceFile, &students[i]);
            printf("Student found: %s %s, Group: %s, Average Grade: %.2f\n", 
                   students[i].name, students[i].surname, students[i].group,
                   calculateAverageGrade(&students[i]));
            return;
        }
    }
    printf("Student with name %s not found.\n", name);
}

void searchStudentByGroup(const Student* students, size_t count, const char* group, const char* traceFile) {
    if (!isValidGroup(group)) {
        printf("Invalid group provided.\n");
        return;
    }

    int found = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(students[i].group, group) == 0) {
            writeTraceFile(traceFile, &students[i]);
            printf("Student found: %s %s, Group: %s, Average Grade: %.2f\n", 
                   students[i].name, students[i].surname, students[i].group,
                   calculateAverageGrade(&students[i]));
            found = 1;
        }
    }
    
    if (!found) {
        printf("No students found in group %s.\n", group);
    }
}

void printStudents(const Student* students, size_t count) {
    printf("\nList of Students:\n");
    for (size_t i = 0; i < count; i++) {
        printf("ID: %u, Name: %s %s, Group: %s, Average Grade: %.2f\n",
               students[i].id, students[i].name, students[i].surname,
               students[i].group, calculateAverageGrade(&students[i]));
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <trace_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Student* students = NULL;
    size_t count = 0;
    if (readStudentsFromFile(argv[1], &students, &count) != 0) {
        return EXIT_FAILURE;
    }

    int option;
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Search by ID\n");
        printf("2. Search by Surname\n");
        printf("3. Search by Name\n");
        printf("4. Search by Group\n");
        printf("5. List students with average grade above overall average\n");
        printf("6. Print all students\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            continue;
        }

        switch (option) {
            case 1: {
                unsigned int id;
                printf("Enter ID to search: ");
                if (scanf("%u", &id) != 1) {
                    printf("Invalid ID input. Please enter a number.\n");
                    while(getchar() != '\n');
                    break;
                }
                searchStudentById(students, count, id, argv[2]);
                break;
            }
            case 2: {
                char surname[MAX_NAME_LENGTH];
                printf("Enter surname to search: ");
                scanf("%s", surname);
                searchStudentBySurname(students, count, surname, argv[2]);
                break;
            }
            case 3: {
                char name[MAX_NAME_LENGTH];
                printf("Enter name to search: ");
                scanf("%s", name);
                searchStudentByName(students, count, name, argv[2]);
                break;
            }
            case 4: {
                char group[MAX_GROUP_LENGTH];
                printf("Enter group to search: ");
                scanf("%s", group);
                searchStudentByGroup(students, count, group, argv[2]);
                break;
            }
            case 5:
                writeHighAchieversToTraceFile(argv[2], students, count);
                break;
            case 6:
                printStudents(students, count);
                break;
            case 7:
                freeStudents(students, count);
                return EXIT_SUCCESS;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    freeStudents(students, count);
    return EXIT_SUCCESS;
}
