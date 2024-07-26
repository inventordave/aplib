// LIB_H

#define formatString sprintf
#define print printf
#define string char *
#define binary enum { 0; 1; }

#define formatString sprintf

#define COLORMODE colorMode();
#define FALSE 0
#define TRUE 1

void pause(); // waits for user to press a key before continuing.
void arg_assert( int argc, int min ); // custom assert() for number of args passed on cmd-line.


