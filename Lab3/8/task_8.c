#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024

typedef struct PolynomialTerm {
    int coeff;
    int power;
    struct PolynomialTerm *next;
} PolynomialTerm;

PolynomialTerm* createTerm(int coeff, int power) {
    PolynomialTerm* newTerm = (PolynomialTerm*) malloc(sizeof(PolynomialTerm));
    if (newTerm == NULL) {
        printf("Error: Memory allocation failed!\n");
        return NULL;
    }
    newTerm->coeff = coeff;
    newTerm->power = power;
    newTerm->next = NULL;
    return newTerm;
}

void freePolynomial(PolynomialTerm* poly) {
    while (poly != NULL) {
        PolynomialTerm* temp = poly;
        poly = poly->next;
        free(temp);
    }
}

PolynomialTerm* addTerm(PolynomialTerm *poly, int coeff, int power) {
    if (coeff == 0) return poly;

    PolynomialTerm *newTerm = createTerm(coeff, power);
    if (newTerm == NULL) return poly;
    
    if (poly == NULL || poly->power < power) {
        newTerm->next = poly;
        return newTerm;
    }

    PolynomialTerm *prev = NULL, *current = poly;
    while (current != NULL && current->power >= power) {
        if (current->power == power) {
            current->coeff += coeff;
            free(newTerm);
            return poly;
        }
        prev = current;
        current = current->next;
    }
    newTerm->next = current;
    if (prev != NULL) {
        prev->next = newTerm;
    }
    return poly;
}

void printPolynomial(PolynomialTerm *poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    int first = 1;
    for (PolynomialTerm *p = poly; p != NULL; p = p->next) {
        if (!first && p->coeff > 0) printf("+");
        if (p->power == 0) printf("%d", p->coeff);
        else if (p->power == 1) printf("%dx", p->coeff);
        else printf("%dx^%d", p->coeff, p->power);
        first = 0;
    }
    printf("\n");
}

PolynomialTerm* addPolynomials(PolynomialTerm *poly1, PolynomialTerm *poly2) {
    PolynomialTerm *result = NULL;
    while (poly1 != NULL) {
        result = addTerm(result, poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        result = addTerm(result, poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }
    return result;
}

PolynomialTerm* subtractPolynomials(PolynomialTerm *poly1, PolynomialTerm *poly2) {
    PolynomialTerm *result = NULL;
    while (poly1 != NULL) {
        result = addTerm(result, poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        result = addTerm(result, -poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }
    return result;
}

PolynomialTerm* multiplyPolynomials(PolynomialTerm *poly1, PolynomialTerm *poly2) {
    PolynomialTerm *result = NULL;
    for (PolynomialTerm *p1 = poly1; p1 != NULL; p1 = p1->next) {
        for (PolynomialTerm *p2 = poly2; p2 != NULL; p2 = p2->next) {
            result = addTerm(result, p1->coeff * p2->coeff, p1->power + p2->power);
        }
    }
    return result;
}

PolynomialTerm* dividePolynomials(PolynomialTerm *poly1, PolynomialTerm *poly2) {
    if (poly2 == NULL || poly2->coeff == 0) {
        printf("Error: Division by zero polynomial!\n");
        return NULL;
    }
    PolynomialTerm *quotient = NULL;
    PolynomialTerm *remainder = poly1;
    while (remainder != NULL && remainder->power >= poly2->power) {
        int coeff = remainder->coeff / poly2->coeff;
        int power = remainder->power - poly2->power;
        quotient = addTerm(quotient, coeff, power);

        PolynomialTerm *subPoly = createTerm(coeff, power);
        PolynomialTerm *tempPoly = poly2;
        PolynomialTerm *subList = NULL;
        while (tempPoly != NULL) {
            subList = addTerm(subList, tempPoly->coeff * coeff, tempPoly->power + power);
            tempPoly = tempPoly->next;
        }
        remainder = subtractPolynomials(remainder, subList);
        freePolynomial(subList);
    }
    return quotient;
}

PolynomialTerm* modPolynomials(PolynomialTerm *poly1, PolynomialTerm *poly2) {
    if (poly2 == NULL || poly2->coeff == 0) {
        printf("Error: Division by zero polynomial!\n");
        return NULL;
    }

    PolynomialTerm *remainder = poly1;
    while (remainder != NULL && remainder->power >= poly2->power) {
        int coeff = remainder->coeff / poly2->coeff;
        int power = remainder->power - poly2->power;

        PolynomialTerm *subPoly = createTerm(coeff, power);
        PolynomialTerm *tempPoly = poly2;
        PolynomialTerm *subList = NULL;
        while (tempPoly != NULL) {
            subList = addTerm(subList, tempPoly->coeff * coeff, tempPoly->power + power);
            tempPoly = tempPoly->next;
        }
        remainder = subtractPolynomials(remainder, subList);
        freePolynomial(subList);
    }
    return remainder;
}

int evaluatePolynomial(PolynomialTerm *poly, int x) {
    int result = 0;
    for (PolynomialTerm *p = poly; p != NULL; p = p->next) {
        result += p->coeff * (int)pow(x, p->power);
    }
    return result;
}

PolynomialTerm* differentiatePolynomial(PolynomialTerm *poly) {
    PolynomialTerm *result = NULL;
    for (PolynomialTerm *p = poly; p != NULL; p = p->next) {
        if (p->power > 0) {
            result = addTerm(result, p->coeff * p->power, p->power - 1);
        }
    }
    return result;
}

PolynomialTerm* composePolynomials(PolynomialTerm *poly1, PolynomialTerm *poly2) {
    PolynomialTerm *result = NULL;
    for (PolynomialTerm *p1 = poly1; p1 != NULL; p1 = p1->next) {
        PolynomialTerm *termPoly = NULL;
        int coeff = p1->coeff;
        for (int i = 0; i < p1->power; i++) {
            termPoly = multiplyPolynomials(termPoly == NULL ? poly2 : termPoly, poly2);
        }
        termPoly = addTerm(termPoly, coeff, 0);
        result = addPolynomials(result, termPoly);
        freePolynomial(termPoly);
    }
    return result;
}

void skipWhitespaceAndComments(FILE *file) {
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '%') {
            while ((c = fgetc(file)) != '\n' && c != EOF) {
            }
        } else if (c == '[') {
            while ((c = fgetc(file)) != ']' && c != EOF) {
            }
        } else if (!isspace(c)) {
            ungetc(c, file);
            break;
        }
    }
}

PolynomialTerm* parsePolynomial(const char *str) {
    PolynomialTerm *poly = NULL;
    int coeff = 0, power = 0, sign = 1;
    const char *ptr = str;

    while (*ptr) {
        if (*ptr == '-') {
            sign = -1;
            ptr++;
        } else if (*ptr == '+') {
            sign = 1;
            ptr++;
        }
        if (isdigit(*ptr) || *ptr == 'x') {
            coeff = 0;
            if (isdigit(*ptr)) {
                while (isdigit(*ptr)) {
                    coeff = coeff * 10 + (*ptr - '0');
                    ptr++;
                }
                coeff *= sign;
            } else {
                coeff = sign;
            }
        }

        power = 0;
        if (*ptr == 'x') {
            ptr++;
            if (*ptr == '^') {
                ptr++;
                while (isdigit(*ptr)) {
                    power = power * 10 + (*ptr - '0');
                    ptr++;
                }
            } else {
                power = 1;
            }
        }

        poly = addTerm(poly, coeff, power);
    }
    return poly;
}

void removeSpaces(char* source) {
    char* i = source;
    char* j = source;
    while (*j != '\0') {
        if (*j != ' ') {
            *i = *j;
            i++;
        }
        j++;
    }
    *i = '\0';
}

void processCommand(const char *command, PolynomialTerm **accumulator) {
    char cmd[MAX_COMMAND_LENGTH];
    char arg1[MAX_COMMAND_LENGTH];
    char arg2[MAX_COMMAND_LENGTH];

    char tempCommand[MAX_COMMAND_LENGTH];
    strncpy(tempCommand, command, MAX_COMMAND_LENGTH);
    tempCommand[MAX_COMMAND_LENGTH - 1] = '\0';
    removeSpaces(tempCommand);

    if (tempCommand[0] == '%' || (strchr(tempCommand, '[') && !strchr(tempCommand, ']'))) {
        return;
    }

    if (sscanf(tempCommand, "%[^'('](%[^','],%[^')'])", cmd, arg1, arg2) == 3) {
        PolynomialTerm *poly1 = parsePolynomial(arg1);
        PolynomialTerm *poly2 = parsePolynomial(arg2);

        if (strcmp(cmd, "Add") == 0) {
            *accumulator = addPolynomials(poly1, poly2);
            printf("Add result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Sub") == 0) {
            *accumulator = subtractPolynomials(poly1, poly2);
            printf("Sub result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Mult") == 0) {
            *accumulator = multiplyPolynomials(poly1, poly2);
            printf("Mult result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Div") == 0) {
            *accumulator = dividePolynomials(poly1, poly2);
            printf("Div result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Mod") == 0) {
            *accumulator = modPolynomials(poly1, poly2);
            printf("Mod result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Cmps") == 0) {
            *accumulator = composePolynomials(poly1, poly2);
            printf("Cmps result: ");
            printPolynomial(*accumulator);
        }
        freePolynomial(poly1);
        freePolynomial(poly2);
    }
    else if (sscanf(tempCommand, "%[^'('](%[^')'])", cmd, arg1) == 2) {
        PolynomialTerm *poly = parsePolynomial(arg1);

        if (strcmp(cmd, "Add") == 0) {
            if (*accumulator == NULL) {
                *accumulator = createTerm(0, 0);
            }
            *accumulator = addPolynomials(*accumulator, poly);
            printf("Add result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Sub") == 0) {
            if (*accumulator == NULL) {
                *accumulator = createTerm(0, 0);
            }
            *accumulator = subtractPolynomials(*accumulator, poly);
            printf("Sub result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Mult") == 0) {
            if (*accumulator == NULL) {
                *accumulator = createTerm(0, 0);
            }
            *accumulator = multiplyPolynomials(*accumulator, poly);
            printf("Mult result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Div") == 0) {
            if (*accumulator == NULL) {
                *accumulator = createTerm(0, 0);
            }
            *accumulator = dividePolynomials(*accumulator, poly);
            printf("Div result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Mod") == 0) {
            if (*accumulator == NULL) {
                *accumulator = createTerm(0, 0);
            }
            *accumulator = modPolynomials(*accumulator, poly);
            printf("Mod result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Eval") == 0) {
            if (*accumulator == NULL) {
                *accumulator = createTerm(0, 0);
            }
            int x = atoi(arg1);
            int result = evaluatePolynomial(*accumulator, x);
            printf("Eval result: %d\n", result);
        } else if (strcmp(cmd, "Diff") == 0) {
            if (*accumulator == NULL) {
                *accumulator = createTerm(0, 0);
            }
            *accumulator = differentiatePolynomial(*accumulator);
            printf("Diff result: ");
            printPolynomial(*accumulator);
        } else if (strcmp(cmd, "Cmps") == 0) {
            if (*accumulator == NULL) {
                *accumulator = createTerm(0, 0);
            }
            if (composePolynomials(*accumulator, poly)) {
                printf("Polynomials are equal.\n");
            } else {
                printf("Polynomials are not equal.\n");
            }
        } else {
            printf("Error: Invalid command format!\n");
        }
        freePolynomial(poly);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    PolynomialTerm *accumulator = NULL;
    char command[MAX_COMMAND_LENGTH];
    while (fgets(command, sizeof(command), file) != NULL) {
        skipWhitespaceAndComments(file);
        processCommand(command, &accumulator);
    }

    fclose(file);
    freePolynomial(accumulator);
    return 0;
}