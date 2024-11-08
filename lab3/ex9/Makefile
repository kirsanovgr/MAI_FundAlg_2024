CFLAGS = -Wall -Wextra -g -lm -std=c99
LIBS_FLAG = -lerrors -lvector -lmstring -L../lib
TEST_FLAGS = -lcheck -lsubunit -lrt -lpthread `pkg-config --cflags --libs check`

COMP = gcc

ex8: main.c
	$(COMP) $(CFLAGS) main.c ex9.c -o ex9.a $(LIBS_FLAG)
	#valgrind --leak-check=full --show-leak-kinds=all ./ex9.a test "," "." "1" ";" "(" ")" "[" "]"
	#rm *a