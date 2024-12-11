#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* MULv2( char*, char* );

int main( int argc, char** argv )  {

	char* _ = MULv2( argv[1],argv[2] );

	printf( "Result := '%s'\n", _ );
	
	return 0;
}

char* MULv2( char* A, char* B )	{

	int lenA = strlen( A );
	int lenB = strlen( B );
	int lenC = lenA + 1;
	int lenT = lenA + lenB;
	
	int x;
	int y;
	int z;

	char a;
	char b;
	char c;
	int trailing_zeroes = 0;

	char* str;
	
	char* C = (char*) malloc( lenC + 1 );
	str = (char *)memset( C,'0', lenC );
	C[ lenC ] = '\0';
	int C_carat = lenC-1;
	
	char* T = (char*) malloc( lenT + 1 );
	str = (char *)memset( T,'0', lenT );
	T[ lenT ] = '\0';
	int T_carat = lenT-1;

	for( y=lenB-1; y>=0; y-- )	{

		for( z=trailing_zeroes; z>0; z-- )
			C[ lenC-z-1 ] = '0';

		C_carat = lenC-1-trailing_zeroes;
		
		b = B[y] -'0';

		for( x=lenA-1; x>=0; x-- )	{
	
			a = A[x] - '0';
			a += C[ C_carat ] - '0'; // *, or + ?
		
			c = b * a;
	
			if( c>9 )	{
		
				C[ C_carat ] = (c % 10) + '0';
		
				while( (c-=10)>0 )
					C[ C_carat-1 ] += 1;
			}
			else	{
				
				C[ C_carat ] = c + '0';
			}
		}

		trailing_zeroes++;
		
		z = lenT-1;
		for( x=lenC-1; x >= 0; x-- )	{

			T[z--] += ( C[x] - '0' );
			C[x] = '0';
		}		
	}

		
  return T;
} // 107 vs 77.

// ALT SECTION.
/**
int buffer_len = 0;
y=1;
while( (y++)<= lenA )
	buffer_len += lenA + 1 + (y-1) + 1;
char** rows = (char**) calloc( 1, buffer_len + 2 );
// IMPLICIT ARRAY TERMINATOR, "\0\0":
//rows[bufferlen] = '\0';
//rows[bufferlen+1] = '\0';
*/

