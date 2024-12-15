COMP = gcc
FLAGS = -c -Wall -Wextra -Werror


comp:
	$(COMP) $(FLAGS) errors.c
	ar cr liberrors.a errors.o
	mv liberrors.a ../
	rm *.o
