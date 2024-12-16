# Makefile 'aplib'
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
aplib: aplib.c aplib.h
	gcc $(warnings) -g -DDEBUG -Dcm$(colorMode) aplib.c -lstd -c -o aplib.o

stringy:	../stringy/stringy.c ../stringy/stringy.h
	gcc $(warnings) -g -DDEBUG ../stringy/stringy.c -lstd -c -o stringy.o

colour:		../colour/colour.c ../colour/colour.h
	gcc $(warnings) -g -DDEBUG -Dcm$(colorMode) ../colour/colour.c -lstd -c -o colour.o
	
aplib_pkg: GC aplib stringy colour mul

	make -C ../davelib/ io
	make -C ../davelib/ lib
	ar r -p aplibarc.a aplib.o ../colour/colour.o ../stringy/stringy.o ../davelib/io.o ../davelib/lib.o ./t.o


mul: t.c
	gcc $(warnings) -g -DDEBUG -Dcm$(colorMode) t.c -lstd -c -o t.o

GC:
	make -C ../gcollect/ gcd

test:	aplib_pkg
	gcc $(warnings) -O -g -DDEBUG -Dcm$(colorMode) aplibarc.a -lstd -lm -o $(outFile)

# For removing the detritus of the last compilation cycle that tried to' mess wi' oos!!	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f ./gcollect/*.o
	rm -f *.a
	rm -f $(outFile)
	make -C ../regex_w/ clean

