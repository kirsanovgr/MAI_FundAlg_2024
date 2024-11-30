# Название исполняемого файла
TARGET = main

# Компилятор и флаги
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic

# Файлы проекта
SRCS = 1.c
OBJS = $(SRCS:.c=.o)

# Цель по умолчанию
all: $(TARGET)

# Компиляция исполняемого файла
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Компиляция объектных файлов
%.o: %.c func.h
	$(CC) $(CFLAGS) -c $< -o $@

# Тестирование программы
test: $(TARGET)
	./$(TARGET) input_2.txt
	./$(TARGET) input
	./$(TARGET) input_1
	./$(TARGET) input_3
	./$(TARGET) input_4


# Удаление временных файлов
clean:
	rm -f $(OBJS) $(TARGET)

# Удаление временных файлов и результата
distclean: clean
	rm -f output.txt
