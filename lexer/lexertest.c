// LEXERTEST_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../stringy.h"
#include "../c_static.h"
#include "../colour.h"
#include "lexer.h"

#include "lexertest.h"

int main( int argc, char** argv )	{

	colorMode();
	
	printf( "%s%sTest.%s\n", FG_BRIGHT_RED, BG_BRIGHT_BLUE, NORMAL );

	char* sc;
	if( argc>1 )
		sc = getstring( argv[1] );
	else
		sc = "lexer.c";

	char* lr;
	if( argc>2 )
		lr = getstring( argv[2] );
	else
		lr = "c--.lex";
	
	struct LexInstance* lexer = initLex( sc, lr );
	
	int success = lex( lexer );

	if( !success )	{

		printf( "Lexer is reporting failure. Carat position '%d' of file buffer size '%d'.\n", lexer->carat, lexer->strlen_sourceCode );

	}

	int x;
	for( x=0; x<lexer->tokensCount; x++ )	{

		if( lexer->tokens[x][0]==NULL )
			break;
		
		printf( "%sToken Type: %s%s\n%sToken Literal: %s%s%s\n", FG_BRIGHT_YELLOW, FG_BRIGHT_GREEN, FG_BRIGHT_YELLOW, lexer->tokens[x][0], FG_BRIGHT_GREEN, lexer->tokens[x][1], NORMAL );

	}

	return 0;
}

