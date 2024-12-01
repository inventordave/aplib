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
	void** descendents;
	signed numDescendents;

	struct GrammarUnit** token_groups;
	signed numTokenGroups; 
	
}	CSTNode;


typedef struct ParserStack	{

	struct GrammarUnit** _;
	int numEntries;

} ParserStack;



char** split( char* line, char delim );

struct CSTNode* createNode( char* nodeName )	{

	struct CSTNode* _ = (struct CSTNode*) malloc( sizeof(struct CSTNode) );

	_->nodeName = nodeName;
	
	_->ancestor = NULL;

	// FOR CSTNODE NONTERMINALS. EITHER/OR WITH TERMINALS SECTION BELOW.
	_->descendents = malloc( sizeof( struct CSTNode* ) * (1<<13) );
	_->descendents[0] = NULL;
	_->numDescendents = 0;

	// FOR TERMINALS AS ATTACHED LEAF-NODE.
	_->token_groups = NULL;
	_->numTokenGroups = 0;

	return _;
}
void AddNode( struct CSTNode* node, struct CSTNode* ancestor )	{

	node->ancestor = (void*) ancestor;
	int x = ancestor->numDescendents;

	ancestor->descendents[ x+1 ] = node;
	ancestor->descendents[ x+2 ] = NULL;
	ancestor->numDescendents++;

	return;
}
void AddLeaf( struct GrammarUnit* g, struct CSTNode* node )	{

	// Alternatively, the below line of code can be used inline to attach a leaf terminal to a CSTNode.
	node->token_groups[ ++node->numTokenGroups ] = g;

	return;
}

typedef struct ParseInstance	{

	struct LexInstance* lexer;

	// Example Potential Usage:
	// struct ParseInstance parseInstance = newParser( );
	// int a = parseInstance.parse( &parseInstance );
	int (*parse)( struct ParseInstance* self );

	char* CFG; // filename of .cfg production rules file.
	int numPRs; // number of production rules.

	struct CSTNode* Root;

	
} ParseInstance;

// FUNCTIONS

// INITIALIZATION FUNCTIONS
struct CSTNode* initNode( char* nodeName );
void InitParserStack( struct ParserStack* );

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

