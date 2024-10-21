FLAGS = -Wall -Wextra -Werror -g -lm -std=c99
COMP = gcc

ex6: main.c
	$(COMP) $(FLAGS) main.c ../SystemErrors/errors.c  ../vector/stringvector.c ../vector/charvector.c -lcheck -lsubunit -lrt -lm -lpthread test.c ex6.c -o ex6.a
