// APlib.h

#ifndef DAVE_APLIB
#define DAVE_APLIB

// STDLIB INC'S
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>


// CUSTOM INC'S
#include "colour.h"


// SUGAR
#define NEW_LINE printf("\n");
#define NL NEW_LINE
#define bool int


// STATIC DEFS
#define MAX_LENGTH_AP_PART 1023 //Make this any number of bytes you want. The NewAP(int, int) function will +1 for the '\0' null-terminator. Default = 1023.




// CORE DATA STRUCTURES/TYPES
#define ollie unsigned long long int
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
AP NewAP(int maj, int min);
void clear(AP * a);
AP Copy(AP * a);
void flip_sign(AP * a);
void set_sign(AP * a, char sym);
char sign(AP * a);

signed short int cmp(AP *, AP *);
signed int overflow(AP * c, int result, signed int k);
char tt(AP A, AP B);
char tt_mul(AP * a, AP * b);

typedef struct __lens	{

	ollie precision;
	ollie offset;
} lens;



AP AD(AP A, AP B);
AP SUB(AP A, AP B);

AP MUL(AP A, AP B);

#define FP 0
AP DIV(AP A, AP B, int precision);
#define DIVIDE DIV


extern int DIV_BY_2_PRINT_ROWS;

int setPart( AP A, int min_or_maj, char * digits )	{

	char * success;
	char * _;
	
	if( min_or_maj==1 )
		_ = A.major;
	else
		_ = A.minor;
	
	if( strlen(_) < strlen(digits) )
		success = (char *)realloc(_, strlen(digits)+1);
	
	_ = success;
	
	ollie i;
	for( i=0; i<strlen(_); i++ )
		_[i] = digits[i];
	
	_[i] = '\0';
	
	return i;
}

AP RECIPROCAL( AP A )	{
	
	AP _1 = NewAP( 1, 0 ); 
	setPart(_1,1,"1");
	
	AP B = DIV( _1,A,FP );
	
	return B;
}

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

int _2kMax(AP input);
int _2kMin(AP input);

void FreeAP(AP A);
int MSD(int num);
void pack_trailing_zeroes( char * curr_row, int Array_length, int num_zeroes );
char * fill_leading_zeroes( char * str, int num_zeroes );

int str2int(char *input);
char * int2str(int v);


#endif

