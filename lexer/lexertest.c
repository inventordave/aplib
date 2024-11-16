// LEXERTEST_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../c_static.h"
#include "../colour.h"


#include "lexertest.h"

int main( int argc, char** argv )	{

	colorMode();
	
	printf( "%s%sTest.%s\n", FG_BRIGHT_RED, BG_BRIGHT_BLUE, NORMAL );
	
	return 0;
}

