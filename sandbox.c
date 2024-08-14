// DEV_TESTING SANDBOX

// INC'S
#include "stdlib.h"
#include "lib.h"
#include "stringy.h"
#include "i754.h"
#include "aplib.h"
#include "sandbox.h"

#define op OP

// QUICKDRAW
char* opcode;

// C needs to be pre-allocated with zeroes, or a starting null to the correct length.
// in an ADD op, C will be len( longest digit-string between A and B ) + 1.

#define ap AP
APL A;
APL B;
APL C;


LARGE searcharray( char** p2p2, char* _, LARGE arraysize ){
	
	for( LARGE i=0; i<arraysize; i++ )
		if( !strcmp( p2p2[i],_ ) )
			return i;
		
	return 0;
	
}


APL OP( char* opcode, APL A, APL B ){

	#define digit char

	LARGE symbol = searcharray( getaplibsymbols(), opcode );	
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
			if( CmpAP( A,AP0 ) )
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
			return NOT( A,AP0) );
		
		case OP_NAND:
			return NAND( A,B );
			
		default:
			break;
	}
	
	//case 'e': a * a; // does this 'exp' times, unless 'exp' is 0 or 1. if exp is 0, just returns 1 once. if exp is 1, just return a once.

	return CopyAP( AP0 );
}
	
// MAIN() ENTRYPOINT
int main(int argc, char **argv)	{

	if( argc<3 )
		exit( printf( "Not enough command-line args passed. You should pass an Operator, then 2 Integer values, with at least 1 space between each of the 3 args.\n") );

	init_();
	
	ANSI_init();
	Init_ANSIVT_CTABLE();
	ResetAnsiVtCodes(1);
	colorMode();
	ANSI->SetVT( "black", "lightblue" ); //fg and bg colour.

	APL (*OP)( APL A, APL B );
	int OPCODE = 0;
	
	// archaic.
	//printf( "%s", FG_BRIGHT_WHITE );
	
	if( seq(argv[1], "*") || seq(argv[1],"MUL") || seq(argv[1],"MULTIPLY") )
	{OP = MUL;
	OPCODE = 1;}
	else
	if( seq(argv[1], "/") || seq(argv[1], "DIV") || seq(argv[1], "DIVIDE") )
	{OP = DIV;
	OPCODE = 2;}
	else
	if( seq(argv[1], "+") || seq(argv[1], "ADD") )
	{OP = ADD;
	OPCODE = 3;}
	else
	if( seq(argv[1], "-") || seq(argv[1], "SUB") || seq(argv[1], "SUBTRACT") )
	{OP = SUB;
	OPCODE = 4;}
	else
	if( seq(argv[1], "E") || seq(argv[1], "EXP") || seq(argv[1], "EXPONENT") )
	{OP = EXP;
	OPCODE = 5;}
	else
	{OP = NOP;
	OPCODE = 0;}
	
	AP A = NewAP( strlen(argv[2]), 0 );
	setPartW( A,argv[2] );

	AP B;
	
	if( argc < 4 )
	B = CopyAP( AP1 );
	else{
	B = NewAP( strlen(argv[3]), 0 );
	setPartW( B,argv[3] );
	}
	
	AP C = OP( A,B );
	
	printf( "%sResult:\nA='%s'\nOPCODE(%d)\nB='%s'\n==\nC='%s'\n", FG_BRIGHT_YELLOW, A->integer, OPCODE, B->integer, C->integer );
	
	return 0;
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
		va_start( args, refCount+1 );
		free( _ );
		_ = mem( i*10 );
		goto loop;}
	// loop()

	_[i] = '\0';
	_ = (char*)realloc( (void*)_,i );

	return _; }

