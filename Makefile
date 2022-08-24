aplib: aplib_.o
	gcc -mconsole -g -O0 aplib_.o -lole32 -loleaut32  -o aplib.exe
	
aplib_.o: aplib.c aplib.h
	gcc -c -g -O0 -o aplib_.o aplib.c

