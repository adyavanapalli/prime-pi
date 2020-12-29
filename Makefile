CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
INCLUDE=-I include/
OPT=-O3

all: bin/naive-soe bin/odd-integers-soe

bin/naive-soe: src/sieve-of-eratosthenes/naive-soe.c
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPT) src/sieve-of-eratosthenes/naive-soe.c -o bin/naive-soe

bin/odd-integers-soe: src/sieve-of-eratosthenes/odd-integers-soe.c
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPT) src/sieve-of-eratosthenes/odd-integers-soe.c -o bin/odd-integers-soe

clean:
	rm -f bin/* obj/*

.PHONY=all clean
