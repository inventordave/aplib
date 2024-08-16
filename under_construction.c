	
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
	signed short int equalityAB = CmpAP( A,B );
	
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

