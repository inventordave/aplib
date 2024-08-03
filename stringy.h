// STRINGY_H
// STRING METHODS //

#ifndef DAVELIB_STRINGY_V1
#define DAVELIB_STRINGY_V1

// INC'S
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colour.h"

short int CC_NULL = 0;

short int CC_FG_BLACK = 1;
short int CC_FG_RED = 2;
short int CC_FG_GREEN = 3;
short int CC_FG_YELLOW = 4;
short int CC_FG_BLUE = 5;
short int CC_FG_MAGENTA = 6;
short int CC_FG_CYAN = 7;
short int CC_FG_WHITE = 8;

short int CC_FG_BRIGHT_BLACK = 9;
short int CC_FG_BRIGHT_RED = 10;
short int CC_FG_BRIGHT_GREEN = 11;
short int CC_FG_BRIGHT_YELLOW = 12;
short int CC_FG_BRIGHT_BLUE = 13;
short int CC_FG_BRIGHT_MAGENTA = 14;
short int CC_FG_BRIGHT_CYAN = 15;
short int CC_FG_BRIGHT_WHITE = 16;

short int CC_BG_BLACK = 17;
short int CC_BG_RED = 18;
short int CC_BG_GREEN = 19;
short int CC_BG_YELLOW = 20;
short int CC_BG_BLUE = 21;
short int CC_BG_MAGENTA = 22;
short int CC_BG_CYAN = 23;
short int CC_BG_WHITE = 24;

short int CC_BG_BRIGHT_BLACK = 25;
short int CC_BG_BRIGHT_RED = 26;
short int CC_BG_BRIGHT_GREEN = 27;
short int CC_BG_BRIGHT_YELLOW = 28;
short int CC_BG_BRIGHT_BLUE = 29;
short int CC_BG_BRIGHT_MAGENTA = 30;
short int CC_BG_BRIGHT_CYAN = 31;
short int CC_BG_BRIGHT_WHITE = 32;

short int CC_NORMAL = 33;

short int CC_BOLD = 34;
short int CC_ITALIC = 35;
short int CC_UNDERLINE = 36;
short int CC_STRIKETHROUGH = 37;
short int CC_CAPSLOCK_ON = 38;
short int CC_CAPSLOCK_OFF = 39;

short int CC_UNSWITCH; // for rolling-back most recent control instruction.

short int CC_HIDDEN_ON;
short int CC_HIDDEN_OFF;
short int CC_HIDDEN_MASKTYPE_BG;
short int CC_HIDDEN_MASKTYPE_COLOR; // if selected "colour_h" subsystem needs to know whch color.

char* getVTCodeString( char cc )	{

	switch( cc )	{
		
		case 
		
	}
}


char* ANSIVT( char* str, char cc[], LARGE offsets[], int _frees )	{

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
	
	return _;
}

// ADD NULL-TERMINATOR TO CHAR*, REQUIRES INDEX
#define addnullt( _,i ) _[i]='\0';

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

