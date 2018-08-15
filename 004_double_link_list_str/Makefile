all: main cppmain dlist_toupper

main: main.o dlist.o
	gcc -o main dlist.o main.o

dlist_toupper: dlist_toupper.o dlist.o
	gcc -o dlist_toupper dlist.o dlist_toupper.o

cppmain: cppmain.o dlist.o
	g++ -o cppmain dlist.o cppmain.o

dlist.o: dlist.c dlist.h
	gcc -c dlist.c

main.o: main.c dlist.h
	gcc -c main.c

dlist_toupper.o: dlist_toupper.c dlist.h
	gcc -c dlist_toupper.c

cppmain.o: cppmain.cpp dlist.h
	g++ -c cppmain.cpp

clean:
	rm *.o main cppmain dlist_toupper
