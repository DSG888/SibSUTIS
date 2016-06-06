all :	LR

LR: prog.o prog.o input_output.o processing.o string.o
	gcc -o prog prog.o input_output.o processing.o string.o
	rm *.o

Test: prog.o prog.o input_output.o processing.o string.o
	gcc -o prog prog.o input_output.o processing.o string.o

prog.o: prog.c
	gcc -c prog.c

input_output.o: input_output.c
	gcc -c input_output.c

processing.o: processing.c
	gcc -c processing.c

string.o: string.c
	gcc -c string.c

.PHONY: clean
clean:
	rm sort *.o
