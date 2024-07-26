release: ap
	gcc -mconsole -g -O3 main.c io.o colour.o lib.o aplib.o ap.o -o ./build/AP.exe 

sandbox: sandbox.c sandbox.h ap_io.c ap_io.h io colour lib aplib i754
	gcc -Wall -mconsole -g -O0 sandbox.c ap_io.c APlib.c io.o colour.o lib.o aplib.o -o test.exe

ap: ap.c ap.h ap_io.c ap_io.h tests.c tests.h aplib colour
	gcc -Wall -mconsole -g ap.c -c -o ap.o

aplib: aplib.c aplib.h i754 lib
	gcc -Wall -g aplib.c -c -o aplib.o

i754: i754.c i754.h
	gcc -Wall -g i754.c -c -o i754.o

lib: lib.c lib.h getOptions.h io
	gcc -Wall -g lib.c -c -o lib.o

io: io.c io.h colour
	gcc -Wall -g io.c -c -o io.o

colour: colour.c colour.h
	gcc -Wall -g colour.c -c -o colour.o


# For removing the detritus of the last compilation cycle that tried to'  mess wi' oos!!	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *stackdump
	rm -f *.gch

