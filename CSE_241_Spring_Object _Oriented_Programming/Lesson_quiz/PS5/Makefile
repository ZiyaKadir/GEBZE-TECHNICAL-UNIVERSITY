all : clear clean compile run1


compile: q1.cpp q2.cpp

	@g++ q1.cpp -o run1
	@g++ q2.cpp -o run2


run1: compile

	@./run1

run2: compile

	@./run2

clean:

	@rm -rf run1 run2

clear:

	@clear