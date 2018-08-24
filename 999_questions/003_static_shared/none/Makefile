all: main

main: adder.o main.o
	gcc -o main adder.o main.o

adder.o: adder.h adder.c
	gcc -c adder.c

main.o: adder.h main.c
	gcc -c main.c

clean:
	rm -f main *.o
