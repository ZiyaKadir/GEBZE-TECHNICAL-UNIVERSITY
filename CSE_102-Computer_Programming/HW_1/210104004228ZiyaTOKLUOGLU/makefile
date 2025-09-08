all: clean compile run

compile: main.c utils.c utils.h

	@gcc -o hw1 main.c utils.c utils.h

run:
	@./hw1

clean:
	@rm -f *.o
	@rm -f hw1
	@rm -f customeraccount.txt
