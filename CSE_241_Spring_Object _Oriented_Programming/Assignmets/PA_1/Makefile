SRC := Ziya_Kadir_TOKLUOGLU_PA1.cpp

TARGET := mastermind


all: clean clear compile run1


compile: $(SRC)

	@echo "======================================"
	g++ $(SRC) -o $(TARGET)
run1: compile
	@echo "======================================"
	./$(TARGET) -r 7

run2: compile

	@echo "======================================"
	./$(TARGET) -u 01345

clear:
	@echo "======================================"
	@echo "=======Clear Terminal screen=========="
	clear
clean:

	@echo "======================================"
	@echo "==========Cleaning Files=============="
	@rm -rf $(TARGET)
	@echo "======================================"