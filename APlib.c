#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#include "APlib.h"

FP a;
FP b;

void init()	{
	
	a.minor = (char *)malloc(10);
	strcpy(a.minor, "123456789");
	
	b.minor = (char *)malloc(10);
	strcpy(b.minor, "987654321");
	
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
	
	_.sign = +1;
	
	return _;
	
}

int main(int argc, char ** argv)	{

		init();
		
		FP D, a2, b2;
		D = createFP();
		a2 = createFP();
		b2 = createFP();

		//memcpy(&a.minor, &a2.minor, sizeof (a.minor));
		strcpy(a2.minor, a.minor);
		strcpy(a2.major, a.major);
		a2.sign = a.sign;
		
		strcpy(b2.minor, b.minor);
		strcpy(b2.major, b.major);
		b2.sign = b.sign;
		
		
		printf("A = %s . %s\n", a.major, a.minor);
		printf("B = %s . %s\n", b.major, b.minor);
		
		D = PLUS(a, b);
		printf("RESULT a + b: '%s.%s'\n", D.major, D.minor);
		
		
		strcpy(a.minor, a2.minor);
		strcpy(a.major, a2.major);
		a.sign = a2.sign;
		
		strcpy(b.minor, b2.minor);
		strcpy(b.major, b2.major);
		b.sign = b2.sign;


		printf("A = %s . %s\n", a.major, a.minor);
		printf("B = %s . %s\n", b.major, b.minor);
		
		D = MINUS(a, b);
		printf("RESULT a - b: %c'%s.%s'\n", ((D.sign == -1) ? '-' : '+'), D.major, D.minor);
		

		return 0;
}


FP MINUS(FP A, FP B)	{

	FP C;
	C = createFP();

	signed char lt = 0;
	
	for(int q = 0; q < (strlen(A.major)); q++)	{
		
		if( A.major[q] == B.major[q] )
			continue;
		
		if( A.major[q] < B.major[q] )	{
			
			lt = +1;
			break;
		}

		if( A.major[q] > B.major[q] )	{

			lt = -1;
			break;
		}
	}
	
	if( lt==1  )	{

		//printf("Hack invoking...\n");
		C = MINUS(B, A);
		C.sign *= -1;
		
		return C;
	}
	
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
		
	
		for (i = strlen(A_P) - 1; i > 0; i--)	{
			
			if (A_P[i] < B_P[i])	{

				j = i - 1;
				
				loop1:
				
				if(A_P[j] > 0)	{
				
					A_P[j] -= 1;
					A_P[i] += 10;
				}
				else if( A_P[j] == '0' )	{
				
					char c = 0;
					k = j;
					
					while( k >= 0 )	{
					
						--k;
						
						if(A_P[k] == '0')
							continue;
							
						A_P[k] -= 1;
						
						loop2:
						
						
						if(A_P[k] < '0')	{
						
							A_P[k] = ('0' + 10) - ('0' - A_P[k]);
							
							if( (k-1) >= 0)	{
							
								A_P[k-1] -=1;
							
								--k;
								++c;
							}
							
							goto loop2;
						}
						
						k += c;
						c = 0;
					}
					
					k++;
					while (k < j)	{
					
						A_P[k] = '0' + 9;
						++k;
					}
					
					A_P[k] = '0' + 10;
					
					goto loop1;
				
				}

				else if (A_P[i] < '0')	{
					
					A_P[i] = ('0' + 10) - ('0' - A_P[i]);
					
					if( (i-1) >= 0)	{
					
						A_P[i-1] -=1;
					}
					
					continue;
				}
			}

			C_P[i] = '0' + (A_P[i] - B_P[i]);
		}
		
		if(A_P[0] < B_P[0])	{
			
			if(flag==1)	{
			
			C.sign *= -1;
			}
			else
				A.major[strlen(A.major) - 1] -= 1;
			
			C_P[0] = ('0' + 10) - (B_P[0] - A_P[0]);
		}
		else	{
			
			C_P[0] = '0' + (A_P[0] - B_P[0]);
		}
		
		--flag;
	}
	
	return C;
}



FP PLUS(FP A, FP B)	{

	FP C;
	C.minor = (char *)calloc( 1, strlen(A.minor)+1 );
	C.major = (char *)calloc( 1, strlen(A.major)+1 );
	
	strcpy(C.minor, "000000000");
	strcpy(C.major, "000000000");

	//printf("A = '%s.%s'\n", A.major, A.minor);
	//printf("B = '%s.%s'\n", B.major, B.minor);
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

