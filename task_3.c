#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum StatusCodes {
    ERROR = -1,
    SUCCESS,
};

typedef int (*CallbackFunction)(const char* inputFile, const char* outputFile);

typedef struct Employee {
    float wage;
    char lastName[BUFSIZ];
    char firstName[BUFSIZ];
    unsigned int id;
} Employee;

int StringsEqual(const char* left, const char* right) {
    return strcmp(left, right) == 0;
}

int ValidateString(const char* str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))) {
            return 0;
        }
    }
    return 1;
}

int ValidateWage(const char* str) {
    int seenDecimalPoint = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '.') {
            if (seenDecimalPoint) return 0;
            seenDecimalPoint = 1;
        } else if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int ValidateId(const char* str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int ValidateEmployeeData(const char* id, const char* firstName, const char* lastName, const char* wage) {
    return ValidateId(id) && ValidateString(firstName) && ValidateString(lastName) && ValidateWage(wage);
}

int FindFlagIndex(const char* arg, const char* flags[], int numFlags) {
    for (int i = 0; i < numFlags; ++i) {
        if (StringsEqual(arg, flags[i])) return i;
    }
    return ERROR;
}

int CompareAscending(const void* a, const void* b) {
    Employee* emp1 = (Employee*)a;
    Employee* emp2 = (Employee*)b;
    if (emp1->wage != emp2->wage) return (emp1->wage > emp2->wage) ? 1 : -1;
    int firstNameComparison = strcmp(emp1->firstName, emp2->firstName);
    if (firstNameComparison != 0) return firstNameComparison;
    int lastNameComparison = strcmp(emp1->lastName, emp2->lastName);
    return lastNameComparison != 0 ? lastNameComparison : (emp1->id > emp2->id ? 1 : -1);
}

int CompareDescending(const void* a, const void* b) {
    Employee* emp1 = (Employee*)a;
    Employee* emp2 = (Employee*)b;
    if (emp1->wage != emp2->wage) return (emp1->wage < emp2->wage) ? 1 : -1;
    int firstNameComparison = strcmp(emp1->firstName, emp2->firstName);
    if (firstNameComparison != 0) return -firstNameComparison;
    int lastNameComparison = strcmp(emp1->lastName, emp2->lastName);
    return lastNameComparison != 0 ? -lastNameComparison : (emp1->id < emp2->id ? 1 : -1);
}

int ProcessFileAscending(const char* inputFile, const char* outputFile) {
    FILE* in = fopen(inputFile, "r");
    if (!in) return ERROR;

    FILE* out = fopen(outputFile, "w");
    if (!out) {
        fclose(in);
        return ERROR;
    }

    int index = 0, capacity = 10;
    Employee* employees = malloc(capacity * sizeof(Employee));
    if (!employees) {
        fclose(in);
        fclose(out);
        return ERROR;
    }

    char id[BUFSIZ], firstName[BUFSIZ], lastName[BUFSIZ], wage[BUFSIZ];
    while (fscanf(in, "%s %s %s %s", id, firstName, lastName, wage) != EOF) {
        if (!ValidateEmployeeData(id, firstName, lastName, wage)) {
            fclose(in);
            fclose(out);
            free(employees);
            return ERROR;
        }

        if (index >= capacity) {
            capacity *= 2;
            employees = realloc(employees, capacity * sizeof(Employee));
            if (!employees) {
                fclose(in);
                fclose(out);
                return ERROR;
            }
        }

        employees[index].id = atoi(id);
        strcpy(employees[index].firstName, firstName);
        strcpy(employees[index].lastName, lastName);
        employees[index].wage = atof(wage);
        ++index;
    }
    fclose(in);

    qsort(employees, index, sizeof(Employee), CompareAscending);

    for (int i = 0; i < index; ++i) {
        fprintf(out, "%u %s %s %f\n", employees[i].id, employees[i].firstName, employees[i].lastName, employees[i].wage);
    }
    fclose(out);
    free(employees);

    return SUCCESS;
}

int ProcessFileDescending(const char* inputFile, const char* outputFile) {
    FILE* in = fopen(inputFile, "r");
    if (!in) return ERROR;

    FILE* out = fopen(outputFile, "w");
    if (!out) {
        fclose(in);
        return ERROR;
    }

    int index = 0, capacity = 10;
    Employee* employees = malloc(capacity * sizeof(Employee));
    if (!employees) {
        fclose(in);
        fclose(out);
        return ERROR;
    }

    char id[BUFSIZ], firstName[BUFSIZ], lastName[BUFSIZ], wage[BUFSIZ];
    while (fscanf(in, "%s %s %s %s", id, firstName, lastName, wage) != EOF) {
        if (!ValidateEmployeeData(id, firstName, lastName, wage)) {
            fclose(in);
            fclose(out);
            free(employees);
            return ERROR;
        }

        if (index >= capacity) {
            capacity *= 2;
            employees = realloc(employees, capacity * sizeof(Employee));
            if (!employees) {
                fclose(in);
                fclose(out);
                return ERROR;
            }
        }

        employees[index].id = atoi(id);
        strcpy(employees[index].firstName, firstName);
        strcpy(employees[index].lastName, lastName);
        employees[index].wage = atof(wage);
        ++index;
    }
    fclose(in);

    qsort(employees, index, sizeof(Employee), CompareDescending);

    for (int i = 0; i < index; ++i) {
        fprintf(out, "%u %s %s %.2f\n", employees[i].id, employees[i].firstName, employees[i].lastName, employees[i].wage);
    }
    fclose(out);
    free(employees);

    return SUCCESS;
}

int main(int argc, char *argv[]) {
    const char* flags[] = {"-a", "/a", "-d", "/d"};
    CallbackFunction operations[] = {ProcessFileAscending, ProcessFileDescending};

    if (argc != 4) {
        fprintf(stderr, "USAGE: <input_file> <flag> <output_file>\n");
        return ERROR;
    }

    int flagIndex = FindFlagIndex(argv[2], flags, sizeof(flags) / sizeof(char*));
    if (flagIndex == ERROR) {
        fprintf(stdout, "ERROR: unknown flag\n");
        return ERROR;
    }

    if (StringsEqual(argv[1], argv[3])) {
        fprintf(stdout, "ERROR: input and output files must be different\n");
        return ERROR;
    }

    int result = operations[flagIndex / 2](argv[1], argv[3]);
    if (result == ERROR) {
        fprintf(stdout, "ERROR: operation failed\n");
        return ERROR;
    }

    return SUCCESS;
}
