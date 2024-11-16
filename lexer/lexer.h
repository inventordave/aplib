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

	int carat;
	char*** tokens;
	int tokensCount;

	int (*lex)( struct LexInstance* );

} LexInstance;

// FUNCTIONS
char*** initRuleSetArray( int numRules );
char*** initTokenResultsArray( int assumpt );

struct LexInstance* initLex( char* sc, char* lr );
char* patternMatch( char* str, struct LexInstance* );

int lex( struct LexInstance* );
void push( char* token_type, char* literal, struct LexInstance* );

#endif // DAVELIB_SIMPLE_LEXER_H

