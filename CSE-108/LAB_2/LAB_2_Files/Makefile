all : clear clean compile link run

compile:
	@gcc -c Lab2.c -o main.o -lm

link:
	@gcc main.o -o main.out -lm

run :
	@./main.out

clean :
	@rm -rf main.o main.out

clear :
	@clear
