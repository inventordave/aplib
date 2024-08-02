// DEV_TESTING SANDBOX

// INC'S
#include "stdlib.h"
#include "lib.h"
#include "aplib.h"
#include "sandbox.h"



// QUICKDRAW
char opcode;

// C needs to be pre-allocated with zeroes, or a starting null to the correct length.
// in an ADD op, C will be len( longest digit-string between A and B ) + 1.


ap* A;
ap* B;
ap* C;


/*

digit OP( opcode, ap* A, ap* B ){

	typedef digit char;

	ap* C = NewAP( (strlen(B)>strlen(A)?strlen(B):strlen(A))+1 );
	ap* R = NewAP( strlen(B) );
	
	
	char* A_ = A->_;
	char* B_ = B->_; // B->_ is typeof (char*)
	char* C_ = C->_; // C->_ should be digit-zeroed (char '0', approx. ascii value 68).
	char* R_ = R->_;


	
	R_[strlen(B_)-1] = A_[0];
	
	
	
	digit ASCII = '0';
	digit overflow = ASCII - 0;
	
	
	digit a = *(A++) - ASCII;
	digit b = *(B++) - ASCII;
	digit c = *(C++) - ASCII;
	c += overflow;
	
	88/24: if( A - (b*c) * (*B)*c   )) < B )continue;
	2*4=8;4*4=16;8*16=128;
	2*3=6;4*3=12;6*12=72;
	
	B * 3 = 72;
	
	( 88%24=88-(B*3) );
	
	char b[2];
	b[0] = '0';
	b[1] = '\0';
	
	char c[2];
	c[0] = overflow-1;
	c[1] = '\0';

	
	ap* _ = NewAP( strlen(B)+1 );
	//char* _ = __->_;
	
	ap* _b = NewAP( 1 );
	ap* _c = NewAP( 1 );
	
	case '/':
	
	while (1) {

		++c[0];
		
		while( B_!='\0' ){
			
			b[0] = *(B_++);

			//_ += b*c;
			
			_b->_=b, _c->_=c;
			op( '+=', _, op( "*",  ) );

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
	
	*(C++) = c[0];

	op( "=", R,op( "-", R,_ )

	{loop:
	digit b = B++;
	;c += overflow;overflow = 0;
	{switch( opcode ){
		
		
		case '-':	b = -b;
		case '+':	c += a + b;
					break;
				
		case '/':	if( a < (c * b) ){--c;break;}
					++c;
					continue;
	; // c is populated with a guess from 0 to 9 for a coefficient of b, which is the remainder from the 1st multiplication (MSD of C) * B <= A[1 to len(B)].
		case '*':	c = a * b;
					break;}

	if( c > 9 )
	while( c > 9 ){
	++overflow;
	c -= 10;
	}
	*C = c + 

	if( *B=='\0' )
		B -= 
	**/	
	//case 'e': a * a; // does this 'exp' times, unless 'exp' is 0 or 1. if exp is 0, just returns 1 once. if exp is 1, just return a once.

// MAIN() ENTRYPOINT
int main(int argc, char **argv)	{

	if( argc<3 )
		exit( printf( "Not enough command-line args passed. You should pass an Operator, then 2 Integer values, with at least 1 space between each of the 3 args.\n") );

	init_();
	
	resetAnsiVtCodes(0);
	
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

char * formatString( char * fmt, ... )	{

	char * str = (char *)malloc(1024);
	str[0] = '\0';

	//sprintf( str, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );

	return str;
}