#FIXME
#lr2: main.o bstree.o hashtab.o
#	gcc main.o bstree.o hashtab.o -o lr2 -Wall

lr2: main.o
	gcc main.o -o lr2 -Wall
#FIXME






main.o: main.c
	gcc -c main.c -o main.o -Wall

bstree.c: bstree.c
	gcc -c bstree.c -o bstree.o -Wall

hashtab.c: hashtab.c
	gcc -c hashtab.c -o hashtab.o -Wall

clean:
	rm ./*.o ./lr2

.PHONY: clean
clean:
	rm sort *.o
