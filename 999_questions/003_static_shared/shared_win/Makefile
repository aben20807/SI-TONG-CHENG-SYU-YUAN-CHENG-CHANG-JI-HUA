CC = x86_64-w64-mingw32-gcc
all: main

main: main.o adder.dll
	$(CC) -o main main.o -L. -ladder -Wl,-rpath=.

adder.dll: adder.o
	$(CC) -o adder.dll -shared adder.o

adder.o: adder.h adder.c
	$(CC) -c -fPIC adder.c

main.o: main.c
	$(CC) -c main.c

clean:
	rm -f main *.o *.dll
