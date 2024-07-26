// LIB_H

#include "io.h"
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define formatString sprintf

#define statusCode int

#define colouriser colorMode
#define colourizer colouriser


void pause(); // waits for user to press a key before continuing.
void arg_assert( int argc, int min ); // custom assert() for number of args passed on cmd-line.


