#include "func.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Использование: %s <входной файл> <выходной файл>\n", argv[0]);
    return INPUT_ERROR;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Ошибка открытия входного файла");
        return INPUT_ERROR;
    }

    FILE* output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        perror("Ошибка открытия выходного файла");
        fclose(input_file);
        return INPUT_ERROR;
    }

    char line[MAX_STACK_SIZE];
    while (fgets(line, sizeof(line), input_file)) {
        Node* tree = ParseExpression(line);
        PrintTree(output_file, tree, 0);  // Выводим дерево в файл
        FreeTree(tree);  // Освобождаем память дерева
    }

    fclose(input_file);
    fclose(output_file);

    return SUCCESS;
}