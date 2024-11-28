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

typedef struct GrammarUnit	{

	int num_tokens; // from lexer
	char** tokens;

} GrammarUnit;

typedef struct ParserStack	{

	struct GrammarUnit* _[65536];
	int numEntries;

} ParserStack;

typedef struct CSTNode	{

	char* nodeName; // OPTIONAL ID-STRING, NONTERMINAL DESIGNATION.

	void* ancestor; 	// typeof( struct CSTNode* ), back-reference
	void** descendents;
	signed numDescendents;

	struct GrammarUnit** token_groups;
	signed numTokenGroups;
	
}	CSTNode;

struct CSTNode* createNode( char* nodeName )	{

	struct CSTNode* _ = (struct CSTNode*) malloc( sizeof(struct CSTNode) );
	_->nodeName = nodeName;
	_->numDescendents = 0;
	_->numTokenGroups = 0;

	_->descendents = malloc( sizeof( struct CSTNode* ) * (1<<13) );
	_->descendents[0] = NULL;
	return _;
}


void AddNode( struct CSTNode* node, struct CSTNode* ancestor )	{

	node->ancestor = (void*) ancestor;
	int x = ancestor->numDescendents;

	descendents[ x+1 ] = node;
	descendents[ x+2 ] = NULL;
	ancestor->numDescendents++;

	return;
}


typedef struct ParseInstance	{

	struct LexInstance* lexer;
	int (*parse)( struct ParseInstance* self );

	char* CFG; // filename of .cfg production rules file.
	int numPRs; // number of production rules.

	struct CSTNode* Root;

	
} ParseInstance;




// FUNCTIONS
struct CSTNode* initNode( char* nodeName, int numEntries );
void InitParserStack( struct ParserStack* );

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

