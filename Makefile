fs: fs.o str.o barnyard.o ansivt2.o error.o regex.o
	gcc -mconsole barnyard.o str.o fs.o ansivt2.o error.o regex/regex.o -lole32 -loleaut32  -o fs.exe

fs.o: fs.c fs.h ansivt2.h
	gcc -c -o fs.o fs.c 

str.o: str.c str.h ansivt2.h
	gcc -c -o str.o str.c

barnyard.o: ../barnyard/barnyard.c ../barnyard/barnyard.h
	gcc -c -o barnyard.o ../barnyard/barnyard.c
	
ansivt2.o: ansivt2.c ansivt2.h
	gcc -c -o ansivt2.o ansivt2.c
	
error.o: error.c error.h
	gcc -c -o error.o error.c
	
regex.o:
	make -C regex lib

fsd: fsd.o strd.o barnyardd.o ansivt2d.o errord.o regexd.o
	gcc -mconsole -std=gnu++11 -DDEBUG -g barnyardd.o ansivt2d.o strd.o fsd.o errord.o regex/regexd.o -lole32 -loleaut32 -o fsd.exe
	
fsd.o: fs.c fs.h
	gcc -g -DDEBUG -c -o fsd.o fs.c 

strd.o: str.c str.h
	gcc -g -DDEBUG -c -o strd.o str.c

barnyardd.o: ../barnyard/barnyard.c ../barnyard/barnyard.h
	gcc -g -DDEBUG -c -o barnyardd.o ../barnyard/barnyard.c
	
ansivt2d.o: ansivt2.c ansivt2.h
	gcc -g -DDEBUG -c -o ansivt2d.o ansivt2.c
	
errord.o: error.c error.h
	gcc -g -DDEBUG -c -o errord.o error.c
	
regexd.o:
	make -C regex libd
	
clean:
	rm -f *.o
	rm -f *.exe
	
	