all: main

main: adder.o main.o
	gcc adder.o main.o -o main

adder.o: adder.h adder.c
	gcc -c adder.c

main.o: adder.h main.c
	gcc -c main.c

clean:
	rm main *.o
