CC = /opt/mpich-3.1.4/bin/mpicc
CFLAGS = -O2 -Wall -std=c11
LDFLAGS = -lm $(NBYTE) $(MPI_BC)
SOURCES = main.c
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.c=.o))
EXECUTABLE = msg

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) $(OBJECT_FILES) $(LDFLAGS) $(CFLAGS) -o $@

obj/%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -rf obj $(EXECUTABLE)
