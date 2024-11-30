# Название исполняемого файла
TARGET = vector_test

# Компилятор и флаги
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic

# Файлы проекта
SRCS = main.cpp 6.cpp
OBJS = $(SRCS:.cpp=.o)

# Цель по умолчанию
all: $(TARGET)

# Компиляция исполняемого файла
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Компиляция объектных файлов
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка временных файлов
clean:
	rm -f $(OBJS) $(TARGET)

# Полная очистка
distclean: clean
	rm -f *.txt
