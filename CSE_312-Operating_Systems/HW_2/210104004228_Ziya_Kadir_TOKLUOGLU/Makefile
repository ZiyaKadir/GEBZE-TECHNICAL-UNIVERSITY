# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra -Werror

# Source files
SRCS := $(filter-out main.cpp main2.cpp, $(wildcard *.cpp))

# Object files
OBJS := $(SRCS:.cpp=.o)

ARGS := 4 mySystem.dat /home/ziya/Desktop/OS_HW1
ARGS_DIR := mySystem.dat dir “/src”
ARGS_DUMP2FS := mySystem.dat dumpe2fs
ARGS_READ := mySystem.dat read “/src” linuxFile2.data



# Target executable
TARGET:= makeFileSystem
TARGET_2 := fileSystemOper


run1: compile1
	./$(TARGET) $(ARGS)

run2: compile2
	./$(TARGET_2) $(ARGS_DIR)


compile1: $(OBJS)
	g++	-c -o main.o main.cpp
	g++  main.o $(OBJS) -o $(TARGET) 

compile2: $(OBJS)
	g++	-c -o main2.o main2.cpp
	g++ main2.o $(OBJS) -o $(TARGET_2) 

# Clean up object files and the target executable
clean:
	rm -f *.o $(TARGET) $(TARGET_2)
	rm -f mySystem.dat
	



