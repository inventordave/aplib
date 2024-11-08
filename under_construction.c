#define L unsigned long long int

#include <stdio.h>
#include <string.h>

char* genAlgorithm( char* A, char* B )	{

	L strlen_A = (L)strlen( A );
	L strlen_B = (L)strlen( B );

	L strlen_C = strlen_A < strlen_B ? strlen_strlen_B : strlen_A ;

	// ADD, SUB have 1 result row.
	// MUL, DIV have N result rows ( N = len(B) )

	L N;

	if( !strcmp( op, "MUL") || !strcmp( op, "DIV") )
		N = (L)strlen_B;
	else
		N = 1;

	char* C;
	if( N==1 ) C = malloc( (strlen_C = strlen_C + 1 + 1) );
	else C = malloc( (strlen_C = strlen_C * 2 + 1) );

	char* A_sub = N==1 ? calloc( 2 ) : calloc( strlen_B + 1 + 1 );
	char* B_sub = N==1 ? calloc( 2 ) : calloc( strlen_B + 1 );
	char* C_sub = malloc( 2 ); // this is only 1 char wide. [0, 9]
	C_sub[0] = '0';
	C-sub[1] = '\0';

	unsigned C_factor = 0; // note the different type. C_factor is in range 0 to 9.
	signed step_r = 0; // step_r is "step result", between -9 and +81


	

	int f;
	if( !strcmp( op, "SUB") || !strcmp( op, "DIV") )
		f = 0;
	else
		f = +1;


	// Iteratively generate the result row(s).

	int i, j, k;

	char val;

	if( N==1 )	{ // ADD, SUB
		B_sub[0] = A_sub[0];
	}
	else	{

		int b;
		for( b = 0; b<strlen_B; b++ )
			B_sub[b] = B[b]; 
	}

	for( i=0; i<N; i++ )	{
		
		for( j=strlen_B-1; j>=0; j-- )	{

			for( k=strlen_A-1; k>=0; k-- )	{

					if( !f )
					step_r = SUB( A_sub, B_sub ) ;
					else
					step_r = ADD( A_sub, B_sub ) ;

				switch( N )	{

					case 1:

						break;
					
					default:


				}
			}
		}
		
	}
}	



AP testFncDivMul( AP A, AP B ) {	
	
	int t = (strlen(B->integer)>strlen(A->integer)?strlen(B->integer):strlen(A->integer));
	APL C = NewAP( t+2, 0 );
	APL R = NewAP( t, 0 );
	
	
	char* A_ = A->integer;
	char* B_ = B->integer;
	char* C_ = C->integer; // C->_ should be digit-zeroed (char '0', approx. ascii value 68).
	char* R_ = R->integer;
	
	large strlen_b = strlen(B_);
	R_[strlen_b-1] = A_[0];
	
	
	
	char* _A_ = A_;
	char* _B_ = B_;
	char* _C_ = C_;
	char* _R_ = R_;

	digit overflow = 0;
	digit a;
	digit b;
	digit c = overflow-1;
	*C = c + '0';
	
	APL _b = NewAPr( 1, 0 );
	APL _c = NewAPr( 1, 0 );

	//case '/':
	while (1) {

		++c;	
		while( *B_!='\0' ){
			
			b = *(B_++);
			c = *(C_++);
			//_ += b*c;
			_b->integer[0]=b, _c->integer[0]=c;
			APL temp2;
			APL temp=op( "+=", _, temp2=op( "*", _b, _c ) );
			
			free( temp2 );
			free( _ );
			
			_ = temp;
			
			free( temp );
		}
		
		// reset the char* pointer to AP B->integer
		B_ = B->integer;
		
		APL temp;
		if( (temp=op( ">", _,R ))->integer[0]=='1' )
			--c;
		else{
			free( temp );
			continue;
		}

		free( temp );
		break;	
	}
		
	*(C_++) = c;

	APL temp2;
	APL temp = op( "=", R, temp2=op( "-", R,_ ) );


	loop_with_equality_cmp:
	signed short int equalityAB = CmpAP_abs( A,B );
	
	loop:

	
	a = *(A_++) - '0';
	b = *(B_++) - '0';
	c = *(C_++) - '0';
	;c += overflow;overflow = 0;



    // .....
	
	
		
	if( c > 9 )
	while( c > 9 ){
		++overflow;
		c -= 10;
	}
	*C_ = c + ASCII;

	if( *B_=='\0' )
		B_ = B->integer;
	
	goto loop;


	// fallback
	return CopyAP( AP0 );
}

