// aplib.h

#ifndef DAVE_aplib
#define DAVE_aplib

// STDLIB INC'S
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>


// CUSTOM INC'S
#include "lib.h"
#include "colour.h"


// SUGAR
#define NEW_LINE printf("\n");
#define NL NEW_LINE
#define bool int


// STATIC DEFS
#define MAX_LENGTH_AP_PART 1023 //Make this any number of bytes you want. The NewAP(int, int) function will +1 for the '\0' null-terminator. Default = 1023.


// CORE DATA STRUCTURES/TYPES

typedef struct
AP {
char * major;
char * minor;
char sign;
}
AP;


typedef char OPCODE; // +, -, *, /, ^ (exp), and, or, not...

typedef struct
APExp { // AP OP AP
AP A;
AP B;
OPCODE OP;
}
APExp;

typedef struct APExpC	{ // (AP op AP) op (AP op AP)
	
	APExp A;
	APExp B;
	
	OPCODE OP;

} APExpC;

typedef struct APExpC_2	{ // (APExpC op APExpC)

	APExpC A;
	APExpC B;
	
	OPCODE OP;
	
} APExpC_2;


// FNC PROTOTYPES
AP NewAP( large,large );
void ClearAP( AP* );
AP CopyAP( AP* );
void flipSign( AP* );
void setSign( AP*,char );
char getSign( AP* );

signed short int cmpAP( AP*,AP* );
signed int overflow( AP*, int result, signed int k );
char tt( AP,AP );
char tt_mul( AP*,AP* );

#define part byte
statusCode setPart( AP, char *, part );

AP DefaultPrecision;

typedef struct __lens	{

	large precision;
	large offset;
} lens;



AP ADD( AP A, AP B );
AP ADDP( AP A, AP B, AP P );




AP SUB( AP A, AP B );
AP SUBP( AP A, AP B, AP P );
#define SUBTRACT SUB
#define SUBTRACTP SUBP


AP MUL( AP A, AP B );
AP MULP( AP A, AP B, AP P );
#define MULTIPLY MUL
#define MULTIPLYP MULP

AP DIV( AP A, AP B );
AP DIVP( AP A, AP B, AP P );
#define DIVIDE DIV
#define DIVIDEP DIVP
#define SUBDIVIDE DIVIDE
#define SUBDIVIDEP DIVIDEP

extern int DIV_BY_2_PRINT_ROWS;

char* memp( large numParts, large numBytes );


char* mem( large numBytes );




void* cmem( large nb )	{ return calloc( nb,1 ); }

char* zmem( large nb );
char* zmem( large nb )	{

	char* _ = (char*) malloc( nb+1 );
	
	large i;
	for( i=0; i<nb; i++ )
		_[i] = '0';

	_[i] = '\0';
	
	return _;
}

#define PartW 1
#define PartF 2
#define SignPart 0


statusCode setPartW( AP A, char * _ )	{

	return setPart( A, _, PartW );
}
statusCode setPartF( AP A, char * _ )	{

	return setPart( A, _, PartF );
}

statusCode setPart( AP A, char * digits, int sign_maj_min )	{

	if( sign_maj_min==SignPart )	{

		A->sign = *digits;
		
		if( A->sign==digits[0] )
		freturn SUCCESS;
		else
		return FAIL;
	}

	char * success;
	char * _;
	
	if( sign_maj_min==1 )
		_ = A.major;
	else
		_ = A.minor;
	
	if( strlen(_) < strlen(digits) )
		success = (char *)realloc(_, strlen(digits)+1);
	
	_ = success;
	
	large i;
	for( i=0; i<strlen(_); i++ )
		_[i] = digits[i];
	
	_[i] = '\0';
	
	return i;
}

AP RECIPROCAL( AP A );

// These are full-precision by nature.
AP DIV_BY_2(AP A);
AP EXP(AP A, AP B);
AP RECIPROCAL( AP A );

#define D2 DIV_BY_2
#define E EXP

char * AND(char * LHS, char * RHS);
char * OR (char * LHS, char * RHS);
char * XOR(char * LHS, char * RHS);
char * NOT(char * v);
char * NAND(char * LHS, char *RHS);



int lcm_test(int, int[], int[]);
int LCM(int, int, int);
int GCD(int a, int b, int lcm);

char * DEC_2_BIN(AP input, int packed);
char * BIN_2_DEC(char * bin);

int max2k(AP input);
int min2k(AP input);

void FreeAP(AP A);
int MSD(int num);
void pack_trailing_zeroes( char * curr_row, int Array_length, int num_zeroes );
char * fill_leading_zeroes( char * str, int num_zeroes );

int str2int(char *input);
char * int2str(int v);


#endif

