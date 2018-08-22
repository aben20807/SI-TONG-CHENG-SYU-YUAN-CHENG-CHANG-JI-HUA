CC = gcc
FLAGS = -g -lpthread
CFILES = dlist.c locker_pthread.c

# all: main
#
# main: main.o dlist.o
# 	${CC} -o main dlist.o main.o
#
# dlist.o: dlist.c dlist.h
# 	${CC} -c dlist.c
#
# main.o: main.c dlist.h
# 	${CC} -c main.c

test:
	${CC} ${FLAGS} ${CFILES} -shared -o libdlist.so
	${CC} ${FLAGS} ${CFILES} -DDLIST_TEST -o dlist_test
	./dlist_test

clean:
	rm *.o main *.stackdump dlist_test
