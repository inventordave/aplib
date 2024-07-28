// DAVE'S i754 dev-silo

#ifndef DAVE_i754
#define DAVE_i754


// STDLIB INC'S
#include <stdlib.h>
#include <string.h>
#include <assert.h>


// CUSTOM INC'S
#include "aplib.h"


// CORE DATA STRUCTURES
typedef struct i754	{
	
	// CONSTRUCTOR
	char* (*Init)( struct i754* );

	// BINTOOLS
	struct BINARYTOOLS BIN;
	
	// FLOAT/DOUBLE METHODS
	char * (*readFloat)( float );
	char * (*reaDouble)( double );	
	void (*writeFloat)( float* dest, char* str );
	void (*writeDouble)( double* dest, char* str );
	char (*getFloatBit)( char* str, LARGE offset );
	char (*getDoubleBit)( char* str, LARGE offset );
	char * (*convertFloatString2BigEndian)( char* );
	char * (*convertDoubleString2BigEndian)( char* );
	char * (*convertFloatString2LittleEndian)( char* );
	char * (*convertDoubleString2LittleEndian)( char* );

} i754;

typedef struct BINARYTOOLS{

	char (*getBit)( LARGE offset, char* bstr );
	char (*setBit)( LARGE offset, char* bstr, char v );

	char * (*convertBinString2BigEndian)( char* );
	char * (*convertBinString2BigEndian)( char* );
	char * (*convertBinString2LittleEndian)( char* );
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

typedef struct i754_Float	{

	int sign;
	
	int exponent;

	// NOT COMPLETE!
	int significand;

} i754_Float;


// FNC PROTOTYPES //

struct i754 * initi754();

// THE FUNCTION BELOW ADDS 1 TO A BINARY STRING
char* INCB( char* );
// THE FUNCTION BELOW FLIPS (INVERTS) A BIT-STRING
char* FLIPB( char* );
// THIS FUNCTION CALCULATES THE 2'S COMPLEMENT OF A BIT-STRING.
// DEP: FLIPB( char* ), INCB( char* )
char* _2sComplement( char* );


char * IEEE_readFloat( float f );
char * IEEE_reaDouble( double f );

void IEEE_writeFloat(float * dest, char * str);
void IEEE_writeDouble(double * dest, char * str);

char * IEEE_convertFloatString2BigEndian( char * str );
char * IEEE_convertDoubleString2BigEndian( char * str );

struct i754_Float * IEEE_writeFloatStruct( float * f );
float IEEE_readFloatStruct( struct i754_Float* f );

unsigned short int IEEE_getFloatBit( char * str, unsigned int offset );
unsigned short int IEEE_getDoubleBit( char * str, unsigned int offset );

// NOT YET IMPLEMENTED
void systemEndian()	{

	char unknown = 0;
	char le = 1;
	char be = 2;
	
	// Here is the test using signed int.
	
	int iwidth = sizeof( int );
	
	printf( "sizeof( int ) reports a width of %d bytes.\n", iwidth );
	
	signed int t = -256;
	
	char* p = (char*) &t;
	char* _ = (char *)calloc( iwidth );
	
	for( int i=0; i<iwidth; i++ )	{
		
		_[i] = p[i];
	}

	if( iwidth==8 )	{
		
		// size(4) le= byte 0, byte 3, be= byte 0, byte 2
		// size(8) le= byte 1, byte 7, be= byte 0, byte 6
		
		if
		(
			( (p[2] & 255)==1 ) &&
			( (p[7] & 255)==128 )
			
		)	{ printf( "The local system is little-endian.\n" ); }
		else if
		(
			( (p[0] & 255)==128 ) &&
			( (p[6] & 255)==1   )
			
		)	{ printf( "The local system is big-endian.\n" ); }

		
		// the others in size(8) should have 0.
	}
	else if( iwidth==4 ) 	{
		
		
		// assuming int has width of 4.
		// if big-endian, the string would be 10000000 00000000 00000001 00000000 (the MSB of each byte is the left-most bit in each substring ,but the bytes go from
		// left to right in sequence from base-address.
		// if little-endian, the string would be 00000000 00000001 00000000 100000000
		
		if
		(	( (p[0] & 255)==0 ) &&
			( (p[1] & 255)==1 ) &&
			( (p[2] & 255)==0 ) &&
			( (p[3] & 255)==128 )
		)	{ printf( "The local system is little-endian.\n" ); }
		
		else if
		(	( (p[0] & 255)==128 ) &&
			( (p[1] & 255)==0 ) &&
			( (p[2] & 255)==1 ) &&
			( (p[3] & 255)==0 )
		)	{ printf( "The local system is big-endian.\n" ); }
		
		else
			printf( "Unable to determine the local system endianness.\n" );
	}
	
	
	
	return;
}

#endif

