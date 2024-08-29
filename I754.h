// DAVE'S i754 dev-silo

#ifndef DAVE_i754
#define DAVE_i754


// STDLIB INC'S
#include <stdlib.h>
#include <string.h>
#include <assert.h>


// CUSTOM INC'S
#include "aplib.h"
#include "io.h"


// CORE DATA STRUCTURES

typedef struct BINARYTOOLS{

	char (*getBit)( LARGE offset, char* bstr );
	char (*setBit)( LARGE offset, char* bstr, char v );

	char * (*convertBinString2BigEndian)( char* );
	//char * (*convertBinString2BigEndian)( char* );
	//char * (*convertBinString2LittleEndian)( char* );
	char * (*convertBinString2LittleEndian)( char* );

	char* (*DEC_2_BIN)( char* );
	char* (*HEX_2_BIN)( char* );
	char* (*OCTAL_2_BIN)( char* );
	char* (*BIN_2_DEC)( char* );
	char* (*BIN_2_HEX)( char* );
	char* (*BIN_2_OCTAL)( char* );
	char* (*BIN_2_NBASE)( char*,char* );
	char* (*NBASE_2_BIN)( char*,char* );
	
	char* (*INCB)( char* );
	char* (*FLIPB)( char* );
	char* (*_2SCOMP)( char* );

} BINARYTOOLS;

typedef struct i754	{
	
	// CONSTRUCTOR
	char* (*Init)( struct i754* );

	// BINTOOLS
	struct BINARYTOOLS BIN;
	
	// FLOAT/DOUBLE METHODS
	char* (*readFloat)( float );
	char* (*readDouble)( double );	
	void (*writeFloat)( float* dest, char* str );
	void (*writeDouble)( double* dest, char* str );
	char* (*getFloatBit)( char* str, LARGE offset );
	char* (*getDoubleBit)( char* str, LARGE offset );
	char* (*convertFloatString2BigEndian)( char* );
	char* (*convertDoubleString2BigEndian)( char* );
	char* (*convertFloatString2LittleEndian)( char* );
	char* (*convertDoubleString2LittleEndian)( char* );

} i754;
typedef struct i754_Float	{

	int sign;
	
	int exponent;

	// NOT COMPLETE!
	int significand;

} i754_Float;


// FNC PROTOTYPES //

struct i754* initi754();

// THE FUNCTION BELOW ADDS 1 TO A BINARY STRING
char* INCB( char* );
// THE FUNCTION BELOW FLIPS (INVERTS) A BIT-STRING
char* FLIPB( char* );
// THIS FUNCTION CALCULATES THE 2'S COMPLEMENT OF A BIT-STRING.
// DEP: FLIPB( char* ), INCB( char* )
char* _2sComplement( char* );


char* IEEE_readFloat( float f );
char* IEEE_readDouble( double f );

void IEEE_writeFloat(float * dest, char * str);
void IEEE_writeDouble(double * dest, char * str);

char* IEEE_convertFloatString2BigEndian( char * str );
char* IEEE_convertDoubleString2BigEndian( char * str );

struct i754_Float * IEEE_writeFloatStruct( float * f );
float IEEE_readFloatStruct( struct i754_Float* f );

char* IEEE_getFloatBit( char * str, LARGE offset );
char* IEEE_getDoubleBit( char * str, LARGE offset );

// NOT YET IMPLEMENTED
void systemEndian();



#endif

