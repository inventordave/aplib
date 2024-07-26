
ap: ap.c ap.h APlib.c APlib.h APlib-output.c APlib-output.h I754.c I754.h getOptions.h tests.c tests.h colorconsole
	gcc -Wall -mconsole -g ap.c tests.c APlib-output.c APlib.c I754.c cc.o -o ./build/ap.exe

sandbox: incomplete.c incomplete.h APlib.c APlib.h APlib-output.c APlib-output.h I754.c I754.h getOptions.h colorconsole
	gcc -Wall -mconsole -g -O0 incomplete.c APlib-output.c APlib.c I754.c cc.o -o t.exe

colorconsole: ansivt2.c ansivt2.h
	gcc -c ansivt2.c -o cc.o
	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f ./build/*.exe
	rm -f *stackdump
	rm -f *.gch

