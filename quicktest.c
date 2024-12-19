#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* sanitizeStr( char* );
void PrintASCIITable(unsigned char start, unsigned char end);


int str2int(char* input)	{
	
	int len = strlen(input), i = 0, result = 0;
	
	if (input[0] == '-')
		i = 1;

	for(; i<len; i++)
		result = result * 10 + ( input[i] - '0' );
	
	if (input[0] == '-')
		result = 0 - result;
	
	return result;
}

int main( int argc, char** argv ){

	unsigned char* a;
	unsigned char* b;
	
	if( argc>1 ){
	a = argv[1];
	if( argc>2 )
	b = argv[2];
	else
	b = "127";
	}
	else{
	a = "32";
	b = "127";}
		
	
	char* test = "blah b;ah blah, this symbol \\ will be replaced, as will *!\n";
	
	char* result = sanitizeStr( test );
	
	printf( "INput string: %s\nOUTput string: %s\n", test, result );

	PrintASCIITable( str2int(a), str2int(b) );

	return 0;
}

void PrintASCIITable(unsigned char start, unsigned char end)	{

	
	if( (start<32 || end<32) )	{
		
		printf("A scurrilous attempt was made to print the non-printable ascii characters below codepoint 32. Or even those new-fangled extended-ascii characters above codepoint 127. This is an outrage, and the function is immediately returning!");
		return;
	}
	
	if( start>end )	{
	
		unsigned char temp;
		temp = start;
		start = end;
		end = temp;
	}
	
	for( unsigned char i=start; ; i+=5 )	{
		
		if( i>end )
		i = end;
		
		unsigned char j=i;
		int k = (end-i);
		
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
			printf("\n");
			break;
		}
		
		if(i==end)
		return;
	}
	
	return;
}

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

