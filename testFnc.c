#include <stdlib.h>

#include "stringy.h"
#include "colour.h"
#include "aplib.h"
#include "testFnc.h"

int main( int argc, char** argv ){

	//INIT()
	AP0 = NewAPr( 1,1 );
	AP1 = CopyAP( AP0 );
	INC( AP1 );
	
	
	int result = unitTests( char* argv[1], char* argv[2] );

	printf( "Number of Unit tests succeeded: %d\n", result );

	/**
	char* test= getstring( "192" );
	
	char* _ = DEC_2_BIN( test, 1 );
	printf( "Input DEC = %s,\nOutput BIN= %s\n", test, _ );
	*/

	return 0;
}

//char * DEC_2_BIN(char*  input, int packed)

