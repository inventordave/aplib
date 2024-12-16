# Makefile for t.c

all: gcd
	gcc -g -O0 -o mul.exe ../gcollect/gc.c ../colour/colour.c ../stringy/stringy.c  ./t.c

gcd:
	make -C ../gcollect/ gcd
