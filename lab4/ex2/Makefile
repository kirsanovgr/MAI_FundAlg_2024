CFLAGS = -Wall -Wextra -Werror -g -lm -std=c99
COMP = gcc
LIB_FLAGS = -lerrors -lmstring -lvector -L../lib


ex2:
	$(COMP) $(CFLAGS) main.c ex2.c $(LIB_FLAGS) -o ex2.a


val: main.c
	$(COMP) $(CFLAGS) main.c ex2.c $(LIB_FLAGS) -o ex2.a
	valgrind --leak-check=full --show-leak-kinds=all ./ex2.a test
	rm ex2.a
	rm out*.txt