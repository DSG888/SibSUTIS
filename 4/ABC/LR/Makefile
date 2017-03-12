CC = gcc
CFLAGS =  -g2
LDFLAGS = -lncursesw
SOURCES = main.c memory.c cpu.c terminal.c keyboard.c BigChars.c
OBJECT_FILES = $(addprefix obj/, $(SOURCES:.c=.o))
EXECUTABLE = myEVM

all: obj lib lib/libterminal.a lib/libmemory.a lib/libevm.a lib/libBigChars.a $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

lib:
	mkdir lib

$(EXECUTABLE): $(OBJECT_FILES) 
	$(CC) obj/main.o lib/libterminal.a lib/libmemory.a lib/libevm.a lib/libBigChars.a $(LDFLAGS) $(CFLAGS) -o $@

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

lib/libterminal.a: $(OBJECT_FILES)
	ar rc lib/libterminal.a obj/terminal.o && ranlib lib/libterminal.a

lib/libmemory.a: $(OBJECT_FILES)
	ar rc lib/libmemory.a obj/memory.o obj/cpu.o && ranlib lib/libmemory.a

lib/libevm.a: $(OBJECT_FILES)
	ar rc lib/libevm.a obj/keyboard.o && ranlib lib/libevm.a

lib/libBigChars.a: $(OBJECT_FILES)
	ar rc lib/libBigChars.a obj/BigChars.o && ranlib lib/libBigChars.a



clean:
	rm -rf obj lib $(EXECUTABLE)
