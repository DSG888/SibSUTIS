CC = g++
CFLAGS = -O3 -Wall
LDFLAGS = 
SOURCES = main.cpp linkedlist.cpp queue.cpp stack.cpp
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.cpp=.o))
EXECUTABLE = LR7

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) $(OBJECT_FILES) $(LDFLAGS) $(CFLAGS) -o $@

obj/%.o: %.cpp
	$(CC) $(CFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj $(EXECUTABLE)
