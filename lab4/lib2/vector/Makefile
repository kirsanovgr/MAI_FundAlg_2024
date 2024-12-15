COMP = gcc
FLAGS = -c -Wall -Wextra -Werror


comp:
	$(COMP) $(FLAGS) intvector.c
	$(COMP) $(FLAGS) charvector.c
	$(COMP) $(FLAGS) stringvector.c
	ar crs libvector2.a intvector.o charvector.o stringvector.o
	mv libvector2.a ../
	rm *.o
