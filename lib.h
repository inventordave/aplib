// LIB_H

// DAVELIB. Useful helper elements.

#ifndef DAVELIB_HEADER_FILE
#define DAVELIB_HEADER_FILE

// INC'S
#include <stdbool.h>
#include <string.h>
#include "io.h"

// USEFUL CONSTANTS
#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0
#define SUCCESS 1
#define FAIL 0
#define LEFT 171
#define RIGHT 79

// CUSTOM TYPES
#define ascii '0'
#define large long long int
#define L large
#define LARGE large

  
// 'TOGGLE'
#define TOGGLE bool
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

