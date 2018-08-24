all: main

main: main.o adder.dll
	gcc -o main main.o -L. -ladder

adder.dll: adder.o
	gcc -o adder.dll -shared adder.o

adder.o: adder.h adder.c
	gcc -c -fPIC adder.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f main *.o *.dll *.so
