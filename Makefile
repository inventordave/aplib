# Makefile 'aplib'
# I'm currently sticking with only a test config build. APLIB.C (APLIB.H) is where the APlib Engine Code is.

# Vars.
outFile=test.exe
colorMode=1
warnings=-Wall -Wextra -Wshadow -Wimplicit-fallthrough=0 -Wno-unused-variable


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
	gcc $(warnings) -O0 -g -DDEBUG -DWIN32 -Dcm$(colorMode) aplib.c -c -o aplib.o

stringy:
	make -C ../stringy/ stringyd

colour:
	make -C ../colour/ colourd
	
gcollect:
	make -C ../gcollect/ gcd


aplib_pkg: gcollect aplib stringy colour

	make -C ../davelib/ io
	make -C ../davelib/ lib
	make -C ../wernee/regex_w/ libd
	ar -r arc.a aplib.o \
		../wernee/regex_w/regexd.o \
		../gcollect/gcd.o \
		../colour/colourd.o \
		../stringy/stringyd.o \
		../davelib/io.o \
		../davelib/lib.o

mul: t.c ../gcollect/gc.c
	gcc $(warnings) -g -DDEBUG -Dcm$(colorMode) ../gcollect/gc.c t.c -lm -o t.exe

GC:
	make -C ../gcollect/ gcd

test:	aplib_pkg
	gcc $(warnings) -O -g -DDEBUG -Dcm$(colorMode) main.c arc.a  -o $(outFile)

# For removing the detritus of the last compilation cycle that tried to' mess wi' oos!!	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f ../gcollect/*.o
	
	rm -f *.a
	rm -f $(outFile)
	make -C ../wernee/regex_w/ clean
	make -C ../davelib/ clean

