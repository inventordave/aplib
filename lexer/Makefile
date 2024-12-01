# simplelexer Makefile

# vars

compiler= gcc
flags= -g -DDEBUG -Wall -Wextra

# targets

lexertest: lexertest.c lexertest.h
	$(compiler) $(flags) lexertest.c -c -o lexertest.o

simplelexer: lexer.c lexer.h
	$(compiler) $(flags) lexer.c -c -o simplelexer.o

aplib_pkg:
	make -C ../ aplib
	make -C ../ stringy
	make -C ../ colour 
	make -C ../gcollect/ gcd
	make -C ../ io
	make -C ../regex_w libd

test: aplib_pkg simplelexer lexertest
	ar r slarc.a lexertest.o simplelexer.o "../regex_w/wrx_free.o" "../regex_w/wrx_prnt.o" "../regex_w/wrx_comp.o" "../regex_w/wrx_exec.o" "../regex_w/wrx_err.o" "../gcollect/gcd.o" "../aplib.o" "../stringy.o" "../colour.o"  "../io.o"  
	$(compiler) $(flags)  slarc.a -o lextest.exe

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.exe

	make -C ../regex_w/ clean
	make -C ../ clean
	
