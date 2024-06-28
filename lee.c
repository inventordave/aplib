//!! tests.h  
// TESTS.H


#define DAVE_TESTS_H


// TEST FUNCTION DECLS
void dec_2_bin_2_dec(int argc, char **argv);
void basicTest(int argc, char **argv); // ADD, SUB, MUL, EXP - requires 2 decimal strings in argv[1]/argv[2].
void fs_test1(int argc, char **argv);
void q_test(int argc, char **argv);
void readFloatTest(int argc, char **argv);
void writeFloatTest(int argc, char **argv);
void test2kMax(int argc, char **argv);

void notTest(int argc, char ** argv);
void andTest(int argc, char ** argv);
void orTest(int argc, char ** argv);
void exOrTest(int argc, char ** argv);


//!! ansivt2.h


	#define BYPASS_ANSIVT_GUARD 1
	
	extern char ansivt;
	
	extern char FG_BLACK[8];
	extern char FG_RED[8];
	extern char FG_GREEN[8];
	extern char FG_YELLOW[8];
	extern char FG_BLUE[8];
	extern char FG_MAGENTA[8];
	extern char FG_CYAN[8];
	extern char FG_WHITE[8];

	extern char FG_BRIGHT_BLACK[8];
	extern char FG_BRIGHT_RED[8];
	extern char FG_BRIGHT_GREEN[8];
	extern char FG_BRIGHT_YELLOW[8];
	extern char FG_BRIGHT_BLUE[8];
	extern char FG_BRIGHT_MAGENTA[8];
	extern char FG_BRIGHT_CYAN[8];
	extern char FG_BRIGHT_WHITE[8];

	extern char BG_BLACK[8];
	extern char BG_RED[8];
	extern char BG_GREEN[8];
	extern char BG_YELLOW[8];
	extern char BG_BLUE[8];
	extern char BG_MAGENTA[8];
	extern char BG_CYAN[8];
	extern char BG_WHITE[8];

	extern char BG_BRIGHT_BLACK[8];
	extern char BG_BRIGHT_RED[8];
	extern char BG_BRIGHT_GREEN[8];
	extern char BG_BRIGHT_YELLOW[8];
	extern char BG_BRIGHT_BLUE[8];
	extern char BG_BRIGHT_MAGENTA[8];
	extern char BG_BRIGHT_CYAN[8];
	extern char BG_BRIGHT_WHITE[8];

	extern char NORMAL[8];
	
	extern char resetAnsiVtCodes(char);
	void swap4color( char *, char * );



//!! ansivt2.c

#include <string.h>

	char ansivt;
	
	char FG_BLACK[8];
	char FG_RED[8];
	char FG_GREEN[8];
	char FG_YELLOW[8];
	char FG_BLUE[8];
	char FG_MAGENTA[8];
	char FG_CYAN[8];
	char FG_WHITE[8];

	char FG_BRIGHT_BLACK[8];
	char FG_BRIGHT_RED[8];
	char FG_BRIGHT_GREEN[8];
	char FG_BRIGHT_YELLOW[8];
	char FG_BRIGHT_BLUE[8];
	char FG_BRIGHT_MAGENTA[8];
	char FG_BRIGHT_CYAN[8];
	char FG_BRIGHT_WHITE[8];

	char BG_BLACK[8];
	char BG_RED[8];
	char BG_GREEN[8];
	char BG_YELLOW[8];
	char BG_BLUE[8];
	char BG_MAGENTA[8];
	char BG_CYAN[8];
	char BG_WHITE[8];

	char BG_BRIGHT_BLACK[8];
	char BG_BRIGHT_RED[8];
	char BG_BRIGHT_GREEN[8];
	char BG_BRIGHT_YELLOW[8];
	char BG_BRIGHT_BLUE[8];
	char BG_BRIGHT_MAGENTA[8];
	char BG_BRIGHT_CYAN[8];
	char BG_BRIGHT_WHITE[8];

	char NORMAL[8];

char resetAnsiVtCodes(char f)	{
	
	if(f == 0)	{

		strcpy((char *)FG_BLACK, "");
		strcpy((char *)FG_RED, "");
		strcpy((char *)FG_GREEN, "");
		strcpy((char *)FG_YELLOW, "");
		strcpy((char *)FG_BLUE, "");
		strcpy((char *)FG_MAGENTA, "");
		strcpy((char *)FG_CYAN, "");
		strcpy((char *)FG_WHITE, "");

		strcpy((char *)FG_BRIGHT_BLACK, "");
		strcpy((char *)FG_BRIGHT_RED, "");
		strcpy((char *)FG_BRIGHT_GREEN, "");
		strcpy((char *)FG_BRIGHT_YELLOW, "");
		strcpy((char *)FG_BRIGHT_BLUE, "");
		strcpy((char *)FG_BRIGHT_MAGENTA, "");
		strcpy((char *)FG_BRIGHT_CYAN, "");
		strcpy((char *)FG_BRIGHT_WHITE, "");

		strcpy((char *)BG_BLACK, "");
		strcpy((char *)BG_RED, "");
		strcpy((char *)BG_GREEN, "");
		strcpy((char *)BG_YELLOW, "");
		strcpy((char *)BG_BLUE, "");
		strcpy((char *)BG_MAGENTA, "");
		strcpy((char *)BG_CYAN, "");
		strcpy((char *)BG_WHITE, "");

		strcpy((char *)BG_BRIGHT_BLACK, "");
		strcpy((char *)BG_BRIGHT_RED, "");
		strcpy((char *)BG_BRIGHT_GREEN, "");
		strcpy((char *)BG_BRIGHT_YELLOW, "");
		strcpy((char *)BG_BRIGHT_BLUE, "");
		strcpy((char *)BG_BRIGHT_MAGENTA, "");
		strcpy((char *)BG_BRIGHT_CYAN, "");
		strcpy((char *)BG_BRIGHT_WHITE, "");

		strcpy((char *)NORMAL, "");
	}
	
	else if(f == 1)	{
		
		strcpy((char *)FG_BLACK, "[30m");
		strcpy((char *)FG_RED, "[31m");
		strcpy((char *)FG_GREEN, "[32m");
		strcpy((char *)FG_YELLOW, "[33m");
		strcpy((char *)FG_BLUE, "[34m");
		strcpy((char *)FG_MAGENTA, "[35m");
		strcpy((char *)FG_CYAN, "[36m");
		strcpy((char *)FG_WHITE, "[37m");

		strcpy((char *)FG_BRIGHT_BLACK, "[90m");
		strcpy((char *)FG_BRIGHT_RED, "[91m");
		strcpy((char *)FG_BRIGHT_GREEN, "[92m");
		strcpy((char *)FG_BRIGHT_YELLOW, "[93m");
		strcpy((char *)FG_BRIGHT_BLUE, "[94m");
		strcpy((char *)FG_BRIGHT_MAGENTA, "[95m");
		strcpy((char *)FG_BRIGHT_CYAN, "[96m");
		strcpy((char *)FG_BRIGHT_WHITE, "[97m");

		strcpy((char *)BG_BLACK, "[40m");
		strcpy((char *)BG_RED, "[41m");
		strcpy((char *)BG_GREEN, "[42m");
		strcpy((char *)BG_YELLOW, "[43m");
		strcpy((char *)BG_BLUE, "[44m");
		strcpy((char *)BG_MAGENTA, "[45m");
		strcpy((char *)BG_CYAN, "[46m");
		strcpy((char *)BG_WHITE, "[47m");

		strcpy((char *)BG_BRIGHT_BLACK, "[100m");
		strcpy((char *)BG_BRIGHT_RED, "[101m");
		strcpy((char *)BG_BRIGHT_GREEN, "[102m");
		strcpy((char *)BG_BRIGHT_YELLOW, "[103m");
		strcpy((char *)BG_BRIGHT_BLUE, "[104m");
		strcpy((char *)BG_BRIGHT_MAGENTA, "[105m");
		strcpy((char *)BG_BRIGHT_CYAN, "[106m");
		strcpy((char *)BG_BRIGHT_WHITE, "[107m");

		strcpy((char *)NORMAL, "[0m");
	}
	
	return (ansivt = f);
}

void swap4color( char * fg, char * bg )	{
	
	if( strlen(fg)==0 || !strcmp(fg,"0") )
		goto _bg;
	
	if( !strcmp( fg, "black" ) )	{
		strcpy( fg, FG_BLACK );
		goto _bg;
	}
	if( !strcmp( fg, "red" ) )	{
		strcpy( fg, FG_RED );
		goto _bg;
	}
	if( !strcmp( fg, "green" ) )	{
		strcpy( fg, FG_GREEN );
		goto _bg;
	}
	if( !strcmp( fg, "yellow" ) )	{
		strcpy( fg, FG_YELLOW );
		goto _bg;
	}
	if( !strcmp( fg, "blue" ) )	{
		strcpy( fg, FG_BLUE );
		goto _bg;
	}
	if( !strcmp( fg, "magenta" ) )	{
		strcpy( fg, FG_MAGENTA );
		goto _bg;
	}
	if( !strcmp( fg, "cyan" ) )	{
		strcpy( fg, FG_CYAN );
		goto _bg;
	}
	if( !strcmp( fg, "white" ) )	{
		strcpy( fg, FG_WHITE );
		goto _bg;
	}
	if( !strcmp( fg, "bright_black" ) )	{
		strcpy( fg, FG_BRIGHT_BLACK );
		goto _bg;
	}
	if( !strcmp( fg, "bright_red" ) )	{
		strcpy( fg, FG_BRIGHT_RED );
		goto _bg;
	}
	if( !strcmp( fg, "bright_green" ) )	{
		strcpy( fg, FG_BRIGHT_GREEN );
		goto _bg;
	}
	if( !strcmp( fg, "bright_yellow" ) )	{
		strcpy( fg, FG_BRIGHT_YELLOW );
		goto _bg;
	}
	if( !strcmp( fg, "bright_blue" ) )	{
		strcpy( fg, FG_BRIGHT_BLUE );
		goto _bg;
	}
	if( !strcmp( fg, "bright_magenta" ) )	{
		strcpy( fg, FG_BRIGHT_MAGENTA );
		goto _bg;
	}
	if( !strcmp( fg, "bright_cyan" ) )	{
		strcpy( fg, FG_BRIGHT_CYAN );
		goto _bg;
	}
	if( !strcmp( fg, "bright_white" ) )	{
		strcpy( fg, FG_BRIGHT_WHITE );
		goto _bg;
	}

		return; // non-null invalid entry
	
	_bg:
	
	if( strlen(bg)==0 )	{
	
		return;
	}
	
	if( !strcmp( bg, "black" ) )	{
		strcpy( bg, BG_BLACK );

	}
	if( !strcmp( bg, "red" ) )	{
		strcpy( bg, BG_RED );
		
	}
	if( !strcmp( bg, "green" ) )	{
		strcpy( bg, BG_GREEN );
		
	}
	if( !strcmp( bg, "yellow" ) )	{
		strcpy( bg, BG_YELLOW );
		
	}
	if( !strcmp( bg, "blue" ) )	{
		strcpy( bg, BG_BLUE );
		
	}
	if( !strcmp( bg, "magenta" ) )	{
		strcpy( bg, BG_MAGENTA );
		
	}
	if( !strcmp( bg, "cyan" ) )	{
		strcpy( bg, BG_CYAN );
		
	}
	if( !strcmp( bg, "white" ) )	{
		strcpy( bg, BG_WHITE );
		
	}
	if( !strcmp( bg, "bright_black" ) )	{
		strcpy( bg, BG_BRIGHT_BLACK );
		
	}
	if( !strcmp( bg, "bright_red" ) )	{
		strcpy( bg, BG_BRIGHT_RED );
		
	}
	if( !strcmp( bg, "bright_green" ) )	{
		strcpy( bg, BG_BRIGHT_GREEN );
	
	}
	if( !strcmp( bg, "bright_yellow" ) )	{
		strcpy( bg, BG_BRIGHT_YELLOW );
	
	}
	if( !strcmp( bg, "bright_blue" ) )	{
		strcpy( bg, BG_BRIGHT_BLUE );
		
	}
	if( !strcmp( bg, "bright_magenta" ) )	{
		strcpy( bg, BG_BRIGHT_MAGENTA );
		
	}
	if( !strcmp( bg, "bright_cyan" ) )	{
		strcpy( bg, BG_BRIGHT_CYAN );
		
	}
	if( !strcmp( bg, "bright_white" ) )	{
		strcpy( bg, BG_BRIGHT_WHITE );
		
	}
	
	return;
}







//!! APlib.h

#define DAVE_APLIB

// STDLIB INC'S
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>


// SUGAR
#define NEW_LINE printf("\n");
#define NL NEW_LINE


// STATIC DEFS
#define MAX_LENGTH_AP_PART 1023 //Make this any number of bytes you want. The new_ap(int, int) function will +1 for the '\0' null-terminator. Default = 1023.


// CORE DATA STRUCTURES/TYPES
typedef struct	AP {

	char * major;
	char * minor;
	char sign;
	
	int length;
	int major_length;
	int minor_length;
	
} AP;

typedef char OPCODE; // +, -, *, /, ^ (exp), and, or, not...

typedef struct	APExp	{ // AP op AP

	AP A;
	AP B;

	OPCODE _operator;

} APExp;

typedef struct APExpC	{ // (AP op AP) op (AP op AP)
	
	APExp A;
	APExp B;
	
	OPCODE _operator;

} APExpC;

typedef struct APExpC_2	{ // (APExpC op APExpC)

	APExpC A;
	APExpC B;
	
	OPCODE _operator;
	
} APExpC_2;


// FNC PROTOTYPES
AP new_ap(int maj, int min);
void clear(AP * a);
AP copy(AP * a);
void flip_sign(AP * a);
void set_sign(AP * a, char sym);
char sign(AP * a);

signed short int cmp(AP *, AP *);
signed int overflow(AP * c, int result, signed int k);
char tt(AP a, AP b);
char tt_mul(AP * a, AP * b);

AP ADD(AP a, AP b);
AP SUB(AP a, AP b);

AP MUL(AP a, AP b);
AP DIV(AP a, AP b);
extern int DIV_BY_2_PRINT_ROWS;
AP DIV_BY_2(AP a);

AP EXP(AP a, AP b);

char * AND(char * lhs, char * rhs);
char * OR (char * lhs, char * rhs);
char * EX_OR(char * lhs, char * rhs);
char * NOT(char * v);


int lcm_test(int, int[], int[]);
int LCM(int, int, int);
int GCD(int a, int b, int lcm);

char * DEC_2_BIN(AP input, int packed);
char * BIN_2_DEC(char * bin);

int _2kMax(AP input);
int _2kMin(AP input);

void free_ap(AP a);
int MSD(int num);
void pack_trailing_zeroes( char * curr_row, int array_length, int num_zeroes );
char * fill_leading_zeroes( char * str, int num_zeroes );

int str2int(char *input);
char * int2str(int v);


//!! aplib-output.h 
// APLIB_PRETTY_PRINTER

#define DAVE_APLIB_PP

// INFORMATIVE SECTION
/** This subsystem provides ANSI/VT colourization, and other formatting features, for APlib operations/operands.
Utilizes my repo "ColorConsole", currently located at https://github.com/inventordave2/ColorConsole. That repo will need to be cloned, it's make target invoked ("make colorconsole"), the object file generated by the compiler, and then you would link the output object file "cc.o" to your program object files (APlib, APlib-output, [your-program-TU]) at link-time. A sample make target will be avaiable in this repo's Makefile to show a simple way to link this subsystem to your program that presumably also integrates APlib itself.
*/


// STDLIB INC'S
#include <stdio.h>
#include <string.h>


//ColorConsole object file (see it's repo) needs to be available to link to this file, and presumably a 3rd object file representing
// your user program's entry-point (main function).

/*
DECIMAL/BINARY STRINGS (SIGN SYMBOL +/-)

1 = BRIGHT_BLUE, 0 = BRIGHT_YELLOW (BINARY)
SIGN: + = bright_green, - = bright_red
DEC digits: BRIGHT_WHITE

OPERATORS (ADD, SUB, ETC, +, -, *, /, ^) - BRIGHT_CYAN
Program text output FG_BRIGHT_CYAN

Test function output.

NL: words, punctuation
*/

/**
	extern char FG_BLACK[8];
	extern char FG_RED[8];
	extern char FG_GREEN[8];
	extern char FG_YELLOW[8];
	extern char FG_BLUE[8];
	extern char FG_MAGENTA[8];
	extern char FG_CYAN[8];
	extern char FG_WHITE[8];

	extern char FG_BRIGHT_BLACK[8];
	extern char FG_BRIGHT_RED[8];
	extern char FG_BRIGHT_GREEN[8];
	extern char FG_BRIGHT_YELLOW[8];
	extern char FG_BRIGHT_BLUE[8];
	extern char FG_BRIGHT_MAGENTA[8];
	extern char FG_BRIGHT_CYAN[8];
	extern char FG_BRIGHT_WHITE[8];
*/
// DATA STRUCTURES/TYPES


// FNC PROTOTYPES
void setFGColor( int cc );
void setBGColor( int cc );
void setStyle( int sc ); // eg, +i, +b, -i, -b, and so on.
char * truncateAP( AP a );

char * generateSVG( APExp exp );
char * generateLatex_Exp( APExp exp );
char * generateLatex_Number( AP a );

char * formatSign(char sign);
char * formatBinary(char * bin_string);
char * formatAP(AP a);

void normal();
char * c(char * str, char * col);
void print( char * str );









//!! Dave_IEEE754.h 


#define DAVE_IEEE754

// INFORMATIVE SECTION
/** Here is a simple solution I cooked up for accessing the internal bit-representation of floats.
As my system is little-endian, the LSByte is printed first, and the MSByte printed as the 4th subsequence. This obviously means that the left-most bit of the 4th subsequence (bits 24-31) is the sign bit, for signed r-values. There is a "convert string to big-endian" helper function to format the string properly for printing/screen output.
*/


// STDLIB INC'S
#include <stdlib.h>
#include <string.h>
#include <assert.h>


// CORE DATA STRUCTURES
typedef struct IEEE754	{
	
	char * (*readFloat)( float f );
	char * (*readDouble)( double f );
	
	char * (*convertFloatString2BigEndian)( char * str );
	char * (*convertDoubleString2BigEndian)( char * str );
	
	unsigned short int (*getFloatBit)( char * str, unsigned int offset );
	unsigned short int (*getDoubleBit)( char * str, unsigned int offset );
	
	void (*writeFloat)(float * dest, char * str);
	void (*writeDouble)(double * dest, char * str);

} IEEE754;

typedef struct IEEE754_Float	{

	int sign;
	
	int exponent;

	// NOT COMPLETE!
	int significand;

} IEEE754_Float;


// FNC PROTOTYPES
struct IEEE754 * initIEEE754();

char * IEEE_readFloat( float f );
char * IEEE_readDouble( double f );

void IEEE_writeFloat(float * dest, char * str);
void IEEE_writeDouble(double * dest, char * str);

char * IEEE_convertFloatString2BigEndian( char * str );
char * IEEE_convertDoubleString2BigEndian( char * str );

struct IEEE754_Float * IEEE_writeFloatStruct( float * f );
float IEEE_readFloatStruct( struct IEEE754_Float* f );

unsigned short int IEEE_getFloatBit( char * str, unsigned int offset );
unsigned short int IEEE_getDoubleBit( char * str, unsigned int offset );


//!! ap.h 
// AP.H

#define DAVE_AP_H


// HELPER FNCS DECLS
void parseAP(AP * a, char * str); // checks (char *) decimal string for leading sign, and populates AP object accordingly.
void pause(); // waits for user to press a key before continuing.
void arg_assert( int argc, int min ); // custom ASSERT() for number of args passed on cmd-line.
void colorMode(); // activates ANSI/VT support via "cc/colorconsole"
void ap_exit(int status); // always call this on system exit.


//!! (from getOptions.h)

 int seq(char *a, char *b) { // returns true (1) if the 2 c-strings match, as it should...

	return (strcmp(a, b) == 0);
}


//!! aplib-output.c  
// APLIB-OUTPUT.c





//!! aplib.c  
// APLIB_C

int DIV_BY_2_PRINT_ROWS = 0;

char * AND(char * lhs, char * rhs)	{
	
	char * a;
	char * b;
	
	a = lhs; b = rhs;
	int len = ( strlen(a) >= strlen(b) ? strlen(a) : strlen(b) );
	
	char * b_str = (char *)malloc( len+1 );
	b_str[len] = '\0';

	// both binary string are the same length.
	char A = '0';
	char B = '0';
	
	int t, i, j, k;
	for( i=strlen(a)-1,j=strlen(b)-1, k=len-1; ; i--, j--, k-- )	{
		
		t = 0;
		
		if( i<0 )	{
			
			A = '0';
			++t;
		}
		else
			A = a[i];
		
		if( j<0 )	{
			
			B = '0';
			++t;
		}
		else
			B = b[j];
		
		if( t==2 )
			break;
			
		b_str[k] = '0' + ( (A-'0') & (B-'0') );
	}
	
	assert( k==-1 );
	
	return b_str;
}

char * NOT(char * v)	{
	
	char * output = (char *)malloc( strlen(v) + 1 );
	int i;
	for( i=0; i<strlen(v); i++ )
		if( v[i]=='0' )
			output[i] = '1';
		else if( v[i]=='1' )
			output[i] = '0';
		else
			assert(0);
		
	output[i] = '\0';
	
	return output;
}

char * OR(char * lhs, char * rhs)	{

	char * a;
	char * b;
	
	a = lhs; b = rhs;
	int len = ( strlen(a) >= strlen(b) ? strlen(a) : strlen(b) );
	
	char * b_str = (char *)malloc( len+1 );
	b_str[len] = '\0';

	// both binary string are the same length.
	char A = '0';
	char B = '0';
	
	int t, i, j, k;
	for( i=strlen(a)-1,j=strlen(b)-1, k=len-1; ; i--, j--, k-- )	{
		
		t = 0;
		
		if( i<0 )	{
			
			A = '0';
			++t;
		}
		else
			A = a[i];
		
		if( j<0 )	{
			
			B = '0';
			++t;
		}
		else
			B = b[j];
		
		if( t==2 )
			break;
			
		b_str[k] = '0' + ( (A-'0') | (B-'0') );
	}
	
	assert( k==-1 );
	
	return b_str;
}

char * EX_OR(char * lhs, char * rhs)	{

	char * a;
	char * b;
	
	a = lhs; b = rhs;
	int len = ( strlen(a) >= strlen(b) ? strlen(a) : strlen(b) );
	
	char * b_str = (char *)malloc( len+1 );
	b_str[len] = '\0';

	// both binary string are the same length.
	char A = '0';
	char B = '0';
	
	int t, i, j, k;
	for( i=strlen(a)-1,j=strlen(b)-1, k=len-1; ; i--, j--, k-- )	{

		t = 0;

		if( i<0 )	{

			A = '0';
			++t;
		}
		else
			A = a[i];

		if( j<0 )	{

			B = '0';
			++t;
		}
		else
			B = b[j];

		if( t==2 )
			break;

		b_str[k] = '0' + ( (A-'0') ^ (B-'0') );
	}

	assert( k==-1 );

	return b_str;
}


// BASE CONVERSION FNCS
char * BIN_2_DEC(char * bin)	{ /** Converts base2 (binary) string to base10 (decimal) string.

*/

	AP dec = new_ap( strlen(bin)+1, 0 );
	AP mult = new_ap( strlen(bin)+1, 0 );
	
	AP digit = new_ap(1, 0);
	
	AP _2 = new_ap(1, 0);
	AP _j = new_ap(10, 0);
	
	_2.major = strdup( "2" );

	int i, j;
	
	for( i=0, j=strlen(bin)-1; i<strlen(bin); i++, j-- )	{

		digit.major[0] = bin[i];
		
		sprintf(_j.major, "%d", j); // itoa()
		mult = EXP( _2, _j );
		dec = ADD( dec, MUL(digit, mult) );
	}
	
	free_ap( mult );
	free_ap( digit );
	free_ap( _2 );
	free_ap( _j );
	
	char * result = (char *)malloc( strlen(dec.major)+1 );
	result = strdup( dec.major );

	free_ap( dec );
	
	return result;
}

char * DEC_2_BIN(AP input, int packed)	{  /** This function takes a decimal (base10) AP Integer, and returns a binary (base2) string.
Does not assume string-length-boundaries of byte-padding, i.e, an input of 64 will return 1000000 (7 digits), not 01000000 (8 digits).
It is, however, a method for converting Dec->Bin.
Param "int packed" is a flag to determine if the returned binary string should be rounded in length to a multiple of 8.
In other words, 127 would be "01111111" instead of "1111111". An argument of 0 means "do not round", a non-0 value means "round up string-length to multiple of 8".
*/

	int length = 0;
	int flag = 1;

	AP t = new_ap( 1,0 );
	t.major = strdup( "0" );
	
	AP check = copy(&input);
	while ( flag )	{
		
		check=DIV_BY_2(check);

		if( DIV_BY_2_PRINT_ROWS==1 )
			printf( "\t%c%s\n", check.sign, check.major );
			
		++length;
		
		if( cmp(&check,&t)<= 0 )
			flag = 0;
	}
	
	//printf( "length := %d\n", ( packed==1 ? ((length%8==0) ? length: length + (8-(length%8))) : length) );

	AP stack[strlen(input.major)];
	char binary_stack[length+1];

	length = strlen(input.major);

	int pointer;
	int bs_pointer = 0;
	
	AP a = new_ap( length, 0 );
	
	AP result = new_ap( length, 0 );
	flag = 1;
	while( flag )	{

		pointer = 0;
		
		int i;
		for( i=0; i<length; i++ )	{
			
			a.major[i] = input.major[i];
			
			pack_trailing_zeroes( a.major, length, (length-i-1) );
			
			int dividend = a.major[i] - '0';
			int remainder = dividend % 2;
			int quotient = dividend / 2;
			
			result.major[i] = quotient + '0';
			
			// if a_substring != LSDigit (units position)
			// if it is, the remainder is noted as a binary digit 1, and the remainder itself disgarded.

			if( remainder )	{
				
				if( i==(length-1) )	{
			
					binary_stack[bs_pointer++] = '1';
				}
				else
					result.major[i+1] = '5';
			}
			else	{
				
				if( i==(length-1) )	{
			
					binary_stack[bs_pointer++] = '0';
				}
				else
					result.major[i+1] = '0';
			}

			pack_trailing_zeroes( result.major, length, (length-i-2) );
			
			stack[pointer++] = copy(&result);

			// finally...
			
			a.major[i] = '0';
			result.major[i] = '0';
			result.major[i+1] = '0';
		}	
		

		input.major = strdup( "0" );
		for(int k = 0; k < pointer; k++ )
			input = ADD(input, stack[k]);
		
		length = strlen(input.major);
		
		int l = strlen(a.major)-strlen(input.major);
		
		for( int z=0; z<l; z++ )
			++a.major;

		pack_trailing_zeroes( a.major, length, length);
		
		AP t = new_ap(1,0);
		t.major = strdup( "0" );
		
		if( cmp(&input,&t)==0 )
			flag = 0;
	}
	
	char * b_str = (char *)malloc( bs_pointer+1 );
	
	int k;
	for(k=0; k<bs_pointer; k++)	{
		
		b_str[k] = binary_stack[bs_pointer-1-k];
	}
	
	if( packed )	{
	
		int extra = strlen(b_str);
		int qt = 0;
		
		qt = extra % 8;
		
		if( qt==0 )
			extra=0;
		else if( extra>8 )	{
			
			int spare = extra % 8;
			
			extra = 8 - spare;
		}
		else
			extra = 8 - extra;
		
		char * padding = (char *)malloc(extra+1);
		
		int i;
		for( i=0; i<extra; i++ )
			padding[i] = '0';
	
		padding[i] = '\0';
		
		char * temp = (char *)malloc( strlen(b_str)+extra+1 );
		
		strcpy( temp, padding );
		strcat( temp, b_str );
		
		free( b_str );
		b_str = temp;
	}
	
	else
		b_str[k] = '\0';
	
	return b_str;
}


// 2k FNCS
int _2kMax(AP input)	{
	
	char * bin_string = DEC_2_BIN(input, 0);
	
	int len_bin_string = strlen(bin_string);
	
	int i = 0;
	loop:
	if( bin_string[i]=='1' )	{
		// only necessary for bit-strings with leading '0's, which is not always true for return values of DEC_2_BIN()
		int k = i;
		for( ++i; i < len_bin_string; i++ )	{
			
			if( bin_string[i]=='1' )	{
				
				return len_bin_string - k;
			}
		}
		
		return len_bin_string - k - 1;
	}
	else	{
	
		++i;
		goto loop;
	}
	
	return 0;
}

int _2kMin(AP input)	{
	
	char * bin_string = DEC_2_BIN(input, 0);
	
	int len_bin_string = strlen(bin_string);
	
	for( int i=0; i<len_bin_string; i++ )	{
		
		if( bin_string[i]=='1')	{
			
			return len_bin_string - 1 - i;
		}
	}
	
	return 0;
}


// CORE ARITHMETIC OPERATORS
AP ADD(AP a, AP b)	{
	
	int flag = 0;
	
	int size = ( strlen(b.major) > strlen(a.major) ? strlen(b.major) : strlen(a.major) );
	AP c = new_ap(size+1, 0);


	signed short int value;
	signed short int valA, valB, valC;
	
	signed int i, j, k;
	
	if( sign(&a) == sign(&b) )	{
		
		for( i=strlen(a.major)-1, j=strlen(b.major)-1, k=strlen(c.major)-1; k>0; i--, j--, k--)	{
		
			if(i>=0)
				valA = a.major[i] - '0';
			else
				valA = 0;
			
			if(j>=0)
				valB = b.major[j] - '0';
			else
				valB = 0;
			
			valC = (c.major[k] - '0');	
			
			valA += valC;

				
			value = valA + valB;

			if( value>=10 )	{
				
				value -= 10;
				c.major[k-1] += 1;
			}
			
			c.major[k] = '0' + value;
		}
	}
	else	{
		
	//Subtract the smaller absolute value from the larger absolute value and give the answer the same sign as the number with the larger absolute value
		char tsign;
		if( cmp(&a,&b)==-1 )	{
			
			tsign = b.sign;
			
			AP temp;
			temp = a;
			a = b;
			b = temp;
		}
		else
			tsign = a.sign;
		
		a.sign = '+';
		b.sign = '+';
		c = SUB(a,b);
		c.sign = tsign;
		flag = 1;
	}
	
	
	if( (tt(a,b)=='-') && (flag==0) )
		c.sign = '-';

	
	char * _ = (char *)malloc(strlen(c.major)+1);
	strcpy(_, c.major);
	for( i=0; i<(int)strlen(_); i++ )
		if( _[i] == '0' )
			++c.major;
		else
			break;
	
	free( _ );
	
	if( *c.major == '\0' )
		--c.major;
	
	return c;
}

AP SUB(AP a, AP b)	{
	
	if( (a.sign=='+') && (b.sign=='+') && ( (cmp(&a,&b)==+1) || (cmp(&a,&b)==0) ) )	{

		int i, j, k, valA, valB, valC;
		AP c = new_ap(strlen(a.major)+1,0);
		for( i=strlen(a.major)-1, j=strlen(b.major)-1, k=strlen(c.major)-1; k>0; i--, j--, k--)	{
		
			if(i>=0)
				valA = a.major[i] - '0';
			else
				valA = 0;
			
			if(j>=0)
				valB = b.major[j] - '0';
			else
				valB = 0;
			
			valC = (c.major[k] - '0');	
			
			valA += valC;

			if( valA<valB )	{
				
				c.major[k-1] -= 1;
				valA += 10;
			}

			int value = valA - valB;
			c.major[k] = '0' + value;
		}
	
		
		int len = strlen(c.major);
		char * _ = malloc(len+1);
		_ = strdup( c.major );
		for( i=0; i<len; i++ )
			if( _[i] == '0' )
				++c.major;
			else
				break;
	
		free( _ );
	
		if( *c.major == '\0' )
			--c.major;
		
		return c;
	}
	
	// Alt. SUB algorithm:
	// The subtraction of a real number (the subtrahend [B]) from another (the minuend [A]) can be defined as the addition of the minuend [A] and the additive inverse of the subtrahend [B].
	flip_sign(&b);
	AP res = ADD(a, b);
	flip_sign(&b);

	return res;
}

AP MUL(AP a, AP b)  {

	int MAX_NUM_MUL_ROWS = ( strlen(a.major)>strlen(b.major) ? strlen(a.major) : strlen(b.major) );
	
	char ** ResultArray = (char **)calloc(MAX_NUM_MUL_ROWS, sizeof(char *));
	int q = 0;

	for( int k = strlen(b.major)-1; k>=0; k-- )	{
		
		int rev_offset_B = strlen(b.major) - 1 - k;
		
		int curr_row_length = strlen(a.major) + 1 + rev_offset_B;
		char * curr_row = (char *)malloc( curr_row_length + 1 );
		curr_row[ curr_row_length ] = '\0';
		pack_trailing_zeroes( curr_row, curr_row_length, rev_offset_B );
		
		int prev_overflow = 0;
		
		int p = curr_row_length - 1 - rev_offset_B;
		
		for( int i = strlen(a.major)-1; i>=0; i-- )	{
			
			int _a = a.major[i] - '0';
			int _b = b.major[k] - '0';
			
			int result = _a * _b;
			result += prev_overflow;
			
			if( result>9 )	{
				
				prev_overflow = MSD(result);
				curr_row[p] = (result % 10) + '0';
			}
			else	{
				
				prev_overflow = 0;
				curr_row[p] = result + '0';
			}
			
			--p;
		}
	
		if( prev_overflow>0 )	{
		
			curr_row[0] = prev_overflow + '0';
		}
		else
			curr_row[0] = '0';
		
		ResultArray[q++] = curr_row;
	}


	AP c = new_ap(10,0);
	AP d = new_ap(10,0);
	
	for( int t = 0; t < q; t++ )	{
		
		char * result_row = ResultArray[t];
		
		if(result_row==NULL)
			assert(result_row);
		
		free( d.major );
		
		d.major = strdup(result_row);
		
		c = ADD(c, d);
	}
	
	c.sign = tt_mul(&a, &b);
	return c;
}

AP DIV(AP a, AP b)  {

	return new_ap(1, 0);
}

AP DIV_BY_2(AP a)	{
	
	int overflow = 0;
	int value;
	int i;
	for( i=0; i<strlen(a.major); i++ )	{
		
		loop:
		
		value = a.major[i] - '0';
		
		if( value>9	)	{
			// roll over the remainder, ie value=10-value
			
			int value2 = value;
			
			while( value2 >= 0 )
				value2 -= 10;
			
			value2 += 10;

			a.major[i] = '0' + value2;
			a.major[i+1] += (value % 10);	
		}

		value = a.major[i] - '0';
		
		int result = floor( value/2 );
		result += overflow;
		a.major[i] = result + '0';
		
		if( a.major[i] - '0' >= 10 )
			goto loop;
		
		if( value%2!= 0 )
			overflow = 5;
		else
			overflow = 0;

	}
	
	a.major[i] = '\0'; //NULL
	
	int len = strlen( a.major );
	for( i=0; i<len; i++ )
		if( a.major[i]=='0' )	{
			
			++a.major;
			--len;
			--i;
		}
		else
			break;

	if( a.major[0]=='\0' )
		--a.major;
	
	return a;
}

AP EXP(AP a, AP b)	{
	
	// if b (exp) is negative, flip sign.
	if( sign(&b)=='-' )	{
		
		b.sign='+';
		printf("Exponent is negative. Converting to positive (%c%s)\n", b.sign, b.major );
	}
	
	// a * a, b-1 times
	// if b=0, result = 1
	AP c = new_ap(1, 0);
	c.major = strdup( "1" );
	
	AP temp = new_ap(1,0);
	temp.major = strdup( "0" );
	
	if( cmp(&b,&temp)==0 )	{
		
		return c;
	}
	else	{
		
		AP d = SUB(b, c);
		AP e = new_ap(1,0);
		e.major = strdup( "0" );
		AP result = copy(&a);
		while( cmp(&d, &e)==+1 )	{
			
			result = MUL(result, a);
			d = SUB(d,c);
		}
		
		if( sign(&a)=='-' )
			result.sign='-';
		
		return result;
	}
}


// VARIOUS MATH FNCS
int LCM(int a, int b, int flag)	{

	signed int M1 = 0, M2 = 0;
	#define MAX_ITER 4096
	int R1[MAX_ITER] = {0}, R2[MAX_ITER] = {0};
	int val = 1, inc = 0, match = 0;

	if(flag)
		val = 2;
	
	M1 = a; M2 = b;
	
	while (!match)	{
		
		if (inc >= MAX_ITER)	{
			
			printf("Overflow error: More than %d iterations required.\n", MAX_ITER);
			exit(1);
		}
		
		R1[inc] = (int)M1*val; R2[inc] = (int)M2*val;
		
		match = lcm_test(inc, R1, R2);
		
		++inc;
		++val;
	}
	
	//printf("The LCM for %d and %d is %d.\n", M1, M2, R1[inc-1]);

	return R1[inc-1];
}

int lcm_test(int max, int R1[], int R2[])	{
	
	for (int a = 0; a <= max; a++)
		for (int b = 0; b <= max; b++)
			if (R1[a]==R2[b])
				return 1;
			
	return 0;
}

int lcm_example(int argc, char **argv)	{
	
	int flagSet = 0;
	
	if((argc == 4) && (argv[3][0] == '-') && (argv[3][1] == 'n'))	{
		
		//printf("Flag set!\n");
		flagSet = 1;
	}
	
	int a = str2int(argv[1]);
	int b = str2int(argv[2]);
	
	int lcm = LCM(a, b, flagSet);
	int gcd = 1; // = GCD(a, b, lcm);
	
	printf( "lcm := (%d)\ngcd := (%d)\n", lcm, gcd );
	
	return 0;
}


// CREATE, DUPLICATE, RESET & FREE AP TYPE FNCS
AP new_ap(int maj, int min)	{

	AP result;
	result.major = (char *)malloc(maj+1);
	result.minor = (char *)malloc(min+1);
	
	if( (result.major==NULL)||(result.minor==NULL) )	{
		
		printf("AP new_ap(...) failed 1 or 2 of 2 malloc() calls! Exiting...\n");
		exit(0);
	}
	
	int i;
	
	for( i=0; i<maj; i++)
		result.major[i] = '0';
	
	result.major[maj] = '\0';
	
	for( i=0; i<min; i++)
		result.minor[i] = '0';
	
	result.minor[min] = '\0';

	result.length = maj + min;
	result.major_length = maj;
	result.minor_length = min;
	
	result.sign = '+';
	return result;
}

AP copy(AP * a)	{
	
	AP _ = new_ap(strlen(a->major),strlen(a->minor));
	
	strcpy(_.major, a->major);
	strcpy(_.minor, a->minor);
	
	_.sign = a->sign;
	
	_.length = a->length;
	_.major_length = a->major_length;
	_.minor_length = a->minor_length;
	
	return _;
}

void clear(AP * a)	{
	
	int i;
	for( i=0; i< (int)strlen(a->major); i++)
		a->major[i] = '0';
	
	a->major[i] = '\0';
	
	for( i=0; i< (int)strlen(a->minor); i++)
		a->minor[i] = '0';
	
	a->minor[i] = '\0';
	
	a->sign = '+';
}

void free_ap(AP a)	{
	
	free( a.major );
	free( a.minor );
}		


// SIGN FNCS
char sign(AP * a)	{

	return a->sign;
}

void set_sign(AP * a, char sym)	{

	if( sym!='+' && sym!='-' )
		sym='+';
	
	a->sign = sym;
}

void flip_sign(AP * a)	{

	if( a->sign == '-' )
		a->sign = '+';
	else
		a->sign = '-';
}

char tt(AP a, AP b)	{
	
	signed int ag = cmp(&a,&b);
	
	if( (sign(&a)=='+') && (sign(&b)=='+') ) // x2, a < b, a > b
		return '+';
	
	if( (ag==-1) && (a.sign=='-') && (b.sign=='+') )
		return '+';
	
	if( (ag==-1) && (a.sign=='-') && (b.sign=='-') )
		return '-';
	
	if( (ag==-1) && (a.sign=='+') && (b.sign=='-') )
		return '-';
	
	
	if( (ag==+1) && (a.sign=='-') && (b.sign=='-') )
		return '-';

	if( (ag==+1) && (a.sign=='+') && (b.sign=='-') )
		return '+';
	
	if( (ag==+1) && (a.sign=='-') && (b.sign=='+') )
		return '-';
	
	return '+';
	
}

char tt_mul(AP * a, AP * b)	{

	if( sign(a)!=sign(b) )
		return '-';
	
	return '+';
}


// GENERAL HELPER FNCS
signed short int cmp(AP * a, AP * b)	{
	
	
	while( *(a->major)=='0' )
		++a->major;
	
	while( *(b->major)=='0' )
		++b->major;
	
	int len_a = strlen(a->major);
	int len_b = strlen(b->major);
	
	if( len_a<len_b )
		return -1;
	
	if( len_a>len_b )
		return +1;
	
	for( int test=0; test<len_a; test++ )	{
		
		if( a->major[test]>b->major[test] )
			return +1;
		
		if( a->major[test]<b->major[test] )
			return -1;
	}
	
	return 0;
}

signed int overflow(AP * c, int result, signed int k) {
  
  if( (k-1) < 0 ) {
    
    char * temp = (char *)malloc(strlen(c->major) + 1 + 1);
	
    if( temp==NULL )  {
      
      printf("AP MUL(...) malloc() call failed to allocate block! Exiting.\n");
      exit(1);
    }
    
    temp[0] = '0';
    
    int x;
    for(x = 0; x < strlen(c->major); x++) {
      
      temp[x+1] = c->major[x];
    }
    temp[x+1] = 0;
    
    
    free( c->major );
    c->major = temp;
    
  }
  
  
  // 1. get lmost digit of result (1-8)
  
  short int rd = result % 10;
  short int td = (result - rd);
  short int ld = 0;
  
  while(td>0) {
  
    ++ld;
    td = td - 10;
  }
  
  c->major[k] = '0' + rd;
  

  short int iresult = ld+(c->major[k-1] - '0');
  
  if( iresult <= 9 )  {
      
    c->major[k-1] = '0' + iresult;
      
  }
  else  {
    
    // if c[k-1] + ld > 9, recursive overflow, will need to deal with here!
    printf("Recursive overflow! Line %d-ish.\n", __LINE__);
    k = overflow(c, iresult, k-1);
    
  }
    
  return k-1;
  // remember, overflow can be from 1 t0 8! If [k-1] >= 2, itself may additively overflow to [k-2];

}

int MSD(int num)	{
	
  short int rd = num % 10;
  short int td = (num - rd);
  int ld = 0;
  
  while(td>0) {
  
    ++ld;
    td = td - 10;
  }
  
  return ld;
}

void pack_trailing_zeroes( char * curr_row, int array_length, int num_zeroes )	{
	
	curr_row[array_length] = 0;
	
	while( num_zeroes > 0 )	{
		
		--array_length;
		
		curr_row[array_length] = '0';
		
		--num_zeroes;
	}
}

char * fill_leading_zeroes( char * str, int num_zeroes )	{

	char * _ = (char *)malloc( strlen(str) + num_zeroes + 1 );
	
	int i;
	for( i=0; i<num_zeroes; i++ )
		_[i] = '0';
	
	strcat( _, str );
	
	return _;
}

int str2int(char *input)	{
	
	int len = strlen(input), i = 0, result = 0;
	
	if (input[0] == '-')
		i = 1;

	for(; i<len; i++)
		result = result * 10 + ( input[i] - '0' );
	
	if (input[0] == '-')
		result = 0 - result;
	
	return result;
}

 char * int2str(int v)	{
	
	char * str = (char *)malloc(32);
	
	sprintf(str, "%d", v); // itoa()
	
	return str;
}


//!! Dave_IEEE754.c
// CORE FNCS
struct IEEE754_Float * IEEE_writeFloatStruct( float * f )	{
	
	struct IEEE754_Float * a = (struct IEEE754_Float *)malloc( sizeof(IEEE754_Float) );
	
	//char * i = (char *)a;
	
	char * k = (char *)f;
	
	a->sign = (int) ( (k[3] & 0b10000000 ) >> 7 );
	a->exponent = (int) ((unsigned)k[3]) & 0b01111111;
	
	char * temp = (char *)malloc(25);
	char * section = (char *)malloc(9);
	
	char * f_str = IEEE_readFloat( *f );
	
	// 24 bits
	a->significand = (int) (str2int( IEEE_convertFloatString2BigEndian(f_str) /*k[2] . k[1] . k[0]*/) & 0b00000000111111111111111111111111);
	
	printf( "a->significand = %d\n", a->significand );
	
	free( temp );
	free( section );
	
	return a;
}

float IEEE_readFloatStruct( struct IEEE754_Float* f )	{

	float a;
	
	char * str = (char *)malloc(33);
	str[32] = '\0';
	
	str[24] = '0' + f->sign;
	
	int i;
	for( i=0; i<24; i++ )
		str[i] = '0' + ( ( f->significand & (1 << (23-i))     )?1:0 );
	
	for( i=25; i<32; i++ )
		str[i] = '0' + ( ( f->exponent &    (1 << ((32-i)-7)) )?1:0 );
	
	IEEE_writeFloat( &a, str );
	return a;
}		

char * IEEE_convertDoubleString2BigEndian( char * str )	{
	
	char * be_string = malloc(64 + 1);
	
	int offset = 0;
	
	int i;

	for( i=63; i<63+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';

	for( i=54; i<54+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=45; i<45+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';

	for( i=36; i<36+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=27; i<27+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=18; i<18+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=9; i<9+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=0; i<8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset] = '\0';
	
	return be_string;
}

char * IEEE_convertFloatString2BigEndian( char * str )	{
	
	char * be_string = malloc(32 + 1);
	
	int offset = 0;
	
	int i;
	
	for( i=24; i<32; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=16; i<24; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=8; i<16; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=0; i<8; i++ )
		be_string[offset++] = str[i];
	
	be_string[offset] = '\0';
	
	return be_string;
}

char * IEEE_readDouble( double f )	{

	typedef struct container	{

		double f;

	} container;
	
	struct container * tc = malloc( sizeof(double) ); // 4 bytes for the float. Change to sizeof(double), which is 8, for a double.
	
	tc->f = f;
	
	char * offset = (char *) tc;
	char * str = malloc(64 + 1); // 3 for the in-between spaces, 1 for the null-terminator of the string.
	// double := 64 + 7 + 1
	
	int ptr = 0;

	for(int i=0; i<8; i++)	{ // iterate through each of the 4 bytes of the float. (change to 8 when parsing a double.)
		
		for(int k=7; k>=0; k--)	{ // iterate from the MSB (bit 7), to the LSB (bit 0) of an individual byte of the memory.
			
			int r = (*offset) & (1 << k); // is bit 'k' of offset pointer set to 1, or not? In other words, is the &-exp TRUE, or FALSE?
			if( r==0 )
				str[ptr++] = '0';
			else
				str[ptr++] = '1';
		}
		
		++offset; // move pointer "char * offset" along the struct 1 byte
		
		//str[ptr++] = ' ';
	}
		
	str[ptr] = '\0';
	
	return str; // !string returned is little-endian on a little-endian system.
}

char * IEEE_readFloat( float f )	{

	typedef struct container	{

		float f;

	} container;
	
	struct container * tc = (struct container *)malloc( sizeof(float) ); // 4 bytes for the float. Change to sizeof(double), which is 8, for a double.
	
	tc->f = f;
	
	char * offset = (char *) tc;
	char * str = malloc(32 + 1); // 3 for the in-between spaces, 1 for the null-terminator of the string.
	// double := 64 + 7 + 1
	
	int ptr = 0;

	for(int i=0; i<4; i++)	{ // iterate through each of the 4 bytes of the float. (change to 8 when parsing a double.)
		
		for(int k=7; k>=0; k--)	{ // iterate from the MSB (bit 7), to the LSB (bit 0) of an individual byte of the memory.
			
			int r = (*offset) & (1 << k); // is bit 'k' of offset pointer set to 1, or not? In other words, is the &-exp TRUE, or FALSE?
			if( r==0 )
				str[ptr++] = '0';
			else
				str[ptr++] = '1';
		}
		
		++offset; // move pointer "char * offset" along the struct 1 byte
		
		//str[ptr++] = ' ';
	}
		
	str[ptr] = '\0';
	
	return str; // !string returned is little-endian on a little-endian system.
}

unsigned short int IEEE_getFloatBit( char * str, unsigned int offset )	{
	
	if( offset>(31) )
		return 2;
	
	//if( offset==8 offset==17 offset==26 )
		//++offset;
	
	if( str[offset]=='1' )
		return 1;
	else
		return 0;
}

unsigned short int IEEE_getDoubleBit( char * str, unsigned int offset )	{
	
	if( offset>(63) )
		return 2;
	
	//if( offset==8 offset==17 offset==26 offset==35 offset==44 offset==53 offset==62 )
		//++offset;
	
	if( str[offset]=='1' )
		return 1;
	else
		return 0;
}

void IEEE_writeFloat(float * dest, char * str)	{
	
	assert( strlen(str)==(32) );
	
	char * mem = (char *)dest;
	char bitmask;
	
	int offset = 0;
	for( int i=0; i<4; i++ )	{

		bitmask = 0;

		for( int k=0; k<8; k++ )
			bitmask += (str[offset++] - '0') << (7 - k);

		(mem[i]) = bitmask;
	}
}

void IEEE_writeDouble(double * dest, char * str)	{
	
	assert( strlen(str)==(64) );
	
	char * mem = (char *)dest;
	char bitmask;
	
	for( int i=0; i<8; i++ )	{
		
		int offset = 0;
		bitmask = 0;

		for( int k=0; k<8; k++ )
			bitmask += (str[offset++] - '0') << (7 - k);

		(mem[i]) = bitmask;
	}
}

struct IEEE754 * initIEEE754()	{
	
	struct IEEE754 * lib = malloc( sizeof(struct IEEE754) );
	
	lib->readFloat = IEEE_readFloat;
	lib->readDouble = IEEE_readDouble;
	
	lib->convertFloatString2BigEndian = IEEE_convertFloatString2BigEndian;
	lib->convertDoubleString2BigEndian = IEEE_convertDoubleString2BigEndian;
	
	lib->getFloatBit = IEEE_getFloatBit;
	lib->getDoubleBit = IEEE_getDoubleBit;
	
	lib->writeFloat = IEEE_writeFloat;
	lib->writeDouble = IEEE_writeDouble;
	
	return lib;
}


//!! ap.c  
// TEST.C

/** INFORMATIVE SECTION
	This is the test driver for APLib and Dave's IEEE754-Lib. To account for regression issues, all tests run every time "test" is invoked. Thus, if any new features break historical correctness, thus any of the tests, it will become apparent from the test subroutine output.
*/


// STDLIB INC'S
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <error.h>
#include <stdint.h>


// STATIC DEFS
#define PRINT_LINE printf( "---------------------------\n" );


// BINS
int dummy_int;


typedef struct TEST_ENTRY {
	
	void (*addr)(int argc, char **argv);
	char * ref;
	uint32_t index;
} TEST_ENTRY;

typedef struct _TESTS	{

	struct TEST_ENTRY entries[256];
	int length;
	
} _TESTS;


char * formatString( char * fmt, ... )	{


	// temp portability edit

	return fmt;

	///////
	char * str = (char *)malloc(1024);
	str[0] = '\0';

	//sprintf( str, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );

	return str;
}

void addTest( struct _TESTS * T, char * ref, void * fnc )	{

		struct TEST_ENTRY ENTRY;
		ENTRY.addr = fnc;
		ENTRY.ref = strdup( ref );
		ENTRY.index = T->length;
		T->entries[T->length] = ENTRY;
		
		++T->length;
}

void colorMode()	{


	// temp portability edit

	/**
	#define STD_OUTPUT_HANDLE ((DWORD)-11)
	//#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	BOOL color = SetConsoleMode(
		StdHandle,
		0x0001 | 0x0002 | ENABLE_VIRTUAL_TERMINAL_PROCESSING
	);

	//sprintf( msg_str, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );
	//print( msg_str );
	*/

	int color = 0;
	if(color == 0)	{
		
		//printf( "ANSI/VT Support Not Available.\n" );
		resetAnsiVtCodes(0);
	}
	else
		resetAnsiVtCodes(1);

	return;
}

void ap_exit(int status)	{

	printf( "\n%sAPSuite is exiting.%s\n", FG_RED, NORMAL );
	printf( "%s", NORMAL );
	exit(status);
}



// MAIN() ENTRYPOINT
int main(int argc, char **argv)	{

	colorMode();
	
	printf( "%s", FG_BRIGHT_WHITE );
	
	struct _TESTS TESTS_;
	struct _TESTS * TESTS = &TESTS_;
	TESTS->length = 0;
	
	addTest( TESTS, "and", andTest );
	addTest( TESTS, "not", notTest );
	addTest( TESTS, "or", orTest );
	addTest( TESTS, "exor", exOrTest );
	
	addTest( TESTS, "test1", fs_test1 );
	addTest( TESTS, "readfloattest", readFloatTest );
	addTest( TESTS, "operators", basicTest );
	addTest( TESTS, "writefloattest", writeFloatTest );
	addTest( TESTS, "decbin", dec_2_bin_2_dec );
	addTest( TESTS, "quicktest", q_test );
	addTest( TESTS, "2kMax", test2kMax );

	AP ca;
	ca.sign = '-';
	ca.major = strdup( "1701" );
	printf( "Color test: %s\n", formatAP(ca) );
	
	NL;
	char * bin_string = "0011100010101010111101011010101";
	printf( "2nd color test: %s\n", formatBinary(bin_string) );
	
	print( c("lee", FG_BRIGHT_GREEN) );
	printf( " : " );
	print( c("david", FG_MAGENTA) );
	NL;
	
	//printf( "%s : %s\n", c("lee", FG_BRIGHT_GREEN), c("david", FG_MAGENTA) );
	
	normal();
	
	//ap_exit(0);
	//return 0;
	
	loop:
	
	NL;
	printf( "Please enter the test reference for the test you wish to invoke, or \n\"%s\" to see a list of the test functions,\n\"%s\" to invoke all tests,\n\"%s\" to print test output to file,\n\"%s\" to quit the test interface:\t", c("list", FG_BRIGHT_WHITE), c("all", FG_BRIGHT_WHITE), c("p", FG_BRIGHT_WHITE), c("q", FG_BRIGHT_RED) ); 
	
	char * buf = (char *)malloc( 1024 );
	dummy_int = scanf( "%s", buf );

	NL;
	
	char * TEST_OPT_NAME = FG_CYAN;
	printf( "Selection: \"%s\"\n", c(buf, TEST_OPT_NAME) );
	NL;
	
	if( seq( buf, "l" ) )
		strcpy(buf, "list");
	
	if( seq( buf, "list" ) )	{
		
		for( int i=0; i<TESTS->length; i++ )
			printf( "[%d] %s\n\n", i+1, TESTS->entries[i].ref );
		
		goto loop;
	}
	if( seq( buf, "q" ) )	{
		
		printf( "%sSession complete. Exiting.%s", FG_BRIGHT_WHITE, NORMAL );
		exit(0);
	}
	
	if( seq( buf, "p" ) )	{
		
		printf( "%sNot Yet Implemented.%s\n", FG_BRIGHT_WHITE, NORMAL );
		goto loop2;
	}
	
	char * list = (char *)malloc(4096);
	list[0] = '\0';
	char line[256] = {'\0'};
	int i, j=0;
	for( i=0; i<(TESTS->length); i++ )	{
		
		if( seq(buf, "all") )	{
			
			TESTS->entries[i].addr(argc, argv);
			
			if( i>0 )
				strcpy( line, ",\n");
			
			strcat( line, TESTS->entries[i].ref );
			strcat( list, line );
			
			line[0] = '\0';
			++j;
		}
		else if( seq(TESTS->entries[i].ref, buf) )	{

			TESTS->entries[i].addr(argc, argv);
			strcat( line, TESTS->entries[i].ref );
			strcat( list, line );
			
			line[0] = '\0';
			++j;
			break;
		}
	}
	
	NL;
	PRINT_LINE;
	
	if( j>0 )
		printf( "%d test(s) completed:\n\n%s\n\n", j, list );
	else
		printf( "No matching test found.\n\n" );
	
	PRINT_LINE;
	
	free( list );
	loop2:
	free( buf );
	
	goto loop;
	
	// TEST 1
	basicTest(argc, argv);
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 2
	char * test_num;
	AP input = new_ap( 256, 0 );
	
	if( argc > 3 )
		test_num = strdup( argv[3] );
	else
		test_num = strdup( "17011979" );
	
	if( test_num[0]=='+' )	{
	
		input.sign = '+';
		++test_num;
	}
	else if( test_num[0]=='-' )	{
		
		input.sign = '-';
		++test_num;
	}
	
	input.major = strdup( test_num );
	
	int packed = 1;
	char * str = DEC_2_BIN(input, packed);
	printf( "DEC_2_BIN(\"%c%s\") = %s\n", input.sign, input.major, str );
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 3
	test2kMax(argc, argv);
	printf( "The minimum higher 2k exponent for %c%s is %d.\n", input.sign, input.major, dummy_int );
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 4
	dec_2_bin_2_dec(argc, argv);
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 5
	readFloatTest(argc, argv);
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 6
	writeFloatTest(argc, argv);
	NL;
	PRINT_LINE;
	pause();

	// TEST 7
	fs_test1(argc, argv);
	NL;
	PRINT_LINE;
	pause();

	// TESTS COMPLETE.
	printf( "END OF TESTS. EXITING.\n" );
	ap_exit(0);
	
	// For the compiler.
	return 0;
	
}


// HELPER FNCS
void pause()	{

	getchar();
	return;
}

void arg_assert( int argc, int min )	{
	
	if( (argc-1)<min )	{
		
		printf( "Not enough cmd-line arguments. %d are required, only %d args passed. Exiting.", min, argc-1 );
		exit(1);
	}

	return;
}

void parseAP(AP * a, char * str)	{

	// Arg A
	if( str[0] == '-' )	{

		a->sign = '-';
		//str[0] = '0';
		++str;
		a->major = strdup(str);
	}
	else if( str[0] == '+' )	{

		a->sign = '+';
		//str[0] = '0';
		++str;
		a->major = strdup(str);
	}
	else	{

		a->major = strdup(str);
		a->sign = '+';
	}

	return;
}


//!! tests.c  
// T£STS.c

// TEST FNCS
void exOrTest(int argc, char ** argv)	{
	
	char * a = "11100011010101010101010101";
	char * b =           "0001111101011111";
	
	int len_a = strlen(a);
	int len_b = strlen(b);
	
	char * c = EX_OR(a, b);
	
	int a_or_b = (len_a>=len_b)?1:0;
	int diff = a_or_b?(len_a-len_b):(len_b-len_a);
	
	char * buf = (char *)malloc(diff + 1);
	char * dummy = (char *)malloc(1);
	dummy[0] = '\0';
	
	buf[0] = '\0';
	
	for( int i=0;i<diff; i++ )
		buf[i] = ' ';
	
	buf[diff] = '\0';
	
	printf( "%s%s\n", a_or_b?dummy:buf, formatBinary(a) );
	printf( "%s%s\n", a_or_b?buf:dummy, formatBinary(b) );
	printf( "%s\n", formatBinary(c) );
	
	free( buf );
	free( dummy );
	
	return;
}

void orTest(int argc, char ** argv)	{
	
	char * a = "11100011010101010101010101";
	char * b =           "0001111101011111";
	
	int len_a = strlen(a);
	int len_b = strlen(b);
	
	char * c = OR(a, b);
	
	int a_or_b = (len_a>=len_b)?1:0;
	int diff = a_or_b?(len_a-len_b):(len_b-len_a);
	
	char * buf = (char *)malloc(diff + 1);
	char * dummy = (char *)malloc(1);
	dummy[0] = '\0';
	
	buf[0] = '\0';
	
	for( int i=0;i<diff; i++ )
		buf[i] = ' ';
	
	buf[diff] = '\0';
	
	printf( "%s%s\n", a_or_b?dummy:buf, a );
	printf( "%s%s\n", a_or_b?buf:dummy, b );
	printf( "%s\n", formatBinary(c) );
	
	free( buf );
	free( dummy );
	
	return;
}

void notTest(int argc, char ** argv)	{
	
	//char * NOT(char * v)
	char * str = "10101010101010111111001111";
	
	printf( "Input  string: %s\n", formatBinary(str) );
	
	char * str2 = NOT(str);
	printf( "Output string: %s\n", formatBinary(str2) );

	return;
}

void andTest(int argc, char **argv)	{
	
	char * a = "11100011010101010101010101";
	char * b =           "0001111101011111";
	
	int len_a = strlen(a);
	int len_b = strlen(b);
	
	char * c = AND(a, b);
	
	int a_or_b = (len_a>=len_b)?1:0;
	int diff = a_or_b?(len_a-len_b):(len_b-len_a);
	
	char * buf = (char *)malloc(diff + 1);
	char * dummy = (char *)malloc(1);
	dummy[0] = '\0';
	
	buf[0] = '\0';
	
	for( int i=0;i<diff; i++ )
		buf[i] = ' ';
	
	buf[diff] = '\0';
	
	printf( "%s%s\n", a_or_b?dummy:buf, formatBinary(a) );
	printf( "%s%s\n", a_or_b?buf:dummy, formatBinary(b) );
	printf( "%s\n", formatBinary(c) );
	
	free( buf );
	free( dummy );
	
	return;
}

void test2kMax(int argc, char **argv)	{
	
	int temp = DIV_BY_2_PRINT_ROWS;
	DIV_BY_2_PRINT_ROWS = 0;
	
	AP input;
	parseAP(&input, argv[1]);
	
	char * _ = input.major;
	
	int a = _2kMax(input);
	DIV_BY_2_PRINT_ROWS = temp;
	
	printf( "%s %s %s %s\n", c("Minimum Maximal 2k exponent for", FG_BRIGHT_MAGENTA), c(_, FG_BRIGHT_GREEN), c("=", FG_CYAN), c(int2str(a), FG_BRIGHT_GREEN) );
	
	return;
}

void basicTest(int argc, char **argv)	{ // ADD, SUB, MUL, EXP

	arg_assert( argc, 2 );
	
	
	if( argc < 3 )	{
		
		printf("Please pass 2 (possibly signed) integers on the cmd-line, and invoke the program again. Exiting...\n");
		exit(0);
	}
	
	NL;
	
	AP A, B, C;
	A = new_ap( 10, 0 );
	B = new_ap( 10, 0 );
	
	// Arg A
	parseAP(&A, argv[1]);
	
	// Arg B
	parseAP(&B, argv[2]);
	
	
	printf( "Values Entered:\na = %c%s\nb = %c%s\n", A.sign, A.major, B.sign, B.major );
	
	NL;
	
	// ADD
	C = ADD(A, B);
	printf( "%c%s + %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	NL;
	
	// SUB
	C = SUB(A, B);
	printf( "%c%s %s-%s %c%s = %c%s", A.sign, A.major, FG_BRIGHT_GREEN, NORMAL, B.sign, B.major, C.sign, C.major );
	
	NL;

	// MUL
	C = MUL(A, B);
	printf( "%c%s MUL %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	NL;
	
	// EXP
	printf( "The EXP operator may take a while with a larger exponent. Please be patient...\n" );
	C = EXP(A, B);
	if( C.sign=='-' )
		B.sign='+';
	
	
	printf( "%c%s EXP %c%s = %c%s\n", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	printf( "\nCompleted." );
	
	return;
}

void dec_2_bin_2_dec(int argc, char **argv)	{ // DEC->BIN->DEC	(DEC_2_BIN / BIN_2_DEC)
	
	char * decimal = "543212362746234636432864963483264873264932649823649";
	
	AP a = new_ap( strlen(decimal), 0 );
	a.major = strdup( decimal );
	
	char * binary = DEC_2_BIN(a, 1);
	
	char * ret_decimal = BIN_2_DEC(binary);
	
	printf( "decimal = %s\n", decimal );
	printf( "binary = %s\n", binary );
	printf( "back again = %s\n", ret_decimal );
	
	return;
}

void fs_test1(int argc, char **argv)	{
	
	// This test function is to test construction and access to struct "IEEE754_Float"
	struct IEEE754_Float * a;
	
	float f = -85.125f;
	
	char * f_str = IEEE_readFloat( f );
	//f_str = IEEE_convertFloatString2BigEndian( f_str );
	
	IEEE_writeFloat( &f, f_str );
	
	a = IEEE_writeFloatStruct( &f );

	printf( "BIN (%f): %s\n", f, f_str );
	if (a->sign != 1)
		printf( "The sign bit is incorrect. The value is %d\n", a->sign );
	else
		printf( "The sign bit can be accessed and has the correct value.\n" );
	
	printf( "Float->exponent = %d\n", a->exponent );
	printf( "Float->significand = %d\n", a->significand );

	free( a );

	NL;
	
	f = 85.125f;

	f_str = IEEE_readFloat( f );
	//f_str = IEEE_convertFloatString2BigEndian( f_str );
	IEEE_writeFloat( &f, f_str );
	
	a = IEEE_writeFloatStruct( &f );
	
	printf( "BIN (%f): %s\n", f, f_str );
	if (a->sign != 0)
		printf( "The sign bit is incorrect. The value is %d\n", a->sign );
	else
		printf( "The sign bit can be accessed and has the correct value.\n" );

	printf( "Float->exponent = %d\n", a->exponent );
	printf( "Float->significand = %d\n", a->significand );
	assert( a->exponent < 128 );
	
	return;
}

void q_test(int argc, char **argv)	{

	/*
	1. create float.
	2. convert float to string, then printf
	3. create ieee_float object from &float
	4. read ieee_float object to float
	5. convert float to string, then printf
	6. when correct, both printed strings should be identical
	*/

	float f = -6543.21f;
	char * str = IEEE_readFloat( f );
	printf( "f := %f\n", f );
	
	float ff;
	IEEE_writeFloat( &ff, str );
	printf( "ff := %f\n", ff );
	
	print( c("If both values are the same, it indicates readFloat() & writeFloat() are working correctly.\n", FG_YELLOW) );
	

	struct IEEE754_Float* f2 = IEEE_writeFloatStruct( &f );
	float _f = IEEE_readFloatStruct( f2 );
	printf( "_f = %f\n", _f );
	printf( "%sIf the above value is the same as (%f), it indicates writeFloatStruct() & readFloatStruct() are working correctly.%s\n", FG_YELLOW, f, NORMAL );
	
	printf( "BIN(%f) := %s\n", f, formatBinary(str) );
	printf( "BE (%f) := %s\n", f, formatBinary(IEEE_convertFloatString2BigEndian( str )) );
	
	return;
}


void writeFloatTest(int argc, char **argv)	{
	
	struct IEEE754 * lib = initIEEE754();
	
	float a = 1701.79f;

	char * str = malloc(32+1);
	str = strdup( IEEE_readFloat( a ) );

	printf( "Value stored in float = %f\nWriting new value to float.\n", a );
	lib->writeFloat( &a, str );
	
	printf( "Value stored in float = %f\n", a );
	
	return;
}

void readFloatTest(int argc, char **argv)	{

	struct IEEE754 * lib = initIEEE754();

	float f;
	
	if( argc<2 )
		f = 17.1f;
	else
		f = atof(argv[1]);
	
	printf( "Float value received: %f\n", f );
	
	char * result = lib->readFloat( f );
	
	printf( "Result (l-endian): %s\n", formatBinary(result) );
	
	char * be_result = lib->convertFloatString2BigEndian( result );
	printf( "Result (b-endian): %s\n", formatBinary(be_result) );

	return;
}


//!! aplib-output.c

// APLIB-OUTPUT.c
#include <stdlib.h>
#include <string.h>


char * formatSign(char sign)	{
	
	return (sign=='-'?FG_BRIGHT_RED:FG_BRIGHT_GREEN);
}

char * formatBinary(char *bin_string)	{

	int bin_string_length = strlen(bin_string);
	
	char * _1 = "1";
	char * _0 = "0";
	
	char * str = (char *)malloc( bin_string_length + 50 + 1 );
	int str_length = bin_string_length + 50;
	
	int flag = 0;
	
	if( bin_string[0]=='0' )
		flag=1;
	else if( bin_string[0]=='1' )
		flag=0;
	
	for( int i=0; i<bin_string_length; i++ )	{
		
		if( bin_string[i]=='1' )	{
			
			if( flag==0 )	{
				
				strcat( str, FG_BRIGHT_BLUE );
				flag=1;
			}
			strcat( str, _1 );
		}
		else if( bin_string[i]=='0' )	{
			
			if( flag==1 )	{
				
				strcat( str, FG_BRIGHT_YELLOW );
				flag=0;
			}
			strcat( str, _0 );
		}
		
		if( strlen(str) >= (str_length-10) )	{
			
			str = realloc( str, strlen(str)+50 );
			str_length += 50;
		}
	}
	
	return str;
}

char * formatAP(AP a)	{
	
	char * str = (char *)malloc( strlen(a.major)+1+1+(8*3) );
	
	strcpy( str, formatSign(a.sign) );
	str[ strlen(str) ] = a.sign;
	
	strcat( str, FG_BRIGHT_CYAN );
	strcat( str, a.major );
	strcat( str, NORMAL );
	
	return str;
}

void print( char * str )	{
	
	printf( "%s", str );

	//temp portability edit
	//free( str );
	
	return;
}


void normal()	{

	printf( "%s", NORMAL );
}

char * c(char * str, char * col)	{

	char * str2 = (char *)malloc( strlen(str) + 16 + 1);
	sprintf( str2, "%s%s%s", col, str, NORMAL );
	return str2;
}




