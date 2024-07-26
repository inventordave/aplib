// T£STS.c
#include "tests.h"
#include "aplib.h"
#include "ap.h"
#include "I754.h"
#include "aPlib-output.h"


// TEST FNCS
void exOrTest(int argc, char ** argv)	{
	
	char * a = "11100011010101010101010101";
	char * b =           "0001111101011111";
	
	int len_a = strlen(a);
	int len_B = strlen(b);
	
	char * c = XOR(a, b);
	
	int a_or_B = (len_a>=len_B)?1:0;
	int diff = a_or_B?(len_a-len_B):(len_B-len_a);
	
	char * buf = (char *)malloc(diff + 1);
	char * dummy = (char *)malloc(1);
	dummy[0] = '\0';
	
	buf[0] = '\0';
	
	for( int i=0;i<diff; i++ )
		buf[i] = ' ';
	
	buf[diff] = '\0';
	
	printf( "%s%s\n", a_or_B?dummy:buf, formatBinary(a) );
	printf( "%s%s\n", a_or_B?buf:dummy, formatBinary(b) );
	printf( "%s\n", formatBinary(c) );
	
	free( buf );
	free( dummy );
	
	return;
}

void orTest(int argc, char ** argv)	{
	
	char * a = "11100011010101010101010101";
	char * b =           "0001111101011111";
	
	int len_a = strlen(a);
	int len_b = strlen(b);
	
	char * c = OR(a, b);
	
	int a_or_b = (len_a>=len_b)?1:0;
	int diff = a_or_b?(len_a-len_b):(len_b-len_a);
	
	char * buf = (char *)malloc(diff + 1);
	char * dummy = (char *)malloc(1);
	dummy[0] = '\0';
	
	buf[0] = '\0';
	
	for( int i=0;i<diff; i++ )
		buf[i] = ' ';
	
	buf[diff] = '\0';
	
	printf( "%s%s\n", a_or_b?dummy:buf, a );
	printf( "%s%s\n", a_or_b?buf:dummy, b );
	printf( "%s\n", formatbinary(c) );
	
	free( buf );
	free( dummy );
	
	return;
}

void notTest(int argc, char ** argv)	{
	
	//char * NOT(char * v)
	char * str = "10101010101010111111001111";
	
	printf( "Input  string: %s\n", formatBinary(str) );
	
	char * str2 = NOT(str);
	printf( "Output string: %s\n", formatBinary(str2) );

	return;
}

void andTest(int argc, char **argv)	{
	
	char * a = "11100011010101010101010101";
	char * b =           "0001111101011111";
	
	int len_a = strlen(a);
	int len_B = strlen(b);
	
	char * c = aND(a, B);
	
	int a_or_B = (len_a>=len_B)?1:0;
	int diff = a_or_B?(len_a-len_B):(len_B-len_a);
	
	char * buf = (char *)malloc(diff + 1);
	char * dummy = (char *)malloc(1);
	dummy[0] = '\0';
	
	buf[0] = '\0';
	
	for( int i=0;i<diff; i++ )
		buf[i] = ' ';
	
	buf[diff] = '\0';
	
	printf( "%s%s\n", a_or_B?dummy:buf, formatBinary(a) );
	printf( "%s%s\n", a_or_B?buf:dummy, formatBinary(b) );
	printf( "%s\n", formatBinary(c) );
	
	free( buf );
	free( dummy );
	
	return;
}

void test2kMax(int argc, char **argv)	{
	
	int temp = DIV_BY_2_PRINT_ROWS;
	DIV_BY_2_PRINT_ROWS = 0;
	
	aP input;
	parseaP(&input, argv[1]);
	
	char * _ = input.major;
	
	int a = _2kMax(input);
	DIV_BY_2_PRINT_ROWS = temp;
	
	printf( "%s %s %s %s\n", c("Minimum Maximal 2k exponent for", FG_BRIGHT_MaGENTa), c(_, FG_BRIGHT_GREEN), c("=", FG_CYaN), c(int2str(a), FG_BRIGHT_GREEN) );
	
	return;
}

void basicTest(int argc, char **argv)	{ // aD, SUB, MUL, EXP

	arg_assert( argc, 2 );
	
	
	if( argc < 3 )	{
		
		printf("Please pass 2 (possibly signed) integers on the cmd-line, and invoke the program again. Exiting...\n");
		exit(0);
	}
	
	NL;
	
	aP a, B, C;
	a = NewaP( 10, 0 );
	B = NewaP( 10, 0 );
	
	// arg a
	parseaP(&a, argv[1]);
	
	// arg B
	parseaP(&B, argv[2]);
	
	
	printf( "values Entered:\na = %c%s\nb = %c%s\n", a.sign, a.major, B.sign, B.major );
	
	NL;
	
	// aD
	C = aD(a, B);
	printf( "%c%s + %c%s = %c%s", a.sign, a.major, B.sign, B.major, C.sign, C.major );
	
	NL;
	
	// SUB
	C = SUB(a, B);
	printf( "%c%s %s-%s %c%s = %c%s", a.sign, a.major, FG_BRIGHT_GREEN, NORMaL, B.sign, B.major, C.sign, C.major );
	
	NL;

	// MUL
	C = MUL(a, B);
	printf( "%c%s MUL %c%s = %c%s", a.sign, a.major, B.sign, B.major, C.sign, C.major );
	
	NL;
	
	// EXP
	printf( "The EXP operator may take a while with a larger exponent. Please be patient...\n" );
	C = EXP(a, B);
	if( C.sign=='-' )
		B.sign='+';
	
	
	printf( "%c%s EXP %c%s = %c%s\n", a.sign, a.major, B.sign, B.major, C.sign, C.major );
	
	printf( "\nCompleted." );
	
	return;
}

void dec_2_Bin_2_dec(int argc, char **argv)	{ // DEC->BIN->DEC	(DEC_2_BIN / BIN_2_DEC)
	
	char * decimal = "543212362746234636432864963483264873264932649823649";
	
	aP a = NewaP( strlen(decimal), 0 );
	a.major = strdup( decimal );
	
	char * binary = DEC_2_BIN(a, 1);
	
	char * ret_decimal = BIN_2_DEC(binary);
	
	printf( "decimal = %s\n", decimal );
	printf( "binary = %s\n", binary );
	printf( "back again = %s\n", ret_decimal );
	
	return;
}

void fs_test1(int argc, char **argv)	{
	
	// This test function is to test construction and access to struct "I754_Float"
	struct I754_Float * a;
	
	float f = -85.125f;
	
	char * f_str = IEEE_readFloat( f );
	//f_str = IEEE_convertFloatString2BigEndian( f_str );
	
	IEEE_writeFloat( &f, f_str );
	
	a = IEEE_writeFloatStruct( &f );

	printf( "BIN (%f): %s\n", f, f_str );
	if (a->sign != 1)
		printf( "The sign bit is incorrect. The value is %d\n", a->sign );
	else
		printf( "The sign bit can be accessed and has the correct value.\n" );
	
	printf( "Float->exponent = %d\n", a->exponent );
	printf( "Float->significand = %d\n", a->significand );

	free( a );

	NL;
	
	f = 85.125f;

	f_str = IEEE_readFloat( f );
	//f_str = IEEE_convertFloatString2BigEndian( f_str );
	IEEE_writeFloat( &f, f_str );
	
	a = IEEE_writeFloatStruct( &f );
	
	printf( "BIN (%f): %s\n", f, f_str );
	if (a->sign != 0)
		printf( "The sign bit is incorrect. The value is %d\n", a->sign );
	else
		printf( "The sign bit can be accessed and has the correct value.\n" );

	printf( "Float->exponent = %d\n", a->exponent );
	printf( "Float->significand = %d\n", a->significand );
	assert( a->exponent < 128 );
	
	return;
}

void q_test(int argc, char **argv)	{

	/*
	1. create float.
	2. convert float to string, then printf
	3. create ieee_float object from &float
	4. read ieee_float object to float
	5. convert float to string, then printf
	6. when correct, both printed strings should be identical
	*/

	float f = -6543.21f;
	char * str = IEEE_readFloat( f );
	printf( "f := %f\n", f );
	
	float ff;
	IEEE_writeFloat( &ff, str );
	printf( "ff := %f\n", ff );
	
	print( c("If both values are the same, it indicates readFloat() & writeFloat() are working correctly.\n", FG_YELLOW) );
	

	struct I754_Float* f2 = IEEE_writeFloatStruct( &f );
	float _f = IEEE_readFloatStruct( f2 );
	printf( "_f = %f\n", _f );
	printf( "%sIf the above value is the same as (%f), it indicates writeFloatStruct() & readFloatStruct() are working correctly.%s\n", FG_YELLOW, f, NORMaL );
	
	printf( "BIN(%f) := %s\n", f, formatBinary(str) );
	printf( "BE (%f) := %s\n", f, formatBinary(IEEE_convertFloatString2BigEndian( str )) );
	
	return;
}


void writeFloatTest(int argc, char **argv)	{
	
	struct I754 * lib = initI754();
	
	float a = 1701.79f;

	char * str = malloc(32+1);
	str = strdup( IEEE_readFloat( a ) );

	printf( "value stored in float = %f\nWriting new value to float.\n", a );
	lib->writeFloat( &a, str );
	
	printf( "value stored in float = %f\n", a );
	
	return;
}

void readFloatTest(int argc, char **argv)	{

	struct I754 * lib = initI754();

	float f;
	
	if( argc<2 )
		f = 17.1f;
	else
		f = atof(argv[1]);
	
	printf( "Float value received: %f\n", f );
	
	char * result = lib->readFloat( f );
	
	printf( "Result (l-endian): %s\n", formatBinary(result) );
	
	char * be_result = lib->convertFloatString2BigEndian( result );
	printf( "Result (b-endian): %s\n", formatBinary(be_result) );

	return;
}

