// APLIB_PRETTY_PRINTER

#ifndef DAVE_APLIB_PP
#define DAVE_APLIB_PP

// INFORMATIVE SECTION
// This subsystem provides colourization, and other formatting features, for APLIB output (stdout).


// STD INC'S
#include <stdio.h>
#include <string.h>

// CUSTOM INC'S
#include "aplib.h"
#include "colour.h"

// DATA STRUCTURES/TYPES


// FNC PROTOTYPES
void setFGColor( int cc );
void setBGColor( int cc );
void setStyle( int sc ); // eg, +i, +b, -i, -b, and so on.
char * truncateAP( AP A );

char * generateSVG( APExp exp );
char * generateLatex_Exp( APExp exp );
char * generateLatex_Number( AP A );

char * formatSign(char sign);
char * formatBinary(char * bin_string);
char * formatAP(AP A);

void normal();
char * c(char * str, char * col);
void print( char * str );

#endif

