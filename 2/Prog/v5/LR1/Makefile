CC = gcc
CFLAGS =  -c -Wall
LDFLAGS = 
SOURCES = check.c check_func.c input.c main.c output.c process.c strings.c
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.c=.o))
EXECUTABLE = LR1

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) $(LDFLAGS) $(OBJECT_FILES) -o $@

obj/%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -rf obj LR1
