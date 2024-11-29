// DAVELIB_LEXER_C

#include "../io.h"
#include "../stringy.h"
#include "../lib.h"
#include "../colour.h"

// LEXER & PARSER Includes. 
#include "lexer.h"
#include "parser.h"

// W STOOP'S REGEX LIBRARY
#include "../regex_w/wregex.h"
#include "../regex_w/wrx_prnt.h"

// LEXER::ScanLanguageString : Match substring from start to a regex-defined TOKEN_TYPE.
char* patternMatch( char* str, struct LexInstance* lexer )	{

	int e, ep;
	wregex_t *r;
	wregmatch_t *subm;

	char* pattern;
	char* token_type;

	int x = 0;
	while( x < lexer->numRules )	{

		token_type = lexer->tokenRules[x][0];
		pattern = lexer->tokenRules[x][1];

		r = wrx_comp(pattern, &e, &ep);

		if(!r) {

			fprintf(stderr, "\n[%s:%d] ERROR......: %s\n%s\n%*c\n", lexer->sourceCodeFileName, lexer->carat, wrx_error(e), pattern, ep );

			token_type = NULL;
			break;
		}

		if(r->n_subm > 0) {

			subm = calloc(sizeof *subm, r->n_subm);
			if(!subm) {

				fprintf(stderr, "Error: out of memory (submatches). Exiting Program.\n");
				wrx_free(r);
				exit(EXIT_FAILURE);
			}
		}
		else
			subm = NULL;
	
		e = wrx_exec(r, str, &subm, &r->n_subm);

		if(e < 0)
			fprintf(stderr, "Error: %s\n", wrx_error(e));
		
		if( e <= 0 )
			token_type = NULL;
		else
			break;
		
		free(subm);
		wrx_free(r);

		x++;
	}
	
	// If we got here, wregex has either matched the pattern to the rule, or has failed to find a match in the Ruleset.
	return token_type;
}

// LEXER::LEX() : [in] A pointer to a LexInstance Context.
int lex( struct LexInstance* lexer )	{

	int i;
	int k = 0;
	char c;

	int error = 1;
	char* _ = (char*) calloc( 256, 1 );
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
	lexer->tokens[lexer->tokensCount][1] = getstring( literal );

	lexer->tokensCount++;

	return;
}

struct LexInstance* initLex( char* sc, char* lr )	{

	// HELPER VARS.
	struct FileContext fc_source = readFile( sc );
	struct FileContents fc_lex = read_f_split( lr, "\n" );

	// GENERATE LEXER INSTANCE STATE.
	struct LexInstance* lexInstance = (struct LexInstance*) calloc( 1, sizeof(LexInstance) );
	lexInstance->TOK_TYPE = 0;
	lexInstance->TOK_REGEX = 1;

	lexInstance->lexRulesFileName = lr;
	lexInstance->tokenRules = (char***) calloc( fc_lex.lineCount, 2 * sizeof(char*) );
	lexInstance->numRules = fc_lex.lineCount;
	
	lexInstance->sourceCodeFileName = sc;
	lexInstance->sourceCode = fc_source.fileContents;
	lexInstance->strlen_sourceCode = fc_source.length;

	lexInstance->tokens = (char***) calloc( lexInstance->strlen_sourceCode, 2 * sizeof(char*) );
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


int Parse( struct LexInstance* lexer	)	{

	int x, x2;
	int flag;
	char* token;
	char* tok_type;
	char** prSegment;

	// INIT
	getNextProductionRuleSegment( NULL );

	// FOR_EACH lexed token in the Lexer stream.
	
	for( x=0; x<lexer->tokenCount; x++ )	{

		tok_type = lexer->tokens[x][0];
		token = lexer->tokens[x][1];
		
		// if the PR entry is a non-terminal, we need to recursively stack (LIFO), until we find a terminal definition.
		// if that terminal definition matches an entry in a production-rule segment, we need to wait until the full production-rule section
		// is matched by sequential tokens.

		section_scan:

		prSegment = getNextProductionRuleSegment( lexer );
		
		if( prSegment == NULL )	{
			
			// out of production rule segments.
			break;
		}
		
		unsigned y=0;
		char* _ = prSegment[0];

		if( _ == NULL )	{
			
			// This edge case shouldn't arise, but it constitutes a production rule nonterminal/terminal decleration at the
			// beginning of a production rule section/segment that is NULL.

			fprintf( stderr, "%s%sDEBUG MSG:%s %sAn Edge Case has arisen. A production rule has a NULL nonterminal/terminal decleration \
				at the beginning of one of it's segments. Rule Name: %s'%s%s%s'%s.\n", BG_GRAY, FG_BRIGHT_YELLOW, NORMAL, FG_BRIGHT_BLUE,\
				FG_WHITE, FG_BRIGHT_GREEN, *getNextProductionRuleSegment( (void*)1 ), FG_WHITE, NORMAL );
			
			break;
		}

		x2 = x;
		flag = 1; // assume match will be found in section/segment.
		while( _ != NULL )	{

			if( _ != tok_type )	{

				flag = 0; // match not found.
				x2 = x;
				break;	  // skip to next section
			}
			else	{

				// token match to token_type in current prSegment.
				_ = prSegment[ ++y ];
				tok_type = lexer->tokens[++x2][0];
				token = lexer->tokens[++x2][1];
						
				continue;
			}
		}
		
		if( flag!=1 )	{	
			// unable to match to entry (token) in segment.
			goto section_scan;
		}

		// ELSE, reset PoductionRules' static scanner, set latest PR-type, and continue anew from next token in stream.
		prSegment = getNextProductionRuleSegment( NULL );

		char** collection = (char**) malloc( sizeof(char*) * (x2-x) );
		unsigned j;
		for( j=x; j<x2; j++ )	{

			collection+(j-x) = lexer->tokens[j];
		}

		prRule = getNextProductionRuleSegment( (void*)1 );
		
		pushParserStack( prRule, collection, j+1 );

		x = x2;
		flag = 0;

		// tautological, included for clarity.
		continue;
	}

	if( lexer->tokenCount != x )	{

		fprintf( stderr, "%squickparse failed to complete parsing of source file '%s' at token '%d'%s\n", \
			FG_BRIGHT_RED, lexer->sourceFileName, x-1, NORMAL );
		return 0;
	}

	printf( "%sHuzzah! Quickparse completed parsing of source file '%s'%s\n.", FG_GREEN, lexer->sourceFileName, NORMAL );
	return 1;
}


typedef struct GrammarUnit	{

	int num_tokens; // from lexer
	char** tokens;

} GrammarUnit;

typedef struct ParserStack	{

	struct GrammarUnit* _[65536];
	int numEntries;

} ParserStack;

void InitParserStack( struct ParserStack* _ )	{

	_->numEntries=0;
	_->_ = (struct GrammarUnit*) malloc( sizeof(struct GrammarUnit) * 65536 );
	_->_[0] = (struct GrammarUnit*) NULL; // Presumptively, I can use indice 0 for a custom storage.
	_->_[1] = (struct GrammarUnit*) NULL;
}

void PushParserStack( char* prRule, char** collection, int amount )	{

	struct GrammarUnit* _ = (struct GrammarUnit*) malloc( sizeof(struct GrammarUnit) );
	_->num_tokens = amount;
	_->tokens = collection;

	parserStack._[ ++parserStack.numEntries ] = _;
	parserStack._[ (parserStack.numEntries)+1 ] = (struct GrammarUnit*) NULL;

	return;
}

char** getNextProductionRuleSegment( struct LexInstance* lexer )	{

	static unsigned x = 0;
	static unsigned y = 0;
	static char* prType = NULL;
	
	char** result;

	if( lexer==NULL )	{
		// reset statics.
		x = 0, y = 0;

		if( prRule != NULL )
			free( prRule );
		
		prRule = getstring( "" );
		return NULL;
	}

	if( lexer==1 )	{
		// return prType;		
		return &prRule;
	}
	
	checkAgain:

	if( !!strcmp(prRule,lexer->productionRules[x]) )
		prRule = lexer->productionRules[x];
	
	result = lexer->productionRules[x][y++];
	
	if( result == NULL )	{
	// no more production rules to provide a segment from.

		x = 0;
		y = 0;

		if( prRule != NULL )	{
			
			free( prRule );
			prRule = NULL;
		}
		
		return NULL;
	}
	
	if( result[0] == NULL )	{

		if( prRule != NULL )
			free( prRule );

		x++;
		y = 0;
		prRule = lexer->productionRules[x];
		goto checkAgain;
	}

	return result;
}


int extend( void* self )	{

	struct CSTNode* node = (struct CSTNode*) self;

	node->T_NT; // = realloc( ... );

	int success = 0;
	int numEntries;
	int newNumOfEntries = 1;
	if( success )
		numEntries = newNumOfEntries;

	return success;
}

struct CSTNode* initNode( char* nodeName, int numEntries )	{

	struct CSTNode _ = (struct CSTNode*) calloc( sizeof(struct CSTNode),1 );
	
	_->nodeName = getstring( nodeName );
	_->T_NT = (char**) calloc( sizeof(char*), numEntries );
	_->numEntries = numEntries;
	_->extend = extend;

	return _;
}

