# simplelexer Makefile

# vars

compiler= gcc
flags= -ggdb -DDEBUG -Wall -Wextra
output= lexer.o

# targets

davio: davio.c davio.h
	$(compiler) $(flags) davio.c -c -o davio.o
	
simplelexer: lexer.c lexer.h
	$(compiler) $(flags) lexer.c -c -o simplelexer.o

wregex:
	make -C ../regex_w/ libd
	
aplib:
	make -C ../ aplib_pkg

lexertest: lexertest.c lexertest.h
	$(compiler) $(flags) lexertest.c -c -o lexertest.o
	
test: aplib simplelexer lexertest  davio  wregex
	ar r -p  slarc.a ../aplibarc.a simplelexer.o "../regex_w/regexd.o" davio.o  lexertest.o       

	$(compiler) $(flags) slarc.a -o lextest.exe

clean:
	rm -f *.o
	rm -f *.exe

	make -C ../regex_w/ clean
	make -C ../ clean

