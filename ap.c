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
#include <windows.h>


// LIB INC'S
#include "ap.h"
#include "Dave_IEEE754.h"
#include "APlib.h"
#include "APlib-output.h"
#include "getOptions.h"
#include "ansivt2.h"
#include "tests.h"

#include "wregex.h"

// STATIC DEFS
#define PRINT_LINE printf( "---------------------------\n" );


// BINS
int dummy_int;
extern int maxLoopsSet;

typedef struct TEST_ENTRY {
	
	void (*addr)(int argc, char **argv);
	char * ref;
	uint32_t index;
} TEST_ENTRY;

typedef struct _TESTS	{

	struct TEST_ENTRY entries[256];
	int length;
	
} _TESTS;


char * formatString( char * fmt, ... )	{

	char * str = (char *)malloc(1024);
	str[0] = '\0';

	//sprintf( str, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );

	return str;
}

void addTest( struct _TESTS * T, char * ref, void * fnc )	{

		struct TEST_ENTRY ENTRY;
		ENTRY.addr = fnc;
		ENTRY.ref = strdup( ref );
		ENTRY.index = T->length;
		T->entries[T->length] = ENTRY;
		
		++T->length;
}

void colorMode()	{

	#define STD_OUTPUT_HANDLE ((DWORD)-11)
	//#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	BOOL color = SetConsoleMode(
		StdHandle,
		0x0001 | 0x0002 | ENABLE_VIRTUAL_TERMINAL_PROCESSING
	);

	//sprintf( msg_str, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );
	//print( msg_str );
	
	if(color == 0)	{
		
		printf( "ANSI/VT Support Not Available.\n" );
		resetAnsiVtCodes(0);
	}
	else
		resetAnsiVtCodes(1);

	return;
}

void ap_exit(int status)	{

	printf( "\n%sAPSuite is exiting.%s\n", FG_RED, NORMAL );
	printf( "%s", NORMAL );
	exit(status);
}



// MAIN() ENTRYPOINT
int main(int argc, char **argv)	{

	colorMode();
	
	printf( "%s", FG_BRIGHT_WHITE );
	
	// div(a,b)
	
	AP _1 = new_ap( 1024, 0 );
	AP _2 = new_ap( 1024, 0 );
	
	strcpy( _1.major, argv[1] );
	strcpy( _2.major, argv[2] );
	
	AP _3 = DIV( _1, _2 );
	
	if( argc>3 )
		maxLoopsSet = str2int( argv[2] );
	else
		maxLoopsSet = 100;
	
	printf( "Result of %s / %s = %s\n", _1.major, _2.major, _3.major );
	
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
	ca.major = strdup( "1701" );
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
	test2kMax(argc, argv);
	printf( "The minimum higher 2k exponent for %c%s is %d.\n", input.sign, input.major, dummy_int );
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
		//str[0] = '0';
		++str;
		a->major = strdup(str);
	}
	else if( str[0] == '+' )	{

		a->sign = '+';
		//str[0] = '0';
		++str;
		a->major = strdup(str);
	}
	else	{

		a->major = strdup(str);
		a->sign = '+';
	}

	return;
}

