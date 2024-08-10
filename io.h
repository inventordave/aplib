// IO_H

#ifndef DAVELIB_IO
#define DAVELIB_IO

#include <stdio.h>
#include <stdlib.h>

#define string char *
//#define in getchar
//#define out putchar

#define byte char
#define octet unsigned char
#define large unsigned long long int

#define FALSE 0
#define TRUE 1

byte getbyte( char* );

// MEMORY HELPER FNC'S
extern char* mem( large numBytes );
extern char* memp( large numParts, large numBytes );
extern void* cmem( large nb );
extern char* zmem( large nb );

#endif

