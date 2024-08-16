#include "io.h"

byte getbyte( char* c )	{ return *c; }

void* cmem( large nb )	{ return calloc( nb+1,1 ); }
char* mem( large numBytes )	{ return memp( (large)1,numBytes ); }
char* memp( large numParts, large numBytes )	{

		return (char*) malloc( numParts*numBytes + 2 + (numParts-1) );
		// Each "part" is expected to be delimited by a single NULL '\0' char in the buffer.
		// The end of the buffer is expected to end in 2 contiguous NULL '\0' chars.
}

char* zmem( large nb )	{

	char* _ = (char*) malloc( nb+1 );
	
	large i;
	for( i=0; i<nb; i++ )
		_[i] = '0';

	_[i] = '\0';
	
	return _;
}

