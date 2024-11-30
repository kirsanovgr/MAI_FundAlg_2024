#include <stdio.h>
#include "func.h"

int main() {
    printf("Testing overfscanf:\n");

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return ERROR_WITH_FILE;
    }

    int roman, base, zeckendorf;
    overfscanf(file, "%Ro", &roman);
    printf("Roman number: %d\n", roman);

    overfscanf(file, "%Zg", &zeckendorf);
    printf("Zeckendorf number: %d\n", zeckendorf);

    overfscanf(file, "%Cv", &base, 8);
    printf("Base number: %d\n", base);

    fclose(file);

    printf("\nTesting oversscanf:\n");

    oversscanf("XIII", "%Ro", &roman);
    printf("Roman number: %d\n", roman);

    oversscanf("100101", "%Zg", &zeckendorf);
    printf("Zeckendorf number: %d\n", zeckendorf);

    oversscanf("12345", "%Cv", &base, 8);
    printf("Base number: %d\n", base);

    return SUCCESS;
}
