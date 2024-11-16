// DAVELIB_DAVIO_C

#include <stdlib.h>
#include <stdio.h>
#include "davio.h"

struct FileContext readFile( char* filename )	{

	struct FileContext fc;

	char * buffer = 0;
	long length;
	long actual_length;
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

