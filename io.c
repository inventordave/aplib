#include "io.h"

byte getbyte( char* c )	{ return *c; }

extern void* cmem( large nb )	{ return calloc( nb,1 ); }
extern char* mem( large numBytes )	{ return memp( (large)1,numBytes ); }
extern char* memp( large numParts, large numBytes )	{

		return (char*) malloc( numParts*numBytes + 2 + (numParts-1) );
		// Each "part" is expected to be delimited by a single NULL '\0' char in the buffer.
		// The end of the buffer is expected to end in 2 contiguous NULL '\0' chars.
}




