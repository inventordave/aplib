/ 
# Makefile 'aplib'


aplib:	aplib.c aplib.h
	gcc -g -DDEBUG -c aplib.c -o aplib.o

stringy: stringy.c stringy.h
	gcc -g -DDEBUG -O -c stringy.c -o stringy.o

colour: colour.c colour.h
	gcc -g -DDEBUG -O -c colour.c -o colour.o

	

io: io.c io.h
	gcc -g -DDEBUG -O -c io.c -o io.o


# I'm currently sticking with only a test config build. APLIB.C (APLIB.H) is where the APlib Engine Code is.

# Vars.
outFile=test.exe
colorMode=1
warnings=-Wall -Wextra


# Rules.

# Simple test of pack() and unpack() method.
packtest: packtest.c
	rm -f packtest.exe
	gcc $(warnings) -g -DDEBUG -O0 packtest.c -o packtest.exe

# If you want to compile aplib or the test program with no ANSIVT colour support.
nocolour:
	colorMode=0
	make aplib
	make test

# The APLIB object file.
aplib: aplib.c aplib.h io.c io.h stringy.c stringy.h colour.c colour.h
	gcc $(warnings) -g -DDEBUG -Dcm$(colorMode) aplib.c -lstd -c -o aplib.o

stringy: stringy.c stringy.h
	gcc $(warnings) -g -DDEBUG stringy.c -lstd -c -o stringy.o

colour: colour.c colour.h
	gcc $(warnings) -g -DDEBUG -Dcm$(colorMode) colour.c -lstd -c -o colour.o
	
aplib_pkg: aplib stringy colour
	ar r -p aplibarc.a aplib.o colour.o stringy.o

GC:
	make -C ./gcollect/ gcd

test:	GC main.c main.h tests.c tests.h aplib.c aplib.h stringy.c stringy.h colour.c colour.h lib.c lib.h
	gcc $(warnings) -O -g -DDEBUG -Dcm$(colorMode) ./gcollect/gcd.o lib.c io.c stringy.c colour.c tests.c aplib.c main.c -lm -o $(outFile)

# For removing the detritus of the last compilation cycle that tried to' mess wi' oos!!	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f ./gcollect/*.o
	rm -f *.a
	rm -f $(outFile)
	make -C ../regex_w/ clean

