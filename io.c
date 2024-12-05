#include "./gcollect/gc.h"
#include "io.h"

byte getbyte( char* c )	{ return *c; }

void* cmem( unsigned long long int nb )	{ return g( calloc( nb+1,1 ) ); }
char* mem( unsigned long long int numBytes )	{ return memp( (unsigned long long int)1,numBytes ); }
char* memp( unsigned long long int numParts, unsigned long long int numBytes )	{

		return (char*) g( malloc( numParts*numBytes + 2 + (numParts-1) ) );
		// Each "part" is expected to be delimited by a single NULL '\0' char in the buffer.
		// The end of the buffer is expected to end in 2 contiguous NULL '\0' chars.
}

char* zmem( unsigned long long int nb )	{

	char* _ = (char*) g( malloc( nb+1 ) );
	
	unsigned long long int i;
	for( i=0; i<nb; i++ )
		_[i] = '0';

	_[i] = '\0';
	
	return _;
}

struct FileContext readFile( char* filename )	{

	struct FileContext fc;

	char * buffer = 0;
	unsigned long long int length = 0;
	unsigned long long int actual_length = 0;
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

	struct FileContext fcx = readFile( char* filename );
	struct FileContents	_;

	int n = fcx.length;
	// n is the number of lines in the input file.
	// This is needed to initialise _.lines with enough
	// allocation for a char* ptr for each line.

	_.lines = (char**) malloc( n * sizeof(char*) );

	int i = 0;
	char c;

	loop:
	
	while( ((c = fxc.fileContents[i]) != '\n') )	{

		if( i==n )
			goto complete;
		
		_.lines[j][k++] = c;
		i++;
		c = fxc.fileContents[i];
	}

	j++;
	k=0;
	
	goto loop;

	complete:

	// The if-block below needs to be refactored for allocation-safety.
	if( j<n )	{
		
		_.lines = (char**) realloc( _.lines, (j+2) * sizeof(char*) );

		if( _.lines==NULL )	{

			fprintf( stderr, "Function '%s' in file '%s' failed to re-allocate memory. Exiting.\n", __func__, __FILE__ );
			exit( EXIT_FAILURE );
			
		}
		_.lines[j] = NULL;
		_.lines[j+1] = NULL;
	}

	_.lineCount = j;

	return _;
}

