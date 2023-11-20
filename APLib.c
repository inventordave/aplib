// APlib.c

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "APLib.h"
#include "Dave_IEEE754.h"


int main(int argc, char **argv)	{

	float f = -6543.21;
	q_test( f );
	
	return 0;
/**
	char * wecheckin = "1101110100010101111111101000011010101111111110101101100100010010010010011110111100001110101101110001001111110011100111101011111010101010100110000111101101101110011011111100101101000101101101000101111000100111000110110101100001010010110110110000001111111111";
	
	printf(" strlen = %d\n", strlen(wecheckin) );
	
	return 0;
*/

	/**
	AP l = new_ap(10,0);
	l.major = strdup( argv[1] );

	AP t = new_ap( 1, 0 );
	t.major = strdup( "0" );
	
	printf( "AP l = %s\n", l.major );
	int flag = 1;
	while( flag )	{
		
		l=DIV_BY_2(l);
		
		printf( "AP l = %s\n", l.major );
		
		//getc();
		
		if( cmp(&l,&t)!=+1 )
			flag=0;
	}

	return 0;
	*/
	
	/**
	AP _a = new_ap( strlen(argv[1]), 0 );
	_a.major = strdup( argv[1] );
	int result1 = _2kMax(_a);
	int result2 = _2kMin(_a);
	
	printf( "For value '%s', the nearest Max 2k-form is 2 ^ %d, nearest Min 2k-form is 2 ^ %d\n", _a.major, result1, result2 );
	
	return 0;
	*/
	
	if(argc<3)	{
		
		printf( "Please pass 2 args to the comnand line: a decimal string to convert, and a 0 or 1 to indicate byte-width-padding.\n" );
		exit(1);
	}
	
	AP a = new_ap( strlen(argv[1]), 0 );
	a.major = strdup( argv[1] );
	
	char * result = DEC_2_BIN(a, str2int(argv[2]));
	printf( "String = %s\n", result );
	
	return 0;
	
	
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
	C = EXP(A, B);
	if( C.sign=='-' )
		B.sign='+';
	
	printf( "%c%s EXP %c%s = %c%s\n", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	printf( "\nCompleted.\n" );
	
	return 0;
}

