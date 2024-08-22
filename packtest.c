#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define L unsigned long long int

#define strlen strlen_
L strlen_(char * str)	{
	
	L i = 0;
	while( str[i++] != '\0' )
		;
	return i-1;
}


char* unpack( char* );
char* pack( char* );


int main( int argc, char** argv )	{

	char* _;

	if( argc<2 )
		_ = strdup( "12345678765432922" );
	else
		_ = argv[1];

	printf( "string := \"%s\" (length: %d)\n", _, strlen( _ ) );
	
	char* packedstr = pack( _ );

	printf( "packedstr := \"%s\" (length: %d)\n", packedstr, strlen( packedstr ) );
	
	char* unpackedstr = unpack( packedstr );
	
	printf( "unpacked := \"%s\" (length: %d)\n", unpackedstr, strlen( unpackedstr ) );
	
	return strcmp( unpackedstr,packedstr );
}


// assumes a packed-digit string of 4 bits/digit.
char* unpack( char* _ ) {
	
	L strlen__ = strlen( _ );

	int BITMASK_LOWER = 15;
	int BITMASK_UPPER = 255-15; //240, which is 11110000 (128+64+32+16)
	char t;
	
	L i, j;
	char* _U = (char*)calloc( 1, (strlen__>>2) + 1 );
	for( i=0, j=0; i<strlen__; i++ ) {
		
		t = _[i] & BITMASK_LOWER;
		if( t==10 )	t=0;
		
		_U[j++] = t + '0';
		
		t = (_[i] & BITMASK_UPPER)>>4;
		if( t==0 )
			_U[j++] = '\0';
		else if( t==10 )
			_U[j++] = '0';

	}

	if( _U[j-1]!='\0' )
		_U[j] = '\0';

	return _U;
}

// assumes an unpacked string of 1 char per decimal digit.
char* pack( char* _ ) {
	
	L strlen__ = strlen( _ );

	char* _P = (char*)calloc( 1, (strlen__>>1) + 2 );
	char t;
	
	L i,j;
	for( i=0,j=0; i<strlen__-1; i+=2, j++ )	{
		
		t = _[i] - '0';
		if( t==0 )
			t=10;
		
		char nd = (_[i+1] - '0');
		if( nd==0 )
			nd=10;
		
		t += ( nd << 4 );
		
		_P[j] = t;		
	}

	if( i==strlen__-1 )	{

	t = _[i] - '0';
	if( t==0 )
		t=10;
	
	_P[j++] = t;
	
	}
	_P[j] = '\0';
	return _P;
}

