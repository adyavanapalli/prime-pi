CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
INCLUDE=-I include/
OPT=-O3

all: bin/naive-soe

bin/naive-soe: src/sieve-of-eratosthenes/naive-soe.c
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPT) src/sieve-of-eratosthenes/naive-soe.c -o bin/naive-soe

clean:
	rm -f bin/* obj/*

.PHONY=all clean 
