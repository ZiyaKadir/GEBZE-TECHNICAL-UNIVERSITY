CC = gcc
CFLAGS  = -Wall -g -Iinclude 

LDFLAGS = -pthread -lrt -lm

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = src/obj
CLIENT_FILES_DIR = ClientFolder

# Executable names
SERVER = $(SRC_DIR)/server
CLIENT = $(SRC_DIR)/client

# Source files
SERVER_SRCS = $(SRC_DIR)/server.c $(SRC_DIR)/Parse_server.c $(SRC_DIR)/Parse_client.c $(SRC_DIR)/BinaryTree.c $(SRC_DIR)/IPC_communication.c  $(SRC_DIR)/teller.c  $(SRC_DIR)/shm_comm.c  $(SRC_DIR)/helper_log.c  
CLIENT_SRCS = $(SRC_DIR)/client.c  $(SRC_DIR)/Parse_client.c $(SRC_DIR)/IPC_communication.c 

# SERVER_SRCS = $(SRC_DIR)/Server_part.c $(SRC_DIR)/Parse_server.c $(SRC_DIR)/BinaryTree.c $(SRC_DIR)/bank_ipc.c $(SRC_DIR)/teller.c 
# CLIENT_SRCS = $(SRC_DIR)/Client_part.c $(SRC_DIR)/Parse_client.c $(SRC_DIR)/bank_ipc.c

# Object files
SERVER_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SERVER_SRCS))
CLIENT_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(CLIENT_SRCS))

# Header files
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

# Default target
all: setup server client

# Create directories
setup:
	@mkdir -p $(OBJ_DIR)

# Build server
server: setup $(SERVER)

# Build client
client: setup $(CLIENT)

# Build server executable
$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Build client executable
$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ_DIR)/*.o $(SERVER) $(CLIENT)

# Clean server only
clean-server:
	rm -f $(SERVER) $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SERVER_SRCS))

# Clean client only
clean-client:
	rm -f $(CLIENT) $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(CLIENT_SRCS))

valgrind-server: $(SERVER)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(SERVER) ClientFolder/DATABASE.csv /tmp/ServerFIFO

valgrind-client: $(CLIENT)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(CLIENT) ClientFolder/Client01.file /tmp/ServerFIFO

# Test server
run-server: $(SERVER)
	./$(SERVER) ClientFolder/DATABASE.csv /tmp/ServerFIFO

# Test client with sample client file
run-client: $(CLIENT)
	./$(CLIENT) $(CLIENT_FILES_DIR)/Client01.file /tmp/ServerFIFO

# Test client with sample client file
run-client2: $(CLIENT)
	./$(CLIENT) $(CLIENT_FILES_DIR)/Client02.file /tmp/ServerFIFO

# Test client with sample client file
run-client3: $(CLIENT)
	./$(CLIENT) $(CLIENT_FILES_DIR)/Client03.file /tmp/ServerFIFO

.PHONY: all setup clean clean-server clean-client server client run-server run-client