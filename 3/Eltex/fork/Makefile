CC = gcc
CFLAGS = -Wall
LDFLAGS = 
SOURCES = main.c list.c
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.c=.o))
EXECUTABLE = fork

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $@

obj/%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -rf obj $(EXECUTABLE)
