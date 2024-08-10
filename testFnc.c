#include <stdlib.h>

#include "stringy.h"
#include "colour.h"
#include "aplib.h"

int main( int argc, char** argv ){

	char* test="192";
	printf( "hmmm..." );
	
		AP0 = NewAP( 1,0 );
		AP0->integer[0] = '0';
	
	char* _ = DEC_2_BIN( test, 1 );
	printf( "Input DEC = %s,\nOutput BIN= %s\n", test, _ );
	
	return 0;
}

//char * DEC_2_BIN(char*  input, int packed)

