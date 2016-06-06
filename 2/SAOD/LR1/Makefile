sort: main.o sort.o
	gcc -o sort main.o sort.o

main.o: main.c
	gcc -c main.c

sort.o: sort.c
	gcc -c sort.c

.PHONY: clean
clean:
	rm sort *.o
