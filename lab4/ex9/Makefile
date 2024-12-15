COMP = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra -g
SPECIAL_C_FLAGS = #-fsanitize=address
LIB_FLAGS = -L../lib2 -lerrors2 -lvector2 -lmstring2 -lm
FILES = application/application.c department/*.c data-storages/*/*.c heaps/heaps.c heaps/*/*.c data-storages/data-storages.c process_files/process_files.c main_files/*.c

# find . -name "*.*" -print0 | xargs -0 wc -l

ex2: main.c
	$(COMP) $(CFLAGS) $(SPECIAL_C_FLAGS) main.c $(FILES) $(LIB_FLAGS) -o ex9


# 100 sss test_file_1 test_file_2 test_file_3 test_file_4 test_file_5

val: ex2
	valgrind -s --leak-check=full --show-leak-kinds=all ./ex9 100 sss test_file_1 test_file_2 test_file_3 test_file_4 test_file_5 test_file_6 test_file_7 test_file_8 test_file_9 test_file_10 test_file_11 test_file_12 test_file_13 test_file_14 test_file_15 test_file_16 test_file_17 test_file_18 test_file_19 test_file_20 test_file_21 test_file_22 test_file_23 test_file_24 test_file_25 test_file_26 test_file_27 test_file_28 test_file_29 test_file_30
	rm ex9

run:
	./ex9 100 sss test_file_1 test_file_2 test_file_3 test_file_4 test_file_5 test_file_6 test_file_7 test_file_8 test_file_9 test_file_10 test_file_11 test_file_12 test_file_13 test_file_14 test_file_15 test_file_16 test_file_17 test_file_18 test_file_19 test_file_20 test_file_21 test_file_22 test_file_23 test_file_24 test_file_25 test_file_26 test_file_27 test_file_28 test_file_29 test_file_30

d1: auxiliary_application_1
	$(COMP) $(CFLAGS) auxiliary_application_1/auxiliary_application_1.c $(FILES) $(LIB_FLAGS) -o d1

d2: auxiliary_application_2
	$(COMP) $(CFLAGS) auxiliary_application_2/auxiliary_application_2.c $(FILES) $(LIB_FLAGS) -o d2


clean:
	rm -f */test_file_*
	rm -f test_file_*
	rm -f d1
	rm -f d2
	rm -f ex9
