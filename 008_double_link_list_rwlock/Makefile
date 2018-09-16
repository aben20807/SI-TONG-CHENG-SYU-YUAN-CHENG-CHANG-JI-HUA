CC = gcc
CFLAGS = -Wall -Wno-unused-function
CFILES = dlist.c locker_pthread.c locker_nest.c rw_locker.c
OBJS = dlist.o locker_pthread.o locker_nest.o rw_locker.o
EXEC = main
TARGETS = $(EXEC)
LIB = libdlist.dll
LINK = -L./ -ldlist

.PHONY: all
all: $(TARGETS)

$(EXEC): $(EXEC).o $(LIB)
	$(CC) $(CFLAGS) -pthread $(EXEC).o $(LINK) -o $@

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -shared -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: test
test:
	$(CC) $(CFLAGS) $(CFILES) -g -shared -o $(LIB)
	$(CC) $(CFLAGS) $(CFILES) -g -DDLIST_TEST -pthread -o dlist_test
	./dlist_test

.PHONY: clean
clean:
	rm -f *.o main *.stackdump dlist_test *.so *.dll
