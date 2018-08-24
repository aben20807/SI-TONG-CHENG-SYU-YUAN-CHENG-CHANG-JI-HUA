all: main

main: main.o libadder.so
	gcc -o main main.o -L./ -ladder -Wl,-rpath=./

libadder.so: adder.o
	gcc -o libadder.so -shared adder.o

adder.o: adder.h adder.c
	gcc -c -fPIC adder.c

main.o: main.c
	gcc -c -fPIC main.c

clean:
	rm -f main *.o *.dll *.so
