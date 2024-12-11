#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main( argc, char** argv )  {

	char* _ = MULv2( argv[1],argv[2] );

	return 0;
}

char* MULv2( char* A, char* B )	{

	int lenA = strlen( A );
	int lenB = strlen( B );
	int lenC = lenA + lenB + (lenB-1);
	int lenTotal = lenA + lenB + (lenB-1);
	
	int x;
	int y;
	int z;
	
	// ALT SECTION.
	int buffer_len = 0;
	y=1;
	while( (y++)<= len_A )
		buffer_len += len_A + 1 + (y-1) + 1;
	char** rows = (char**) calloc( bufferlen + 2 );
	// IMPLICIT ARRAY TERMINATOR, "\0\0":
	//rows[bufferlen] = '\0';
	//rows[bufferlen+1] = '\0';
	
	char a;
	char b;
	char c;
	int trailing_zeroes = 0;
	
	char* C = (char*) calloc( lenC + 1 );
	int C_carat = lenC-1;
	
	char* T = (char*) malloc( lenTotal + 1 );
	int tt = lentTotal;
	T[lenTotal] = '\0';
	while( tt>=0 )
		T[--tt] = '0';


	for( y=lenB-1; y>=0; y-- )	{
	
		b = B[y] -'0';
	
		C_carat = lenA + trailing_zeroes;
	
		trailing_zeroes++;  // len(B) interim result rows for addition.
	
		for( x=len_A-1; x>=0; x-- )	{
	
			a = A[x] - '0';
			c = b * a;
	
			C[ C_carat ] = '0' + C[ C_carat ];
	
			if( result>9 )	{
		
				C[ C_carat ] += (result % 10);
		
				while( (result-=10)>0 )
					C[ C_carat-1 ] += 1;
			}
			else	{
				
				C[ C_carat ] += c;
			}
		}
	
		if( C_carat > 0 )
		while( C_carat>=0 )
			C[ C_carat-- ] = '0';
	
		z = lenC - 1;
		for( x=lenTemp-1; x >= 0; x-- )	{

			T[x] += ( C[z] - '0' );
			if( z==0 )
				break;
			z--;
		}		
	}

  return T;
} // 107 vs 77.

