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

typedef struct ParseInstance	{

	struct LexInstance* lexer;
	int (*parse)( struct ParseInstance* self );

	char* CFG; // filename of .cfg production rules file.
	int numPRs; // number of production rules.

	struct CSTNode* Root;

	
} ParseInstance;


typedef struct CSTNode	{

	void** descendants; // [ typeof( struct CSTNode* ) ]
	void* ancestor; 	// typeof( struct CSTNode* )
	char* nodeName;
	char** T_NT;
	unsigned numEntries;

	int (*extend)( void* self );

}	CSTNode;


// FUNCTIONS
struct CSTNode* initNode( char* nodeName, int numEntries );
int extend( void* _ );

char*** initRuleSetArray( int numRules );
char*** initTokenResultsArray( int assumpt );

struct LexInstance* initLex( char* sc, char* lr );
char* patternMatch( char* str, struct LexInstance* );

int lex( struct LexInstance* );
void push( char* token_type, char* literal, struct LexInstance* );

// int Parse( struct ParseInstance* );
// void pushFromParser( struct CSTNode* nodeName, char* literal );

#endif // DAVELIB_SIMPLE_LEXER_H

