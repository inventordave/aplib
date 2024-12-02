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

	// init :  sizeof(char*) * n * max_num_segments * max_num entries in a segment
	char**** productionRules; //[][][]
	char* parseRulesFileName;
	int numProductionRules;

	int (*lex)( struct LexInstance* );
	

	struct ParserInstance* parser;



} LexInstance;

// CSTNode for NonTerminals.
// grammarEntry for Terminals.
typedef struct GrammarUnit	{

	int num_tokens; // from lexer
	char** tokens;

} GrammarUnit;

typedef struct CSTNode	{

	char* nodeName; // OPTIONAL ID-STRING, NONTERMINAL DESIGNATION.

	void* ancestor; 	// typeof( struct CSTNode* ), back-reference

	char* termStr;
	signed isTerminal; 
	// if this is FAlSE, 0, then the below struct members must be populated, as the
	// descendents will be nonterminals.

	void** descendents;
	signed numDescendents;

	
}	CSTNode;

char** split( char* line, char delim );

void AddNode( struct CSTNode* node, struct CSTNode* ancestor )	{

	node->ancestor = (void*) ancestor;
	int x = ancestor->numDescendents;

	ancestor->descendents[ x+1 ] = node;
	ancestor->descendents[ x+2 ] = NULL;
	ancestor->numDescendents++;

	return;
}
void AddLeaf( struct CSTNode* node struct CSTNode* ancestor )	{

	node->isTerminal = +1;

	if( node->termStr == NULL )
		node->termStr = getstring( "[NULL String Node passed to AddLeaf() ]" );]" );

	node->ancestor = (void*) ancestor;
 	node->descendents = NULL;
	node->numDescendents = 0;
	
	return;
}

typedef struct ParserInstance	{

	struct LexInstance* lexer;

	// Example Potential Usage:
	// struct ParseInstance parseInstance = newParser( );
	// int a = parseInstance.parse( &parseInstance );
	int (*parse)( struct ParserInstance* self );

	char* CFG; // filename of .cfg production rules file.
	int numPRs; // number of production rules.

	struct CSTNode* Root;

	void (*AddNode)( struct CSTNode* node, struct CSTNode* ancestor );

	void (*AddLeaf)( struct CSTNode* node, struct CSTNode* leaf );
} ParserInstance;

void PushParserStack( char* prRule, char*** collection, int amount 
, struct ParserInstance* );


// FUNCTIONS

// INITIALIZATION FUNCTIONS
struct CSTNode* initNode( char* nodeName );
struct ParseInstance* InitParserStack(void);

int extend( void* _ );

char*** initRuleSetArray( int numRules );
char*** initTokenResultsArray( int assumpt );

char** getNextProductionRuleSegment( struct LexInstance* lexer );

// LEXER
struct LexInstance* initLex( char* sc, char* lr );
int lex( struct LexInstance* );
char* patternMatch( char* str, struct LexInstance* );
void push( char* token_type, char* literal, struct LexInstance* );

// PARSER
int Parse( struct LexInstance* );
void AddNode( struct CSTNode*, struct CSTNode* ancestor );
// The 'leaf' is the GrammarUnit, equivalentlya Terminal.
void AddLeaf( struct GrammarUnit*, struct CSTNode* );

#endif // DAVELIB_SIMPLE_LEXER_H

