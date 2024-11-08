// DEV_TESTING SANDBOX

// INC'S
#include <ctype.h>
#include "stdlib.h"
#include "lib.h"
#include "stringy.h"
#include "i754.h"
#include "aplib.h"
#include "sandbox.h"

#include <signal.h>

// QUICKDRAW
#define op OP
#define ap AP
APL A;
APL B;
APL C;

char* strtolower( char* _ )	{
	
	L strlen__ = strlen( _ );
	char* s = (char*)malloc( strlen__ + 1 );
	char* t = s;
	while( strlen__-- )	{

		*t++ = tolower( *_++ );
	}
	
	*t = 0;
	
	return s;
}


void* davealloc( L size, uint8_t item )	{

	char* _ = malloc( size );
	char* t = _;
	
	while( size-->0 )
		*t++ = item;
	
	*t = 0;
	return _;
}


char* strtoupper( char* _ )	{

	L strlen__ = strlen( _ );
	char* s = (char*)malloc( strlen__ + 1 );
	char* t = s;
	while( strlen__-- )	{

		*t++ = toupper( *_++ );
	}

	*t = 0;

	return s;
}

volatile sig_atomic_t status = 0;

static void _catchFnc( int sig )	{
	
	status = sig;
	printf( "Caught signal %d!!\n", status );
	
	fflush( stdout );
	
}

// MAIN() ENTRYPOINT
int main(int argc, char **argv)	{

	if( argc<3 )
		exit( printf( "Not enough command-line args passed. You should pass an Operator, then 2 Integer values, with at least 1 space between each of the 3 args.\n") );

	//struct _APLIB* APLIB = Init_APLIB();

	// not using the APLIB object yet, but I need to initialise the aplib-local globals, AP0 and AP1
	struct _APLIB*  APLIB = Init_APLIB();

	if( APLIB == NULL )
		printf( "APLIB did not initialise!\n" );
	
	ANSI_init();
	Init_ANSIVT_CTABLE();
	ResetAnsiVtCodes(1);
	colorMode();
	ANSI->c->fg( getstring( "green" ) );
	//ANSI->c->bg( getstring( "black" ) ); //fg and bg colour.

	APL (*OP)( APL A, APL B );
	opcode OPCODE = 0;
	
	// archaic.
	//printf( "%s", FG_BRIGHT_WHITE );
	
	if( seq(argv[1], "*") || seq(argv[1],"MUL") || seq(argv[1],"MULTIPLY") )
	{OP = MUL;
	OPCODE = "MUL";}
	else
	if( seq(argv[1], "/") || seq(argv[1], "DIV") || seq(argv[1], "DIVIDE") )
	{OP = DIV;
	OPCODE = "DIV";}
	else
	if( seq(argv[1], "+") || seq(argv[1], "ADD") )
	{OP = ADD;
	OPCODE = "ADD";}
	else
	if( seq(argv[1], "-") || seq( strtoupper( argv[1] ), "SUB") || seq(argv[1], "SUBTRACT") )
	{OP = SUB;
	OPCODE = "SUB";}
	else
	if( seq(argv[1], "E") || seq(argv[1], "EXP") || seq(argv[1], "EXPONENT") )
	{OP = EXP;
	OPCODE = "EXP";}
	else
	{OP = NULL;
	OPCODE = "NOP";}
	
	printf( "OPCODE set to '%s'.\n", OPCODE );
	
	
	if( signal(SIGSEGV, _catchFnc)==SIG_ERR ) printf( "Couldn't register SIGSEGV handle.\n"), exit(1);
	if( signal(SIGABRT, _catchFnc)==SIG_ERR ) printf( "Couldn't register SIGABRT handle.\n"), exit(1);
	
	
	AP A = NewAP( strlen(argv[2]), 0 );

	AP B;
	
	setPartW( A,argv[2] );
	
	if( argc < 4 )
	B = CopyAP( AP1 );
	else{
	B = NewAP( strlen(argv[3]), 0 );
	setPartW( B,argv[3] );
	}


	AP C = OP( A,B );
	
	char* fractpart = (char*)malloc( strlen(C->fractional) + 1 );
	
	if( cmp_dstr( C->fractional, AP0->integer ) )	{
	
		strcpy( fractpart, "." );
		strcat( fractpart, C->fractional );
	}
	else
		strcpy( fractpart, "" );
	
	printf( "Result:\nA='%s'\nOPCODE(%s)\nB='%s'\n==\nC='%s%s'\n", A->integer, OPCODE, B->integer, C->integer, fractpart );
	
	ANSI->SetVT( getstring( "black" ), getstring( "white" ) );
	return 0;
}




LARGE searcharray( char** p2p2, char* _, LARGE arraysize ){
	
	for( LARGE i=0; i<arraysize; i++ )
		if( p2p2[i][0] == '\0' )
			break;
		else if( !strcmp( p2p2[i],_ ) )
			return i;
		
	return arraysize;

}

APL OP( char* opcode, APL A, APL B ){

	#define digit char
	scint equalityAB = CmpAP_abs( A,B );
	LARGE symbol = searcharray( GetAPSymbols(), opcode, 65535 );	
	AP P = DefaultPrecision;
	
	switch( symbol )	{

		case OP_MINUS:
			return SUBP( A,B,P );
		
		case OP_PLUS:
			return ADDP( A,B,P );
		break;
		
		case OP_DIV:
			return DIVP( A,B,P );
			break;
			
		case OP_MUL:
			return MULP( A,B,P );
			break;

		case OP_PLUSEQUALS:
			free( C );
			C =	ADDP( A,B,P );
			free( A );
			A = C;
			return A;
		
		//ASSIGN
		case OP_EQUALS:
			free( A );
			A = CopyAP( B );
			return A;
		
		case OP_MINUSEQUALS:
			free( C );
			C = SUBP( A,B,P );
			free( A );
			A = C;
			return C;
		
		case OP_NOTEQUALTO:
			free( C );
			if( equalityAB!=0 )
			return CopyAP( AP1 );
			else
			return CopyAP( AP0 );
		
		case OP_GTORISEQUALTO:		
		case OP_GT:
			if( equalityAB==+1 )
			return CopyAP( AP1 );
			else
			return CopyAP( AP0 );
	
		case OP_ISEQUALTO:
		if( equalityAB==0 )
		return CopyAP( AP1 );
		else
		return CopyAP( AP0 );


		case OP_LTORISEQUALTO:
		if( equalityAB<+1 )
		return CopyAP( AP1 );
		else
		return CopyAP( AP0 );
		break;		

		case OP_LT:
		if( equalityAB==-1 )
		return CopyAP( AP1 );
		else
		return CopyAP( AP0 );

		case OP_MODULO:
		case OP_MODULO_ASSIGN:
		case OP_MODULO_ISEQUALTO:
			break;
			
		case OP_ISNOT:
			free( C );
			if( CmpAP_abs( A,AP0 ) )
			return CopyAP( AP1 );
			else
			return CopyAP( AP0 );

		case OP_AND:
			return AND( A,B );
			
		case OP_OR:
			return OR( A,B );

		case OP_XOR:
			break;
			
		case OP_NOT:
			return NOT( A );
		
		case OP_NAND:
			return NAND( A,B );
			
		default:
			break;
	}
	
	//case 'e': a * a; // does this 'exp' times, unless 'exp' is 0 or 1. if exp is 0, just returns 1 once. if exp is 1, just return a once.

	return CopyAP( AP0 );
}
	

#define string char*
#define eq !strcmp

char* nextArg( char* type, va_list args )	{

	char* _ = (char*)malloc( 2 );
	_[0] = '\0';
	_[1] = '\0';
	
	if( !strcmp( type,"char*" ) ||
			eq( type,"char *" ))
	 return va_arg( args, char* );
	if( !strcmp( type,"int" ) )
	 return itoad(va_arg( args, int ));
	if( !strcmp( type,"float" ) )
	 return IEEE_readFloat((float)va_arg( args, double ));
	if( !strcmp( type,"double" ) )
	 return IEEE_readDouble(va_arg( args, double ));
	
	if( !strcmp( type,"char" ) ){
	 _[0]=(char)va_arg( args, int );
	return _;}
	if( eq( type,"AP" ) ||
		!strcmp( type,"ap" )){
	
	AP A = va_arg( args, AP );
	char* _A = getstring( A->integer );
	FreeAP( A );
	return _A;
	}
	if( !strcmp( type,"void*" ) ||
			 eq( type,"void *"))
	 return va_arg( args, void* );

	// ELSE
	return (char*)calloc( 2, 1 );
}

//sprintf( str, ... )

/**
char* formatString( char* fmt, ... )	{

	va_list args;
	int escape = 0;
	int mode = 0;
	char* _ = getstring( "" );
	
	L fmtstr_length = strlen( fmt );
	L refCount=0;
	
	LARGE i;
	loop:
	for( i=0; i<fmtstr_length; i++ ){

	if( fmt[i]=='\\' ){
		if( escape )
		escape = 0;
		else
		escape = 1;}
		
	else if( fmt[i]=='%' ){
		if( !escape )
		continue;
		if( fmt[++i]=='s' ){
			if( mode==0 )
				++refCount;
			else
				safecat( _,nextArg( "char*",args ) );}
		else if( fmt[i]=='d' ){
			if( mode==0 )
				++refCount;
			else
			safecat( _,nextArg( "int",args ) );}
		else if( fmt[i]=='f' ){
			if( mode==0 )
			++refCount;
			else
			safecat( _,nextArg( "float",args ) );}
		else if( fmt[i]=='b' ){
			if( mode==0 )
			++refCount;
			else
			safecat( _,nextArg( "b",args) );}
		else
		continue;}}

	if( mode==0 ){
		mode=1;
		va_start( args, fmt );
		free( _ );
		_ = mem( i*10 );
		goto loop;}
	// loop()

	_[i] = '\0';
	_ = (char*)realloc( (void*)_,i );

	return _; }
*/



