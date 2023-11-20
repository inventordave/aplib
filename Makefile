
aplibc: aplibc.o
	gcc -Wall -mconsole -g aplibc.o  -o aplibc.exe
	
aplibc.o: aplib.c aplib.h Dave_IEEE754.h
	gcc -Wall -c -g aplib.c  -o aplibc.o

test: test.c aplib.h Dave_IEEE754.h
	gcc -Wall -mconsole -g test.c -o test.exe

clean:
	rm -f *.o
	rm -f *.exe

