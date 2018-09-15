CC = gcc
N = not_atomic
A = atomic
CFLAGS = -pthread -Wall

.PHONY: all, clean, test
all: $(N) $(A)

$(N): $(N).o
	$(CC) $(CFLAGS) -o $@ $(N).o

$(A): $(A).o
	$(CC) $(CFLAGS) -o $@ $(A).o

%.o: %.c
	$(CC) -c $<

test: all
	@ printf "\n"
	@ ./$(N)
	@ printf "\n"
	@ ./$(A)

clean:
	rm -f $(N) $(A) *.o
