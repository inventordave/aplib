// DAVE'S i754 dev-silo
// 
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
	
	char * (*readFloat)( float f );
	char * (*reaDouble)( double f );
	
	char * (*convertFloatString2BigEndian)( char * str );
	char * (*convertDoubleString2BigEndian)( char * str );
	
	unsigned short int (*getFloatBit)( char * str, unsigned int offset );
	unsigned short int (*getDoubleBit)( char * str, unsigned int offset );
	
	void (*writeFloat)(float * dest, char * str);
	void (*writeDouble)(double * dest, char * str);

} i754;

typedef struct i754_Float	{

	int sign;
	
	int exponent;

	// NOT COMPLETE!
	int significand;

} i754_Float;


// FNC PROTOTYPES
struct i754 * initi754();

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

#endif

