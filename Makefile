# I'm currently sticking with only a test config build. APLIB.C (APLIB.H) is where the AP Engine Code is.


compiler=gcc
target=win32
flag1=null

build=debug
flag2=null




aplib: aplib.c aplib.h colour.c colour.h io.c io.h
	if [ $(build)=="debug" ] \
		[ flag2 = "-g -DDEBUG" ]; \
	fi

	if [ $(target)=="win32" ] \
		[ flag1="-mconsole" ]; \
	fi

	@ $(compiler) -Wall $(flag2) aplib.c colour.c io.c -lstd -c aplib.o

test: aplib
	$(compiler) -Wall -g -DDEBUG stringy.c aplib.c i754.c lib.c io.c tests.c testFnc.c -o test.exe

sandbox: sandbox.c sandbox.h aplib.c aplib.h i754.c i754.h stringy.c stringy.h colour.c colour.h lib.c lib.h io.c io.h
	gcc -Wall $(flag1) -g -DDEBUG aplib.c i754.c stringy.c colour.c lib.c io.c sandbox.c -o s.exe

# For removing the detritus of the last compilation cycle that tried to' mess wi' oos!!	
clean:
	rm -f *.o
	rm -f test.exe
	rm -f *stackdump
	rm -f *.gch


# This is the Bison program from inventordave2/Calculator. This is the basis for the APLIB front-end.
fpcalc:	
	bison -d fpcalc.y
	flex fpcalc.l
	
	$(compiler) fpcalc.tab.c lex.yy.c -o fpcalc.exe
	
cleancalc:
	rm -f fpcalc.exe 
	rm -f fpcalc.tab.c 
	rm -f fpcalc.tab.h 
	rm -f lex.yy.c

