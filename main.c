#include <stdlib.h>
#include <stdio.h>

#include "./gcollect/gc.h"
#include "stringy.h"
#include "colour.h"
#include "aplib.h"

#include "tests.h"
#include "main.h"


void flushBuffer() {
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n'));
}

int main( int argc, char** argv ){

	
	printf( "Begin...\n" );
	fflush( stdout );

	//ActivateColorConsole();
	colorMode();

	// Test colourization output.

	printf( "%s%sThis text should be yellow on black.%s\n", FG_BRIGHT_YELLOW, BG_BLACK, NORMAL );
	printf( "If the above text is not colourized as expected, ANSI/VT support is not available.\n\n");
	
	//

	aplib_gc = initGC( 10 );

	
	//INIT()
	AP0 = NewAP( 1,0 );
	AP0->integer[0] = '0';
	AP1 = NewAP( 1,0 );
	AP1->integer[0] = '1';

	AP (*fnc)( AP A, AP B );

	AP A = NewAP( 0,0 );
	AP B = NewAP( 0,0 );
	AP C = NewAP( 0,0 );

	//printf( "Trying to run Unit tests...\n\n" );

	printf( "Select from the following Unit Tests:\n\n" );

	printf( "%s1. ADD +%s\n", FG_BRIGHT_GREEN, NORMAL );
	printf( "%s2. SUB +%s\n", FG_BRIGHT_BLUE, NORMAL );

	printf( "%s3. MUL *%s\n", FG_BRIGHT_RED, NORMAL );
	printf( "%s4. DIV *%s\n", FG_BRIGHT_YELLOW, NORMAL );

	char opsym;
	char c = getchar();

	switch( c-'0' )	{

		case 1:
			fnc = ADD;
			opsym = '+';
			break;

		case 2:
			fnc = SUB;
			opsym = '-';
			break;

		case 3:
			fnc = MUL;
			opsym = '*';
			break;

		case 4:
			fnc = DIV;
			opsym = '/';
			break;

		default:
			printf( "Key pressed: %c\n", c );
			fflush( stdout );
			break;
	}


	char** _ = (char**) g( calloc( 2, sizeof(char*) * 2  ) );
	*_ = (char*) g( malloc( 1024 ) );
	*(++_) = (char*) g( malloc( 1024 ) );
	_--;
    
    	printf( "Input 2 Integer Operands to pass to %c operator.\n\n", opsym );

	int i;
	for (i = 0; i < 2; i++) {
        	scanf("%s", *(_+i) );
    	}

	setPartW( A, *_ );
	setPartW( B, *(_+1) );

	freeRef( *_ );
	freeRef( *(_+1) );
	freeRef ( _ );
	
	printf( "A: %s\nB: %s\n", A->integer, B->integer );

	C = fnc( A,B );

	printf( "Result of %s %c %s = %s\n\n", OPERAND_ARGS_MULTISELECT );	

	struct gc_report gc_result = cleanUp();

	#ifndef report
	#define report printf
	#endif

	report( "GC has cleaned-up %d references, for a process-lifetime total of %d.\n", gc_result.v, gc_result.totalDeleted  );
	return 0;
}

//char * DEC_2_BIN(char*  input, int packed)

