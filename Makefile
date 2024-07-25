
ap: ap.c ap.h APlib.c APlib.h APlib-output.c APlib-output.h Dave_IEEE754.c Dave_IEEE754.h getOptions.h tests.c tests.h colorconsole

	gcc -Wall -mconsole -g ap.c tests.c APlib-output.c APlib.c Dave_IEEE754.c cc.o -o ap.exe

colorconsole: ansivt2.c ansivt2.h
	gcc -c ansivt2.c  -o cc.o
	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *stackdump
	rm -f *.gch

