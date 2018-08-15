all: main

main: main.o dlist.o
	gcc -o main dlist.o main.o

dlist.o: dlist.c dlist.h
	gcc -c dlist.c

main.o: main.c dlist.h
	gcc -c main.c

test:
	gcc dlist.c -g -DDLIST_TEST -o dlist_test

clean:
	rm *.o main *.stackdump dlist_test
