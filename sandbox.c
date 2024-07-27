// DEV_TESTING SANDBOX

// INC'S
#include "stdlib.h"
#include "lib.h"
#include "aplib.h"
#include "sandbox.h"

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
	
	printf( "%sResult:\nA='%s'\nOPCODE(%d)\nB='%s'\n==\nC='%s'\n", A.major, OPCODE, B.major, C.major );
	
	return 0;
}

char * formatString( char * fmt, ... )	{

	char * str = (char *)malloc(1024);
	str[0] = '\0';

	//sprintf( str, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );

	return str;
}