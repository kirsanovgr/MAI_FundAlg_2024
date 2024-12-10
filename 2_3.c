#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <linux/limits.h>

typedef enum errCodes{
    UNABLE_OPEN_FILE,
    MALLOC_ERR,
    REALLOC_ERR,
    SUBSTR_ERR,
    SUCCESS
}errCodes;

errCodes is_same_file(char *a, char *b){
    errCodes res = SUCCESS;
    char input_path[PATH_MAX];
    char output_path[PATH_MAX];
    realpath(a, input_path);
    realpath(b, output_path);
    int is_not_same = 0;

    for (int i = 0; (input_path[i] && output_path[i]); i++) {
        if (input_path[i] != output_path[i]) is_not_same = 1;
    }
    if (!is_not_same) res = UNABLE_OPEN_FILE;

    return res;
}

int get_len(const char* str){
    int len = 0;
    for (int i = 0; str[i]; i++) len++;
    return len;
}

int compare_strings(const char* str1, const char* str2){
    while (*str2 != '\0'){
        if (*str1 != *str2) return 0;
        str1++;
        str2++;
    }
    return 1;
}

errCodes find_str(const char* file_name, const char* str, char*** out_strings){
    FILE *file = fopen(file_name, "r");
    if (file == NULL) return UNABLE_OPEN_FILE;

    int mem_size = 10;
    char** out_msg = malloc(sizeof(char*) * (mem_size + 1));
    if (!out_msg) {
        fclose(file);
        return MALLOC_ERR;
    }
    int count = 0;

    fseek(file, 0, SEEK_END);
    long int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + sizeof(char));
    if(!buffer){
        fclose(file);
        free(out_msg);
        return MALLOC_ERR;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    int line_index = 1;
    int chars_in_line = 1;
    int str_len = get_len(str);

    for(int i = 0; i <= file_size - str_len; i++){
        if(compare_strings(&buffer[i], str)){
            char* msg = malloc(sizeof(char) * 200);
            if (!msg) {
                fclose(file);
                for (int j = 0; j < count; j++) free(out_msg[j]);
                free(out_msg);
                free(buffer);
                return MALLOC_ERR;
            }
            sprintf(msg, "Файл: %s, строка: %d, cимвол: %d", file_name, line_index, chars_in_line);
            if(mem_size <= count + 1) {
                mem_size *= 2;
                char** temp = realloc(out_msg, sizeof(char*) * (mem_size + 1));
                if (!temp) {
                    fclose(file);
                    for (int j = 0; j < count; j++) free(out_msg[j]);
                    free(out_msg);
                    free(buffer);
                    return REALLOC_ERR;
                }
                out_msg = temp;
            }
            out_msg[count] = msg;
            count++;
        }

        if (buffer[i] == '\n') {
            line_index++;
            chars_in_line = 1;
        } else chars_in_line++;
    }
    out_msg[count] = NULL;

    fclose(file);
    free(buffer);
    *out_strings = out_msg;

    return SUCCESS;
}

errCodes find_str_in_files(const char* str, char*** result, const int n, ...){
    if (get_len(str) <= 0) return SUBSTR_ERR;

    int mem_size = 10;
    int count = 0;
    char **out_msg = malloc(sizeof(char*) * (mem_size + 1));
    if (!out_msg) return MALLOC_ERR;

    va_list list;
    va_start(list, n);
    for (int i = 0; i < n; i++){
        char* file_name = va_arg(list, char*);

        char** messages;
        errCodes err_status = find_str(file_name, str, &messages);
        if (err_status != SUCCESS) {
            for (int k = 0; k < count; k++) free(out_msg[k]);
            free(out_msg);
            va_end(list);
            return err_status;
        }
        for (int j = 0; messages[j]; j++){
            if (count + 1 >= mem_size){
                mem_size *= 2;
                char** temp = realloc(out_msg, sizeof(char*) * (mem_size + 1));
                if(!temp){
                    for (int k = 0; k < count; k++) free(out_msg[k]);
                    free(out_msg);
                    return REALLOC_ERR;
                }
                out_msg = temp;
            }
            out_msg[count] = messages[j];
            count++;
        }
        free(messages);
    }
    va_end(list);
    out_msg[count] = NULL;

    *result = out_msg;

    return SUCCESS;
}

int main(int argc, char** argv){
    char **result;
    errCodes status = find_str_in_files("AXXAXAXAXXAxAX", &result, 4, "2_3.1.txt", "2_3.2.txt", "2_3.3.txt", "2_3.4.txt");
    if (status != SUCCESS){
        switch (status){
        case MALLOC_ERR:
            printf("Malloc error occured!\n");
            break;
        case REALLOC_ERR:
            printf("Realloc error occured!\n");
            break;
        case UNABLE_OPEN_FILE:
            printf("Cannot open file!\n");
            break;
        case SUBSTR_ERR:
            printf("The substring must not be empty!\n");
            break;
        default:
            break;
        }
        return 1;
    }

    for (int i = 0; result[i]; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    };
    free(result);

    return 0;
}
