
aplibc: aplibc.o
	gcc -Wall -mconsole -g aplibc.o ../colorconsole/cc.o -o aplibc.exe
	
aplibc.o: aplib.c aplib.h
	gcc -Wall -c -g aplib.c -o aplibc.o 
		
cc.o: 
	make -C ../colorconsole/ colorconsole

aplibcpp: aplibcpp.o
	g++ -Wall -mconsole -g aplibcpp.o -o aplibcpp.exe
	
aplibcpp.o: aplib.cpp aplib.hpp
	g++ -Wall -c -g aplib.cpp -o aplibcpp.o
	

clean:
	rm -f aplib.o
	rm -f aplib.exe

