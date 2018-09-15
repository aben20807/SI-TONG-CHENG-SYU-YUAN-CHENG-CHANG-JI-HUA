CC = gcc
N = not_atomic
A = atomic
CFLAGS = -pthread -Wall

all: $(N) $(A)

$(N): $(N).o
	$(CC) $(CFLAGS) -o $@ $(N).o

$(A): $(A).o
	$(CC) $(CFLAGS) -o $@ $(A).o

%.o: %.c
	$(CC) -c $<

clean:
	rm -f $(N) $(A) *.o
