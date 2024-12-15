CFLAGS = -Wall -Wextra -Werror -g -lm -std=c99
COMP = gcc
LIB_FLAGS = -lerrors2 -lmstring2 -lvector2 -L../lib2


ex7:
	$(COMP) $(CFLAGS) main.c ex7.c $(LIB_FLAGS) -o ex7.a


val: main.c
	$(COMP) $(CFLAGS) main.c ex7.c $(LIB_FLAGS) -o ex7.a
	valgrind --leak-check=full --show-leak-kinds=all ./ex7.a test
	rm ex7.a