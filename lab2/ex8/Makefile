FLAGS = -Wall -Wextra -Werror -g -lm -std=c99
COMP = gcc

ex8: main.c
	$(COMP) $(FLAGS) main.c ../SystemErrors/errors.c ../vector/charvector.c ../vector/stringvector.c -lcheck -lsubunit -lrt -lm -lpthread test.c ex8.c -o ex8.a
