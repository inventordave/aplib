#include "./gcollect/gc.h"
#include "io.h"

byte getbyte( char* c )	{ return *c; }

void* cmem( large nb )	{ return g( calloc( nb+1,1 ) ); }
char* mem( large numBytes )	{ return memp( (large)1,numBytes ); }
char* memp( large numParts, large numBytes )	{

		return (char*) g( malloc( numParts*numBytes + 2 + (numParts-1) ) );
		// Each "part" is expected to be delimited by a single NULL '\0' char in the buffer.
		// The end of the buffer is expected to end in 2 contiguous NULL '\0' chars.
}

char* zmem( large nb )	{

	char* _ = (char*) g( malloc( nb+1 ) );
	
	large i;
	for( i=0; i<nb; i++ )
		_[i] = '0';

	_[i] = '\0';
	
	return _;
}

struct FileContext readFile( char* filename )	{

	struct FileContext fc;

	char * buffer = 0;
	long length = 0;
	long actual_length = 0;
	FILE * f = fopen (filename, "r");

	if (f)	{

		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length);

		if (buffer)
			actual_length = fread (buffer, 1, length, f);

		fclose (f);
	}


	fc.fileContents = buffer;
	fc.length = actual_length;

	return fc;
}

// Stub function. Will dev later.
struct FileContents read_f_split( char* fn, char* delim )	{

	struct FileContents	_;

	int n = 0;
	// n is the number of lines in the input file.
	// This is needed to initialise _.lines with enough
	// allocation for a char* ptr for each line.

	_.lines = (char**) malloc( n * sizeof(char*) );

	// populate fc.lines[] with text lines from fn.
	// ...

	return _;
}



