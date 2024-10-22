FLAGS = -Wall -Wextra -Werror -lm -std=c99 -fsanitize=address -lcheck -lsubunit -lrt -lpthread
COMP = gcc

ex6: main.c
	$(COMP) main.c ../SystemErrors/errors.c  ../vector/stringvector.c ../vector/charvector.c test.c ex6.c $(FLAGS) -o ex6.a

