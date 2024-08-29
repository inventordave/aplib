
#include <stdio.h>

int systemEndian();

int main( int argc, char ** argv )	{
	
	int a = systemEndian();
	printf( "systemEndian() returned code: %d\n", a );
	return 0;
}

int systemEndian()	{
	
	int s = sizeof(int);	
	int v = 0;
	
	int i;
	for( i=0; i<s; i++ )
		v+= ('1'+(i))<<(i*8);

	for( i=0; i<s; i++ )
		printf( "Byte at offset '%d' contains '%c'\n", i, ((char*)(void*)(&v))[i] );
	
	int b = ((char*)(&v))[0] == ('0' + s);
	if( b )
		printf( "System is big-endian.\n" );
	else
		printf( "System is little-endian.\n" );

	return ((char*)(&v))[0] == ('0' + 1); // returns 1 if little-endian. returns 0 if big-endian.
}

void* systemcheck ( void* istruct )	{

	return (void*) 0;
}

