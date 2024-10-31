#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Employee {
    int id;
    char* name;
    char* surname;
    float salary;
} Employee;

typedef enum {
    SUCCESS,
    ERROR_INVALID_ARGUMENTS,
    ERROR_INVALID_FLAG,
    ERROR_FILE_OPEN_FAILED,
    ERROR_MEMORY_ALLOCATION_FAILED
} StatusCode;

int compareEmployees(const void* a, const void* b) {
    Employee* emp1 = (Employee*)a;
    Employee* emp2 = (Employee*)b;

    if (emp1->salary != emp2->salary)
        return (emp1->salary < emp2->salary) ? -1 : 1;
    if (strcmp(emp1->surname, emp2->surname) != 0)
        return strcmp(emp1->surname, emp2->surname);
    if (strcmp(emp1->name, emp2->name) != 0)
        return strcmp(emp1->name, emp2->name);
    
    return (emp1->id - emp2->id);
}

void sortEmployees(Employee* employees, int count, int ascending) {
    qsort(employees, count, sizeof(Employee), compareEmployees);
    if (!ascending) {
        for (int i = 0; i < count / 2; ++i) {
            Employee temp = employees[i];
            employees[i] = employees[count - 1 - i];
            employees[count - 1 - i] = temp;
        }
    }
}

int main(int argc, char* argv[]) {
    const char* outputFile = "output_file.txt";
    char bufName[BUFSIZ], bufSurname[BUFSIZ];
    Employee* employees = NULL;
    int employeeCount = 0;
    FILE* input_file;
    FILE* output_file;

    int id;
    float salary;

    if (argc != 4) {
        printf("Usage: %s <input_file> <flag> <output_file>\n", argv[0]);
        return ERROR_INVALID_ARGUMENTS;
    }

    int ascending;
    if (strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "/a") == 0) {
        ascending = 1;
    } else if (strcmp(argv[2], "-d") == 0 || strcmp(argv[2], "/d") == 0) {
        ascending = 0;
    } else {
        printf("Invalid flag. Use ['-a'] / ['/a'] or ['-d'] / ['/d'].\n");
        return ERROR_INVALID_FLAG;
    }

    if (!(input_file = fopen(argv[1], "r"))) {
        perror("Input file cannot be opened");
        return ERROR_FILE_OPEN_FAILED;
    }

    while (fscanf(input_file, "%d %s %s %f", &id, bufName, bufSurname, &salary) == 4) {
        Employee* temp = (Employee*)realloc(employees, (employeeCount + 1) * sizeof(Employee));
        if (!temp) {
            perror("Memory allocation failed");
            free(employees);
            fclose(input_file);
            return ERROR_MEMORY_ALLOCATION_FAILED;
        }
        employees = temp;

        employees[employeeCount].id = id;
        employees[employeeCount].name = malloc(strlen(bufName) + 1);
        if (!employees[employeeCount].name) {
            perror("Memory allocation failed for name");
            free(employees);
            fclose(input_file);
            return ERROR_MEMORY_ALLOCATION_FAILED;
        }
        strcpy(employees[employeeCount].name, bufName);
        
        employees[employeeCount].surname = malloc(strlen(bufSurname) + 1);
        if (!employees[employeeCount].surname) {
            perror("Memory allocation failed for surname");
            free(employees);
            fclose(input_file);
            return ERROR_MEMORY_ALLOCATION_FAILED;
        }
        strcpy(employees[employeeCount].surname, bufSurname);
        employees[employeeCount].salary = salary;

        employeeCount++;
    }
    fclose(input_file);

    sortEmployees(employees, employeeCount, ascending);

    if (!(output_file = fopen(argv[3], "w"))) {
        perror("Output file cannot be opened");
        free(employees);
        return ERROR_FILE_OPEN_FAILED;
    }

    fprintf(output_file, "%s%20s%20s%20s\n", "Id", "Name", "Surname", "Salary");
    for (int i = 0; i < employeeCount; i++) {
        fprintf(output_file, "%2d%20s%20s%20.2f\n", employees[i].id, employees[i].name, employees[i].surname, employees[i].salary);
        free(employees[i].name);
        free(employees[i].surname);
    }

    free(employees);
    fclose(output_file);
    return SUCCESS;
}
