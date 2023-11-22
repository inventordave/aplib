// TEST.C

/** INFORMATIVE SECTION
	This is the test driver for APLib and Dave's IEEE754-Lib. To account for regression issues, all tests run every time "test" is invoked. Thus, if any new features break historical correctness, thus any of the tests, it will become apparent from the test subroutine output.
*/


// STDLIB INC'S
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <error.h>

// LIB INC'S
#include "Dave_IEEE754.h"
#include "APlib.h"


// STATIC DEFS
#define PRINT_LINE printf( "---------------------------\n" );


// BINS
int dummy_int;


// HELPER FNCS
void pause()	{

	getchar();
	return;
}


// TEST FUNCTION DECLS
void test(void);
int basicTest(int argc, char **argv);
void fs_test1(void);
void q_test(float);
void testADD(void);
int readFloatTest(int argc, char **argv);
int writeFloatTest(int argc, char **argv);
int test2kMax(AP input);


// MAIN() ENTRYPOINT
int main(int argc, char **argv)	{
	
	// TEST 1
	dummy_int = basicTest(argc, argv);
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 2
	char * test_num;
	AP input = new_ap( 256, 0 );
	
	if( argc > 3 )
		test_num = strdup( argv[3] );
	else
		test_num = strdup( "17011979" );
	
	if( test_num[0]=='+' )	{
	
		input.sign = '+';
		++test_num;
	}
	else if( test_num[0]=='-' )	{
		
		input.sign = '-';
		++test_num;
	}
	
	input.major = strdup( test_num );
	
	int packed = 1;
	char * str = DEC_2_BIN(input, packed);
	printf( "DEC_2_BIN(\"%c%s\") = %s\n", input.sign, input.major, str );
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 3
	dummy_int = test2kMax(input);
	printf( "The minimum higher 2k exponent for %c%s is %d.\n", input.sign, input.major, dummy_int );
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 4
	test();
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 5
	dummy_int = readFloatTest(argc, argv);
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 6
	fs_test1();
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 7
	testADD();
	NL;
	PRINT_LINE;
	pause();
	
	
	// TESTS COMPLETE.
	printf( "End of Tests. Exiting.\n" );
	return 0;
}


// TEST FNCS
int test2kMax(AP input)	{
	
	DIV_BY_2_PRINT_ROWS = 0;
	int a = _2kMax(input);
	DIV_BY_2_PRINT_ROWS = 1;
	return a;
}

int basicTest(int argc, char **argv)	{

	if( argc < 3 )	{
		
		printf("Please pass 2 (possibly signed) integers on the cmd-line, and invoke the program again. Exiting...\n");
		exit(0);
	}
	
	NL;
	
	AP A, B, C;
	A = new_ap( 10, 0 );
	B = new_ap( 10, 0 );
	
	// Arg A
	if( argv[1][0] == '-' )	{
		
		A.sign = '-';
		++argv[1];
		A.major = strdup(argv[1]);
	}
	else if( argv[1][0] == '+' )	{

		A.sign = '+';
		++argv[1];
		A.major = strdup(argv[1]);
		
	}
	else	{
		
		A.major = strdup(argv[1]);
		A.sign = '+';
	}
	
	// Arg B
	if( argv[2][0] == '-' )	{
		
		B.sign = '-';
		++argv[2];
		B.major = strdup(argv[2]);
	}
	else if( argv[2][0] == '+' )	{

		B.sign = '+';
		++argv[2];
		B.major = strdup(argv[2]);
		
	}
	else	{
			
		B.sign = '+';
		B.major = strdup(argv[2]);
	}
	
	printf( "Values Entered:\na = %c%s\nb = %c%s\n", A.sign, A.major, B.sign, B.major );
	
	NL;
	
	// ADD
	C = ADD(A, B);
	printf( "%c%s ADD %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	NL;
	
	// SUB
	C = SUB(A, B);
	printf( "%c%s SUB %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	NL;

	// MUL
	C = MUL(A, B);
	printf( "%c%s MUL %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	NL;
	
	// EXP
	printf( "The EXP operator may take a while with a larger exponent. Please be patient...\n" );
	C = EXP(A, B);
	if( C.sign=='-' )
		B.sign='+';
	
	
	printf( "%c%s EXP %c%s = %c%s\n", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	printf( "\nCompleted.\n" );
	
	return 0;
}

void testADD()	{
	
	AP a = new_ap( 10, 0 );
	AP b = new_ap( 10, 0 );
	
	a.major = strdup( "222222" );
	b.major = strdup( "1024" );
	
	AP c = ADD(a, b);
	
	printf( "%s ADD %s = %s\n", a.major, b.major, c.major );
	
	return;
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
	
	// This test function is to test construction and access to struct "IEEE754_Float"
	struct IEEE754_Float * a;
	
	float f = -12.12;
	
	char * f_str = IEEE_readFloat( f );
	f_str = IEEE_convertFloatString2BigEndian( f_str );
	
	IEEE_writeFloat( &f, f_str );
	
	a = IEEE_writeFloatStruct( &f );

	if (a->sign != 1)
		printf( "The sign bit is incorrect. The value is %d\n", a->sign );
	else
		printf( "The sign bit can be accessed and has the correct value.\n" );
	
	printf( "struct IEEE754_Float.exponent = %d\n", a->exponent );
	
	
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

	printf( "struct IEEE754_Float.exponent = %d\n", a->exponent );
	
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
	

	struct IEEE754_Float* f2 = IEEE_writeFloatStruct( &f );
	float _f = IEEE_readFloatStruct( f2 );
	printf( "_f = %f\n", _f );
	
	printf( "f := %s\n", str );
	
	return;
}

int writeFloatTest(int argc, char **argv)	{
	
	struct IEEE754 * lib = initIEEE754();
	
	char * str = malloc(32+1);
	str = strdup( "10000101011010111111011011000010" );
	
	float a = 17.1f;
	
	printf( "Value stored in float = %f\nWriting new value to float.\n", a );
	lib->writeFloat( &a, str );
	
	printf( "Value stored in float = %f\n", a );
	
	return 0;
}

int readFloatTest(int argc, char **argv)	{

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

