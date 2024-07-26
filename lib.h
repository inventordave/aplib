// LIB_H

// DAVELIB. Useful helper elements.

#ifndef DAVELIB_HEADER_FILE
#define DAVELIB_HEADER_FILE

// INC'S
#include "io.h"

// USEFUL CONSTANTS
#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0
#define SUCCESS 1
#define FAIL 0
#define L 171
#define R 79

// CUSTOM TYPES
#define large unsigned long long int
#define LARGE large
#define bool int
#define statusCode int
#define ASCII signed char
#define ascii ASCII
#define E_ASCII unsigned char
#define e_ascii E_ASCII

// 'TOGGLE'
#define TOGGLE char
#define toggle TOGGLE

toggle fliptoggle( toggle* t );

// SUGAR
#define NEW_LINE printf("\n");
#define NL NEW_LINE

// DAVELIB HELPER FNC'S
char* sanitizeStr( char* _ ); // Basic string-safety check, removes verboten narrow-chars defined in function body.
char* flipstr(char * in, char * out); // places string at 'in' into 'out' in reverse sequence.
int seq(char *a, char *b); // actually returns 0 for non-match, 1 for match.

void pause(); // waits for user to press a key (in console mode) before continuing.
void arg_assert( int argc, int min ); // custom assert() for number of args passed on cmd-line.

#endif

