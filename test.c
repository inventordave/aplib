// TEST.C

/** INFORMATIVE SECTION
	This is the test driver for APLib and Dave's IEEE754-Lib. To account for regression issues, all tests run every time "test" is invoked. Thus, if any new features break historical correctness, thus any of the tests, it will become apparent from the test subroutine output.
*/


// STDLIB INC'S
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <error.h>
#include <stdint.h>


// LIB INC'S
#include "Dave_IEEE754.h"
#include "APlib.h"
#include "APlib-output.h"
#include "getOptions.h"


// STATIC DEFS
#define PRINT_LINE printf( "---------------------------\n" );


// BINS
int dummy_int;


// HELPER FNCS DECLS
void parseAP(AP * a, char * str); // checks (char *) decimal string for leading sign, and populates AP object accordingly.
void pause(); // waits for user to press a key before continuing.
void arg_assert( int argc, int min ); // custom ASSERT() for number of args passed on cmd-line.


// TEST FUNCTION DECLS
void dec_2_bin_2_dec(void);
void basicTest(int argc, char **argv); // ADD, SUB, MUL, EXP - requires 2 decimal strings in argv[1]/argv[2].
void fs_test1(int argc, char **argv);
void q_test(float);
void readFloatTest(int argc, char **argv);
void writeFloatTest(int argc, char **argv);
int test2kMax(AP input);


typedef struct TEST_ENTRY {
	
	void (*addr)(int argc, char **argv);
	char * ref;
	uint32_t index;
} TEST_ENTRY;

typedef struct _TESTS	{

	struct TEST_ENTRY entries[256];
	int length;
	
} _TESTS;


void addTest( struct _TESTS * T, char * ref, void * fnc )	{

		struct TEST_ENTRY ENTRY;
		ENTRY.addr = fnc;
		ENTRY.ref = strdup( ref );
		ENTRY.index = T->length;
		T->entries[T->length] = ENTRY;
		
		++T->length;
}


// MAIN() ENTRYPOINT
int main(int argc, char **argv)	{
	
	struct _TESTS TESTS_;
	struct _TESTS * TESTS = &TESTS_;
	TESTS->length = 0;
	
	addTest( TESTS, "test1", fs_test1 );
	addTest( TESTS, "readfloattest", readFloatTest );
	addTest( TESTS, "operators", basicTest );
	addTest( TESTS, "writefloattest", writeFloatTest );
	addTest( TESTS, "decbin", dec_2_bin_2_dec );
	

	
	
	loop:
	
	NL;
	printf( "Please enter the test reference for the test you wish to invoke,\nor type \"list\" to see all,\n\"all\" to invoke all tests,\n\"q\" to quit the test interface,\n\"p\" to print test output to file: "); 
	
	char * buf = (char *)malloc( 1024 );
	dummy_int = scanf( "%s", buf );

	NL;
	printf( "Selection: \"%s\"\n", buf );
	NL;
	
	if( seq( buf, "list" ) )	{
		
		for( int i=0; i<TESTS->length; i++ )
			printf( "[%d] %s\n\n", i+1, TESTS->entries[i].ref );
		
		goto loop;
	}
	if( seq( buf, "q" ) )	{
		
		printf( "Session complete. Exiting." );
		exit(0);
	}
	
	if( seq( buf, "p" ) )	{
		
		printf( "Not Yet Implemented.\n" );
		goto loop2;
	}
	
	char * list = (char *)malloc(4096);
	list[0] = '\0';
	char line[256] = {'\0'};
	int i, j=0;
	for( i=0; i<(TESTS->length); i++ )	{
		
		if( seq(buf, "all") )	{
			
			TESTS->entries[i].addr(argc, argv);
			
			if( i>0 )
				strcpy( line, ",\n");
			
			strcat( line, TESTS->entries[i].ref );
			strcat( list, line );
			
			line[0] = '\0';
			++j;
		}
		else if( seq(TESTS->entries[i].ref, buf) )	{

			TESTS->entries[i].addr(argc, argv);
			strcat( line, TESTS->entries[i].ref );
			strcat( list, line );
			
			line[0] = '\0';
			++j;
			break;
		}
	}
	
	NL;
	PRINT_LINE;
	
	if( j>0 )
		printf( "%d test(s) completed:\n\n%s\n\n", j, list );
	else
		printf( "No matching test found.\n\n" );
	
	PRINT_LINE;
	
	free( list );
	loop2:
	free( buf );
	
	goto loop;
	
	// TEST 1
	basicTest(argc, argv);
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
	dec_2_bin_2_dec();
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 5
	readFloatTest(argc, argv);
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 6
	writeFloatTest(argc, argv);
	NL;
	PRINT_LINE;
	pause();

	// TEST 7
	fs_test1(argc, argv);
	NL;
	PRINT_LINE;
	pause();

	// TESTS COMPLETE.
	printf( "END OF TESTS. EXITING.\n" );
	return 0;
}


// TEST FNCS
int test2kMax(AP input)	{
	
	int temp = DIV_BY_2_PRINT_ROWS;
	DIV_BY_2_PRINT_ROWS = 0;
	int a = _2kMax(input);
	DIV_BY_2_PRINT_ROWS = temp;
	return a;
}

void basicTest(int argc, char **argv)	{ // ADD, SUB, MUL, EXP

	arg_assert( argc, 2 );
	
	
	if( argc < 3 )	{
		
		printf("Please pass 2 (possibly signed) integers on the cmd-line, and invoke the program again. Exiting...\n");
		exit(0);
	}
	
	NL;
	
	AP A, B, C;
	A = new_ap( 10, 0 );
	B = new_ap( 10, 0 );
	
	// Arg A
	parseAP(&A, argv[1]);
	
	// Arg B
	parseAP(&B, argv[2]);
	
	
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
	
	printf( "\nCompleted." );
	
	return;
}

void dec_2_bin_2_dec()	{ // DEC->BIN->DEC	(DEC_2_BIN / BIN_2_DEC)
	
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

void fs_test1(int argc, char **argv)	{
	
	// This test function is to test construction and access to struct "IEEE754_Float"
	struct IEEE754_Float * a;
	
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

void writeFloatTest(int argc, char **argv)	{
	
	struct IEEE754 * lib = initIEEE754();
	
	float a = 1701.79f;

	char * str = malloc(32+1);
	str = strdup( IEEE_readFloat( a ) );

	printf( "Value stored in float = %f\nWriting new value to float.\n", a );
	lib->writeFloat( &a, str );
	
	printf( "Value stored in float = %f\n", a );
	
	return;
}

void readFloatTest(int argc, char **argv)	{

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

	return;
}


// HELPER FNCS
void pause()	{

	getchar();
	return;
}

void arg_assert( int argc, int min )	{
	
	if( (argc-1)<min )	{
		
		printf( "Not enough cmd-line arguments. %d are required, only %d args passed. Exiting.", min, argc-1 );
		exit(1);
	}
	
	return;
}

void parseAP(AP * a, char * str)	{

	// Arg A
	if( str[0] == '-' )	{
		
		a->sign = '-';
		str[0] = '0';
		a->major = strdup(str);
	}
	else if( str[0] == '+' )	{

		a->sign = '-';
		str[0] = '0';
		a->major = strdup(str);
		
	}
	else	{
		
		a->major = strdup(str);
		a->sign = '+';
	}	
}

