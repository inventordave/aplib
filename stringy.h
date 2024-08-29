// STRINGY_H
// STRING METHODS //

#ifndef DAVELIB_STRINGY_V1
#define DAVELIB_STRINGY_V1

// INC'S
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colour.h"

#define scint signed short int
extern scint CC_NULL;

extern scint CC_FG_BLACK;
extern scint CC_FG_RED;
extern scint CC_FG_GREEN;
extern scint CC_FG_YELLOW;
extern scint CC_FG_BLUE;
extern scint CC_FG_MAGENTA;
extern scint CC_FG_CYAN;
extern scint CC_FG_WHITE;

extern scint CC_FG_BRIGHT_BLACK;
extern scint CC_FG_BRIGHT_RED;
extern scint CC_FG_BRIGHT_GREEN;
extern scint CC_FG_BRIGHT_YELLOW;
extern scint CC_FG_BRIGHT_BLUE;
extern scint CC_FG_BRIGHT_MAGENTA;
extern scint CC_FG_BRIGHT_CYAN;
extern scint CC_FG_BRIGHT_WHITE;

extern scint CC_BG_BLACK;
extern scint CC_BG_RED;
extern scint CC_BG_GREEN;
extern scint CC_BG_YELLOW;
extern scint CC_BG_BLUE;
extern scint CC_BG_MAGENTA;
extern scint CC_BG_CYAN;
extern scint CC_BG_WHITE;

extern scint CC_BG_BRIGHT_BLACK;
extern scint CC_BG_BRIGHT_RED;
extern scint CC_BG_BRIGHT_GREEN;
extern scint CC_BG_BRIGHT_YELLOW;
extern scint CC_BG_BRIGHT_BLUE;
extern scint CC_BG_BRIGHT_MAGENTA;
extern scint CC_BG_BRIGHT_CYAN;
extern scint CC_BG_BRIGHT_WHITE;

extern scint CC_NORMAL;

extern scint CC_BOLD;
extern scint CC_ITALIC;
extern scint CC_UNDERLINE;
extern scint CC_STRIKETHROUGH;
extern scint CC_CAPSLOCK_ON;
extern scint CC_CAPSLOCK_OFF;

extern scint CC_UNSWITCH; // for rolling-back most recent control instruction.

extern scint CC_HIDDEN_ON;
extern scint CC_HIDDEN_OFF;
extern scint CC_HIDDEN_MASKTYPE_BG;
extern scint CC_HIDDEN_MASKTYPE_COLOR; // if selected "colour_h" subsystem needs to know whch color.

void PrintASCIITable(char start, char end);


// SAFE-CONCATENATE
extern char* safecat(char* s, char* rhs);

extern char* int2str(int v);
extern int str2int(char*);

// SUGAR
extern int streq( char*,char* ); // returns true (1) if the 2 c-strings match, as it should...
int seq(char *a, char *b); // actually returns 0 for non-match, 1 for match.

extern scint cmp_dstr( char*, char* );

#define strcmp strcmp_
extern int strcmp_( char* LHS, char* RHS );

// ADD NULL-TERMINATOR TO CHAR*, REQUIRES INDEX
#define addnullt( _,i ) _[i]='\0';

// Basic string-safety check, removes verboten narrow-chars as defined in function body.
extern char* sanitizeStr( char* );

// places string at 'in' into 'out' in reverse sequence.
char* flipstr(char* in, char* out); 




// ITOA() FUNCTION "ITOAD()"
extern char* itoad(int v);

// CONCATENATE (VARIADIC FNC)
extern char* cat(int c, char * s, ...);


// STRING-SAFETY METHODS //

extern char* getstring( char* in );

extern void addnult( char*, unsigned long long int );

#endif

