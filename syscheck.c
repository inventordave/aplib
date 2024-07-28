#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void systemEndian();

int main( int argc, char ** argv )	{
	
	int v;
	
	if( argc==1 )
	v = (4096 + 1024 + 512 + 256 + 32 + 8 + 4);
	else
	v = atoi(argv[1]);

	systemEndian( v );
	
	return 0;
}





void* systemcheck ( void* istruct )	{

	return (void*) 0;
}

