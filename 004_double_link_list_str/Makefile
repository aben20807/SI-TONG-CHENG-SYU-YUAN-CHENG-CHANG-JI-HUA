all: main cppmain

main: main.o dlist.o
	gcc -o main dlist.o main.o

cppmain: cppmain.o dlist.o
	g++ -o cppmain dlist.o cppmain.o

dlist.o: dlist.c dlist.h
	gcc -c dlist.c

main.o: main.c dlist.h
	gcc -c main.c

cppmain.o: cppmain.cpp dlist.h
	g++ -c cppmain.cpp

clean:
	rm *.o main
