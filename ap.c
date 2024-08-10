// TEST.C

// STDLIB INC'S
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <error.h>
#include <stdint.h>
#include <windows.h>

// LIB INC'S
#include "ap.h"
#include "i754.h"
#include "aplib.h"
#include "ap_io.h"
#include "getOptions.h"
#include "colour.h"
#include "tests.h"

// STATIC DEFS
#define PRINT_LINE printf( "---------------------------\n" );

// BINS
int dummy_int;

// MAIN() ENTRYPOINT
int main(int argc, char **argv)	{

	if( argc<3 )
		exit( print( "Not enough command-line args passed. You should pass an Operator, then 2 Integer values, with at least 1 space between each of the 3 args.\n") );

	init_();
	colorMode();
	
	AP (*OP)( AP A, AP B );
	int OPCODE = 0;
	
	printf( "%s", FG_BRIGHT_WHITE );
	
	if( seq(argv[1], "*") || seq(argv[1],"MUL") || seq(argv[1],"MULTIPLY") )
	{OP = MUL;
	OPCODE = 1;}
	else
	if( seq(argv[1], "/") || seq(argv[1], "DIV") || seq(argv[1], "DIVIDE") )
	{OP = DIV;
	OPCODE = 2;}
	else
	if( seq(argv[1], "+") || seq(argv[1], "ADD") )
	{OP = ADD;
	OPCODE = 3;}
	else
	if( seq(argv[1], "-") || seq(argv[1], "SUB") || seq(argv[1], "SUBTRACT") )
	{OP = SUB;
	OPCODE = 4;}
	else
	if( seq(argv[1], "E") || seq(argv[1], "EXP") || seq(argv[1], "EXPONENT") )
	{OP = EXP;
	OPCODE = 5;}
	else
	{OP = NOP;
	OPCODE = 0;}
	
	AP A = NewAP( strlen(argv[2]), 0 );
	setPartW( &A,argv[2] );
	
	AP B;
	
	if( argc < 4 )
	B = CopyAP( &AP1 );
	else{
	B = NewAP( strlen(argv[3]), 0 );
	setPartW( &B,argv[3] );
	}
	
	AP C = OP( A,B );
	
	print( "%sResult:\nA='%s'\nOPCODE(%d)\nB='%s'\n==\nC='%s'\n", A.integer, OPCODE, B.integer, C.integer );
	
	return 0;
	
	
	// div(a,b)
	
	AP _1 = NewAP( 1024, 0 );
	AP _2 = NewAP( 1024, 0 );
	
	strcpy( _1.integer, argv[1] );
	strcpy( _2.integer, argv[2] );
	
	AP _3 = DIV( _1, _2 );
	
	if( argc>3 )
		maxLoopsSet = str2int( argv[2] );
	else
		maxLoopsSet = 100;
	
	printf( "Result of %s / %s = %s\n", _1.integer, _2.integer, _3.integer );
	
	return 0;
	
	struct _TESTS TESTS_;
	struct _TESTS * TESTS = &TESTS_;
	TESTS->length = 0;
	
	addTest( TESTS, "and", andTest );
	addTest( TESTS, "not", notTest );
	addTest( TESTS, "or", orTest );
	addTest( TESTS, "exor", exOrTest );
	
	addTest( TESTS, "test1", fs_test1 );
	addTest( TESTS, "readfloattest", readFloatTest );
	addTest( TESTS, "operators", basicTest );
	addTest( TESTS, "writefloattest", writeFloatTest );
	addTest( TESTS, "decbin", dec_2_bin_2_dec );
	addTest( TESTS, "quicktest", q_test );
	addTest( TESTS, "2kMax", test2kMax );

	AP ca;
	ca.sign = '-';
	ca.integer = strdup( "1701" );
	printf( "Color test: %s\n", formatAP(ca) );
	
	NL;
	char * bin_string = "0011100010101010111101011010101";
	printf( "2nd color test: %s\n", formatBinary(bin_string) );
	
	print( c("lee", FG_BRIGHT_GREEN) );
	printf( " : " );
	print( c("david", FG_MAGENTA) );
	NL;
	
	//printf( "%s : %s\n", c("lee", FG_BRIGHT_GREEN), c("david", FG_MAGENTA) );
	
	normal();
	
	//ap_exit(0);
	//return 0;
	
	loop:
	
	NL;
	printf( "Please enter the test reference for the test you wish to invoke, or \n\"%s\" to see a list of the test functions,\n\"%s\" to invoke all tests,\n\"%s\" to print test output to file,\n\"%s\" to quit the test interface:\t", c("list", FG_BRIGHT_WHITE), c("all", FG_BRIGHT_WHITE), c("p", FG_BRIGHT_WHITE), c("q", FG_BRIGHT_RED) ); 
	
	char * buf = (char *)malloc( 1024 );
	dummy_int = scanf( "%s", buf );

	NL;
	
	char * TEST_OPT_NAME = FG_CYAN;
	printf( "Selection: \"%s\"\n", c(buf, TEST_OPT_NAME) );
	NL;
	
	if( seq( buf, "l" ) )
		strcpy(buf, "list");
	
	if( seq( buf, "list" ) )	{
		
		for( int i=0; i<TESTS->length; i++ )
			printf( "[%d] %s\n\n", i+1, TESTS->entries[i].ref );
		
		goto loop;
	}
	if( seq( buf, "q" ) )	{
		
		printf( "%sSession complete. Exiting.%s", FG_BRIGHT_WHITE, NORMAL );
		exit(0);
	}
	
	if( seq( buf, "p" ) )	{
		
		printf( "%sNot Yet Implemented.%s\n", FG_BRIGHT_WHITE, NORMAL );
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
	AP input = NewAP( 256, 0 );
	
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
	
	input.integer = strdup( test_num );
	
	int packed = 1;
	char * str = DEC_2_BIN(input, packed);
	printf( "DEC_2_BIN(\"%c%s\") = %s\n", input.sign, input.integer, str );
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 3
	test2kMax(argc, argv);
	printf( "The minimum higher 2k exponent for %c%s is %d.\n", input.sign, input.integer, dummy_int );
	NL;
	PRINT_LINE;
	pause();
	
	// TEST 4
	dec_2_bin_2_dec(argc, argv);
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
	ap_exit(0);
	
	// For the compiler.
	return 0;
	
}

void addTest( struct _TESTS * T, char * ref, void * fnc )	{

		struct TEST_ENTRY ENTRY;
		ENTRY.addr = fnc;
		ENTRY.ref = strdup( ref );
		ENTRY.index = T->length;
		T->entries[T->length] = ENTRY;
		
		++T->length;
}


void ap_exit(int status)	{

	printf( "\n%sAPSuite is exiting.%s\n", FG_RED, NORMAL );
	printf( "%s", NORMAL );
	exit(status);
}



// HELPER FNCS



void parseAP(AP * A, char * str)	{

	// Arg A
	if( str[0] == '-' )	{

		A->sign = '-';
		//str[0] = '0';
		++str;
		A->integer = strdup(str);
	}
	else if( str[0] == '+' )	{

		A->sign = '+';
		//str[0] = '0';
		++str;
		A->integer = strdup(str);
	}
	else	{

		A->integer = strdup(str);
		A->sign = '+';
	}

	return;
}

