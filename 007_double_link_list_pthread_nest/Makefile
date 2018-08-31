CC = gcc
CFLAGS = -lpthread -Wall -Wno-unused-function
CFILES = dlist.c locker_pthread.c locker_nest.c
OBJS = dlist.o locker_pthread.o locker_nest.o
EXEC = main
TARGETS = $(EXEC)
LIB = libdlist.dll
LINK = -L./ -ldlist

.PHONY: all
all: $(TARGETS)

$(EXEC): $(EXEC).o $(LIB)
	$(CC) $(CFLAGS) $(EXEC).o $(LINK) -o $@

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -shared -o $@

%.o: %.c
	$(CC) -c $<

.PHONY: test
test:
	$(CC) $(CFLAGS) $(CFILES) -g -shared -o $(LIB)
	$(CC) $(CFLAGS) $(CFILES) -g -DDLIST_TEST -o dlist_test
	./dlist_test

.PHONY: clean
clean:
	rm -f *.o main *.stackdump dlist_test *.so *.dll
