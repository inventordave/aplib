# I'm currently sticking with only a test config build. APLIB.C (APLIB.H) is where the APlib Engine Code is.

aplib: aplib.c aplib.h io.c io.h stringy.c stringy.h colour.c colour.h
	gcc -Wall -g -DDEBUG stringy.c aplib.c io.c -lstd -c aplib.o

test:	testmain.c testmain.h aplib.c aplib.h tests.c tests.h
	gcc -Wall -g -DDEBUG io.c stringy.c colour.c tests.c testmain.c -o test.exe

# For removing the detritus of the last compilation cycle that tried to' mess wi' oos!!	
clean:
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

