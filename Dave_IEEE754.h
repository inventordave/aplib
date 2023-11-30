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


// CUSTOM INC'S
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

	int sign;
	
	int exponent;

	// NOT COMPLETE!
	int significand;

} IEEE754_Float;


// FNC PROTOTYPES
struct IEEE754 * initIEEE754();

char * IEEE_readFloat( float f );
char * IEEE_readDouble( double f );

void IEEE_writeFloat(float * dest, char * str);
void IEEE_writeDouble(double * dest, char * str);

char * IEEE_convertFloatString2BigEndian( char * str );
char * IEEE_convertDoubleString2BigEndian( char * str );

struct IEEE754_Float * IEEE_writeFloatStruct( float * f );
float IEEE_readFloatStruct( struct IEEE754_Float* f );

unsigned short int IEEE_getFloatBit( char * str, unsigned int offset );
unsigned short int IEEE_getDoubleBit( char * str, unsigned int offset );

#endif

