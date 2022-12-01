// APlib.c
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../colorconsole/ansivt2.h"
#include "APlib.h"

	
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
	
	for( signed short int i=start; i<=end; i+=5 )	{
		
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
				NEW_LINE;
			break;
		}
		
		if(i==end)
			return;
	}
}


int main(int argc, char **argv)	{
	
	//print_ASCII(32, 126);
	if( !strcmp(argv[1], "ascii") )	{
	
		print_ASCII( atoi(argv[2]),  atoi(argv[3]) );
		exit(0);
	}
	
	if( argc < 3 )	{
		
		printf("Please pass 2 (possibly signed) integers on the cmd-line, and invoke the program again. Exiting...\n");
		exit(0);
	}
		
	char _fg = 0;
	char _bg = 0;
	
	if( argc > 3 )	{
	
		// color options passed!
		_fg = ( argc >= 4 ? 1 : 0 );
		_bg = ( argc > 4 ? 1 : 0 );
	}
	
	char * fg = (char *)malloc(16);
	fg[0] = '\0';
	char * bg = (char *)malloc(16);
	bg[0] = '\0';
	
	if( _fg )
		strcpy( fg, argv[3] );
	if( _bg )
		strcpy( bg, argv[4] );
	
	if( _fg || _bg )
		swap4color( fg,bg );
	
	BOOL color = 1;
	
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if(color != 0)
	color = SetConsoleMode(
		StdHandle,
		0x0001 | 0x0002 | ENABLE_VIRTUAL_TERMINAL_PROCESSING
	);
	
	resetAnsiVtCodes(1);
	
	NL;
	
	AP A, B, C;
	A = new( MAX_LENGTH_AP_PART, MAX_LENGTH_AP_PART );
	B = new( MAX_LENGTH_AP_PART, MAX_LENGTH_AP_PART );
	
	// Arg A
	if( argv[1][0] == '-' )	{
		
		A.sign = '-';
		++argv[1];
		strcpy(A.major, argv[1]);
	}
	else if( argv[1][0] == '+' )	{

		A.sign = '+';
		++argv[1];
		strcpy(A.major, argv[1]);		
		
	}
	else	{
		
		strcpy(A.major, argv[1]);
		A.sign = '+';
	}
	
	// Arg B
	if( argv[2][0] == '-' )	{
		
		B.sign = '-';
		++argv[2];
		strcpy(B.major, argv[2]);
	}
	else if( argv[2][0] == '+' )	{

		B.sign = '+';
		++argv[2];
		strcpy(B.major, argv[2]);		
		
	}
	else	{
			
		B.sign = '+';
		strcpy(B.major, argv[2]);
	}
	
	printf("%sValues Entered:%s\na = %c%s\nb = %c%s\n\n", "[1;31;47m", NORMAL, A.sign, A.major, B.sign, B.major);
	
	// ADD
	C = ADD(A, B);
	printf("%c%s\nADD\n%c%s\n=\n%c%s\n", A.sign, A.major, B.sign, B.major, C.sign, C.major); 
	
	NL;
	
	// SUB	
	C = SUB(A, B);
	printf("%c%s\nSUB\n%c%s\n=\n%c%s\n", A.sign, A.major, B.sign, B.major, C.sign, C.major); 
	
	exit(0);

}

signed short int cmp(AP a, AP b)	{
	
	ollie len_a = strlen(a.major);
	ollie len_b = strlen(b.major);
	
	if( len_a<len_b )
		return -1;
	
	if( len_a>len_b )
		return +1;
	
	for( ollie test=0; test<len_a; test++ )	{
		
		if( a.major[test]>b.major[test] )
			return +1;
		
		if( a.major[test]<b.major[test] )
			return -1;
	}
	
	return 0;
}

AP ADD(AP a, AP b)	{

	if( cmp(a,b)==-1 )	{
		
		AP temp = b;
		b = a;
		a = temp;
	}
	
	if( a.sign=='-' )
		return SUB(a,b);

	int size = ( strlen(b.major) > strlen(a.major) ? strlen(b.major) : strlen(a.major) );
	AP c = new(size+1, 0);
	clear(&c);

	signed short int value;
	signed short int valA, valB, valC;

	signed int i, j, k;
	for( i=strlen(a.major)-1, j=strlen(b.major)-1, k=strlen(c.major)-1; k>0; i--, j--, k--)	{
	
		if(i>=0)
			valA = a.major[i] - '0';
		else
			valA = 0;
		
		if(j>=0)
			valB = b.major[j] - '0';
		else
			valB = 0;
		
		valC = (c.major[k] - '0');
		
		if( sign(&a) == '-' )
				valA = 0 - valA;

		if( sign(&b) == '-' )
			valB = 0 - valB;

		value = valA + valB + valC;
		
		//c.major[k] += '0' + (valA + valB);
		
		if( value<0 )	{
			
			c.major[k] = '0' + (10 + value);
			c.major[k-1] -= 1;
		}
		
		// ABOVE IF-BLOCK!!	
		
		else if( value>10 )	{
			
			c.major[k] = '0' + (value - 10);
			c.major[k-1] += 1;
		}
		else if( value==10 )	{
			
			c.major[k] = '0';
			c.major[k-1] += 1;
		}
		else
			c.major[k] = '0' + value;
	}
	
	if( c.major[0] < '0' )	{
		
		printf("OOPS!\n");
		c.major[0] = '0' + ('0' - c.major[0]);
	}
	
	
	
	if( tt(a,b)=='-' )
		c.sign = '-';	

	
	char * _ = (char *)malloc(strlen(c.major)+1);
	strcpy(_, c.major);
	for( i=0; i<(int)strlen(_); i++ )
		if( _[i] == '0' )
			++c.major;
		else
			break;
	
	free( _ );
			
	return c;
}

AP SUB(AP a, AP b)	{
	
	AP c;
	
	// SUB(A,B): if ( abs(b) > abs(a)), flip_sign(sub(b,a))	
	if( cmp(a,b)==-1 )	{
		
		printf("SUB, a < b, so flipped\n");
		c = SUB(b,a);
		flip_sign(&c);
		
		return c;
	}

	if( a.sign=='-' )
		return ADD(a,b);
	
	flip_sign(&b);
	c = ADD(a, b);
	//flip_sign(&b);
	
	return c;
}


char tt(AP a, AP b)	{
	
	if( (sign(&a)=='+') && (sign(&b)=='+') ) // x2
		return '+';
	
	if( ( cmp(a, b)==-1 ) && (a.sign=='-') && (b.sign=='+') )
		return '+';

	if( ( cmp(a, b)==+1 ) && (a.sign=='+') && (b.sign=='-') )
		return '+';
	
	return '-';
}

AP new(ollie maj, ollie min)	{

	AP result;
	result.major = (char *)malloc(maj+1);
	result.minor = (char *)malloc(min+1);
	
	if( (result.major==NULL)||(result.minor==NULL) )	{
		
		printf("get_new_value_object failed 1 or 2 of 2 malloc() calls! Exiting...\n");
		exit(0); // <---- peek via gdb step-trace
	}
	
	ollie i;
	
	for( i=0; i<maj; i++)
		result.major[i] = '0';
	
	result.major[maj] = '\0';
	
	for( i=0; i<min; i++)
		result.minor[i] = '0';
	
	result.minor[min] = '\0'; 

	result.length = maj + min;
	result.major_length = maj;
	result.minor_length = min;
	
	result.sign = '+';
	return result;
}


AP copy(AP a)	{
	
	AP _ = new(strlen(a.major),strlen(a.minor));
	
	strcpy(_.major, a.major);
	strcpy(_.minor, a.minor);
	
	_.sign = a.sign;
	
	_.length = a.length;
	_.major_length = a.major_length;
	_.minor_length = a.minor_length;
	
	return _;
}

void clear(AP * a)	{
	
	ollie i;
	for( i=0; i< (ollie)strlen(a->major); i++)
		a->major[i] = '0';
	
	a->major[i] = '\0';
	
	for( i=0; i< (ollie)strlen(a->minor); i++)
		a->minor[i] = '0';
	
	a->minor[i] = '\0';
	
	a->sign = '+';
}
		

char sign(AP * a)	{

	return a->sign;
}

void set_sign(AP * a, char sym)	{

	if( sym!='+' && sym!='-' )
		sym='+';
	
	a->sign = sym;
}

void flip_sign(AP * a)	{

	if( a->sign == '+' )
		a->sign = '-';
	else
		a->sign = '+';
}

