all: main

main: libadder.a main.o
	gcc -o main main.o -static -L. -ladder
	# gcc -o main -static -L. -ladder main.o

libadder.a: adder.o
	ar rcs libadder.a adder.o

adder.o: adder.h adder.c
	gcc -c adder.c

main.o: adder.h main.c
	gcc -c main.c

clean:
	rm main *.o *.a
