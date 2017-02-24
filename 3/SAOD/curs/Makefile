CC = gcc
CFLAGS = -O0 -Wall
LDFLAGS = -lm
SOURCES = main.c aatree.c bstree.c rbtree.c tester.c visual.c
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.c=.o))
EXECUTABLE = curs

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) $(OBJECT_FILES) $(LDFLAGS) $(CFLAGS) -o $@

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj $(EXECUTABLE)
