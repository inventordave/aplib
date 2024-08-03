// DEV_TESTING SANDBOX

// INC'S
#include "stdlib.h"
#include "lib.h"
#include "aplib.h"
#include "native.h"
#include "sandbox.h"


#define op OP

// QUICKDRAW
char* opcode;

// C needs to be pre-allocated with zeroes, or a starting null to the correct length.
// in an ADD op, C will be len( longest digit-string between A and B ) + 1.

#define ap AP
ap* A;
ap* B;
ap* C;

char* getstring( char* in ){
	
	LARGE str_length = strlen( in );
	char* _ = (char*)malloc( str_length+1 );
	
	LARGE i;
	for( i=0; i<str_length; i++ )
		_[i] = in[i];
	
	_[i] = '\0';
	
	return _;
}

LARGE searcharray( char** p2p2, char* _, LARGE arraysize ){
	
	for( LARGE i=0; i<arraysize; i++ )
		if( !strcmp( p2p2[i],_ ) )
			return i;
		
	return 0;
	
}


ap* OP( char* opcode, ap* A, ap* B ){

	#define digit char

	int t = (strlen(B->wp)>strlen(A->wp)?strlen(B->wp):strlen(A->wp));
	ap* C = &(ap*)NewAP( +1, 0 );
	ap* R = &(ap*)NewAP( t, 0 );
	
	
	char* A_ = A->_;
	char* B_ = B->_;
	char* C_ = C->_; // C->_ should be digit-zeroed (char '0', approx. ascii value 68).
	char* R_ = R->_;


	
	R_[strlen(B_)-1] = A_[0];
	
	
	
	digit ASCII = '0';
	digit overflow = ASCII - 0;
	
	char* _A_ = A_;
	char* _B_ = B_;
	char* _C_ = C_;
	
	char* _R_ = R_;
	
	
	
	digit a = *(A_++) - ASCII;
	digit b = *(B_++) - ASCII;
	digit c = *(C_++) - ASCII;
	c += overflow;
	
	// 88/24: if( A - (b*c) * (*B)*c   )) < B )continue;
	// 2*4=8;4*4=16;8*16=128;
	// 2*3=6;4*3=12;6*12=72;
	
	//B * 3 = 72;
	
	//( 88%24=88-(B*3) );
	
	char b[2];
	b[0] = '0';
	b[1] = '\0';
	
	char c[2];
	c[0] = overflow-1;
	c[1] = '\0';

	
	ap* _ = &NewAP( strlen(B_)+1, 0 );
	//char* _ = __->_;
	
	ap* _b = &NewAP( 1, 0 );
	ap* _c = &NewAP( 1, 0 );
	
	//case '/':
	
	while (1) {

		++c[0];
		
		while( B_!='\0' ){
			
			b[0] = *(B_++);

			//_ += b*c;
			
			_b->_=b, _c->_=c;
			ap* temp2;
			ap* temp=op( "+=", _, temp2=op( "*", _a, _b ) );
			
			free( _ );
			_ = temp;
			free( temp );
			free( temp2 );

		}		
		B_ = B->_;
		
		ap* temp;
		if( (temp=op( ">", _,R ))->_[0]=='1' )
			--c[0];
		else{
			free( temp );
			continue;}

		free( temp );
		break;	
	}
	
	*(C_++) = c[0];

	ap* temp2;
	ap* temp = op( "=", R, temp2=op( "-", R,_ ) );

	{loop:
	digit b = B++;
	;c += overflow;overflow = 0;
	
	char** symbols = getaplibsymbols();

	char** getaplibsymbols(){
		
		char** symbols = (char**)malloc( sizeof( char* )*655536 ); // this implies up to 64k symbols in list.
		
		#define UNKNOWN 0
		#define OP_AND 1
		#define OP_OR 2
		#define OP_XOR 3
		#define OP_NOT 4
		#define OP_NAND 5
		
		#define OP_PLUS 17
		#define OP_MINUS 18
		#define OP_STAR 19
		#define OP_FORWARDSLASH 20
		
		#define OP_EQUALS 21
		#define OP_LTORISEQUALTO 22
		#define OP_PLUSEQUALS 23
		#define OP_MINUSEQUALS 24
		#define OP_ISEQUALTO 25
		#define OP_NOTEQUALTO 26
		#define OP_GTORISEQUALTO 27
		#define OP_GT 28
		#define OP_LT 29
		
		#define OP_CARAT 30
		#define OP_RATIO 31
		#define OP_RATIO_ASSIGN 32
		#define OP_RATIO_ISEQUALTO 33
		
		
		symbols[UNKOWN] = getstring("UNKNOWN");
		symbols[OP_AND] = getstring("AND");
		symbols[OP_OR] = getstring("OR");
		symbols[OP_XOR] = getstring("XOR");
		symbols[OP_NOT] = getstring("NOT");
		symbols[OP_PLUS] = getstring("+");
		symbols[OP_MINUS] = getstring("-");
		symbols[OP_STAR] = getstring("*");
		symbols[OP_FORWARDSLASH] = getstring("/");
	

		//symbols[OP_] = getstring("");	
		symbols[OP_GT] = getstring( ">" );
		symbols[OP_LT] = getstring("<");
	
		#define OP_INCREMENT 34
		#define OP_DECREMENT 35
		#define OP_ISDEFINEDAS 36
		#define OP_CONDITIONAL 37
		#define OP_BITWISE_AND 38
		#define OP_BITWISE_NOT 39
		#define OP_BITWISE_OR 40
		#define OP_PERIOD 41
		#define OP_LOGICAL_AND 42
		#define OP_LOGICAL_OR 43
		#define OP_LOGICAL_ISNOT 44
		
		
		
		symbols[OP_PLUSEQUALS] = getstring("+=");
		symbols[OP_ISEQUALTO] = getstring("==");
		symbols[OP_RATIO] = getstring("%");
		symbols[OP_RATIO_ASSIGN] = getstring("%=");
		symbols[OP_RATIO_ISEQUALTO] = getstring("%==");
		symbols[OP_CARAT] = getstring("^");
		symbols[OP_LTORISEQUALTO] = getstring("<=");
		symbols[OP_GTORISEQUALTO] = getstring(">=");
		symbols[OP_MINUSEQUALS] = getstring("-=");
		symbols[OP_PLUSEQUALS] = getstring("+=");
		symbols[OP_FORWARDSLASHEQUALS] = getstring("/=");
		symbols[OP_DOUBLESTAR] = getstring("**");
		symbols[OP_CARATEQUALS] = getstring("^=");
		symbols[OP_ISEQUALTO] = getstring("==");
		symbols[OP_INCREMENT] = getstring("++");
		symbols[OP_DECREMENT] = getstring("--");
		symbols[OP_ISDEFINEDAS] = getstring(":=");
		symbols[OP_CONDITIONAL] = getstring("?");
		symbols[OP_BITWISE_AND] = getstring("&");
		symbols[OP_BITWISE_NOT] = getstring("~");
		symbols[OP_PERIOD] = getstring(".");
		symbols[OP_BITWISE_OR] = getstring("|");
		symbols[OP_LOGICAL_OR] = getstring("||");
		symbols[OP_LOGICAL_AND] = getstring("&&");
		symbols[OP_LOGICAL_ISNOT] = getstring("!!");
		
		return symbols;
	}
	LARGE symbol = searcharray( symbols, opcode );
	
	signed short int equalityAB = cmp( A,B );
	switch( symbol ){
		
		
		case OP_MINUS:	b = -b;
		case OP_PLUS:	c += a + b;
		break;
				
		case OP_FORWARDSLASH:
		while(1)
		if( a < (c * b) ){--c;break;}
		else
		++c;
        printf( "This line of code should be unreachable.\nFile: %s\nLine: %d\n", __FILE__, __LINE__ );
		break;
	; // c+= is populated with a guess from 0 to 9 for a coefficient of b, which is the remainder from the 1st multiplication (MSD of C) * B <= A[1 to len(B)].
		case OP_STAR:
		c = a * b;
		break;

		case OP_PLUSEQUALS:
		free( C );
		C =	ADD( A,B );
		free( A );
		A = C;
		return C;
		
		//ASSIGN
		case OP_EQUALS:
		free( A );
		A = CopyAP( B );
		return A;
		
		case OP_MINUSEQUALS:
		free( C );
		C = SUB( A,B );
		free( A );
		A = C;
		return C;
		
		
		case OP_NOTEQUALTO:
		free( C );
		if( equalityAB!=0 )
		return CopyAP( &AP1 );
		else
		return CopyAP( &AP0 );
		

		
		case OP_GTORISEQUALTO:		
		case OP_GT:
		if( equalityAB==+1 )
		return CopyAP( &AP1 );
		else
		return CopyAP( &AP0 );
	
		case OP_ISEQUALTO:
		if( equalityAB==0 )
		return CopyAP( &AP1 );
		else
		return CopyAP( &AP0 );


		case OP_LTORISEQUALTO:
		if( equalityAB<+1 )
		return CopyAP( &AP1 );
		else
		return CopyAP( &AP0 );
		break;

		case OP_LT:
		if( equalityAB==-1 )
		return CopyAP( &AP1 );
		else
		c=0;
		break;
		
		c = value(
	
		case OP_CARAT:
		case OP_RATIO:
		case OP_RATIO_ASSIGN:
		case OP_RATIO_ISEQUALTO:
		
		case OP_ISNOT:
		case OP_AND:
		case OP_OR:
		case OP_XOR:
		case OP_NOT:
		case OP_NAND:
		break;
	}
	
	
	if( c > 9 )
	while( c > 9 ){
	++overflow;
	c -= 10;
	}
	*C_ = c + ASCII;

	if( *B_=='\0' )
		;//B -= 	
	//case 'e': a * a; // does this 'exp' times, unless 'exp' is 0 or 1. if exp is 0, just returns 1 once. if exp is 1, just return a once.
	
	return C;
}
	
// MAIN() ENTRYPOINT
int main(int argc, char **argv)	{

	if( argc<3 )
		exit( printf( "Not enough command-line args passed. You should pass an Operator, then 2 Integer values, with at least 1 space between each of the 3 args.\n") );

	init_();
	
	resetAnsiVtCodes(1);
	colorMode();
	
	AP (*OP)( AP A, AP B );
	int OPCODE = 0;
	
	printf( "%s", FG_BRIGHT_WHITE );
	
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
	setPartW( &A,argv[2] );
	
	AP B;
	
	if( argc < 4 )
	B = CopyAP( &AP1 );
	else{
	B = NewAP( strlen(argv[3]), 0 );
	setPartW( &B,argv[3] );
	}
	
	AP C = OP( A,B );
	
	printf( "%sResult:\nA='%s'\nOPCODE(%d)\nB='%s'\n==\nC='%s'\n", FG_BRIGHT_YELLOW, A.major, OPCODE, B.major, C.major );
	
	return 0;
}

#define string char*
#define eq !strcmp

char* nextArg( char* type, va_list& args )	{

	char _[2];
	_[0] = '\0';
	_[1] = '\0';
	
	if( !strcmp( type,"char*" ) ||
			eq( type,"char *" ))
	 return va_arg( args, char* );
	if( !strcmp( type,"int" ) )
	 return itoad(va_arg( args, int ));
	if( !strcmp( type,"float" ) )
	 return IEEE_readFloat(va_arg( args, float ));
	if( !strcmp( type,"double" ) )
	 return IEEE_readDouble(va_arg( args, double ));
	
	if( !strcmp( type,"char" ) ){
	 _[0]=va_arg( args, char );
	return _;}
	if( eq( type,"AP" ) ||
		!strcmp( type,"ap" ))
	 return va_arg( args, AP ).wp;
	if( !strcmp( type,"void*" ) ||
			 eq( type,"void *"))
	 return va_arg( args, void* );
	
	
	
	// ELSE
	return calloc( 2, 1 );
}


char* formatString( char* fmt, ... )	{

	va_list args;
	int escape = 0;

	char* str = (char *)malloc( );
	
	for( i=0; i<fmtstr_length; i++ ) {
		if( fmt[i]=='\' ){
			if( escape )
				escape = 0;
			else
				escape = 1;}
			
			
		else if( fmt[i]=='%' ){
			if( !escape )
				continue;
			if( fmt[++i]=='s' )
			safecat( _,(char*)nextArg( "char*",&args ) );
			else if( fmt[i]=='d' )
			safecat( _,nextArg( "int",&args ) );
			else if( fmt[i]=='f' )
			safecat( _,nextArg( "float",&args ) );
			else if( fmt[i]=='b' )
			safecat( _,nextArg( "b",&args) );
		}
	}
	
	

	str[0] = '\0';
	return str;

	//sprintf( str, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );
}

