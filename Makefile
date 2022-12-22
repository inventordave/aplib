
aplib: aplib.o cc.o
	gcc -Wall -mconsole -g aplib.o ../colorconsole/cc.o -o aplib.exe
	
aplib.o: aplib.c aplib.h
	gcc -Wall -c -g aplib.c  -o aplib.o 
		
cc.o: 
	make -C ../colorconsole/ colorconsole

clean:
	rm -f aplib.o
	rm -f aplib.exe

