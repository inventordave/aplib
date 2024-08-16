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

#define APLS char*

#define scint signed short int



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

#define wp integer
typedef char small;
typedef struct
APP {
	char* integer;
	char* fractional;
	char sign;
	small base;
	L fp;
	L p;

	lens_ lens;
}
APP;
typedef APP* APL;
#define AP APP*
#define ap AP

typedef struct
APExp { // AP OP AP
AP A;
AP B;
OPCODE OP;
}
APExp;
typedef APExp* APE;
#define ape APE
#define apex APE
#define apexp APE
#define apexpression APE

typedef struct
APExpC	{ // (AP OP AP) [OP] (AP OP AP)
	
	APExp A;
	APExp B;	
	OPCODE OP;
}
APExpC;
typedef APExpC* CEX;
#define cex CEX
#define complex CEX
#define complexexpression CEX
#define cexp CEX
#define complexexp CEX
	#
typedef struct
APExpC_2	{ // (APExpC OP APExpC)

	APExpC A;
	APExpC B;
	
	OPCODE OP;
	
}
APExpC_2;

typedef struct
_APLIB	{
	
	APL (*RESET0)( APL );
	APL (*RESET1)( APL );

	
	APL (*NOP)( APL );
	APL (*ADD)( APL,APL );
	APL (*ADDP)( APL,APL, APL );
	APL (*SUB)( APL,APL );
	APL (*SUBP)( APL,APL, APL );
	APL (*MUL)( APL,APL );
	APL (*MULP)( APL,APL, APL );
	APL (*DIV)( APL,APL );
	APL (*DIVP)( APL,APL, APL );
	APL (*DIVBY2)( APL );
	APL (*RECIPROCAL)( APL );
	APL (*RECIPROCAL2)( APL,APL );
	APL (*RECIPROCALP)( APL, APL );
	APL (*RECIPROCAL2P)( APL,APL, APL );
	APL (*EXP)( APL,APL );	
	APL (*CROSS)( APL,APL );
	APL (*CROSSP)( APL,APL, APL );	
	APL (*DOT)( APL,APL );
	APL (*DOTP)( APL,APL, APL );	

	APL (*AND)( APL,APL );
	APL (*OR)( APL,APL );
	APL (*XOR)( APL,APL );
	APL (*NAND)( APL,APL );
	APL (*NOT)( APL );	

	int (*INC)( APL );
	int (*DEC)( APL );
	
	void (*flipSign)( APL );
	char (*getSign)( APL );
	void (*setSign)( APL, char );
	
	L (*DSTRING2LARGE)( APL );
	
	L p;
	small packed;
	small defaultBase;
	
	struct _ANSI* ANSI;
}
_APLIB;	

// APLIB SYSTEM INTRINSICS
extern AP AP0;
extern AP AP1;
extern AP DefaultPrecision;
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
extern char d( APL,L );
// DIGIT::SET( DIGIT,INDEX )
#define sd setDigit
extern void setDigit( APL,L,char );

// CREATE/RESET/GC AP VALUES //
extern APL NewAP( L,L );
extern APL NewAPr( L,L );
extern APL CopyAP( APL );
extern void ClearAP( APL );
extern void FreeAP( APL );

// EQUALITY READ-OPERATOR
extern short CmpAP( APL,APL );

// CORE OPERATORS
extern int INC( AP A );
extern int DEC( AP A );


extern APL NOP( APL A, APL B );
extern APL ADD( APL A, APL B );
extern APL ADDP( APL A, APL B, APL P );
extern APL SUB( APL A, APL B );
extern APL SUBP( APL A, APL B, APL P );
#define SUBTRACT SUB
#define SUBTRACTP SUBP
extern APL MUL( APL A, APL B );
extern APL MULP( APL A, APL B, APL P );
#define MULTIPLY MUL
#define MULTIPLYP MULP
extern APL DIV( APL A, APL B );
extern APL DIVP( APL A, APL B, APL P );
extern APL DIVBY2(APL A);
#define DIVIDE DIV
#define DIVIDEP DIVP
#define SUBDIVIDE DIVIDE
#define SUBDIVIDEP DIVIDEP
#define D2 DIVBY2
extern APL RECIPROCAL( APL A );
extern APL RECIPROCAL2( APL A, APL B );
#define N1 RECIPROCAL
#define NM RECIPROCAL2
extern APL RECIPROCALP( APL A, APL P );
extern APL RECIPROCAL2P( APL A, APL B, APL P );
extern APL EXP(APL A, APL B);
extern APL CROSS( APL A, APL B );
extern APL CROSSP( APL A, APL B, APL P );
extern APL DOT( APL A, APL B );
extern APL DOTP( APL A, APL B, APL P );
// BOOLEAN BIT-WISE OPERATORS
extern APL AND( APL LHS, APL RHS );
extern APL OR (APL LHS, APL RHS);
extern APL XOR(APL LHS, APL RHS);
extern APL NOT(APL v);
extern APL NAND(APL LHS, APL RHS);

// SIGN ( +,- )
extern void flipSign( APL );
extern void setSign( APL,char );
extern char getSign( APL );

// 1-based peek at [large]-th digit.
extern char peek( L,char* );
#define PEEK peek

extern char poke( char*, char*, L offset );



// QUICK SIGN-IDENTIFICATION FOR NORMAL'D RESULT VALUES.
extern char TT_ADD( APL,APL );
extern char TT_MUL( APL,APL );

// FOR DIAGNOSTICS, OR JUST FOR THE PRETTY-PRINTER.
extern large DIVBY2_PRINT_ROWS;

// MODIFYING AP VALUES
extern L setPart( APL, char*, large part );
extern L setPartW( APL, char* ); // "integer" part
extern L setPartF( APL, char* ); // "fractional" part
#define SignPart 0
#define PartW 1
#define PartF 2
extern APL RESET0( APL );
extern APL RESET1( APL );

// USEFUL FEATURES
#define APTR APL
extern APL GCD( APL,APL, APL lcm );
extern APL LCM( APL,APL );
extern APL LCMTESTSTR( APTR, APTR*,APTR* ); // Not a typo. The last 2 parameters are each (APL*).
extern L DSTRING2LARGE( APL );

// BASE CONVERSION
typedef char* String;
extern char* DEC_2_BIN( char*,L packed );
extern char* BIN_2_DEC( char* );
extern APTR DEC_2_HEX( APTR,L packed );
extern APTR HEX_2_DEC( APTR );
extern APTR DEC_2_OCTAL( APTR,L );
extern APTR OCTAL_2_DEC( APTR );
extern APTR BIN_2_HEX( APTR );
extern APTR HEX_2_BIN( APTR );

extern APTR OCTAL_2_HEX( APTR );
extern APTR HEX_2_OCTAL( APTR );
extern APTR OCTAL_2_BIN( APTR );
extern APTR BIN_2_OCTAL( APTR );

extern LARGE lenp( APL );



#define aplibstdreturn(b) APTR _ = NewAPr( 1,0 ); setPartW( _,"1" ); _->base = b; return _;

// 2k-BOUNDARY
extern L Max2K(APL);
extern L Min2K(APL);

extern L MSD( int );

// ALIGNMENT TOOLS
extern void PackTrailingZeroes( char* cr, L alength, L n0 );
extern string PackLeadingZeroes( char* str, L n0 );

extern signed OverFlow( APL, int result, signed k );

// ENCODE/DECODE
extern L charp2L(char* input);
extern char* L2charp( L v );

// APLIB API SUPPORT FUNCTIONS
extern char** GetAPSymbols();
// 	GetAPSymbols DEFS.
#include "aplib_sym.h"

#endif

	