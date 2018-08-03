main: main.o dlist.o
	gcc -o main dlist.o main.o

dlist.o: dlist.c dlist.h
	gcc -c dlist.c

main.o: main.c dlist.h
	gcc -c main.c

clean:
	rm *.o main
