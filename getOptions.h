// GET_CMD_LINE_ARGS
#ifndef DAVE_GETOPTIONS
#define DAVE_GETOPTIONS

// INFORMATIVE SECTION
/** A straightforward skeletal subsystem for processing a variable number of args passed on the cmd-line. Look in core function "getOptions".
	Essentially, the idea is that the getOptions function would return a status code of -1 if any of the cmd-line were unrecognized as they passed through the scan loop in the "for(;;)" block of the function. It is in this block that an individual (unordered) cmd-line arg/switch (contained in an argv[i] indice) is detected, and if identified, you simply implement how your program reacts to that cmd-line arg. Very simple, just browse through the getOptions(...) function, and remember to pass &argc as a pointer, and argv to the function. Internally, the function modifies the value of argc, until it is finally reduced to 0 (indicating that all cmd-line invocation parts - args - have been scanned). This means that unless you store a copy before invoking the function, the initial value of argc will be lost.
*/


// STDLIB INC'S
#include <stdio.h>
#include <string.h>
#include <assert.h>

// FNC PROTOTYPES
signed int getOptions(int * argc, char ** argv);
void rotate(int * argc, char * argv[]);
void sanitizeStr(char * fn);
inline int seq(char *a, char *b);


// EXAMPLE USAGE
int _main(int argc, char **argv)	{
	
	int status = getOptions( &argc, argv );
	
	return status;
}

// SUGAR
inline int seq(char *a, char *b) { // returns true (1) if the 2 c-strings match, as it should...

	return (strcmp(a, b) == 0);
}

// CORE FNCS
void rotate(int * argc, char * argv[])	{

	assert( *argc >= 0 );
	
	for(int i = 0; i < (*argc - 1); i++)	{
		
		argv[i] = argv[i+1];
	}

	argv[*argc - 1] = '\0';
	*argc -= 1;
}

signed int getOptions(int * argc, char ** argv)	{

	int status = +1;

	// EXAMPLE L-VALUE OBJECTS. You would probably define them in TU/static scope.
	int FLAGS = 0;
	char * outputFile = (char *)malloc(262); outputFile[0] = '\0';
	char * ignoreList = (char *)malloc(1024); ignoreList[0] = '\0';
	
	// EXAMPLE R-VALUES. Again, at design-time, you would probably place these in static scope.
	int RECURSE = 1;
	int OTF = 2;
	char * defaultIgnoreList = (char *)malloc(1024); defaultIgnoreList[0] = '\0';
	
	for(;;)	{
		
		rotate(argc, argv); // consume last cmd-line component, first time around, that's the program binary ".exe" name.

		if(*argc==0)		
			// all cmd-line args consumed.
			break;
		
		if(seq(argv[0], "-r"))	{
			
			FLAGS |= RECURSE;
			continue;
		}
		
		if(seq(argv[0], "-o"))	{

			strcpy(outputFile, argv[1]);
			FLAGS |= OTF;
			
			rotate(argc, argv);
			// 2 components,
			// -o then "filename"
			// delete 1st ("-o"), 2nd ("filename") will be shifted
			// on loop-around
			
			continue;
		}
		
		if(seq(argv[0], "-c"))	{

		// ...
			continue;
		}
		
		if(seq(argv[0], "-i"))	{
			
			if(argv[1][0] == '-')	{ // This identifies the next cmd-line string to be a seperate switch, therefore...
				
				printf( "Used '-i' switch, but passed no DIR_BLOCK list! Assuming default list.\n" );
				strcpy(ignoreList, defaultIgnoreList);
			}
			else	{
				
				strcpy(ignoreList, argv[1]);
				rotate(argc, argv); // remember for 2-part (key-value) cmd-line switches, must manually call rotate(), as it needs to be invoked twice, as it is removing 2 strings from **argv, not 1. rotate() is auto-invoked once.			}
			
			continue;
		}

		status = -1;
		break;
	}
	
	return status;
}


// EXTRA FNCS
void sanitizeStr(char * fn)	{ // General method for pre-processing of an input c-string (safety).

	char invalid = '\0';
	
	while((*fn) != '\0')	{
		
		switch(*fn)	{

			case 92: // \ backslash
			case 34: // " double-quote
			case 42: // * star
			case 47: // / forward-slash
			case 58: // : colon
			case 60: // < lt
			case 62: // > gt
			case 63: // ? question-mark
			case 124:// | pipe
			
				invalid = *fn;
				printf( "Invalid char ('%c') (%d).\n", invalid, invalid );
				break;
			
			default:
				//printf( "Char ok: '%c'\n", (*fn) );
				break;	
		}
		
		++fn;
	}
}

// EXTRA FNCS
void print_ASCII(char start, char end)	{
	
	if( (start<32 || end<32) )	{
		
		printf("A scurrilous attempt was made to print the non-printable ascii characters below codepoint 32. Or even those new-fangled extended-ascii characters above codepoint 127. This is an outrage, and the function is immediately returning!");
		return;
	}
	
	if( start>end )	{
	
		char temp;
		temp = start;
		start = end;
		end = temp;
	}
	
	for( signed short int i=start; ; i+=5 )	{
		
		if( i>end )
			i = end;
		
		char j=(char)i;
		signed int k = (end-i);
		
		if( k>4 )
			k=4;
		
		switch(k)
		{
			case 4:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 3:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 2:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 1:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 0:
				printf("[%d]:=(%c)", j, j);
			default:
				NL;
			break;
		}
		
		if(i==end)
			return;
	}
}


#endif

