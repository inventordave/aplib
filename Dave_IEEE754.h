#ifndef DAVE_IEEE754
#define DAVE_IEEE754

// INFORMATIVE SECTION
/** Here is a simple solution I cooked up for accessing the internal bit-representation of floats.
As my system is little-endian, the LSByte is printed first, and the MSByte printed as the 4th subsequence. This obviously means that the left-most bit of the 4th subsequence (bits 24-31) is the sign bit, for signed r-values. There is a "convert string to big-endian" helper function to format the string properly for printing/screen output.
*/


// STDLIB INC'S
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "APlib.h"


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
	// NOT COMPLETE!
	int significand:24;
	
	int sign:1;
	
	int exponent:7;
	
} IEEE754_Float;


// FNC PROTOTYPES
struct IEEE754 * initIEEE754();
char * IEEE_readFloat( float f );
char * IEEE_convertFloatString2BigEndian( char * str );


// CORE FNCS
struct IEEE754_Float * IEEE_writeFloatStruct( float * f )	{
	
	struct IEEE754_Float * a = malloc( sizeof(IEEE754_Float) );
	
	char * i = (char *)a;
	
	char * k = (char *)f;
	
	for( int z=0; z<4; z++ )
		i[z] = k[z];
	
	return a;

}

float IEEE_readFloatStruct( struct IEEE754_Float* f )	{

	float a;
	
	char * i = (char *)&a;
	
	char * k = (char *)f;
	
	for( int z=0; z<4; z++ )
		i[z] = k[z];
	
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
	
	struct container * tc = malloc( sizeof(float) ); // 4 bytes for the float. Change to sizeof(double), which is 8, for a double.
	
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


#endif

