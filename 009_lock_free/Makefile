CC = gcc
F = failed
A = atomic
L = locked
OBJS = locker_pthread.o
CFLAGS = -pthread -Wall

.PHONY: all, clean, test
all: $(F) $(A) $(L)

$(F): $(F).o
	$(CC) $(CFLAGS) -o $@ $(F).o

$(A): $(A).o
	$(CC) $(CFLAGS) -o $@ $(A).o

$(L): $(L).o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(L).o $(OBJS)

%.o: %.c
	$(CC) -c $<

test: all
	@ printf "\n"
	@ time -p ./$(F)
	@ printf "\n"
	@ time -p ./$(A)
	@ printf "\n"
	@ time -p ./$(L)

clean:
	rm -f $(F) $(A) $(L) *.o
