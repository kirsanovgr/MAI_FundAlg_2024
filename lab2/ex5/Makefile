FLAGS = -Wall -Wextra -Werror -g -lm -std=c99 -fsanitize=address -lcheck -lsubunit -lrt -lpthread
COMP = gcc

ex5: main.c
	$(COMP) main.c ../SystemErrors/errors.c  ../vector/stringvector.c overloads.c test.c $(FLAGS) -o ex5.a
