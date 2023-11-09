#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Dave_IEEE754.h"


/**

	Here is a simple solution I cooked up for accessing the internal bit-representation of floats. It's trivially extendable to doubles, you simply need to allocate sufficient memory for the "struct container" that wraps the target float storage. The (very simple) method uses a char * pointer called "offset" in my code, which acts as an l-value for a (char *) cast of the containing struct as r-value. This trivially internally-flattens the struct as an array of char's (bytes - sizeof(1) ). Then the inner-most loop scans, from MSB to LSB of each individual byte in the struct internal array, and does an AND mask against the bit (from bit 7 to bit 0), and if it's a 1, prints 1, or if a 0 ,prints 0.
	As my system is little-endian, the LSByte is printed as the first row, and the MSByte printed as the 4th row, but each row, each byte, is printed with the MSB printed left-most. This obviously means that the left-most bit of the 4th row is the sign bit, for signed r-values.
	
*/


int main2(int argc, char **argv)	{
	
	struct IEEE754 * lib = initIEEE754();
	
	char * str = malloc(32+1);
	str = strdup( "10000101011010111111011001000010" );
	
	float a = 17.1f;
	
	lib->writeFloat( &a, str );
	
	printf( "Value stored in float = %f\n", a );
	
	return 0;
}

int main(int argc, char **argv)	{

	struct IEEE754 * lib = initIEEE754();

	float f;
	
	if( argc<2 )
		f = 17.1f;
	else
		f = atof(argv[1]);
	
	printf( "Float value received: %f\n", f );
	
	char * result = lib->readFloat( f );
	
	printf( "Result (l-endian): %s\n", result );
	
	char * be_result = lib->convertFloatString2BigEndian( result );
	printf( "Result (b-endian): %s\n", be_result );

	return 0;
}

