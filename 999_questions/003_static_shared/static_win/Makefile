CC = x86_64-w64-mingw32-gcc
all: main

main: adder.lib main.o
	$(CC) -o main main.o -static -L. -ladder

adder.lib: adder.o
	ar rcs adder.lib adder.o

adder.o: adder.h adder.c
	$(CC) -c adder.c

main.o: adder.h main.c
	$(CC) -c main.c

clean:
	rm -f main *.o *.lib
