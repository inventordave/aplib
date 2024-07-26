release: ap
	gcc -mconsole -g -O3 main.c ap.o -o ./build/AP.exe 

sandbox: sandbox.c sandbox.h ap_io.c ap_io.h colour aplib
	gcc -Wall -mconsole -g -O0 sandbox.c ap_io.c APlib.c I754.c colour.o aplib.o -o test.exe

ap: ap.c ap.h ap_io.c ap_io.h tests.c tests.h aplib colour
	gcc -Wall -mconsole -g ap.c tests.c ap_io.c colour.o aplib.o -c -o ap.o

aplib: aplib.c aplib.h I754.c I754.h lib
	gcc -Wall -g aplib.c I754.c io.o colour.o lib.o -c
	
lib: lib.c lib.h getOptions.h io
	gcc -Wall -g lib.c io.o -o lib.o

colour: colour.c colour.h
	gcc -c colour.c -o colour.o

io: io.c io.h
	gcc -Wall -g io.c -o io.o


# For removing the detritus of the last compilation cycle that tried to'  mess wi' oos!!	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *stackdump
	rm -f *.gch

