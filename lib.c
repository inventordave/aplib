// LIB_C
// DAVE'S DAVELIB.

// INC'S
#include "io.h"
#include "lib.h"

// 'TOGGLE'
toggle fliptoggle( toggle* t )	{
	
	if( *t==1 )
	*t=0;
	else
	*t=1;

	return *t;
}

// DAVELIB FNC'


/*
// SANITIZESTR: General method for pre-processing of an input c-string (safety).
char* sanitizeStr( char* A )	{
	
	char * B = (char *)malloc( strlen(A)+1 );
	char * _ = B;
	
	while((*A) != '\0')	{
		
		switch(*A)	{

			case 92: // \ backslash
			case 34: // " double-quote
			case 42: // * star
			case 47: // / forward-slash
			case 58: // : colon
			case 60: // < lt
			case 62: // > gt
			case 63: // ? question-mark
			case 124:// | pipe

				// printf( "Invalid char ('%c') (%d).\n", *A, *A );
				// Uncomment above line to see reporting to stdout of detected invalid chars in the input string.
				*B = '.'; // Arbitrary printable-char to replace invalid char with.
				break;
			
			default:
				*B = *A; 
				//printf( "char ok: '%c'\n", (*A) );
				break;	
		}
		
		++A;
		++B;
	}
	
	*B = '\0';
	
	return _;
}

*/

// SEQ: Sensible version of strcmp(a,b) which returns 1 on a match, not 0.
int seq(char *a, char *b){
return (strcmp(a, b) == 0); }


// PAUSE: Simply pauses interactivity in console-mode until a key is pressed.
void pause()	{

	getchar();
	return;
}

// ARG_ASSERT: Custom assert() for the cmd-line args count. Pass the "argc" Env variable to it, with the min number of cmd-line args needed to continue
// Does not include argv[0], which by system default holds the executable name ,so just the min-count for actual args passed.)
void arg_assert( int argc, int min ){
if( (argc-1)<min ){
//printf( "Not enough cmd-line arguments. %d are required, only %d args passed. Exiting.", min, argc-1 );
exit(1);}

return; }

