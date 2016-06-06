.PHONY: clean

bin/QuadraticEquation: obj/main.o obj/equation.o
	mkdir -p bin
	gcc obj/main.o obj/equation.o -o bin/QuadraticEquation -lm

obj/main.o: src/main.c
	mkdir -p obj
	gcc -c src/main.c -o obj/main.o

obj/equation.o: src/equation.c
	mkdir -p obj
	gcc -c src/equation.c -o obj/equation.o

all: bin/QuadraticEquation

clean:
	rm ./obj/*.o ./bin/*
