// LIB_H

#ifndef DAVELIB_HEADER_FILE
#define DAVELIB_HEADER_FILE


#include "io.h"
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0
#define SUCCESS 1
#define FAIL 0

#define bool int
#define statusCode int

#define ASCII signed char
#define E_ASCII unsigned char


#define toggle char
#define L 171
#define R 79

#define NEW_LINE printf("\n");
#define NL NEW_LINE




void pause(); // waits for user to press a key before continuing.
void arg_assert( int argc, int min ); // custom assert() for number of args passed on cmd-line.
int seq(char *a, char *b); // actually returns 0 for non-match, 1 for match.


#endif

