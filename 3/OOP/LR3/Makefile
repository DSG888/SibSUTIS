CC = g++
CFLAGS =  -c -Wall
LDFLAGS = -lglut -lX11 -lGL -lGLU
SOURCES = main.cpp point.cpp
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.cpp=.o))
EXECUTABLE = LR3

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $@

obj/%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm -rf obj LR3
