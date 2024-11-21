COMP = gcc
FLAGS = -c -Wall -Wextra -Werror


comp:
	$(COMP) $(FLAGS) mstring.c
	ar cr libmstring2.a mstring.o
	mv libmstring2.a ../
	rm *.o
