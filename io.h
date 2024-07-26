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
#define large unsigned long long int

#define FALSE 0
#define TRUE 1

byte getbyte( char* );

char* memp( large numParts, large numBytes );

char* mem( large );
char* memc( large );
char* memz( large );

#endif

