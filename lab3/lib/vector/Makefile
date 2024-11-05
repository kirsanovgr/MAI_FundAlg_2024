COMP = gcc
FLAGS = -c -Wall -Wextra -Werror


comp:
	$(COMP) $(FLAGS) intvector.c
	$(COMP) $(FLAGS) charvector.c
	$(COMP) $(FLAGS) stringvector.c
	ar crs libvector.a intvector.o charvector.o stringvector.o
	mv libvector.a ../
	rm *.o
