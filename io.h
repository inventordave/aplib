// IO_H

#ifndef DAVELIB_IO
#define DAVELIB_IO

#include <stdio.h>
#include <stdlib.h>

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
extern char* mem( unsigned unsigned long long int numBytes );
extern char* memp( unsigned long long int numParts, long long int numBytes );
extern void* cmem( unsigned long long int nb );
extern char* zmem( unsigned long long int nb );

#endif

