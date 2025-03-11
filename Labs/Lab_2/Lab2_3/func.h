#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_SUBSTRING_LENGTH 1024

typedef enum {
    SUCCESS = 0,
    FILE_ERROR
} Status;

int len(const char* str);
int Shift_Table(const char *template, int n, int *result);
int Substr(const char* str, int n, const char* key, int m);
int Line_Counter(const char *str, int size);
int Pos_In_Line(const char *str, int size);
int File_Handler(char *key, int m, char *filename);
void Process_Newline_In_Substring(char *substr);