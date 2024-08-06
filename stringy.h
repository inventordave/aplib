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
scint CC_NULL = 0;

scint CC_FG_BLACK = 1;
scint CC_FG_RED = 2;
scint CC_FG_GREEN = 3;
scint CC_FG_YELLOW = 4;
scint CC_FG_BLUE = 5;
scint CC_FG_MAGENTA = 6;
scint CC_FG_CYAN = 7;
scint CC_FG_WHITE = 8;

scint CC_FG_BRIGHT_BLACK = 9;
scint CC_FG_BRIGHT_RED = 10;
scint CC_FG_BRIGHT_GREEN = 11;
scint CC_FG_BRIGHT_YELLOW = 12;
scint CC_FG_BRIGHT_BLUE = 13;
scint CC_FG_BRIGHT_MAGENTA = 14;
scint CC_FG_BRIGHT_CYAN = 15;
scint CC_FG_BRIGHT_WHITE = 16;

scint CC_BG_BLACK = 17;
scint CC_BG_RED = 18;
scint CC_BG_GREEN = 19;
scint CC_BG_YELLOW = 20;
scint CC_BG_BLUE = 21;
scint CC_BG_MAGENTA = 22;
scint CC_BG_CYAN = 23;
scint CC_BG_WHITE = 24;

scint CC_BG_BRIGHT_BLACK = 25;
scint CC_BG_BRIGHT_RED = 26;
scint CC_BG_BRIGHT_GREEN = 27;
scint CC_BG_BRIGHT_YELLOW = 28;
scint CC_BG_BRIGHT_BLUE = 29;
scint CC_BG_BRIGHT_MAGENTA = 30;
scint CC_BG_BRIGHT_CYAN = 31;
scint CC_BG_BRIGHT_WHITE = 32;

scint CC_NORMAL = 33;

scint CC_BOLD = 34;
scint CC_ITALIC = 35;
scint CC_UNDERLINE = 36;
scint CC_STRIKETHROUGH = 37;
scint CC_CAPSLOCK_ON = 38;
scint CC_CAPSLOCK_OFF = 39;

scint CC_UNSWITCH; // for rolling-back most recent control instruction.

scint CC_HIDDEN_ON;
scint CC_HIDDEN_OFF;
scint CC_HIDDEN_MASKTYPE_BG;
scint CC_HIDDEN_MASKTYPE_COLOR; // if selected "colour_h" subsystem needs to know whch color.

char* getVTCodeString( char cc )	{

	switch( cc )	{
		
		case 
		
	}
}

char* ANSIVT( char* str, char cc[], LARGE offsets[], int _frees ){
LARGE str_width = strlen(str);
LARGE width = str_width + (strlen(cc)*VTCODEWIDTH);
char* _ = mem( width );
char* bucket = mem( width );
char* vtcodestr;

LARGE q=0;
LARGE t=0;
while( t<str_width ){

	for( LARGE p=0; p<offsets[q]; p++ ) // offsets are relative.
		bucket[p] = str[t++];
	bucket[p] = '\0';
	
	safecat( _,bucket );
	vtcodestr = getVTCodeString( *cc );
	safecat( _,vtcodestr );
	
	free( vtcodestr );
	
	++cc;
	++q;
	
	if( *cc == '\0' ){
		
		LARGE y = strlen(_);
		for( LARGE x=t;x<str_width; x++ )
			_[y++]=str[x];
		_[y] = '\0';			
		break;}}

return _; }

// SUGAR
int streq(char *a, char *b){ // returns true (1) if the 2 c-strings match, as it should...
return (strcmp(a, b) == 0);}

// ADD NULL-TERMINATOR TO CHAR*, REQUIRES INDEX
#define addnullt( _,i ) _[i]='\0';

// SANITIZESTR: General method for pre-processing of an input c-string (safety).
char* sanitizeStr( char* );

// ITOA() FUNCTION "ITOAD()"
char * itoad(int v);

// CONCATENATE (VARIADIC FNC)
char * cat(int c, char * s, ...);

// STRING-SAFETY METHODS //

// SAFE-CONCATENATE
char * safecat(char* s, char* rhs);


#endif

