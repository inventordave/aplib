// STRINGY_H
// STRING METHODS //

#ifndef DAVELIB_STRINGY_V1
#define DAVELIB_STRINGY_V1

// INC'S
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colour.h"


// SANITIZESTR: General method for pre-processing of an input c-string (safety).
char* sanitizeStr( char* A );

// ITOA() FUNCTION "ITOAD()"
char * itoad(int v);

// CONCATENATE (VARIADIC FNC)
char * cat(int c, char * s, ...);

// STRING-SAFETY METHODS //

// SAFE-CONCATENATE
char * safecat(char* s, char* rhs);


#endif

