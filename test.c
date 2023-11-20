#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <error.h>

#include "Dave_IEEE754.h"

#define PRINT_LINE printf( "---------------------------\n" );

// FUNCTION DECLS
void test(void);
void fs_test1(void);
void q_test(float);
int main2(int argc, char **argv);
int main3(int argc, char **argv);

int main(int argc, char **argv)	{
	
	test();
	NL;
	PRINT_LINE;
	
	int a = main2(argc, argv);
	NL;
	PRINT_LINE
	fs_test1();
	
	return 0;
}

void test()	{
	
	char * decimal = "543212362746234636432864963483264873264932649823649";
	
	AP a = new_ap( strlen(decimal), 0 );
	a.major = strdup( decimal );
	
	char * binary = DEC_2_BIN(a, 1);
	
	char * ret_decimal = BIN_2_DEC(binary);
	
	printf( "decimal = %s\n", decimal );
	printf( "binary = %s\n", binary );
	printf( "back again = %s\n", ret_decimal );
	
	return;
}

void fs_test1()	{
	
	// This test function is to test construction and access to struct "IEEE654_Float"
	struct IEEE654_Float * a;
	
	float f = -12.12;
	
	char * f_str = IEEE_readFloat( f );
	f_str = IEEE_convertFloatString2BigEndian( f_str );
	
	IEEE_writeFloat( &f, f_str );
	
	a = IEEE_writeFloatStruct( &f );

	if (a->sign != 1)
		printf( "The sign bit is incorrect. The value is %d\n", a->sign );
	else
		printf( "The sign bit can be accessed and has the correct value.\n" );
	
	printf( "struct IEEE654_Float.exponent = %d\n", a->exponent );
	
	
	free( a );
	
	f = +12.12;
	
	f_str = IEEE_readFloat( f );
	f_str = IEEE_convertFloatString2BigEndian( f_str );
	IEEE_writeFloat( &f, f_str );
	
	a = IEEE_writeFloatStruct( &f );
	if (a->sign != 0)
		printf( "The sign bit is incorrect. The value is %d\n", a->sign );
	else
		printf( "The sign bit can be accessed and has the correct value.\n" );

	printf( "struct IEEE654_Float.exponent = %d\n", a->exponent );
	
	assert( a->exponent < 128 );
	
	return;
}

void q_test( float f )	{
	
	/*
	1. create float.
	2. convert float to string, then printf
	3. create ieee_float object from &float
	4. read ieee_float object to float
	5. convert float to string, then printf
	6. when correct, both printed strings should be identical
	*/
	
	char * str = IEEE_readFloat( f );
	//str = IEEE_convertFloatString2BigEndian( str );
	printf( "f := %f\n", f );
	
	float ff;
	IEEE_writeFloat( &ff, str );
	printf( "ff := %f\n", ff );
	

	struct IEEE654_Float* f2 = IEEE_writeFloatStruct( &f );
	float _f = IEEE_readFloatStruct( f2 );
	printf( "_f = %f\n", _f );
	
	printf( "f := %s\n", str );
	
	return;
}


int main3(int argc, char **argv)	{
	
	struct IEEE754 * lib = initIEEE754();
	
	char * str = malloc(32+1);
	str = strdup( "10000101011010111111011011000010" );
	
	float a = 17.1f;
	
	printf( "Value stored in float = %f\nWriting new value to float.\n", a );
	lib->writeFloat( &a, str );
	
	printf( "Value stored in float = %f\n", a );
	
	return 0;
}

int main2(int argc, char **argv)	{

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

