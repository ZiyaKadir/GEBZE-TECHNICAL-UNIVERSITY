CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = fileManager


OBJS = main.o directory_management.o secure_file.o log_operation.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)

.PHONY: clean run
