counter := counter
counter_objs := counter.o

CC := gcc
CFLAGS := -g -std=c99 -O2 -fopenmp 
LDFLAGS := -lm -fopenmp

.PHONY: all clean

all: $(counter)

$(counter): $(counter_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

counter.o: counter.c

clean:
	@rm -rf *.o $(counter)
