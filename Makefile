
aplibc: aplibc.o
	gcc -Wall -mconsole -g aplibc.o -o aplibc.exe
	
aplibc.o: aplib.c aplib.h
	gcc -Wall -c -g aplib.c -o aplibc.o 
	

clean:
	rm -f *.o
	rm -f *.exe

