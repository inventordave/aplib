// GET_CMD_LINE_ARGS
#ifndef DAVE_GETOPTIONS
#define DAVE_GETOPTIONS

// INFORMATIVE SECTION
/** A straightforward skeletal subsystem for processing a variable number of args passed on the cmd-line. Look in core function "getOptions".
	Essentially, the idea is that the getOptions function would return A status code of -1 if any of the cmd-line were unrecognized as they passed through the scan loop in the "for(;;)" block of the function. It is in this block that an individual (unordered) cmd-line arg/switch (contained in an argv[i] indice) is detected, and if identified, you simply implement how your program reacts to that cmd-line arg. Very simple, just browse through the getOptions(...) function, and remember to pass &argc as a pointer, and argv to the function. Internally, the function modifies the value of argc, until it is finally reduced to 0 (indicating that all cmd-line invocation parts - args - have been scanned). This means that unless you store a copy before invoking the function, the initial value of argc will be lost.
*/


// STDLIB INC'S
#include <stdio.h>
#include <string.h>
#include <assert.h>

// FNC PROTOTYPES
signed int getOptions(int * argc, char ** argv);
void rotate(int * argc, char * argv[]); // ruddy useful, shifts the cmd-line arguments array left, removing the one at argv[0]
void sanitizeStr(char * str);
int streq(char *a, char *b); // bool( str_a == str_b ), returns sensible 1 if strings match.

// EXAMPLE USAGE
int getopt_main(int argc, char **argv)	{
	
	int status = getOptions( &argc, argv );
	
	return status;
}

// SUGAR
int streq(char *a, char *b) { // returns true (1) if the 2 c-strings match, as it should...

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

signed int getOptions( int* argc, char** argv )	{

	int status = +1;

	// EXAMPLE L-value OBJECTS. You would probably define them in TU/static scope.
	int flags = 0;
	char * outputFile = (char *)malloc(262); outputFile[0] = '\0';
	char * ignoreList = (char *)malloc(1024); ignoreList[0] = '\0';
	
	// EXAMPLE R-valueS. Again, at design-time, you would probably place these in static scope.
	int RECURSE = 1;
	int OTF = 2;
	char * defaultIgnoreList = (char *)malloc(1024); defaultIgnoreList[0] = '\0';
	
	for(;;)	{
		
		rotate(argc, argv); // consume last cmd-line component, first time around, that's the program binary ".exe" name.

		if( *argc==0 )		
			// all cmd-line args consumed.
			break;
		
		if( seq(argv[0], "-r") )	{
			
			flagS |= RECURSE;
			continue;
		}
		
		if( seq(argv[0], "-o") )	{

			strcpy( outputFile, argv[1] );
			flags |= OTF;
			
			rotate(argc, argv);
			// 2 components,
			// -o then "filename"
			// delete 1st ("-o"), 2nd ("filename") will be shifted
			// on loop-around
			
			continue;
		}
		
		if( seq(argv[0], "-c") )	{

		// ... some action here based on your program's feature
			continue;
		}
		
		if( seq(argv[0], "-i") )	{
			
			if( argv[1][0] == '-' )	{ // This identifies the next cmd-line string to be a seperate switch, therefore...
				
				printf( "Used '-i' switch, but passed no DIR_BLOCK list! Assuming default list.\n" );
				strcpy( ignoreList, defaultIgnoreList );
			}
			else	{
				
				strcpy( ignoreList, argv[1] );
				rotate( argc, argv );
				// remember, for 2-part (key-value) cmd-line switches, you must manually call rotate(), as it needs to be invoked twice, as it is removing 2 strings from **argv, not 1. rotate() is auto-invoked once.			}
			
				continue;
			}

		}
		
		status = -1;
		break;
	}
	
	return status;
}


// EXTRA FNCS
void PrintASCIITable(char start, char end)	{

	
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
	
	for( char i=start; ; i+=5 )	{
		
		if( i>end )
		i = end;
		
		char j=i;
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
	
	return;
}


#endif

