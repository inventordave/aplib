
ap: test.c APlib.h APlib-output.h Dave_IEEE754.h getOptions.h
	gcc -Wall -mconsole -O3 -g test.c -o ap.exe

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *stackdump
	rm -f *.gch

