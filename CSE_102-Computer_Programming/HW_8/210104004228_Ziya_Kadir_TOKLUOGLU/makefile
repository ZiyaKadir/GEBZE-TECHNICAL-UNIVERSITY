all:clean clear compile run

compile: main.c util.c util.h

	@gcc -o hw08 main.c util.c util.h

run:
	@./hw08

clean:
	@rm -f *.o
	@rm -f hw08

clear:
	@clear
