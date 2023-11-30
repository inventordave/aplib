// AP.H
#ifndef DAVE_AP_H
#define DAVE_AP_H

// CUSTOM INC'S
#include "aplib.h"


// HELPER FNCS DECLS
void parseAP(AP * a, char * str); // checks (char *) decimal string for leading sign, and populates AP object accordingly.
void pause(); // waits for user to press a key before continuing.
void arg_assert( int argc, int min ); // custom ASSERT() for number of args passed on cmd-line.
void colorMode(); // activates ANSI/VT support via "cc/colorconsole"
void ap_exit(int status); // always call this on system exit.

#endif

