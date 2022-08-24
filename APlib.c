#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#include "APlib.h"

FP a;
FP b;

void init()	{
	
	a.minor = (char *)malloc(10);
	strcpy(a.minor, "245361728");
	
	b.minor = (char *)malloc(10);
	strcpy(b.minor, "941116613");
	
	a.major = (char *)malloc(10);
	strcpy(a.major, "240027689");
	
	b.major = (char *)malloc(10);
	strcpy(b.major, "731051763");
	
	// A* 2 = 48
}

FP createFP()	{
	
	FP _;
	_.minor = (char *)calloc(1, 10);
	_.major = (char *)calloc(1, 10);
	
	return _;
	
}

int main(int argc, char ** argv)	{

		init();
		
		FP D;
		
		D = createFP();
		
		D = PLUS(a, b);
		
		printf("RESULT: '%s.%s'\n", D.major, D.minor);
		
		return 0;
}


FP PLUS(FP A, FP B)	{

	FP C;
	C.minor = (char *)calloc( 1, strlen(A.minor)+1 );
	C.major = (char *)calloc( 1, strlen(A.major)+1 );
	
	strcpy(C.minor, "000000000");
	strcpy(C.major, "000000000");

	printf("A = '%s.%s'\n", A.major, A.minor);
	printf("B = '%s.%s'\n", B.major, B.minor);
	//printf("C = '%s.%s'\n", C->major, C->minor);
	
	char k;
	char j = 0;
	
	signed int i;
	
	unsigned char flag = 2;
	
	while(flag > 0)	{
		
		char * A_P;
		char * B_P;
		char * C_P;
		
		
		if ( (flag % 2) == 0 )	{
		
			A_P = A.minor;
			B_P = B.minor;
			C_P = C.minor;
			
			//printf("C.minor = '%s'\t", C.minor);
		}
		
		else	{
			
			A_P = A.major;
			B_P = B.major;
			C_P = C.major;

			//printf("A.major = '%s'\t", A.major);
		}
		
		char _A, _B;
		for (i = strlen(A_P) - 1; i > 0; i--)	{
		
			k = 0;
			
			_A = (A_P[i] - '0');
			
			_B = (B_P[i] - '0');
			
			j =  _A + _B;
			
			//printf("j = %d\n", j);
			
			if( j > 9 )	{
				
				k = j - 10;
				A_P[i-1] += 1;
			}
			else
				k = j;
			
			C_P[i] = '0' + k;
			
			//printf("next = %d\n", (C.minor[i] - '0'));
		}
		
		j = ( A_P[i] - '0' ) + ( B_P[i] - '0' );
		//printf("j = %d\n", j);
		
		if(j>9)	{
			
			k = j - 10;
			
			if(flag==2)	{
				
				A.major[strlen(A.major) - 1] += 1;
				// rolls-over overflow from minor to major component (rh-most digit of major)
			}
			
			C_P[i] = ('0' + k );
		}
		else
			C_P[i] = ('0' + j);
		
		--flag;
	}
	
	return C;
}

