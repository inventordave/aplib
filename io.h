// IO_H

#ifndef DAVELIB_IO
#define DAVELIB_IO

#include <stdio.h>
#include <stdlib.h>
#include "aplib.h"

//#define in getchar
//#define out putchar

#define byte char
#define octet unsigned char


// GLOBALS
typedef struct FileContents	{

	char** 	lines;
	int		lineCount;

} FileContents;

typedef struct FileContext	{

	char* fileContents;
	int length;

} FileContext;

// FUNCTIONS
struct FileContext readFile( char* filename );
struct FileContents read_f_split( char* fn, char* delim );




byte getbyte( char* );

// MEMORY HELPER FNC'S
extern char* mem( large numBytes );
extern char* memp( large numParts, large numBytes );
extern void* cmem( large nb );
extern char* zmem( large nb );

#endif

