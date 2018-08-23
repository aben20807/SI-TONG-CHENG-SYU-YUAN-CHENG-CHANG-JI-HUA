all: main

main: main.o adder.dll
	gcc -L./ -ladder main.o -o main

adder.dll: adder.o
	gcc -shared adder.o -o adder.dll

adder.o: adder.h adder.c
	gcc -c adder.c

main.o: main.c
	gcc -c main.c

clean:
	rm main *.o *.dll
