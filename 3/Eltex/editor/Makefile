CC = gcc
CFLAGS =  -c -Wall
LDFLAGS = -lcurses
SOURCES = main.c edit.c
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.c=.o))
EXECUTABLE = editor

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $@

obj/%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -rf obj $(EXECUTABLE)
