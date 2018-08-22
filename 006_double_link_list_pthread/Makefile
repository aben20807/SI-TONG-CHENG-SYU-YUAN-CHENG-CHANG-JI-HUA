CC = gcc
CFLAGS = -lpthread -Wall
CFILES = dlist.c locker_pthread.c
OBJS = main.o dlist.o locker_pthread.o
EXEC = main
TARGETS = $(EXEC)
LIB = libdlist.so
LINK = -L. -ldlist

.PHONY: all
all: $(TARGETS)

$(EXEC): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) -L. -ldlist -o $@

$(LIB): dlist.o locker_pthread.o
	$(CC) $(CFLAGS) dlist.o locker_pthread.o -shared -o $@

%.o: %.c
	$(CC) -c $<

.PHONY: test
test:
	$(CC) $(CFLAGS) $(CFILES) -g -shared -o libdlist.so
	$(CC) $(CFLAGS) $(CFILES) -g -DDLIST_TEST -o dlist_test
	./dlist_test

.PHONY: clean
clean:
	rm *.o main *.stackdump dlist_test
