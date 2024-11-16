// SIMPLE_LEXER_H
#ifndef DAVELIB_SIMPLE_LEXER_H
#define DAVELIB_SIMPLE_LEXER_H

// GLOBALS
typedef struct LexInstance	{

	int TOK_TYPE;
	int TOK_REGEX;

	char* lexRulesFileName;
	char*** tokenRules;
	int numRules;

	char* sourceCodeFileName;
	char* sourceCode;
	int strlen_sourceCode;

	int (*lex)( struct LexInstance );

} LexInstance;

// FUNCTIONS
char*** initRuleSetArray( int numRules );

struct LexInstance initLex( char* sc, char* lr );

int globalLexFnc( struct LexInstance );

#endif // DAVELIB_SIMPLE_LEXER_H

