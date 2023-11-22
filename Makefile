
test: test.c APlib.h Dave_IEEE754.h
	gcc -Wall -mconsole -g -O3 test.c -o test.exe

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *stackdump
	rm -f *.gch

