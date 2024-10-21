FLAGS = -Wall -Wextra -Werror -g -lm
COMP = gcc

ex5: main.c
	$(COMP) $(FLAGS) main.c ../SystemErrors/errors.c  ../vector/stringvector.c ../vector/charvector.c overloads.c -lcheck -lsubunit -lrt -lm -lpthread -lm test.c -o ex5.a
