// DAVELIB_LEXER_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "davio.h"
#include "lexer.h"
#include "../stringy.h"

// W STOOP'S REGEX LIBRARY
#include "../regex_w/wregex.h"
#include "../regex_w/wrx_prnt.h"

char* patternMatch( char* str, struct LexInstance* lexer )	{

	int e, ep;
	wregex_t *r;
	wregmatch_t *subm;

	char* pattern;
	char* token_type;
	
	int x = 0;
	
	
	token_type = lexer->tokenRules[x][0];
	pattern = lexer->tokenRules[x][1];
	x++;

	if( x == lexer->numRules )	{

		return NULL;
	}
	
	r = wrx_comp(pattern, &e, &ep);
	
	if(!r) {
		
		fprintf(stderr, "\n[%s:%d] ERROR......: %s\n%s\n%*c\n", lexer->sourceCodeFileName, lexer->carat, wrx_error(e), pattern, ep + 1, '^');
		
		exit(EXIT_FAILURE);
	}

	if(r->n_subm > 0) {
		
		subm = calloc(sizeof *subm, r->n_subm);
		if(!subm) {
			
			fprintf(stderr, "Error: out of memory (submatches)\n");
			wrx_free(r);
			exit(EXIT_FAILURE);
		}
	}
	else
		subm = NULL;

	e = wrx_exec(r, str, &subm, &r->n_subm);

	if(e < 0)	{
		
		fprintf(stderr, "Error: %s\n", wrx_error(e));

		return NULL;
	}
	
	free(subm);
	wrx_free(r);

	if( e==0 )	{

		return NULL;
	}

	// If we got here, wregex has matched the pattern to the buffer.
	return token_type;
}

int lex( struct LexInstance* lexer )	{

	int i;
	int k = 0;
	char c;

	int error = 1;
	char* _ = (char*) calloc( 100, 1 );
	char* match;
	
	for( i=0; i<lexer->strlen_sourceCode; i++ )	{

		lexer->carat = i;
		
		c = lexer->sourceCode[i];
		_[k++] = c;
		_[k] = '\0';
		
		if( (match = patternMatch( _,lexer ))==NULL )	{

			error = 1;
			continue;
		}
		else	{
			
			k = 0;
			error = 0;

			push( match, _, lexer );
		}
	}

	return !error;
}

void push( char* token_type, char* literal, struct LexInstance* lexer )	{

	lexer->tokens[lexer->tokensCount][0] = getstring( token_type );
	lexer->tokens[lexer->tokensCount][0] = getstring( literal );

	lexer->tokensCount++;

	return;
}

struct LexInstance* initLex( char* sc, char* lr )	{

	// HELPER VARS.
	struct FileContext fc_source = readFile( sc );
	struct FileContents fc_lex = read_f_split( lr, "\n" );

	// GENERATE LEXER INSTANCE STATE.
	struct LexInstance* lexInstance = (struct LexInstance*) calloc( 1, sizeof *lexInstance );
	lexInstance->TOK_TYPE = 0;
	lexInstance->TOK_REGEX = 1;

	lexInstance->lexRulesFileName = lr;
	lexInstance->tokenRules = initRuleSetArray( fc_lex.lineCount );
	lexInstance->numRules = fc_lex.lineCount;
	
	lexInstance->sourceCodeFileName = sc;
	lexInstance->sourceCode = fc_source.fileContents;
	lexInstance->strlen_sourceCode = fc_source.length;

	lexInstance->tokens = initTokenResultsArray( lexInstance->strlen_sourceCode );
	lexInstance->tokensCount = 0;
	lexInstance->lex = lex;

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
			lexInstance->tokenRules[i][lexInstance->TOK_TYPE] = getstring( found );

		offset = strlen( found );
		free( found );
		
		line += offset;
		lexInstance->tokenRules[i][lexInstance->TOK_REGEX] = getstring( line );

		line -= offset; // need to reset ptr to allocated location before freeing.
		free( line );
	}

	// LEXINSTANCE prepared. Return the Active Lex Instance.
	return lexInstance;
}
char*** initTokenResultsArray( int assumpt )	{

	char*** tokenResultsArray = (char***) malloc( assumpt * 2 * sizeof(char*) );
	char** _tokenMatchPair;

	int i;
	for( i=0; i<assumpt; i++ )	{

		// 512 is an arbitrary assumption of string length for items in
		// lex file entry-pairs.

		_tokenMatchPair = (char**) malloc( 2 * sizeof(char*) );

		_tokenMatchPair[0] = NULL;
		_tokenMatchPair[1] = NULL;

		tokenResultsArray[i] = _tokenMatchPair;

		free( _tokenMatchPair );
	}

	return tokenResultsArray;
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

