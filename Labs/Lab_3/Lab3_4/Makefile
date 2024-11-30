FLAGS = -Wall -Wextra -Werror -g -lm -lcheck -lsubunit -lrt -lpthread -D_POSIX_C_SOURCE=200809L
COMP = gcc

Lab3_4: 4.c
	$(COMP) $(FLAGS) main.c 4.c my_string.c -o 4.a

#-D_POSIX_C_SOURCE=200809L - какая-то фигня, чтобы работать со временемы