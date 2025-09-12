# === Variables ===
CC = gcc
CFLAGS = -Wall -Wextra -g -lpthread
SRC = 210104004228_main.c utils.c buffer.c
OBJ = $(SRC:.c=.o)
TARGET = LogAnalyzer

# === Targets ===

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)


# Example runnning commands
# ./LogAnalyzer 50 8 logs/large.log "404"
# 