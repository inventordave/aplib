// T£STS.c
#include <stdlib.h>
#include "../gcollect/gc.h"
#include "tests.h"
#include "APLIB.h"
#include "ap.h"
#include "ap_io.h"


char* genRndDStr( int len )	{

	char* _ = g( malloc( len+1 ) );

	int i;
	for( i=0; i<len; i++ )
		_[i] ='0' + (rand()%10);

	_[i] = '\0';

	return _;
}

int unitTests_MUL( void )	{

	int count = 0;
	
	AP A = NewAP(0,0);
	AP B = NewAP(0,0);
	AP C;

	

	char* _A;
	char* _B;

	// Tests 1-12, MUL( A,B )

	// A_abs == B_abs

	_A = genRndDStr( 5 );
	setPartW( A, _A );
	setPartW( B, _A );

	// A_sign = +, B_sign = +
	setSign( A, '+' );
	setSign( B, '+' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = -
	setSign( B, '-' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = +
	setSign( A, '-' );
	setSign( B, '+' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = -
	setSign( A, '-' );
	setSign( B, '-' );

	C = MUL( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_abs > B_abs

	_A = genRndDStr( 8 );
	setPartW( A, _A );
	
	_B = genRndDStr( 5 );
	setPartW( B, _B );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	
	// A_sign = +, B_sign = +
	setSign( A, '+' );
	setSign( B, '+' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	
	// A_sign = +, B_sign = -
	setSign( B, '-' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = +
	setSign( A, '-' );
	setSign( B, '+' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = -
	setSign( A, '-' );
	setSign( B, '-' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_abs < B_abs

	_A = genRndDStr( 5 );
	setPartW( A, _A );

	_B = genRndDStr( 8 );
	setPartW( B, _B );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = +
	setSign( A, '+' );
	setSign( B, '+' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = -
	setSign( B, '-' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = +
	setSign( A, '-' );
	setSign( B, '+' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = -
	setSign( A, '-' );
	setSign( B, '-' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_abs > B_abs

	_A = genRndDStr( 8 );
	setPartW( A, _A );

	_B = genRndDStr( 5 );
	setPartW( B, _B );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = +
	setSign( A, '+' );
	setSign( B, '+' );
	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = -
	setSign( B, '-' );

	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = +
	setSign( A, '-' );
	setSign( B, '+' );
	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = -
	setSign( A, '-' );
	setSign( B, '-' );
	C = MUL( A, B );
	printf( "(%c)%s * (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;

	return count;

}


int unitTests_ADD( void )	{

	int count = 0;
	
	AP A = NewAP(0,0);
	AP B = NewAP(0,0);
	AP C;

	#define OPERAND_ARGS A->sign, A->integer, B->sign, B->integer, C->sign, C->integer

	char* _A;
	char* _B;

	// Tests 1-12, ADD( A,B )

	// A_abs == B_abs

	_A = genRndDStr( 5 );
	setPartW( A, _A );
	setPartW( B, _A );

	// A_sign = +, B_sign = +
	setSign( A, '+' );
	setSign( B, '+' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = -
	setSign( B, '-' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = +
	setSign( A, '-' );
	setSign( B, '+' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = -
	setSign( A, '-' );
	setSign( B, '-' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_abs > B_abs

	_A = genRndDStr( 8 );
	setPartW( A, _A );
	
	_B = genRndDStr( 5 );
	setPartW( B, _B );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	
	// A_sign = +, B_sign = +
	setSign( A, '+' );
	setSign( B, '+' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	
	// A_sign = +, B_sign = -
	setSign( B, '-' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = +
	setSign( A, '-' );
	setSign( B, '+' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = -
	setSign( A, '-' );
	setSign( B, '-' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_abs < B_abs

	_A = genRndDStr( 5 );
	setPartW( A, _A );

	_B = genRndDStr( 8 );
	setPartW( B, _B );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = +
	setSign( A, '+' );
	setSign( B, '+' );

		C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = -
	setSign( B, '-' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = +
	setSign( A, '-' );
	setSign( B, '+' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = -
	setSign( A, '-' );
	setSign( B, '-' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_abs > B_abs

	_A = genRndDStr( 8 );
	setPartW( A, _A );

	_B = genRndDStr( 5 );
	setPartW( B, _B );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = +
	setSign( A, '+' );
	setSign( B, '+' );
	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = +, B_sign = -
	setSign( B, '-' );

	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = +
	setSign( A, '-' );
	setSign( B, '+' );
	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;
	// A_sign = -, B_sign = -
	setSign( A, '-' );
	setSign( B, '-' );
	C = ADD( A, B );
	printf( "(%c)%s + (%c)%s = (%c)%s\n", OPERAND_ARGS );
	count++;

	return count;

}

/**


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
	
	char * buf = (char*) g( malloc(diff + 1) );
	char * dummy = (char*) g( malloc(1) );
	dummy[0] = '\0';
	
	buf[0] = '\0';
	
	for( int i=0;i<diff; i++ )
		buf[i] = ' ';
	
	buf[diff] = '\0';
	
	printf( "%s%s\n", a_or_b?dummy:buf, a );
	printf( "%s%s\n", a_or_b?buf:dummy, b );
	printf( "%s\n", formatBinary(c) );
	
	freeRef( buf );
	freeRef( dummy );
	
	return;
}

void notTest(int argc, char ** argv)	{
	
	//char * NOT(char * v)
	char * str = "10101010101010111111001111";
	
	printf( "Input  string: %s\n", formatBinary(str) );
	
	char * str2 = NOT(str)->integer;
	printf( "Output string: %s\n", formatBinary(str2) );

	return;
}

void andTest(int argc, char **argv)	{
	
	char * a = "11100011010101010101010101";
	char * b =           "0001111101011111";
	
	int len_a = strlen(a);
	int len_B = strlen(b);
	
	char * c = AND(a, B);
	
	int a_or_B = (len_a>=len_B)?1:0;
	int diff = a_or_B?(len_a-len_B):(len_B-len_a);
	
	char * buf = (char *) g( malloc(diff + 1) );
	char * dummy = (char*) g( malloc(1) );
	dummy[0] = '\0';
	
	buf[0] = '\0';
	
	for( int i=0;i<diff; i++ )
		buf[i] = ' ';
	
	buf[diff] = '\0';
	
	printf( "%s%s\n", a_or_B?dummy:buf, formatBinary(a) );
	printf( "%s%s\n", a_or_B?buf:dummy, formatBinary(b) );
	printf( "%s\n", formatBinary(c) );
	
	freeRef( buf );
	freeRef( dummy );
	
	return;
}

void test2kMax(int argc, char **argv)	{
	
	int temp = DIVBY2_PRINT_ROWS;
	DIVBY2_PRINT_ROWS = 0;
	
	AP input;
	ParseAP(input, argv[1]);
	
	char * _ = input->integer;
	
	int a = Max2K(input);
	DIVBY2_PRINT_ROWS = temp;
	
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
	
	AP A, B, C;
	A = NewAP( 10, 0 );
	B = NewAP( 10, 0 );
	
	// arg A
	ParseAP(A, argv[1]);
	
	// arg B
	ParseAP(B, argv[2]);
	
	
	printf( "Values Entered:\nA = %c%s\nB = %c%s\n", A->sign, A->integer, B->sign, B->integer );
	
	NL;
	
	// ADD
	C = ADD(A, B);
	printf( "%c%s + %c%s = %c%s", A->sign, A->integer, B->sign, B->integer, C->sign, C->integer );
	
	NL;
	
	// SUB
	C = SUB(A, B);
	printf( "%c%s %s-%s %c%s = %c%s", A->sign, A->integer, FG_BRIGHT_GREEN, NORMAL, B->sign, B->integer, C->sign, C->integer );
	
	NL;

	// MUL
	C = MUL(A, B);
	printf( "%c%s MUL %c%s = %c%s", A->sign, A->integer, B->sign, B->integer, C->sign, C->integer );
	
	NL;
	
	// EXP
	printf( "The EXP operator may take a while with a larger exponent. Please be patient...\n" );
	C = EXP(A, B);
	if( C->sign=='-' )
		B->sign='+';
	
	
	printf( "%c%s EXP %c%s = %c%s\n", A->sign, A->integer, B->sign, B->integer, C->sign, C->integer );
	
	printf( "\nCompleted." );
	
	return;
}

void dec_2_Bin_2_dec(int argc, char **argv)	{ // DEC->BIN->DEC	(DEC_2_BIN / BIN_2_DEC)
	
	char * decimal = "543212362746234636432864963483264873264932649823649";
	
	AP A = NewAP( strlen(decimal), 0 );
	A->integer = strdup( decimal );
	
	char * binary = DEC_2_BIN(A, 1);
	
	char * ret_decimal = BIN_2_DEC(binary);
	
	printf( "decimal = %s\n", decimal );
	printf( "binary = %s\n", binary );
	printf( "back again = %s\n", ret_decimal );

	freeRef( ret_decimal );
	freeRef( binary );

	FreeAP( A );
	return;
}

void fs_test1(int argc, char **argv)	{
	
	// This test function is to test construction and access to struct "i754_Float"
	struct i754_Float * a;
	
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

	freeRef( a );

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

	
	//1. create float.
	//2. convert float to string, then printf
	//3. create ieee_float object from &float
	//4. read ieee_float object to float
	//5. convert float to string, then printf
	//6. when correct, both printed strings should be identical
	


	float f = -6543.21f;
	char * str = IEEE_readFloat( f );
	printf( "f := %f\n", f );
	
	float ff;
	IEEE_writeFloat( &ff, str );
	printf( "ff := %f\n", ff );
	
	print( c("If both values are the same, it indicates readFloat() & writeFloat() are working correctly.\n", FG_YELLOW) );
	

	struct i754_Float* f2 = IEEE_writeFloatStruct( &f );
	float _f = IEEE_readFloatStruct( f2 );
	printf( "_f = %f\n", _f );
	printf( "%sIf the above value is the same as (%f), it indicates writeFloatStruct() & readFloatStruct() are working correctly.%s\n", FG_YELLOW, f, NORMaL );
	
	printf( "BIN(%f) := %s\n", f, formatBinary(str) );
	printf( "BE (%f) := %s\n", f, formatBinary(IEEE_convertFloatString2BigEndian( str )) );
	
	return;
}


void writeFloatTest(int argc, char **argv)	{
	
	struct i754 * lib = initi754();
	
	float a = 1701.79f;

	char * str = malloc(32+1);
	str = strdup( IEEE_readFloat( a ) );

	printf( "value stored in float = %f\nWriting new value to float.\n", a );
	lib->writeFloat( &a, str );
	
	printf( "value stored in float = %f\n", a );
	
	return;
}

void readFloatTest(int argc, char **argv)	{

	struct i754 * lib = initi754();

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

*/

