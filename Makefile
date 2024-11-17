# I'm currently sticking with only a test config build. APLIB.C (APLIB.H) is where the APlib Engine Code is.

aplib: aplib.c aplib.h io.c io.h
	gcc -Wall -g -DDEBUG aplib.c -lstd -c -o aplib.o

stringy: stringy.c stringy.h
	gcc -Wall -g -DDEBUG stringy.c -c -o stringy.o

colour: colour.c colour.h
	gcc -Wall -g -DDEBUG colour.c -c -o colour.o

io: io.c io.h
	gcc -Wall -g -DDEBUG io.c -c -o io.o


GC:
	make -C ./gcollect/ gcd
	
test:	GC main.c main.h tests.c tests.h aplib.c aplib.h stringy.c stringy.h colour.c colour.h lib.c lib.h
	
	gcc -Wall -O -g -DDEBUG ./gcollect/gcd.o lib.c io.c stringy.c colour.c tests.c aplib.c main.c -lm -o test.exe

# For removing the detritus of the last compilation cycle that tried to' mess wi' oos!!	
clean:

	rm -f *.a
	rm -f ./gcollect/*.o
	rm -f test.exe
	rm -f *stackdump


# This is the Bison program from inventordave2/Calculator. This'll be the basis for the APLIB front-end.
fpcalc:	
	bison -d fpcalc.y
	flex fpcalc.l
	
	gcc fpcalc.tab.c lex.yy.c -o fpcalc.exe
	
cleancalc:
	rm -f fpcalc.exe 
	rm -f fpcalc.tab.c 
	rm -f fpcalc.tab.h 
	rm -f lex.yy.c

