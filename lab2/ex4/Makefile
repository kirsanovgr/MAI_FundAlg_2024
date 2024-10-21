FLAGS = -Wall -Wextra -g -lm -std=c99
COMP = gcc

ex4: main.c
	$(COMP) $(FLAGS) main.c ../SystemErrors/errors.c ../vector/charvector.c ../vector/stringvector.c ex4.c -lcheck -lsubunit -lrt -lm -lpthread -lm test.c -o ex4.a
