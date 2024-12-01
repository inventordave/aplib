# Makefile 'aplib'


aplib:	aplib.c aplib.h
	gcc -g -DDEBUG -c aplib.c -o aplib.o

stringy: stringy.c stringy.h
	gcc -g -DDEBUG -O -c stringy.c -o stringy.o

colour: colour.c colour.h
	gcc -g -DDEBUG -O -c colour.c -o colour.o

	

io: io.c io.h
	gcc -g -DDEBUG -O -c io.c -o io.o


clean:
	rm -f *.o
	rm -f *.exe

