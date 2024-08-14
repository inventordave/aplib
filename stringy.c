// STRINGY_C
// DAVE'S STRING LIBRARY, PACKAGED WITH DAVELIB //

// INC'S
#include <stdarg.h>
#include "stringy.h"


int streq( char* a, char* b ){
	
	return !strcmp( a,b );
}


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


int str2int(char* input)	{
	
	int len = strlen(input), i = 0, result = 0;
	
	if (input[0] == '-')
		i = 1;

	for(; i<len; i++)
		result = result * 10 + ( input[i] - '0' );
	
	if (input[0] == '-')
		result = 0 - result;
	
	return result;
}


// STRCMP: Returns 0 for match, +n for larger LHS, -n for larger RHS.

int strcmp_( char* LHS, char* RHS ){

if( strlen(LHS)==strlen(RHS) ){
for( unsigned long long int i=0; i<strlen(LHS); i++ ){
if( LHS[i]==RHS[i] )
	continue;
	else return LHS[i]-RHS[i];}}
else
	return strlen(LHS)-strlen(RHS);

return 0; }



// SANITIZESTR: General method for pre-processing of an input c-string (safety).
char* sanitizeStr( char* A )	{
	
	char * B = (char *)malloc( strlen(A)+1 );
	char * _ = B;
	
	while((*A) != '\0')	{
		
		switch(*A)	{

			case 92: // \ backslash
			case 34: // " double-quote
			case 42: // * star
			case 47: // / forward-slash
			case 58: // : colon
			case 60: // < lt
			case 62: // > gt
			case 63: // ? question-mark
			case 124:// | pipe

				// printf( "Invalid char ('%c') (%d).\n", *_, *_ );
				// Uncomment above line to see reporting to stdout of detected invalid chars in the input string.
				*B = '.'; // Arbitrary printable-char to replace invalid char with.
				break;
			
			default:
				*B = *A; 
				//printf( "char ok: '%c'\n", (*str) );
				break;	
		}
		
		++A;
		++B;
	}
	
	*B = '\0';
	
	return _;
}


// INT -> CSTR
char * itoad(int v)	{
	
	// snprintf (buff, sizeof(buf), "%d",n); // print int 'n' into the char[] buffer
	char * _ = (char*)malloc(16);
	
	snprintf ( _, 16, "%d", v );
	
	return _;
}


// CAT(INT NUM_STRINGS, ...)
// 1ST ARG IS NUMBER OF SUBSEQUENT CSTRING ARGS - VARIADIC
// DEPS: SAFECAT()
char * cat(int c, char * s, ...)	{
	
	va_list ap;
	char * _ = (char *)malloc(4096);
	_[4095] = '\0';
	
	strcpy(_, s);

	va_start(ap, c);
	for(scint i=0; i<c; i++)	{
	
		_ = safecat(_, (char *)va_arg(ap, char*));
	}
	va_end(ap);
	
	//DEBUG_MSG("exiting cat()")
	return _;
}



 char* int2str(int v)	{
	
	char* _ = (char*)malloc( 32+1 );
	sprintf( _, "%d", v );
	
	return _;
}

void addnult( char* _, unsigned long long int i ){

	_[i] = '\0';
}


char* getstring( char* in ){
	
	unsigned long long int str_length = strlen( in );
	char* _ = (char*)malloc( str_length+1 );
	
	unsigned long long int i;
	for( i=0; i<str_length; i++ )
		_[i] = in[i];
	
	_[i] = '\0';
	
	return _;
}




#define ERR_NP_CHAR 1
char * safecat( char* s, char* rhs )	{
	
	// SAFETY
	if( (s==NULL) || (rhs==NULL) )
		return s;
	
	// check s, rhs, for nonprintable chars (0-31)
	
	//unsigned int i = 0;
	char ch = '\0', chr = '\0';
	char * _s = s; char * _rhs = rhs;
	
	do	{
		
		if( (ch = _s[0]) )	{
			
			if( ch < (char)32 || ( (ch > 127) & (ch < 160) ) )
				return (char *)ERR_NP_CHAR;
		} // dangling-else!
		else
			--_s;

		if( (chr = _rhs[0]) )	{
		
			if( chr < (char)32 || ( (ch > 127) & (ch < 160) ) )
				return (char *)ERR_NP_CHAR;
		} // dangling-else!
		else
			--_rhs;
		
		++_s;
		++_rhs;

	} while (ch != '\0' || chr != '\0');
	
	char * _ = (char *)malloc( strlen(s) + strlen(rhs) +1 );
	if( _ == NULL )
		return (char *)NULL;
	
	strcpy(_, s);
	strcat(_, rhs);
	
	free(s);
	s = malloc(strlen(_) + 1);
	if( s == NULL )
		return (char *)NULL;
	
	strcpy(s, _);
	
	free(_);
	// Do safety check on composite string _, before returning the cstring pointer to the caller.
	// ... 1. remove any non-alphabetical control codes, though printable.

	return s;
}

