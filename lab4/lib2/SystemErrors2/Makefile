COMP = gcc
FLAGS = -c -Wall -Wextra -Werror


comp:
	$(COMP) $(FLAGS) errors.c
	ar cr liberrors2.a errors.o
	mv liberrors2.a ../
	rm *.o
