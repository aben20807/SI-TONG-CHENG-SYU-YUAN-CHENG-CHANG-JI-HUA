all: main

main: adder.lib main.o
	gcc -o main main.o -static -L. -ladder

adder.lib: adder.o
	ar rcs adder.lib adder.o

adder.o: adder.h adder.c
	gcc -c adder.c

main.o: adder.h main.c
	gcc -c main.c

clean:
	rm -f main *.o *.lib
