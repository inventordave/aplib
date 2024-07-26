// DAVE'S I754 dev-silo
// 
#ifndef I754
#define I754



// STDLIB INC'S
#include <stdlib.h>
#include <string.h>
#include <assert.h>


// CUSTOM INC'S
#include "APlib.h"


// CORE DATA STRUCTURES
typedef struct I754	{
	
	char * (*readFloat)( float f );
	char * (*reaDouble)( double f );
	
	char * (*convertFloatString2BigEndian)( char * str );
	char * (*convertDoubleString2BigEndian)( char * str );
	
	unsigned short int (*getFloatBit)( char * str, unsigned int offset );
	unsigned short int (*getDoubleBit)( char * str, unsigned int offset );
	
	void (*writeFloat)(float * dest, char * str);
	void (*writeDouble)(double * dest, char * str);

} I754;

typedef struct I754_Float	{

	int sign;
	
	int exponent;

	// NOT COMPLETE!
	int significand;

} I754_Float;


// FNC PROTOTYPES
struct I754 * initI754();

char * IEEE_readFloat( float f );
char * IEEE_reaDouble( double f );

void IEEE_writeFloat(float * dest, char * str);
void IEEE_writeDouble(double * dest, char * str);

char * IEEE_convertFloatString2BigEndian( char * str );
char * IEEE_convertDoubleString2BigEndian( char * str );

struct I754_Float * IEEE_writeFloatStruct( float * f );
float IEEE_readFloatStruct( struct I754_Float* f );

unsigned short int IEEE_getFloatBit( char * str, unsigned int offset );
unsigned short int IEEE_getDoubleBit( char * str, unsigned int offset );

#endif

