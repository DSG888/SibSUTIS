CC = gcc
CFLAGS = -O0 -g2 -Wall
LDFLAGS = -lncurses -lpthread
SOURCES = main.c fm.c
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.c=.o))
EXECUTABLE = FM

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) $(OBJECT_FILES) $(LDFLAGS) $(CFLAGS) -o $@

obj/%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -rf obj $(EXECUTABLE)
