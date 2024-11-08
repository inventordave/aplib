// The below snippet is cut from the APlib.c::SUBP function.

AP SUBP( AP A, AP B, AP P )	{

	if( (A->sign=='+') && (B->sign=='+') && (CmpAP_abs(A,B)>=0) ){

		int i, j, k, valA, valB, valC;
		AP C = NewAPr(strlen(A->integer),0);
		for( i=strlen(A->integer)-1, j=strlen(B->integer)-1, k=strlen(C->integer)-1; k>=0; i--, j--, k--){
		
			if(i>=0)
				valA = A->integer[i] - '0';
			else 
				valA = 0;
			
			if(j>=0)
				valB = B->integer[j] - '0';
			else
				valB = 0;
			
			valC = (C->integer[k] - '0');	
			
			valA += valC;

			if( valA<valB )	{
				
				C->integer[k-1] -= 1;
				valA += 10;
			}

			int value = valA - valB;
			C->integer[k] = '0' + value;
		}
		
		int len = strlen(C->integer);
		char* _ = getstring( C->integer );
		for( i=0; i<len; i++ )
			if( _[i] == '0' )
				++C->integer;
			else
				break;
	
		free( _ );
	
		if( *(C->integer) == '\0' )
			--C->integer;
		
		return C;
	}

	// Alt. SUB Algorithm:
	// The subtrAction of A reAl number (the subtrAhend [B]) from Another (the minuend [A]) cAn be defined As the ADition of the minuend [A] And the ADitive inverse of the subtrAhend [B].
	flipSign(B);
	AP result = ADD(A, B);
	flipSign(B);

	return result;
}

