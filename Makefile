CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
OPT=-O3

all:

clean: rm -f bin/* obj/*

.PHONY=all clean
