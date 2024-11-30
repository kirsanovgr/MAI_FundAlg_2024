#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_HASHSIZE 128

typedef struct Macro {
	char *name;
	char *value;
	struct Macro *next;
} Macro;

//для управления хеш-таблицей
extern Macro **hashtable;
extern unsigned int HASHSIZE;
extern unsigned int macro_count;

typedef enum Error {
	SUCCESS = 0,
	INCORRECT_OPTIONS = -1,
	ERROR_FILE_OPEN = -2,
	ERROR_WITH_MACROS = -3,
	ERROR_MEMORY = -4
} Status;

unsigned int hash(const char *str);
int add_macro(const char *name, const char *value);
const char *find_macro(const char *name);
void free_hashtable();
void rehash(unsigned int new_size);
int process_file(const char *filename);
void run_tests();
