all: main

main: main.o libadder.so
	gcc -o main main.o -L. -ladder -Wl,-rpath=.

libadder.so: adder.o
	gcc -o libadder.so -shared adder.o

adder.o: adder.h adder.c
	gcc -c -fPIC adder.c

main.o: adder.h main.c
	gcc -c main.c

clean:
	rm -f main *.o *.so
