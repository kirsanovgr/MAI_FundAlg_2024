#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef enum kOpts {
    OPT_L,
    OPT_R,
    OPT_U,
    OPT_N,
    OPT_C,
    OPT_INVALID
} kOpts;

typedef struct {
    kOpts option;
    unsigned int seed;
    char* str;
    char** strings;
    int count;
} ProgramOptions;

int my_strlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void my_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void my_strcat_custom(char* dest, const char* src) {
    int dest_len = my_strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

char* concatenate_strings(int start, int end, char** argv) {
    int total_length = 0;
    for (int i = start; i <= end; i++) {
        total_length += my_strlen(argv[i]) + 1;
    }

    char* result = (char*)malloc(total_length * sizeof(char));
    if (result == NULL) {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }
    result[0] = '\0';
    for (int i = start; i <= end; i++) {
        my_strcat_custom(result, argv[i]);
        if (i != end) {
            my_strcat_custom(result, " ");
        }
    }
    return result;
}

kOpts parse_option(const char* opt) {
    if (my_strlen(opt) != 2 || opt[0] != '-')
        return OPT_INVALID;
    
    switch(opt[1]) {
        case 'l': return OPT_L;
        case 'r': return OPT_R;
        case 'u': return OPT_U;
        case 'n': return OPT_N;
        case 'c': return OPT_C;
        default: return OPT_INVALID;
    }
}

int GetOpts(int argc, char** argv, ProgramOptions *options) {
    if (argc < 3) return 1;

    options->option = parse_option(argv[1]);
    if (options->option == OPT_INVALID) return 1;

    switch (options->option) {
        case OPT_L:
        case OPT_R:
        case OPT_U:
        case OPT_N:
            if (argc < 3) return 1;
            options->str = concatenate_strings(2, argc - 1, argv);
            if (!options->str) return 1;
            break;
        case OPT_C:
            if (argc < 4) return 1;
            for (int i = 0; argv[2][i] != '\0'; i++) {
                if (!isdigit((unsigned char)argv[2][i])) return 1;
            }
            options->seed = (unsigned int)atoi(argv[2]);
            options->strings = &argv[3];
            options->count = argc - 3;
            if (options->count < 1) return 1;
            break;
        default:
            return 1;
    }

    return 0;
}

// -l (подсчёт длины строки)
void HandlerOptL(ProgramOptions* options) {
    if (options->str == NULL) {
        printf("Строка для флага -l не предоставлена\n");
        return;
    }
    int n = my_strlen(options->str);
    printf("%d\n", n);
}

// -r (переворот строки)
void HandlerOptR(ProgramOptions* options) {
    if (options->str == NULL) {
        printf("Строка для флага -r не предоставлена\n");
        return;
    }
    int len = my_strlen(options->str);

    char* reversed = (char*)malloc((len + 1) * sizeof(char));
    if (reversed == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    for (int i = 0; i < len; i++) {
        reversed[i] = options->str[len - 1 - i];
    }
    reversed[len] = '\0';

    printf("%s\n", reversed);
    free(reversed);
}

// -u (четные позиции в верхний регистр)
void HandlerOptU(ProgramOptions* options) {
    if (options->str == NULL) {
        printf("Строка для флага -u не предоставлена\n");
        return;
    }
    int len = my_strlen(options->str);
    char* mod_str = (char*)malloc((len + 1) * sizeof(char));
    if (mod_str == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    my_strcpy(mod_str, options->str);

    for (int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            mod_str[i] = toupper((unsigned char)mod_str[i]);
        }
    }
    printf("%s\n", mod_str);
    free(mod_str);
}

// -n (перестановка символов)
void HandlerOptN(ProgramOptions* options) {
    if (options->str == NULL) {
        printf("Строка для флага -n не предоставлена\n");
        return;
    }
    int len = my_strlen(options->str);

    char* new_str = (char*)malloc((len + 1) * sizeof(char));
    if (new_str == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isdigit((unsigned char)options->str[i])) {
            new_str[j++] = options->str[i];
        }
    }
    for (int i = 0; i < len; i++) {
        if (isalpha((unsigned char)options->str[i])) {
            new_str[j++] = options->str[i];
        }
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)options->str[i]) && !isalpha((unsigned char)options->str[i])) {
            new_str[j++] = options->str[i];
        }
    }
    new_str[j] = '\0';

    printf("%s\n", new_str);
    free(new_str);
}

// -c (конкатенация строк в псевдослучайном порядке)
void HandlerOptC(ProgramOptions* options) {
    if (options->strings == NULL || options->count < 1) {
        printf("Строки для флага -c не предоставлены\n");
        return;
    }

    srand(options->seed);

    int* indices = (int*)malloc(options->count * sizeof(int));
    if (indices == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    for (int i = 0; i < options->count; i++) {
        indices[i] = i;
    }

    // Перемешивание с помощью Фишера-Йетса
    for (int i = options->count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    int total_length = 0;
    for (int i = 0; i < options->count; i++) {
        total_length += my_strlen(options->strings[indices[i]]);
    }

    char* concatenated = (char*)malloc((total_length + 1) * sizeof(char));
    if (concatenated == NULL) {
        printf("Ошибка выделения памяти\n");
        free(indices);
        return;
    }
    concatenated[0] = '\0';

    for (int i = 0; i < options->count; i++) {
        my_strcat_custom(concatenated, options->strings[indices[i]]);
    }

    printf("%s\n", concatenated);
    free(concatenated);
    free(indices);
}

void check_of_flag(const ProgramOptions* options) {
    void (*handlers[5])(ProgramOptions*) = {
        HandlerOptL,
        HandlerOptR,
        HandlerOptU,
        HandlerOptN,
        HandlerOptC
    };

    if (options->option >= OPT_L && options->option <= OPT_C) {
        handlers[options->option]( (ProgramOptions*)options );
    } else {
        printf("Неверный аргумент\n");
    }
}

int main(int argc, char* argv[]) {
    ProgramOptions options;
    options.str = NULL;
    options.strings = NULL;
    options.count = 0;

    if (GetOpts(argc, argv, &options)) {
        printf("Неверная опция или отсутствуют аргументы\n");
        return 1;
    }

    check_of_flag(&options);

    if (options.option == OPT_L || options.option == OPT_R || options.option == OPT_U || options.option == OPT_N) {
        free(options.str);
    }

    return 0;
}
