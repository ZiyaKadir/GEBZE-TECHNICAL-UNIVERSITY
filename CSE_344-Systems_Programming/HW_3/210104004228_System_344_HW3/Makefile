CC = gcc
CFLAGS = -Wall -pthread -g
TARGET = satellite_system
SRCS = main.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Check for memory leaks with Valgrind
memcheck: $(TARGET)
	valgrind --tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		./$(TARGET)

# Quick memory leak check with minimal output
leakcheck: $(TARGET)
	valgrind --leak-check=yes ./$(TARGET)

clean:
	rm -f $(TARGET) *.o valgrind_output.txt

.PHONY: clean run memcheck leakcheck