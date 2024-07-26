// DAVE'S DAVELIB.

#include "lib.h"

int seq(char *a, char *b) { // returns true (1) if the 2 c-strings match, as it should...

	return (strcmp(a, b) == 0);
}

// should return 0 for match, +n for larger LHS, -n for larger RHS.
int strcmp_( char* LHS, char* RHS ){

	if( strlen(LHS)==strlen(RHS) ){
		for( large i=0; i<strlen(LHS); i++ )
		{
		if( LHS[i]==RHS[i] )
		continue;
		else
		return LHS[i]-RHS[i];
		}
	}
	else
		return strlen(LHS)-strlen(RHS);
	
	return 0;
}
#define strcmp strcmp_

// simply pauses interactivity in console-mode until a key is pressed.
void pause()	{

	getchar();
	return;
}

// custom assert() for the cmd-line args count. Pass the "argc" Env variable to it, with the min number of cmd-line args needed to continue (does not include argv[0], the executable name!).
void arg_assert( int argc, int min )	{
	
	if( (argc-1)<min ){
	//printf( "Not enough cmd-line arguments. %d are required, only %d args passed. Exiting.", min, argc-1 );
	exit(1);}

	return;
}


