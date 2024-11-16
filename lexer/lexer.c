// DAVELIB_LEXER_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "davio.h"
#include "lexer.h"

int lex( struct LexInstance lexInstance )	{

	return 0;
}

struct LexInstance initLex( char* sc, char* lr )	{

	// HELPER VARS.
	struct FileContext fc_source = readFile( sc );
	struct FileContents fc_lex = read_f_split( lr, "\n" );

	// GENERATE LEXER INSTANCE STATE.
	struct LexInstance lexInstance;

	lexInstance.lexRulesFileName = lr;
	lexInstance.tokenRules = initRuleSetArray( fc_lex.lineCount );
	lexInstance.numRules = fc_lex.lineCount;
	
	lexInstance.sourceCodeFileName = sc;
	lexInstance.sourceCode = fc_source.fileContents;
	lexInstance.strlen_sourceCode = fc_source.length;
	
	lexInstance.lex = lex;

	// POPULATE THE TOKENIZER RULESET.
	int offset;
	char* line;
	char* found;
	int i;
	for( i=0; i<fc_lex.lineCount; i++ )	{

		line = fc_lex.lines[i];
		//tokenRules[i][TOK_TYPE] = strtok(line, "\t");
		
		found = strtok( line,"\t");
		if( found==NULL)
		{
			printf( "Invalid format for '%s' lex file, @ line '%d'.\n", lr, i+1 );
			return lexInstance;
		}
		else
			tokenRules[i][lexInstance.TOK_TYPE] = getstring( found );

		offset = strlen( found );
		free( found );
		
		line += offset;
		tokenRules[i][lexInstance.TOK_REGEX] = getstring( line );

		line -= offset; // need to reset ptr to allocated location before freeing.
		free( line );
	}

	// LEXINSTANCE prepared. Return the Active Lex Instance.
	return lexInstance;
}


char*** initRuleSetArray(int numRules)	{

	char*** _tokenDefPair_Array = (char***) malloc( numRules * 2 * sizeof(char*) );

	char** _tokenDefPair;
	char* tok_type;
	char* tok_regex;

	int i;
	for( i=0; i<numRules; i++ )	{

		// 512 is an arbitrary assumption of string length for items in
		// lex file entry-pairs.
		tok_type = (char*) malloc( 512 );
		tok_regex = (char*) malloc( 512 );

		_tokenDefPair = (char**) malloc( 2 * sizeof(char*) );

		_tokenDefPair[0] = tok_type;
		_tokenDefPair[1] = tok_regex;

		_tokenDefPair_Array[i] = _tokenDefPair;
	}

	return _tokenDefPair_Array;
}

