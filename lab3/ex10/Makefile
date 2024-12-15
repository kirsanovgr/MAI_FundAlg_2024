CFLAGS = -Wall -Wextra -g -lm -std=c99
LIBS_FLAG = -lerrors -lvector -lmstring -L../lib

COMP = gcc


ex10: main.c
	$(COMP) $(CFLAGS) main.c ex10.c -o ex10.a $(LIBS_FLAG)
	valgrind --leak-check=full --show-leak-kinds=all ./ex10.a test result
	rm *a

