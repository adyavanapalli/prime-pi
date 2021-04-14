CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
INCLUDE=-I include/
OPT=-O3 -march=native

all: bin/naive-soe bin/odd-integers-soe bin/bit-packed-odd-integers-soe bin/naive-divisibility

bin/naive-soe: src/sieve-of-eratosthenes/naive-soe.c
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPT) src/sieve-of-eratosthenes/naive-soe.c -o bin/naive-soe

bin/odd-integers-soe: src/sieve-of-eratosthenes/odd-integers-soe.c
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPT) src/sieve-of-eratosthenes/odd-integers-soe.c -o bin/odd-integers-soe

bin/bit-packed-odd-integers-soe: src/sieve-of-eratosthenes/bit-packed-odd-integers-soe.c
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPT) src/sieve-of-eratosthenes/bit-packed-odd-integers-soe.c -o bin/bit-packed-odd-integers-soe

bin/naive-divisibility: src/primality-checking/naive-divisibility.c
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPT) src/primality-checking/naive-divisibility.c -o bin/naive-divisibility

# bin/popcnt_native_vs_array: src/experiments/popcnt_native_vs_array.c
# 	$(CC) $(CCFLAGS) $(INCLUDE) $(OPT) src/experiments/popcnt_native_vs_array.c -o bin/popcnt_native_vs_array

clean:
	rm -f bin/* obj/*

.PHONY=all clean
