// APLIB_H

#ifndef APLIB_INTERFACE
#define APLIB_INTERFACE

// STD INC'S
#include <string.h>
#include <math.h>
#include <assert.h>

// CUSTOM INC'S
#include "lib.h"
#include "colour.h"

// STATIC DEFS
#define MAX_LENGTH_AP_PART 1023 //Make this any number of bytes you want. The NewAP(int, int) function will +1 for the '\0' null-terminator. Default = 1023.

// CORE DATA STRUCTURES/TYPES
#define part toggle
#define PART part


char MUL_SYM = '*';
char ADD_SYM = '+';
char SUB_SYM = '-';
char DIV_SYM = '/';
char EXP_SYM = 'e';
char AND_SYM = '&';
char NOT_SYM = '~';
char OR_SYM =  '|';
char XOR_SYM = '^';
char NAND_SYM = '@';
char POSITIVE_SYM = '+';
char NEGATIVE_SYM = '-';
char DELIMETER_SYM = '.';
char BASE10_SYM = '0';
char BASE2_SYM = '2';
char BASE16_SYM = 'H';
char* ALL_DIGITAL_SYMBOLS = "0123456789abcdefABCDEF.hHxX";


typedef char OPCODE; // +, -, *, /, ^ (exp), and, or, not...
typedef struct
AP {
char * major;
char * minor;
char sign;
}
AP;
typedef struct
APExp { // AP OP AP
AP A;
AP B;
OPCODE OP;
}
APExp;
typedef struct APExpC	{ // (AP OP AP) [OP] (AP OP AP)
	
	APExp A;
	APExp B;	
	OPCODE OP;

} APExpC;
typedef struct APExpC_2	{ // (APExpC OP APExpC)

	APExpC A;
	APExpC B;
	
	OPCODE OP;
	
} APExpC_2;


// APLIB SYSTEM INTRINSICS
AP AP0;
AP AP1;
AP DefaultPrecision;

typedef struct __APLIB__{

int ANSIVT;
large Precision;
} LL;


struct __APLIB__ APLIB_;
struct __APLIB__* APLIB = &APLIB_;


//// --- APLIB FNC'S --- ////



/**
APLIB->DefaultPrecision, // 0 means the LHS/RHS operands determine the precision of a result value.
APLIB->DefaultBase, // 2,10,16
APLIB->PackedStrings, // if set, each digit is stored in 4 bits instead of 8, meaning each byte can store 2 digits instead of 1. the strings would need to be unpacked, though.
*/

 
statusCode InitAPLIB() {

	return 0;
}
void init_();	

// CREATE/RESET/GC AP VALUES.
AP NewAP( large,large );
AP CopyAP( AP* );
void ClearAP( AP* );
void FreeAP( AP* A );

// EQUALITY READ-OPERATOR
signed short int CmpAP( AP*,AP* );

// BOOLEAN BIT-WISE OPERATORS
char * AND(char * LHS, char * RHS);
char * OR (char * LHS, char * RHS);
char * XOR(char * LHS, char * RHS);
char * NOT(char * v);
char * NAND(char * LHS, char *RHS);

// CORE OPERATORS
AP NOP( AP,AP );
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
AP DIVBY2(AP A);
#define DIVIDE DIV
#define DIVIDEP DIVP
#define SUBDIVIDE DIVIDE
#define SUBDIVIDEP DIVIDEP
#define D2 DIVBY2
AP RECIPROCAL( AP A );
AP RECIPROCAL2( AP A, AP B );
#define N1 RECIPROCAL
#define NM RECIPROCAL2
AP RECIPROCALP( AP A, large P );
AP RECIPROCAL2P( AP A, AP B, large P );
AP EXP(AP A, AP B);
AP CROSS( AP A, AP B );
AP CROSSP( AP A, AP B, AP P );
AP DOT( AP A, AP B );
AP DOTP( AP A, AP B, AP P );


int maxLoopsSet;

// SIGN ( +,- )
void flipSign( AP* );
void setSign( AP*,char );
char getSign( AP* );

// 1-based peek at [large]-th digit.
char peek( large,char* );




// QUICK SIGN-IDENTIFICATION FOR NORMAL'D RESULT VALUES.
char tt( AP*,AP* );
char tt_mul( AP*,AP* );



typedef struct __lens	{

	large precision;
	large offset;
} lens;



// FOR DIAGNOSTICS, OR JUST FOR THE PRETTY-PRINTER.
extern int DIVBY2_PRINT_ROWS;


// MODIFYING AP VALUES
statusCode setPart( AP* A, char * digits, int sign_maj_min );
statusCode setPartW( AP* A, char * _ ); // "whole" part
statusCode setPartF( AP* A, char * _ ); // "fractional" part
#define PartW 1
#define PartF 2
#define SignPart 0


int lcm_test(int, int[], int[]);
int LCM(int, int, int);
int GCD(int a, int b, int lcm);

char * DEC_2_BIN(AP input, int packed);
char * BIN_2_DEC(char * bin);

// 2k-BOUNDARY
large max2k(AP input);
large min2k(AP input);


int MSD(int num);
void pack_trailing_zeroes( char * curr_row, int Array_length, int num_zeroes );
char * fill_leading_zeroes( char * str, large num_zeroes );

signed int overflow( AP*, int result, signed int k );

int str2int(char *input);
char * int2str(int v);


#endif

