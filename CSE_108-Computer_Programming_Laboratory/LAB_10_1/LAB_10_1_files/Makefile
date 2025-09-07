CC = gcc
CFLAGS = -g -Wall
TARGET = lab10
SOURCE = lab10.c
OBJECT = lab10.o

all: clear clean compile link run

compile:
	@$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

link:
	@$(CC) $(CFLAGS) $(OBJECT) -o $(TARGET) -lm

run:
	@./$(TARGET)

clean:
	@rm -rf $(OBJECT) $(TARGET)

clear:
	@clear

valgrind: clear clean compile link
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

.PHONY: all compile link run clean clear valgrind