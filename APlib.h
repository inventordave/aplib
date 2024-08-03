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

// STATIC DEF'S
#define MAX_LENGTH_AP_PART 1023 //Make this any number of bytes you want. The NewAP(int, int) function will +1 for the '\0' null-terminator. Default = 1023.
#define L LARGE

// CORE DATA STRUCTURES/TYPES
extern char* MUL_SYM;
extern char* ADD_SYM;
extern char* SUB_SYM;
extern char* DIV_SYM;
extern char* EXP_SYM;
extern char* AND_SYM;
extern char* NOT_SYM;
extern char* OR_SYM;
extern char* XOR_SYM;
extern char* NAND_SYM;
extern char* POSITIVE_SYM;
extern char* NEGATIVE_SYM;
extern char* DELIMETER_SYM;
extern char* BASE10_SYM;
extern char* BASE2_SYM;
extern char* BASE16_SYM;
extern char* ALL_DIGITAL_SYMBOLS;

typedef char*
OPCODE; // +, -, *, /, ^ (exp), and, or, not...

typedef struct
lens_	{

	L p;
	L x;
}
lens_;

#define wp wholepart
typedef struct
AP {
	char* wholepart;
	char* fp;
	char sign;
	lens_ lens;
	
	char base;
}
AP;
#define ap AP

typedef struct
APExp { // AP OP AP
AP A;
AP B;
OPCODE OP;
}
APExp;

typedef struct
APExpC	{ // (AP OP AP) [OP] (AP OP AP)
	
	APExp A;
	APExp B;	
	OPCODE OP;

}
APExpC;
	
typedef struct
APExpC_2	{ // (APExpC OP APExpC)

	APExpC A;
	APExpC B;
	
	OPCODE OP;
	
}
APExpC_2;

typedef struct
_APLIB	{
	
	AP* (*NOP)( AP*,AP* );
	AP* (*ADD)( AP*,AP* );
	AP* (*ADDP)( AP*,AP*, L );
	AP* (*SUB)( AP*,AP* );
	AP* (*SUBP)( AP*,AP*, L );
	AP* (*MUL)( AP*,AP* );
	AP* (*MULP)( AP*,AP*, L );
	AP* (*DIV)( AP*,AP* );
	AP* (*DIVP)( AP*,AP*, L );
	AP* (*DIVBY2)( AP* );
	AP* (*RECIPROCAL)( AP* );
	AP* (*RECIPROCAL2)( AP*,AP* );
	AP* (*RECIPROCALP)( AP*, L );
	AP* (*RECIPROCAL2P)( AP*,AP*, L );
	AP* (*EXP)( AP*,AP* );	
	AP* (*CROSS)( AP*,AP* );
	AP* (*CROSSP)( AP*,AP*, L );	
	AP* (*DOT)( AP*,AP* );
	AP* (*DOTP)( AP*,AP*, L );	

	AP* (*AND)( AP*,AP* );
	AP* (*OR)( AP*,AP* );
	AP* (*XOR)( AP*,AP* );
	AP* (*NAND)( AP*,AP* );
	AP* (*NOT)( AP* );	
	
	void (*flipSign)( AP* );
	char (*getSign)( AP* );
	void (*setSign)( AP* );
	
	L (*DSTRING2LARGE)( AP* );
	
	L p;
	
	struct _ANSI* ANSIVT;
}
_APLIB;	

// APLIB SYSTEM INTRINSICS
extern AP AP0;
extern AP AP1;
extern LARGE DefaultPrecision;
extern large MAX_LENGTH;

//// --- APLIB SETTINGS --- ////
// APLIB->p
// 0 means the LHS/RHS operands determine the precision of a result value.
//APLIB->DefaultBase
// 2,8,10,16
//APLIB->packed
// if set, each digit is stored in 4 bits instead of 8, meaning each byte can store 2 digits instead of 1. the strings would need to be unpacked, though.

// INIT()
extern struct _APLIB* Init_APLIB();

// GRANULAR (DIGIT-WISE) TOOLS //
// DIGIT::GET(INDEX)
extern char d( ap*,L );
// DIGIT::SET( DIGIT,INDEX )
#define sd setDigit
extern void setDigit( ap*,L,char );

// CREATE/RESET/GC AP VALUES //
extern AP NewAP( L,L );
extern AP* NewAPr( L,L );
extern AP CopyAP( AP* );
extern void ClearAP( AP* );
extern void FreeAP( AP* );

// EQUALITY READ-OPERATOR
extern signed short CmpAP( AP*,AP* );

// CORE OPERATORS
extern AP* NOP( AP*,AP* );
extern AP* ADD( AP* A, AP* B );
extern AP* ADDP( AP* A, AP* B, AP* P );
extern AP* SUB( AP* A, AP* B );
extern AP* SUBP( AP* A, AP* B, AP* P );
#define SUBTRACT SUB
#define SUBTRACTP SUBP
extern AP* MUL( AP* A, AP* B );
extern AP* MULP( AP* A, AP* B, AP* P );
#define MULTIPLY MUL
#define MULTIPLYP MULP
extern AP* DIV( AP* A, AP* B );
extern AP* DIVP( AP* A, AP* B, AP* P );
extern AP* DIVBY2(AP* A);
#define DIVIDE DIV
#define DIVIDEP DIVP
#define SUBDIVIDE DIVIDE
#define SUBDIVIDEP DIVIDEP
#define D2 DIVBY2
extern AP* RECIPROCAL( AP* A );
extern AP* RECIPROCAL2( AP* A, AP* B );
#define N1 RECIPROCAL
#define NM RECIPROCAL2
extern AP* RECIPROCALP( AP* A, L P );
extern AP* RECIPROCAL2P( AP* A, AP* B, L P );
extern AP* EXP(AP* A, AP* B);
extern AP* CROSS( AP* A, AP* B );
extern AP* CROSSP( AP* A, AP* B, L P );
extern AP* DOT( AP* A, AP* B );
extern AP* DOTP( AP* A, AP* B, L P );
// BOOLEAN BIT-WISE OPERATORS
extern ap* AND( ap* LHS, ap* RHS );
extern ap* OR (ap* LHS, ap* RHS);
extern ap* XOR(ap* LHS, ap* RHS);
extern ap* NOT(ap* v);
extern ap* NAND(ap* LHS, ap*RHS);

// SIGN ( +,- )
extern void flipSign( AP* );
extern void setSign( AP*,char );
extern char getSign( AP* );

// 1-based peek at [large]-th digit.
extern char peek( L,char* );

// QUICK SIGN-IDENTIFICATION FOR NORMAL'D RESULT VALUES.
extern char tt_add( AP*,AP* );
extern char tt_mul( AP*,AP* );

// FOR DIAGNOSTICS, OR JUST FOR THE PRETTY-PRINTER.
extern large DIVBY2_PRINT_ROWS;

// MODIFYING AP VALUES
extern L setPart( AP*, char*, large part );
extern L setPartW( AP*, char* ); // "whole" part
extern L setPartF( AP*, char* ); // "fractional" part
#define SignPart 0
#define PartW 1
#define PartF 2
extern AP* RESET0( AP* );
extern AP* RESET1( AP* );

// USEFUL FEATURES
#define APTR AP*
extern AP* GCD( AP*,AP*, AP* lcm );
extern AP* LCM( AP*,AP* );
extern AP* LCMTESTSR( APTR, APTR*,APTR* ); // Not a typo. The last 2 parameters are each (AP**).
extern L DSTRING2LARGE( AP* );

// BASE CONVERSION
typedef char* String;
extern APTR DEC_2_BIN( APTR,L packed );
extern APTR BIN_2_DEC( APTR );
extern APTR DEC_2_HEX( APTR,L packed );
extern APTR HEX_2_DEC( APTR );
extern APTR DEC_2_OCTAL( APTR,L );
extern OCTAL_2_DEC( APTR );
extern APTR BIN_2_HEX( APTR );
extern APTR HEX_2_BIN( APTR );

extern OCTAL_2_HEX( APTR );
extern HEX_2_OCTAL( APTR );
extern OCTAL_2_BIN( APTR );
extern BIN_2_OCTAL( APTR );

extern LARGE lenp( AP* );



#define aplibstdreturn(b) APTR _ = NewAPr( 1,0 ); setPartW( _,"1" ); _->base = b; return _;
APTR DEC_2_HEX( APTR A,L packed ){

	aplibstdreturn(2);
}
APTR HEX_2_DEC( APTR A ){

	aplibstdreturn(10);
}
APTR DEC_2_OCTAL( APTR A, L precisiom ){

	aplibstdreturn(8);
}
APTR OCTAL_2_DEC( APTR A ){

	aplibstdreturn(10);
}
APTR DEC_2_HEX( APTR A ){

	aplibstdreturn(16);
}
APTR BIN_2_OCTAL( APTR A ){

	aplibstdreturn(8);
}
APTR OCTAL_2_BIN( APTR A ){

	aplibstdreturn(2);
}





// 2k-BOUNDARY
extern L Max2K(AP*);
extern L Min2K(AP*);

extern L MSD( AP* A );


// ALIGNMENT TOOLS
extern L PackTrailingZeroes( char* cr, L alength#/=/, L n0 );
extern string PackLeadingZeroes( char* str, L n0 );

extern signed OverFlow( AP*, int result, signed k );

// ENCODE/DECODE
extern L charp2L(char* input);
extern char* L2charp( L v );

// APLIB API SUPPORT FUNCTIONS
extern char** GetAPSymbols();
// 	GetAPSymbols DEFS.
#include "aplib_sym.h"

#endif

