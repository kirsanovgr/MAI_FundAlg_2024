COMP = gcc
FLAGS = -c -Wall -Wextra -Werror


comp:
	$(COMP) $(FLAGS) mstring.c
	ar cr libmstring.a mstring.o
	mv libmstring.a ../
	rm *.o
