CC = gcc
CFLAGS =  -g2 -Wall
LDFLAGS = -lncursesw
SOURCES = main.c memory.c cpu.c
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.c=.o))
EXECUTABLE = myEVM

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) $(OBJECT_FILES) $(LDFLAGS) $(CFLAGS) -o $@

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj $(EXECUTABLE)
