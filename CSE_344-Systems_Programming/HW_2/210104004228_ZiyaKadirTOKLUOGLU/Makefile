CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = ipc_daemon

all: $(TARGET)

$(TARGET): ipc_daemon.c
	$(CC) $(CFLAGS) -o $(TARGET) ipc_daemon.c

clean:
	rm -f $(TARGET)
	rm -f /tmp/fifo1
	rm -f /tmp/fifo2
	rm -rf /tmp/daemon_log

.PHONY: all clean