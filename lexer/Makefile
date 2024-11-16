# simplelexer Makefile

# vars

compiler= gcc
flags= -g -DDEBUG
output= lexer.o

# targets

davio: davio.c davio.h
	$(compiler) $(flags) davio.c -c -o davio.o
	
simplelexer: lexer.c lexer.h
	$(compiler) $(flags) lexer.c -c -o simplelexer.o

aplib:
	make -C ../ aplib
	
test: lexertest.c lexertest.h aplib davio simplelexer
	ar r slarc.a davio.o simplelexer.o  "../aplib.o"

	$(compiler) $(flags) slarc.a lexertest.c -o lextest.exe

clean:
	rm -f *.o
	rm -f *.exe

