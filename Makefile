# I'm currently sticking with only a test config build. APLIB.C (APLIB.H) is where the AP Engine Code is.

sandbox: sandbox.c sandbox.h aplib.c aplib.h i754.c i754.h colour.c colour.h lib.c lib.h io.c io.h
	gcc -Wall -mconsole -g aplib.c i754.c colour.c lib.c io.c sandbox.c -o test.exe


# For removing the detritus of the last compilation cycle that tried to'  mess wi' oos!!	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *stackdump
	rm -f *.gch

