// APLIB_H

#ifndef APLIB_INTERFACE
#define APLIB_INTERFACE

// STD INC'S
#include <string.h>
#include <math.h>
#include <assert.h>

// largest primitive integer type on target systems.

#ifndef large
#define large long long
#define L large
#define LARGE large
#endif

// MAX_LOOPS : 
extern L MAX_LOOPS;

// GC structure.
extern volatile struct GC* APLIB_gc;

// CUSTOM INC'S
#include "../davelib/lib.h"
#include "../colour/colour.h"


// STATIC DEF'S
#define MAX_LENGTH_AP_PART 1023
// Make this any number of bytes you want. The NewAP(int, int) function will +1 for the '\0' null-terminator. Default = 1023.

#define CONCAT( l,r ) strcat( l,r )

#define APS char*
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

// +, -, *, /, etc
typedef char* opcode;


// A byte, the smallest primitive integer type on target systems.
typedef unsigned char small;

typedef struct
APP {
	
	char* integer;
	char* fractional;

	// '+' or '-'.
	char sign;
	
	// base2, base10, base16
	small base;

	// The offset where a floating-point would be correctly positioned under the assumption that the
	// digit-string (ASCII numeric alphabet glyphs, beginning at ASCII offset 68)
	L fp; 
	
	// Level of precision.
	L p;

} APP;

// AP Value reference. These (pointer) types have to be instantiated.

typedef APP* AP;
#define ap AP

typedef struct
APExp { // AP OP AP
AP A;
AP B;
opcode OP;
}
APExp;
typedef APExp* APE;
#define ape APE


// APLIB SYSTEM INTRINSICS
extern AP AP0;
extern AP AP1;
extern AP DefaultPrecision;
extern large MAX_LENGTH;

typedef struct _APLIB	{
	
	AP (*RESET0)( AP );
	AP (*RESET1)( AP );

	AP AP0;
	AP AP1;

	AP (*NOP)( AP );
	AP (*ADD)( AP, AP );
	AP (*ADDP)( AP,AP, AP );
	AP (*SUB)( AP,AP );
	AP (*SUBP)( AP,AP, AP );
	AP (*MUL)( AP,AP );
	AP (*MULP)( AP,AP, AP );
	AP (*DIV)( AP,AP );
	AP (*DIVP)( AP,AP, AP );
	AP (*DIVBY2)( AP );
	AP (*RECIPROCAL)( AP );
	AP (*RECIPROCAL2)( AP,AP );
	AP (*RECIPROCALP)( AP, AP );
	AP (*RECIPROCAL2P)( AP,AP, AP );
	AP (*EXP)( AP,AP );	

	AP (*CROSS)( AP,AP );
	AP (*CROSSP)( AP,AP, AP );	
	AP (*DOT)( AP,AP );
	AP (*DOTP)( AP,AP, AP );	

	AP (*AND)( AP,AP );
	AP (*OR)( AP,AP );
	AP (*XOR)( AP,AP );
	AP (*NAND)( AP,AP );
	AP (*NOT)( AP );	

	int (*INC)( AP );
	int (*DEC)( AP );
	
	void (*flipSign)( AP );
	char (*getSign)( AP );
	void (*setSign)( AP, char );
	
	L (*DSTRING2LARGE)( AP );
	
	L DefaultPrecision;
	small packed;
	small DefaultBase;
	
	// The ANSI/VT "colour.h" Interface
	struct _ANSI_* ANSI;
}
_APLIB;	

char TT_MUL(AP A, AP B) ;

// INIT()
extern struct _APLIB* Init_APLIB();
void ANSI_init();

// GRANULAR (DIGIT-WISE) TOOLS //
// DIGIT::GET(INDEX)
extern char d( AP,L );
// DIGIT::SET( DIGIT,INDEX )
#define sd setDigit
extern void setDigit( AP,L,char );

// CREATE/RESET/GC AP VALUES //
extern AP NewAP( L,L );
extern AP NewAPr( L,L );
extern AP CopyAP( AP );
extern void ClearAP( AP );
extern void FreeAP( AP );
extern AP ParseAP( char* );

// MODIFYING AP VALUES
extern L setPart( AP, char*, large part );
extern L setPartW( AP, char* ); // "integer" part
extern L setPartF( AP, char* ); // "fractional" part
#define SignPart 0
#define PartW 1
#define PartF 2
extern AP RESET0( AP );
extern AP RESET1( AP );

// CORE OPERATORS
extern int INC( AP A );
extern int DEC( AP A );
extern AP ADD( AP A, AP B );
extern AP ADDP( AP A, AP B, AP P );
extern AP SUB( AP A, AP B );
extern AP SUBP( AP A, AP B, AP P );
#define SUBTRACT SUB
#define SUBTRACTP SUBP
extern AP MUL( AP A, AP B );
extern AP MULP( AP A, AP B, AP P );
#define MULTIPLY MUL
#define MULTIPLYP MULP
extern AP DIV( AP A, AP B );
extern AP DIVP( AP A, AP B, AP P );

extern char* DIV_str( char*, char* );

extern AP DIVBY2(AP A);
#define DIVIDE DIV
#define DIVIDEP DIVP
#define SUBDIVIDE DIVIDE
#define SUBDIVIDEP DIVIDEP
#define D2 DIVBY2

extern AP NLOG( AP );
extern AP NLOGP( AP, AP epsilon );
extern char* NLOG_str( char* );
extern AP LOGb( AP, AP base );
extern AP LOGb_( AP A, unsigned int base );

extern char* NLOG_str( char* );

extern AP RECIPROCAL( AP );
extern AP RECIPROCAL2( AP A, AP B );
#define N1 RECIPROCAL
#define NM RECIPROCAL2
extern AP RECIPROCALP( AP A, AP P );
extern AP RECIPROCAL2P( AP A, AP B, AP P );
extern AP EXP(AP A, AP B);
extern AP powAP( AP );
extern AP CROSS( AP A, AP B );
extern AP CROSSP( AP A, AP B, AP P );
extern AP DOT( AP A, AP B );
extern AP DOTP( AP A, AP B, AP P );
// BOOLEAN BIT-WISE OPERATORS
extern AP AND( AP LHS, AP RHS );
extern AP OR (AP LHS, AP RHS);
extern AP XOR(AP LHS, AP RHS);
extern AP NOT(AP v);
extern AP NAND(AP LHS, AP RHS);
extern AP NOP( AP A );

// EQUALITY READ-OPERATORS
extern short CmpAP_abs( AP,AP );

// SIGN ( +,- )
extern void flipSign( AP );
extern void setSign( AP,char );
extern char getSign( AP );

// 1-based peek/poke at [large]-th digit.
extern char peek( L,char* );
#define PEEK peek
extern char poke( char*, char*, L offset );
#define POKE poke

// QUICK SIGN-IDENTIFICATION FOR NORMALED RESULT VALUES.
extern char TT_ADD( AP,AP );
extern char TT_MUL( AP,AP );

// FOR DIAGNOSTICS, OR JUST FOR THE PRETTY-PRINTER.
extern large DIVBY2_PRINT_ROWS;

// USEFUL FEATURES

extern L DSTRING2LARGE( AP );
extern char* pack( char* );
extern char* unpack( char* );

// NOT-YET-IMPLEMENTED LCM, GCD FUNCTIONS.
extern AP GCD( AP,AP, AP lcm );
extern AP LCM( AP,AP );
extern AP LCMTESTSTR( AP, AP*,AP* ); // Not a typo. The last 2 parameters are each (AP*).

// BASE CONVERSION
typedef char* string;
extern char* DEC_2_BIN( char*,L packed );
extern char* BIN_2_DEC( char* );
extern AP DEC_2_HEX( AP,L packed );
extern AP HEX_2_DEC( AP );
extern AP DEC_2_OCTAL( AP,L );
extern AP OCTAL_2_DEC( AP );
extern AP BIN_2_HEX( AP );
extern AP HEX_2_BIN( AP );

extern AP OCTAL_2_HEX( AP );
extern AP HEX_2_OCTAL( AP );
extern AP OCTAL_2_BIN( AP );
extern AP BIN_2_OCTAL( AP );

extern LARGE lenp( AP );


#define APLIBstdreturn(b) { AP _ = NewAPr( 1,0 ); setPartW( _,"1" ); _->base = b; _->sign='+'; return _; }

// 2k-BOUNDARY
extern L Max2K(AP);
extern L Min2K(AP);

extern L MSD( int );

// ALIGNMENT TOOLS
extern void PackTrailingZeroes( char* cr, L alength, L n0 );
extern string PackLeadingZeroes( char* str, L n0 );


extern signed OverFlow( AP, int result, signed k );

// ENCODE/DECODE
extern L CharP2L(char* input);
extern char* L2CharP( L v );

// APLIB API SUPPORT FUNCTIONS
#include "aplib_sym.h"
extern char** GetAPSymbols();

#endif

	
