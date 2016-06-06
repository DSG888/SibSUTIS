.PHONY: clean prepare

all: tester2

prepare:
	mkdir -p bin
	mkdir -p obj

remake: clean all

QuadraticEquation: main.o calc.o
	gcc obj/main.o obj/calc.o -o bin/QuadraticEquation -lm
 
main.o: prepare main.o
	gcc -c src/main.c -o obj/main.o
 
calc.o: calc.o
	gcc -c src/calc.c -o obj/calc.o

tester.o: tester.o
	gcc -c test/tester2.c -o obj/tester.o

tester2: QuadraticEquation tester.o calc.o
	gcc obj/calc.o obj/tester.o -o bin/tester2 -lm

RUNTest: tester2
	bin/tester2

clean:
	rm obj/*.o bin/*
