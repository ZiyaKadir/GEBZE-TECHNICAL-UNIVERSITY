
make: compile

compile: gpp_interpreter lex.yy.c y.tab.c


gpp_interpreter: lex.yy.c y.tab.c 
	gcc -g lex.yy.c y.tab.c -o gpp_interpreter

lex.yy.c: y.tab.c gpp_interpreter.l
	lex gpp_interpreter.l

y.tab.c: gpp_interpreter.y
	yacc -d gpp_interpreter.y

clean: 
	rm -rf lex.yy.c y.tab.c y.tab.h gpp_interpreter gpp_interpreter.dSYM

run: gpp_interpreter
	clear
	./gpp_interpreter