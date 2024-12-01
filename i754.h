// DAVE'S i754 dev-silo

#ifndef DAVE_i754
#define DAVE_i754


// STDLIB INC'S
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
// uint32_t etc
//  the types int_leastNN_t and uint_leastNN_t for NN 8, 16, 32, and 64 must always exist.
//There is also a uint128_t if __SIZEOF_INT128__ is defined to 16 or greater (GCC and compatibles).
// Its available on x86_64/amd64 machines, but the processor does not natively support it.
// Only Cray's have that register size.

// CUSTOM INC'S
#include "aplib.h"
#include "io.h"


// DEFINES
#define  CANNOT_OPTIMIZE_TO_NATIVE_uint_32_STORAGE_CLASS 1
#define  CANNOT_OPTIMIZE_TO_NATIVE_uint_16_STORAGE_CLASS 2
#define  CANNOT_OPTIMIZE_TO_NATIVE_uint_8_STORAGE_CLASS 3
//SIGUSR1 and SIGUSR2

//SIGUSR2 is a user-defined signal I can use for reporting error.

uint_32_t ConvertToNativeU32( char* _ );
uint_16_t ConvertToNativeU16( char* _ );

int UserContext;

uint_8_t ConvertToNativeU8( char* _ )	{

	int strlen__ = strlen( _ );

	if( strlen__==0 )
		return (uint_8_t)0;

	if( strlen__ > 3 )	{
		signal( CANNOT_OPTIMIZE_TO_NATIVE_uint_8_STORAGE_CLASS, UserContext );
		return (uint_8_t)0;
	}

	int i;
	uint_8_t v = 0;
	uint_8_t order = 1;
	v += '0' - _[i];
	for( i=strlen__-2; i>=0; i-- )	{

		order *= 10;
		v += ('0' - _[i]) * order;
	}

	return v;
}


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

