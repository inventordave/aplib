#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LARGE long long int
#define L LARGE
#define large L

#define strlen strlen_
L strlen_(char * str)	{
	
	large i = 0;
	while( str[i++] != '\0' )
		;
	return i-1;
}


char* unpack( char* );
char* pack( char* );


int main( int argc, char** argv )	{

	char* _;

	if( argc<2 )
		_ = strdup( "12345678765432922" );
	else
		_ = argv[1];

	printf( "string := \"%s\" (length: %d)\n", _, strlen( _ ) );
	
	char* packedstr = pack( _ );

	printf( "packedstr := \"%s\" (length: %d)\n", packedstr, strlen( packedstr ) );
	
	char* unpackedstr = unpack( packedstr );
	
	printf( "unpacked := \"%s\" (length: %d)\n", unpackedstr, strlen( unpackedstr ) );
	
	return strcmp( _,unpackedstr );
}


// assumes a packed-digit string of 4 bits/digit.
char* unpack( char* _ ) {
	
	L strlen__ = strlen( _ );

	int BITMASK_LOWER = 15;		// 00001111 (8+4+2+1)
	int BITMASK_UPPER = 255-15; // 11110000 (128+64+32+16)
	char t;
	
	L i, j;
	char* _U = (char*)calloc( 1, (2<<strlen__) + 1 );
	for( i=0, j=0; i<strlen__; i++ ) {
		
		t = _[i] & BITMASK_LOWER;
		if( t==10 )	t=0;
		
		_U[j++] = t + '0';
		
		t = (_[i] & BITMASK_UPPER)>>4;
		if( t==0 )
			_U[j++] = '\0';
		else if( t==10 )
			_U[j++] = '0';
		else
			_U[j++] = t + '0';

	}

	if( _U[j-1]!='\0' )
		_U[j] = '\0';

	return _U;
}

/**

a-z0-9		+ - * / = _ . , ! ? ~ % []{}() @ # $ \ and an nbsp whitespacecode.

(definitely need 5 bits, to encode 26 alphabetical chars a-z and the escape code \ 
which would leave 5 codes to fit in [0, 31]
If I just used a-z and \ then everything else, 0-9, null, etc would need to fit between [\a, \z], which gives
me 26 alphabet codes 'a' to 'z', the escape delimeter '\', 26 meta codes '\a' to '\z' and meta code '\\'

which is 54 unique codes (a-z and \ makes 27. Escaping each \x gives 27*2, which is 54 codes/metacodes).

27 primitives, a to z and '\', gives 5 spare primitive encodings, as the range of 5 bits is 32 [min=0, max=31]






a code for capitalisation, or an escape sequence to represent capitalisation, such as \c4 might indicate that the next 4 alphabet...
chars be capitalised.

->	\c0 might indicate a proceeding sequence is chomsky-language code
->	\ca might indicate capitalisation. note that the escape sequence is \ca, so capitalise a proceeding 'a', it would be \caa
	and therefore to capitalise 'x' would be \cax
->	\cn might indicate an entity name is proceeding.

a code for repetition. \l, eg:

\la1024y might repeat the letter 'y' 1024 times.
\ln1024.0 might repeat the didigt '0' 1024 times.

\l (a|n) (decimal sequence indicating amount of repetitions) ( (.[numerical_digit]) | alphabetical_char ) // note the leading '.' for numeric


\d		delimeter, \d1 := (	\d2 := [	\d3 := {
		\d1a = (, \d1b = ), \d2a = [, \d2b = ], \d3a = {, \d3b = }
\0		nul
Just one escape and an operand to indicate base number system, eg: \b8 would be octal, base 8.
\bb \bl might mean booleanbitwise and booleanlogical
\a and
\| or
\! not
\t
\n
\r
\e

extra candidate escape sequences
\%[a-z0-9_@ ... etc ...]


{base,exponent}
{key,value}
{author}
{utc}

*/

char encode( char c )	{

	#define ESCAPECODE '\'
	#define CODE1 '.'
	#define CODE2 '\0'
	#define CODE3 '%'
	#define CODE4 '*'
	#define CODE5 '+'

	char _;
	
	if( (c>='a')&&(c<='z') )
		; // alphabet char

	if( c=='\' )
		; // the escape delimeter

	switch( c )	{

		break;
		case CODE1:

			break;
			
		break;
		case CODE2:

			break;
			
		break;
		case CODE3:

			break;
			
		break;
		case CODE4:

			break;

		break;
		case CODE5:
			
			break;
		
		break;
		default:

			break;
	}

	// ... algorithm goes here

	return _;
}

pack5bits( char* _ )	{

	int i;
	char* packed;

	int strlen__ = strlen( _ );
	char u = 0;
	char p = 0;
	char t = 0;
	for( i=0; i<strlen__; i++ )	{
		u = _[i];

		t = encode( u );

		
	}
	
}

// assumes an unpacked string of 1 char per decimal digit.
char* pack( char* _ ) {
	
	L strlen__ = strlen( _ );

	char* _P = (char*)calloc( 1, (strlen__>>1) + 2 );
	char t;
	
	L i,j;
	for( i=0,j=0; i<strlen__-1; i+=2, j++ )	{
		
		t = _[i] - '0';
		if( t==0 )
			t=10;
		
		char nd = (_[i+1] - '0');
		if( nd==0 )
			nd=10;
		
		t += ( nd << 4 );
		
		_P[j] = t;		
	}

	if( i==strlen__-1 )	{

	t = _[i] - '0';
	if( t==0 )
		t=10;
	
	_P[j++] = t;
	
	}
	_P[j] = '\0';
	return _P;
}

