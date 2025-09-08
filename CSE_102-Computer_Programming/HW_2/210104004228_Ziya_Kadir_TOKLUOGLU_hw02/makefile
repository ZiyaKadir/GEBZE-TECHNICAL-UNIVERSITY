all:clear clean compile run

compile: main.c util.c util.h

	@gcc -o hw02 main.c util.c util.h

run:
	@./hw02

clean:
	@rm -f *.o
	@rm -f hw02

clear:
	@clear
