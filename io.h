// IO_H

#ifndef DAVELIB_IO
#define DAVELIB_IO

#include <stdio.h>
#include <stdlib.h>

#define formatString sprintf
#define print printf
#define string char *
#define in getchar
#define out putchar

#define byte char
#define octet unsigned char


#define large unsigned long long int


#define FALSE 0
#define TRUE 1

byte getbyte( char* );

// MEMORY HELPER FNC'S
char* mem( large numBytes );
char* memp( large numParts, large numBytes );
void* cmem( large nb )	{ return calloc( nb,1 ); }
char* zmem( large nb );
char* zmem( large nb );

#endif

