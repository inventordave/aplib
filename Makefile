# I'm currently sticking with only a test config build. APLIB.C (APLIB.H) is where the APlib Engine Code is.

colorMode=1
nocolour:
	colorMode=0
	make aplib

aplib: aplib.c aplib.h io.c io.h stringy.c stringy.h colour.c colour.h
	gcc -Wall -Wextra -ggdb -DDEBUG aplib.c -lstd -c -o aplib.o

stringy: stringy.c stringy.h
	gcc -Wall -Wextra -ggdb -DDEBUG stringy.c -lstd -c -o stringy.o

colour: colour.c colour.h
	gcc -Wall -Wextra -ggdb -DDEBUG colour.c -lstd -c -o colour.o

aplib_pkg: aplib stringy colour
	ar r -p aplibarc.a aplib.o colour.o stringy.o

GC:
	make -C ./gcollect/ gcd

test:	GC main.c main.h tests.c tests.h aplib.c aplib.h stringy.c stringy.h colour.c colour.h lib.c lib.h
	gcc -Wall -Wextra -O -g -DDEBUG ./gcollect/gcd.o lib.c io.c stringy.c colour.c tests.c aplib.c main.c -lm -o test.exe

# For removing the detritus of the last compilation cycle that tried to' mess wi' oos!!	
clean:
	rm -f ./gcollect/*.o
	rm -f *.a
	rm -f *.exe
	make -C ../regex_w/ clean

