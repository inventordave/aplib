// APLIB_C

#include "lib.h"
#include "aplib.h"

AP AP0;
AP AP1;
L DefaultPrecision;

struct APLIB_ APLIB;

char* MUL_SYM = "*";
char* ADD_SYM = "+";
char* SUB_SYM = "-";
char* DIV_SYM = "/";
char* EXP_SYM = "e";
char* AND_SYM = "&";
char* NOT_SYM = "~";
char* OR_SYM =  '|";
char* XOR_SYM = "^";
char* NAND_SYM = "@";
char* POSITIVE_SYM = "+";
char* NEGATIVE_SYM = "-";
char* DELIMETER_SYM = ".";
char* BASE10_SYM = "0";
char* BASE2_SYM = "2";
char* BASE16_SYM = "H";
char* ALL_DIGITAL_SYMBOLS = "0123456789abcdefABCDEF.hHxX";

L MAX_LENGTH = 4096-1;

L setPartW( AP* A, char * _ )	{

	return setPart( A, _, PartW );
}
L setPartF( AP* A, char * _ )	{

	return setPart( A, _, PartF );
}

L setPart( AP* A, char * digits, int part )	{

	if( part==SignPart )	{

		A->sign = *digits;
		
		if( A->sign==digits[0] )
		return SUCCESS;
		else
		return FAIL;
	}

	char * _;
	
	if( part==1 )
		_ = A->wholepart;
	else
		_ = A->fp;
	
	if( strlen(_) < strlen(digits) )
		_ = (char *)realloc(_, strlen(digits)+1);

	
	large i;
	for( i=0; i<strlen(_); i++ )
		_[i] = digits[i];
	
	_[i] = '\0';
	
	return i;
}


L DIVBY2_PRINT_ROWS = 0;

// CORE BOOLEAN OPERATORS
ap* AND( ap* LHS, ap* RHS )	{
	
	char* A = LHS->wholepart;
	char* B = RHS->wholepart;
	
	L strlen_a = strlen( A );
	L strlen_b = strlen( B );
	L len = ( strlen_a >= strlen_b ? strlen_a : strlen_b );
	
	char* bstr = (char*)malloc( len+1 );
	bstr[len] = '\0';

	// both binary string Are the same length.
	char a = '0';
	char b = '0';
	
	LARGE t, i, j, k;
	for( i=strlen_a-1,j=strlen_b-1, k=len-1; ; i--, j--, k-- )	{
		
		t = 0;
		
		if( i<0 )	{
			
			a = '0';
			++t;
		}
		else
			a = A[i];
		
		if( j<0 )	{
			
			b = '0';
			++t;
		}
		else
			b = B[j];
		
		if( t==2 )
			break;
			
		bstr[k] = '0' + ( (a-'0') & (b-'0') );
	}
	
	AP _ = NewAP( 0,0 );
	setPartW( _,bstr );
	return _;
}
ap* NOT(ap* v)	{
	
	L strlen_v = strlen( v );
	char* _ = (char*)malloc( strlen_v+1 );
	LARGE i;
	for( i=0; i<strlen_v; i++ )
		if( v[i]=='0' )
			_[i] = '1';
		else if( v[i]=='1' )
			_[i] = '0';
		else
			assert(0);
		
	_[i] = '\0';
	
	return _;
}
char * OR(char * LHS, char * RHS)	{

	char * A;
	char * B;
	
	A = LHS; B = RHS;
	int len = ( strlen(A) >= strlen(B) ? strlen(A) : strlen(B) );
	
	char * b_str = (char *)malloc( len+1 );
	b_str[len] = '\0';

	// both binary string Are the sAme length.
	char a = '0';
	char b = '0';
	
	int t, i, j, k;
	for( i=strlen(A)-1,j=strlen(B)-1, k=len-1; ; i--, j--, k-- )	{
		
		t = 0;
		
		if( i<0 )	{
			
			a = '0';
			++t;
		}
		else
			a = A[i];
		
		if( j<0 )	{
			
			b = '0';
			++t;
		}
		else
			b = B[j];
		
		if( t==2 )
			break;
			
		b_str[k] = '0' + ( (a-'0') | (b-'0') );
	}
	
	assert( k==-1 );
	
	return b_str;
}
ap* XOR( ap* LHS, ap* RHS )	{

	char* A = LHS->wholepart;
	char* B = RHS->wholepart;
	
	L strlen_a = strlen( A );
	L strlen_b = strlen( B );
	
	L len = ( strlen_a >= strlen_b ? strlen_a : strlen_b );
	
	char* bstr = (char *)malloc( len+1 );
	bstr[len] = '\0';

	// (both binary string are the same length, as we test 1 digit at a timee)
	char a = '0';
	char b = '0';
	
	LARGE t, i, j, k;
	for( i=strlen_a-1,j=strlen_b-1, k=len-1; ; i--, j--, k-- )	{

		t = 0;

		if( i<0 )	{

			a = '0';
			++t;
		}
		else
			a = A[i];

		if( j<0 )	{

			b = '0';
			++t;
		}
		else
			b = B[j];

		if( t==2 )
			break;

		bstr[k] = '0' + ( (a-'0') ^ (b-'0') );
	}

	assert( k==-1 );
	
	
	return bstr;
}
ap* NAND( ap* LHS, ap* RHS )	{
	
	ap* C = AND( LHS,RHS );
	ap* _ = NOT( C );
	free( C );
	
	return _;
}


// NOP (No-Operation). It returns an AP, or AP0, value.
AP* NOP( AP* A ){

	if( A==0 )
		return CopyAP( &AP0 );
	return A;
}

// CORE ARITHMETIC OPERATORS
AP* ADD( AP* A, AP* B )	{ return ADDP( A, B, DefaultPrecision ); }
AP* ADDP( AP* A, AP* B, AP P )	{
	
	int flag = 0;
	
	large strlen_a = strlen(A->wholepart);
	large strlen_b = strlen(B->wholepart);
	large size = ( strlen_b > strlen_a ? strlen_b : strlen_a );
	AP* C = NewAPr( size+1,0 );

	signed short int value;
	signed short int valA, valB, valC;
	
	signed int i, j, k;
	
	if( getSign(A) == getSign(B) )	{
		
		for( i=strlen_a-1, j=strlen_b-1, k=size; k>0; i--, j--, k--)	{
		
			if(i>=0)
				valA = A->wholepart[i] - '0';
			else
				valA = 0;
			
			if(j>=0)
				valB = B->wholepart[j] - '0';
			else
				valB = 0;
			
			valC = (C->wholepart[k] - '0');	
			
			valA += valC;

				
			value = valA + valB;

			if( value>=10 )	{
				
				value -= 10;
				C->wholepart[k-1] += 1;
			}
			
			//C->wholepart[k] = '0' + value;
			
			setDigit( C,k,('0'+value) );

		}
	}
	else	{
		
	//SubtrAct the smAller Absolute value from the lArger Absolute value And give the Answer the sAme sign As the number with the lArger Absolute value
		char tsign;
		if( CmpAP(&A,&B)==-1 )	{
			
			tsign = B.sign;
			
			AP temp;
			temp = A;
			A = B;
			B = temp;
		}
		else
			tsign = A.sign;
		
		A.sign = '+';
		C.sign = '+';
		C = SUB( A,B );
		C.sign = tsign;
		flag = 1;
	}
	
	
	if( ( tt_add( &A,&B )=='-' ) && (flag==0) )
		C.sign = '-';

	
	char * _ = (char *)malloc(strlen(C.wholepart)+1);
	strcpy(_, C.wholepart);
	for( i=0; i<(int)strlen(_); i++ )
		if( _[i] == '0' )
			++C.wholepart;
		else
			break;
	
	free( _ );
	
	if( *C.wholepart == '\0' )
		--C.wholepart;
	
	return C;
}
AP SUB( AP* A, AP* B )	{ return SUBP( A, B, DefaultPrecision ); }
AP* SUBP( AP* A, AP* B, AP P )	{
	
	if( (A->sign=='+') && (B->sign=='+') && (CmpAP(&A,&B)>=1) ){

		int i, j, k, valA, valB, valC;
		AP* C = NewAPr(strlen(A->wholepart),0);
		for( i=strlen(A->wholepart)-1, j=strlen(B->wholepart)-1, k=strlen(C->wholepart)-1; k>0; i--, j--, k--){
		
			if(i>=0)
				valA = A->wholepart[i] - '0';
			else
				valA = 0;
			
			if(j>=0)
				valB = B->wholepart[j] - '0';
			else
				valB = 0;
			
			valC = (C->wholepart[k] - '0');	
			
			valA += valC;

			if( valA<valB )	{
				
				C->wholepart[k-1] -= 1;
				valA += 10;
			}

			int value = valA - valB;
			C->wholepart[k] = '0' + value; }
		
		int len = strlen(C->wholepart);
		char* _ = getstring( C->wholepart );
		for( i=0; i<len; i++ )
			if( _[i] == '0' )
				++C->wholepart;
			else
				break;
	
		free( _ );
	
		if( *(C->wholepart) == '\0' )
			--C->wholepart;
		
		return C;
	}
	
	// Alt. SUB Algorithm:
	// The subtrAction of A reAl number (the subtrAhend [B]) from Another (the minuend [A]) cAn be defined As the ADition of the minuend [A] And the ADitive inverse of the subtrAhend [B].
	flipSign(&B);
	AP* result = ADD(A, B);
	flipSign(&B);

	return result;
}
AP MUL( AP A, AP B )	{ return MULP( A, B, DefaultPrecision ); }
AP MULP( AP A, AP B, AP P )  {

	int MAX_NUM_MUL_ROWS = ( strlen(A.wholepart)>strlen(B.wholepart) ? strlen(A.wholepart) : strlen(B.wholepart) );
	
	char ** ResultArray = (char **)calloc(MAX_NUM_MUL_ROWS, sizeof(char *));
	int q = 0;

	for( int k = strlen(B.wholepart)-1; k>=0; k-- )	{
		
		int rev_offset_B = strlen(B.wholepart) - 1 - k;
		
		int curr_row_length = strlen(A.wholepart) + 1 + rev_offset_B;
		char * curr_row = (char *)malloc( curr_row_length + 1 );
		curr_row[ curr_row_length ] = '\0';
		pack_trailing_zeroes( curr_row, curr_row_length, rev_offset_B );
		
		int prev_overflow = 0;
		
		int p = curr_row_length - 1 - rev_offset_B;
		
		for( int i = strlen(A.wholepart)-1; i>=0; i-- )	{
			
			int _A = A.wholepart[i] - '0';
			int _B = B.wholepart[k] - '0';
			
			int result = _A * _B;
			result += prev_overflow;
			
			if( result>9 )	{
				
				prev_overflow = MSD(result);
				curr_row[p] = (result % 10) + '0';
			}
			else	{
				
				prev_overflow = 0;
				curr_row[p] = result + '0';
			}
			
			--p;
		}
	
		if( prev_overflow>0 )	{
		
			curr_row[0] = prev_overflow + '0';
		}
		else
			curr_row[0] = '0';
		
		ResultArray[q++] = curr_row;
	}


	AP C = NewAP( 10,0 );
	AP D = NewAP( 1,0 );
	
	for( int t = 0; t < q; t++ )	{
		
		char * result_row = ResultArray[t];
		
		if(result_row==NULL)
			assert(result_row);
		
		free( D.wholepart );
		
		D.wholepart = strdup(result_row);
		
		C = ADD( C,D );
	}
	
	C.sign = tt_mul( &A,&B );
	return C;
}
AP DIV( AP A, AP B )	{

	return DIVP( A, B, DefaultPrecision );
}
AP DIVP( AP A, AP B, AP P )  {

	int fractional = 0;
	int L0 = 1;
	
	//char * wholepart;
	//char * fp;
	
	AP C = NewAP(0, 0);
	large offset = strlen(B.wholepart) - 1;
	AP Remainder = NewAP( strlen(B.wholepart) , 0 );
	
	large i;
	for(i=0;i<strlen(B.wholepart);i++)
		Remainder.wholepart[i] = A.wholepart[i];
	
	Remainder.wholepart[i] = '\0';
	
	AP Dropdown = NewAP(1, 0);
	
	AP v = NewAP(1, 0); v.wholepart[0] = '0';
	AP inc = NewAP(1, 0); inc.wholepart[0] = '1';
	
	AP temp;
	AP v2;
	AP result;
	large strlen_A = strlen(A.wholepart);
	//large strlen_minor_A = LSD_OFFSET(A.fp);
	
	if( strlen(A.wholepart)>strlen(B.wholepart) )
		Dropdown.wholepart[0] = A.wholepart[offset+1];
	else
		Dropdown.wholepart[0] = '0';
	
	
	int LOOPS = 0;
	
	int MAX_LOOPS = 100;

	//int count = 0;
	loop:
	while( offset<strlen_A )	{
		
		++LOOPS;
		if( LOOPS>MAX_LOOPS )
			goto maxiterations;
		
		v.wholepart[0] = '0';
		
		temp = MUL( B,v );
		while( CmpAP( &temp,&Remainder ) < 1 )	{
			
			v2 = ADD(v, inc);
			free( v.wholepart );
			v = CopyAP(&v2);
			free( v2.wholepart );
			
			free( temp.wholepart );
			temp = MUL( B,v );
		}
		
		v2 = SUB(v, inc);
		free( v.wholepart );
		v = CopyAP(&v2);
		free( v2.wholepart );
		
		result = MUL( B,v );
		v2 = SUB(Remainder, result);
		free( result.wholepart );
		free( Remainder.wholepart );
		Remainder = CopyAP(&v2);
		free( v2.wholepart );

		
		#define CONCAT(__A,__B) strcat(__A.wholepart, __B.wholepart)
		
		//printf( "Row %d:\t'%s' + '%s'\n", count, C.wholepart, v.wholepart );
		//++count;
		CONCAT( C,v );
		
		if( !fractional )
			if( L0==1 )	{

				if( v.wholepart[0]=='0' )	{
					
						++C.wholepart;
				}
				else
					L0=0;
			}
		
		if( Remainder.wholepart[0] > '0' )
			CONCAT( Remainder,Dropdown );
		else	
		if( offset != (strlen(B.wholepart)-1) )
			Remainder.wholepart[0] = Dropdown.wholepart[0];

		if( fractional )	{
			
			if( CmpAP( &Remainder,&AP0 ) == 0 )	{
				break;
			}
		}
		else	{

			if( (offset+1)<strlen_A )
				
				Dropdown.wholepart[0] = A.wholepart[offset+1];
			else
				Dropdown.wholepart[0] = '0';
		}

		++offset;
	}
	
	
	// fractional overflow
	
	if( fractional==0 )	{
		
		fractional = 1;

		if( CmpAP( &C,&AP0 )==0 )
			--C.wholepart;
		
		//wholepart = strdup( C.wholepart );
	}
	
	offset = 0;
	Dropdown.wholepart[0] = '0';
	
	if( CmpAP( &Remainder,&AP0 ) == 1 )
		goto loop;
	
	maxiterations: // Upper-bound for precision of calculation reached.
	// RESULT COMPUTED.
	
	//printf( "The fixed-point for the Answer is positioned to the right of digit %d.\n", (int) strlen_A-1 );
	
	for( i=0; i<(strlen_A-1); i++ )
		printf( "%c", C.wholepart[i] );
	
	printf( "." );
	
	for( ; i<strlen(C.wholepart); i++ )	
		printf( "%c", C.wholepart[i] );
	
	NL;
	
	printf( "\n\nSystem paused. Press any (sensible) key to continue..." );
	pause();
	
	return C;
}

// SKELETON FNC'S FOR FUTURE OPERATO
AP CROSS( AP A, AP B )	{

	return CROSSP( A, B, DefaultPrecision );
}
AP CROSSP( AP A, AP B, AP P )	{
	
	return CopyAP( &AP1 );
}
AP DOT( AP A, AP B )	{

	return DOTP( A, B, DefaultPrecision );
}
AP DOTP( AP A, AP B, AP P )	{

	return CopyAP( &AP1 );
}


char* zmem( large nb )	{

	char* _ = (char*) malloc( nb+1 );
	
	large i;
	for( i=0; i<nb; i++ )
		_[i] = '0';

	_[i] = '\0';
	
	return _;
}


AP* RESET0( AP* A ) { setPartW( A,0 ); setPartF( A,0 ); return A; }
AP* RESET1( AP* A ) { setPartW( A,1 ); setPartF( A,0 ); return A; }


struct _APLIB* Init_APLIB(){
	
	// Initialise
	AP0 = NewAP( 1,0 );
	AP0.wholepart[0] = '0';
	AP1 = NewAP( 1,0 );
	AP1.wholepart[0] = '1';
	DefaultPrecision = 0; // Sets default precision to indicate the length of the largest string between the 2 operands.

	struct _APLIB* APLIB = (struct _APLIB*)malloc( sizeof(struct _APLIB) );
	
	// Add the OPERATORS to the APLIB global.
	APLIB->NOP = NOP;
	APLIB->ADD = ADD;
	APLIB->ADDP = ADDP;
	APLIB->SUB = SUB;
	APLIB->SUBP = SUBP;
	APLIB->MUL = MUL;
	APLIB->MULP = MULP;
	APLIB->DIV = DIV;
	APLIB->DIVP = DIVP;
	APLIB->DIVBY2 = DIVBY2;
	APLIB->RECIPROCAL = RECIPROCAL;
	APLIB->RECIPROCAL2 = RECIPROCAL2;
	APLIB->RECIPROCALP = RECIPROCALP;
	APLIB->RECIPROCALP2 = RECIPROCALP2;
	APLIB->EXP = EXP;
	APLIB->CROSS = CROSS;
	APLIB->CROSSP = CROSSP;
	APLIB->DOT = DOT;
	APLIB->DOTP = DOTP;
	APLIB->AND = AND;
	APLIB->OR = OR;
	APLIB->XOR = XOR;
	APLIB->NOT = NOT;
	APLIB->NAND = NAND;

	APLIB->INC = INC;
	APLIB->DEC = DEC;

	APLIB->RESET0 = RESET0;
	APLIB->RESET1 = RESET1;


	// Add the 'sign' helpers.
	APLIB->flipSign = flipSign;
	APLIB->getSign = getSign;
	APLIB->setSign = setSign;
	
	APLIB->DSTRING2LARGE = DSTRING2LARGE;

	return *APLIB;
}

// BASE CONVERSION FNCS
char * BIN_2_DEC(char * bin)	{ /** Converts base2 (binary) string to base10 (decimal) string.

*/

	AP dec = NewAP( strlen(bin)+1, 0 );
	AP mult = NewAP( strlen(bin)+1, 0 );
	
	AP digit = NewAP(1, 0);
	
	AP _2 = NewAP(1, 0);
	AP _j = NewAP(10, 0);
	
	_2.wholepart = strdup( "2" );

	int i, j;
	
	for( i=0, j=strlen(bin)-1; i<strlen(bin); i++, j-- )	{

		digit.wholepart[0] = bin[i];
		
		sprintf(_j.wholepart, "%d", j); // itoa()
		mult = EXP( _2, _j );
		dec = ADD( dec, MUL(digit, mult) );
	}
	
	FreeAP( &mult );
	FreeAP( &digit );
	FreeAP( &_2 );
	FreeAP( &_j );
	
	char * result = (char *)malloc( strlen(dec.wholepart)+1 );
	result = strdup( dec.wholepart );

	FreeAP( &dec );
	
	return result;
}
char * DEC_2_BIN(AP input, int packed)	{
/**
PArAm "int packed" is A flag to determine if the returned binary string should be rounded in length to A multiple of 8.
In other words, 127 would be "01111111" insteAd of "1111111". An Argument of 0 meAns "do not round", A non-0 value meAns "round up string-length to multiple of 8".
*/

	int length = 0;
	int flag = 1;

	AP t = NewAP( 1,0 );
	t.wholepart = strdup( "0" );
	
	AP Check = CopyAP( &input );
	while ( flag )	{
		
		AP* temp;
		temp=DIVBY2(&Check);
		*Check=temp;
		free( temp );
		
		if( DIVBY2_PRINT_ROWS==1 )
			printf( "\t%c%s\n", Check.sign, Check.wholepart );
			
		++length;
		
		if( CmpAP(&Check,&t)<= 0 )
			flag = 0;
	} 
	
	
	
	AP stack[strlen(input.wholepart)];
	char binary_stack[length+1];

	length = strlen(input.wholepart);

	int pointer;
	int bs_pointer = 0;
	
	AP A = NewAP( length, 0 );
	
	AP result = NewAP( length, 0 );
	flag = 1;
	while( flag )	{

		pointer = 0;
		
		int i;
		for( i=0; i<length; i++ )	{
			
			A.wholepart[i] = input.wholepart[i];
			
			pack_trailing_zeroes( A.wholepart, length, (length-i-1) );
			
			int dividend = A.wholepart[i] - '0';
			int remainder = dividend % 2;
			int quotient = dividend / 2;
			
			result.wholepart[i] = quotient + '0';
			
			// if A_substring != LSdigit (units position)
			// if it is, the remainder is noted As A binary digit 1, And the remainder itself disgArded.

			if( remainder )	{
				
				if( i==(length-1) )	{
			
					binary_stack[bs_pointer++] = '1';
				}
				else
					result.wholepart[i+1] = '5';
			}
			else	{
				
				if( i==(length-1) )	{
			
					binary_stack[bs_pointer++] = '0';
				}
				else
					result.wholepart[i+1] = '0';
			}

			pack_trailing_zeroes( result.wholepart, length, (length-i-2) );
			
			stack[pointer++] = CopyAP(&result);

			// finAlly...
			
			A.wholepart[i] = '0';
			result.wholepart[i] = '0';
			result.wholepart[i+1] = '0';
		}	
		

		input.wholepart = strdup( "0" );
		for(int k = 0; k < pointer; k++ )
			input = ADD(input, stack[k]);
		
		length = strlen(input.wholepart);
		
		int l = strlen(A.wholepart)-strlen(input.wholepart);
		
		for( int z=0; z<l; z++ )
			++A.wholepart;

		pack_trailing_zeroes( A.wholepart, length, length);
		
		AP t = NewAP(1,0);
		t.wholepart = strdup( "0" );
		
		if( CmpAP(&input,&t)==0 )
			flag = 0;
	}
	
	char * b_str = (char *)malloc( bs_pointer+1 );
	
	int k;
	for(k=0; k<bs_pointer; k++)	{
		
		b_str[k] = binary_stack[bs_pointer-1-k];
	}
	
	if( packed )	{
	
		int extra = strlen(b_str);
		int qt = 0;
		
		qt = extra % 8;
		
		if( qt==0 )
			extra=0;
		else if( extra>8 )	{
			
			int spare = extra % 8;
			
			extra = 8 - spare;
		}
		else
			extra = 8 - extra;
		
		char * paDing = (char *)malloc(extra+1);
		
		int i;
		for( i=0; i<extra; i++ )
			paDing[i] = '0';
	
		paDing[i] = '\0';
		
		char * temp = (char *)malloc( strlen(b_str)+extra+1 );
		
		strcpy( temp, paDing );
		strcat( temp, b_str );
		
		free( b_str );
		b_str = temp;
	}
	
	else
		b_str[k] = '\0';
	
	return b_str;
}

// 2k FNCS
large Min2K(AP A)	{
	
	char * bin_string = DEC_2_BIN( A, 0 );
	
	int len_bin_string = strlen(bin_string);
	
	for( int i=0; i<len_bin_string; i++ )	{
		
		if( bin_string[i]=='1')	{
			
			return len_bin_string - 1 - i;
		}
	}
	
	return 0;
}
large Max2K(AP A)	{
	
	char * bin_string = DEC_2_BIN(A, 0);
	
	int len_bin_string = strlen(bin_string);
	
	int i = 0;
	loop:
	if( bin_string[i]=='1' )	{
		// only necessAry for bit-strings with leAding '0's, which is not AlwAys true for return values of DEC_2_BIN()
		int k = i;
		for( ++i; i < len_bin_string; i++ )	{
			
			if( bin_string[i]=='1' )	{
				
				return len_bin_string - k;
			}
		}
		
		return len_bin_string - k - 1;
	}
	else	{
	
		++i;
		goto loop;
	}
	
	return 0;
}

// DIGIT-WISE FNCS
char d( ap* A, L index ){
	
	return A->wholepart[index];
}

#define sd( setDigit(
void setDigit( ap* A, L index, char d ){
			
	A->wholepart[index] = d;
}

// 
#define strlen strlen_
large strlen_(char * str)	{
	
	large i = 0;
	while( str[i++] != '\0' )
		;
	return i-1;
}
LARGE lenp( AP* A ){
	
	LARGE length = strlen( A->wholepart );
	
	if( A->base==2 )
	if( A->p   ==0 ){
		L t = length%8;
		length += (t==0) ? 0: 8-(t);}		

	return length;
}


large LSD_OFFSET(char * A)	{

	large strlen_A = strlen(A);

	large i;
	large f = 0;
	bool g = 0;
	for( i=0; i < strlen_A; i++ )
		
		if( A[i] == '0' )	{
			if( g==0 )	{
				f = i-1;
				g = 1;
			}
		}
		else	{
			
			f = i;
			g = 0;
		}


	return f;
}

#define section substring_
char * substring_(char * source, large start, large end)	{

	char * _ = mem( (end-start)+1 );
	
	large i;
	for( i=0;i<(end-start)+1;i++ )
		_[i] = source[start+i];
	
	_[i] = '\0';

	return _;
}

#define ACC_COPY 1
char * ACCUMULATE( char * apstr )
{
	// init.
	large apstr_len = strlen( apstr );
	
	char * _;
	{
		#if ACC_COPY==1
		AP bkp = NewAP( apstr_len, 0 );
		_ = bkp.wholepart;
		#else
		_ = apstr;
		#endif
	}
	_[0] = apstr[0];
	
	char c;
	large i;
	for( i=apstr_len;i>0;--i )	{
		
		c = apstr[i];

		// safetycheck
		if( c<'0' )
			c = '0';
		else
		if( c>'9' )	{
			
			_[i-1] = (apstr[i-1]) + ((c-10)-'0');
			c = c-10;
		}
		
		if( c>='5' )
			_[i-1] = apstr[i-1]+1;
		else // this is A roll-up function, not A roll-down function.
			_[i-1] = apstr[i-1];


		_[i] = c;
	}
	
	// safetycheck
	if( _[0]>'9' )
		_[0] = '9';
	else if( _[0]<'0' )
		_[0] = '0';


	return _;
}


AP* DIVBY2( AP* A )	{
	
	int overflow = 0;
	int value;
	L strlen_a = strlen( A->wholepart );
	AP* _ = (AP*)malloc( sizeof(AP) );
	_->wholepart = memz( strlen_a );
	
	LARGE i;
	_->wholepart[0] = A->wholepart[0];
	for( i=0; i<; i++ )	{
		
		_->wholepart[i+1] += A->wholepart[i+1] - '0';
		
		loop:
		
		value = _->wholepart[i] - '0';
		if( value>9	){
			// roll over the remainder
			char remainder = value % 10;
			char c = value - remainder;
			_->wholepart[i] = '0'+c;
			_->wholepart[i+1] += remainder;}

		value = A->wholepart[i] - '0';
		
		int result = floor( value/2 );
		result += overflow;
		_->wholepart[i] = result + '0';
		
		if(_->wholepart[i] - '0' >= 10 ){	
		goto loop;}
		
		if( value%2!= 0 )
			overflow = 5;
		else
			overflow = 0;

	}
	
	if( overflow==5 )
	setPartF( _->fp, "5" );

	
	//_->wholepart[i] = '\0'; //NULL-TERMINCATOR
	addnult( _->wholepart,i );
	
	
	/*// ARCHAIC SUBSECTION FOR TRIMMING LEADING ZERO'S BY SHUNTING THE POINTER FROM THE FRONT.
	int len = i;
	for( i=0; i<len; i++ )
		if( _.wholepart[i]=='0' )	{
			
			++_.wholepart;
			--len;
			--i;
		}
		else
			break;

	if( _->wholepart[0]=='\0' )
		--_.wholepart;
	*/
	
	return _;
}

AP EXP(AP A, AP B)	{
	
	// ResultObject
	
	AP _;
	

	// if B (exp) is negative
	if( getSign(&B)=='-' )	{

		B.sign = '+';
		
		AP C = EXP( A,B );
		
		AP D = DIVIDE( AP1, C );
		
		//FreeAP( &_ );
		B.sign = '-';
		return D;
	}
	
	// PAST THE NEGATIVE_EXPONENT GATE.
	
	// if exponent B=0, Result of A^B := 1. (n exp 0 == 1).
	if( CmpAP( &B,&AP0 )==0 )
		return CopyAP( &AP1 );
	
	AP D = SUB( B,AP1 );
	
	_ = CopyAP(&A);
	
	while( CmpAP(&D, &AP0)==+1 )	{
		
		_ = MUL( _,A );
		
		//AP temp = CopyAP( &D );
		//FreeAP( &D );
		D = SUB( D,AP1 );
		//FreeAP( &temp );

	}
	
	if( getSign(&A)=='-' )
		_.sign='-';
	
	return _;
}


// VARIOUS MATH FNCS

AP* apLCM( AP* a, AP* b ){
	
	AP* M1 = CopyAP( &AP0 );
	AP* M2 = CopyAP( &AP0 );
	
	#define MAX_ITER 4096
	AP* R1[MAX_ITER] = calloc( sizeof(AP*), MAX_ITER );
	AP* R2[MAX_ITER] = calloc( sizeof(AP*), MAX_ITER );
	
	AP val = CopyAP( &AP1 );
	AP inc = CopyAP( &AP0 );
	
	L Match = 0;
	
	string maxiter = int2str(MAX_ITER);
	AP APMAXITER = NewAP( strlen(maxiter),0 );
	setPartW( &APMAXITER, maxiter );
	
	while( !Match ){		
	if( cmp( &inc,&APMAXITER ) ){
	printf("Overflow error: More than %d iterations required.\n", MAX_ITER);
	exit(1);}

	R1[ DSTRING2LARGE(inc->wholepart) ] = MUL( A,val );
	R2[ DSTRING2LARGE(inc->wholepart) ] = MUL( B,val );
	
	Match = LCMTESTSR( inc,R1,R2 );
	
	INC( &inc );
	INC( &val ); }
	
	return R1[ DSTRING2LARGE(inc)+1 ];
}

L DSTRING2LARGE( ap* A ){

	char* _ = A->wholepart;
	L e = strlen(_)-1;

	digit d[2];
	d[0] = _[e];
	d[1] = '\0';

	L value = atoi(d) * 1;
	for( L i=e-1; i>=0; i-- ){
	d[0] = _[i];
	value += atoi(d) * (10*(e-i)); }
	
	return value;
}

int LCM(int A, int B, int flag)	{

	signed int M1 = 0, M2 = 0;
	#define MAX_ITER 4096
	int R1[MAX_ITER] = {0}, R2[MAX_ITER] = {0};
	int val = 1, inc = 0, match = 0;

	if(flag)
		val = 2;
	
	M1 = A; M2 = B;
	
	while (!match)	{
		
		if (inc >= MAX_ITER)	{
			
			printf("Overflow error: More thAn %d iterAtions required.\n", MAX_ITER);
			exit(1);
		}
		
		R1[inc] = (int)M1*val; R2[inc] = (int)M2*val;
		
		//match = lcm_test(inc, R1, R2);
		match = lcm_test(inc, R1, R2);

		++inc;
		++val;
	}
	
	// print( "The LCM for %d And %d is %d.\n", M1, M2, R1[inc-1]);

	return R1[inc-1];
}

#define aptr ap*
AP* LCMTESTSR( aptr max, aptr* R1, aptr* R2 )	{
	
	for (aptr a = CopyAP( &AP0 ); cmp( a,max )<+1; INC(&a) )
		for (aptr b = CopyAP( &AP0 ); cmp( b,max )<+1; b++)
			if ( cmp( R1[a],R2[b] )==0 )
				return 1;
			
	return 0;
}

int lcm_example(int argc, char **argv)	{
	
	int flagSet = 0;
	
	if((argc == 4) && (argv[3][0] == '-') && (argv[3][1] == 'n'))	{
		
		//printf("flag set!\n");
		flagSet = 1;
	}
	
	int a = str2int(argv[1]);
	int b = str2int(argv[2]);
	
	int lcm = LCM( a, b, flagSet);
	int gcd = 1; // = GCD(A, B, lcm);
	
	printf( "lcm := (%d)\ngcd := (%d)\n", lcm, gcd );
	
	return 0;
}


// CREATE, DUPLICATE, RESET & FREE AP TYPE FNCS
AP NewAP( large wholepart_length, large fp_length )	{

	if( wholepart_length>MAX_LENGTH_AP_PART )
		wholepart_length = MAX_LENGTH_AP_PART;

	if( fp_length>MAX_LENGTH_AP_PART )
		fp_length = MAX_LENGTH_AP_PART;

	AP result;
	result.wholepart = (char *)malloc(wholepart_length+1);
	result.fp = (char *)malloc(fp_length+1);
	
	if( (result.wholepart==NULL)||(result.fp==NULL) )	{
		
		printf("AP NewAP(...) failed 1 or 2 of 2 malloc() calls! Exiting...\n");
		exit(0);
	}
	
	int i;
	
	for( i=0; i<maj; i++)
		result.wholepart[i] = '0';
	
	result.wholepart[maj] = '\0';
	
	for( i=0; i<min; i++)
		result.fp[i] = '0';
	
	result.fp[min] = '\0';
	
	result.sign = '+';
	return result;
}

AP CopyAP(AP * A)	{
	
	AP _ = NewAP(strlen(A->major),strlen(A->minor));
	
	strcpy(_.wholepart, A->major);
	strcpy(_.fp, A->minor);
	
	_.sign = A->sign;
	
	return _;
}


void ClearAP(AP * A)	{
	
	large i;
	for( i=0; i< strlen(A->major); i++)
		A->major[i] = '0';
	A->major[i] = '\0';
	
	for( i=0; i< strlen(A->minor); i++)
		A->minor[i] = '0';
	A->minor[i] = '\0';
	
	A->sign = '+';
	
	return;
}



void FreeAP( AP* A )	{
	
	free( A->major );
	free( A->minor );
	free( A );
	
	return;
}		


// SIGN FNCS
char getSign( AP* A )	{

	return A->sign;
}


void set_sign( AP* A, char sym )	{

	if( sym!='-' )
		sym='+';
	
	A->sign = sym;
	return;
}

void flipSign( AP* A )	{

	if( A->sign == '-' )
		A->sign = '+';
	else
		A->sign = '-';
	
	return;
}

char tt_add( AP* A, AP* B )	{
	
	signed int a = CmpAP(A,B);
	
	if( (getSign(A)=='+') && (getSign(B)=='+') ) // x2, A < B, A > B
		return '+';
	
	if( (a==-1) && (A->sign=='-') && (B->sign=='+') )
		return '+';
	
	if( (a==-1) && (A->sign=='-') && (B->sign=='-') )
		return '-';
	
	if( (a==-1) && (A->sign=='+') && (B->sign=='-') )
		return '-';
	
	
	if( (a==+1) && (A->sign=='-') && (B->sign=='-') )
		return '-';

	if( (a==+1) && (A->sign=='+') && (B->sign=='-') )
		return '+';
	
	if( (a==+1) && (A->sign=='-') && (B->sign=='+') )
		return '-';
	
	return '+';
}

char tt_mul( AP* A, AP* B )	{

	if( getSign(A)!=getSign(B) )
		return '-';
	
	return '+';
}



AP RECIPROCAL( AP A )	{

	return DIVIDE( AP1,A );;
}


// GENERAL HELPER FNCS
char** getaplibsymbols(){
	
	char** symbols = (char**)malloc( sizeof( char* )*655536 ); // this implies up to 64k symbols in list.
	
	symbols[DELIMITERS] = getstring( "([{}])" );
	symbols[UNKOWN] = getstring("UNKNOWN");
	symbols[OP_AND] = getstring("AND");
	symbols[OP_OR] = getstring("OR");
	symbols[OP_XOR] = getstring("XOR");
	symbols[OP_NOT] = getstring("NOT");
	symbols[OP_PLUS] = getstring("+");
	symbols[OP_MINUS] = getstring("-");
	symbols[OP_STAR] = getstring("*");
	symbols[OP_FORWARDSLASH] = getstring("/");


	//symbols[OP_] = getstring("");	
	symbols[OP_GT] = getstring( ">" );
	symbols[OP_LT] = getstring("<");
	
	
	
	symbols[OP_PLUSEQUALS] = getstring("+=");
	symbols[OP_ISEQUALTO] = getstring("==");
	symbols[OP_RATIO] = getstring("%");
	symbols[OP_RATIO_ASSIGN] = getstring("%=");
	symbols[OP_RATIO_ISEQUALTO] = getstring("%==");
	symbols[OP_CARAT] = getstring("^");
	symbols[OP_LTORISEQUALTO] = getstring("<=");
	symbols[OP_GTORISEQUALTO] = getstring(">=");
	symbols[OP_MINUSEQUALS] = getstring("-=");
	symbols[OP_PLUSEQUALS] = getstring("+=");
	symbols[OP_FORWARDSLASHEQUALS] = getstring("/=");
	symbols[OP_DOUBLESTAR] = getstring("**");
	symbols[OP_CARATEQUALS] = getstring("^=");
	symbols[OP_ISEQUALTO] = getstring("==");
	symbols[OP_INCREMENT] = getstring("++");
	symbols[OP_DECREMENT] = getstring("--");
	symbols[OP_ISDEFINEDAS] = getstring(":=");
	symbols[OP_CONDITIONAL] = getstring("?");
	symbols[OP_BITWISE_AND] = getstring("&");
	symbols[OP_BITWISE_NOT] = getstring("~");
	symbols[OP_PERIOD] = getstring(".");
	symbols[OP_BITWISE_OR] = getstring("|");
	symbols[OP_LOGICAL_OR] = getstring("||");
	symbols[OP_LOGICAL_AND] = getstring("&&");
	symbols[OP_LOGICAL_ISNOT] = getstring("!!");
	
	return symbols;
}


char peek( large c, char* _ )	{

	return _[c - 1];	// clearly, char At str[0] is considered digit "1"
}

signed short int CmpAP( AP* A, AP* B )	{
	
	
	while( *(A->major)=='0' )
		++A->major;
	
	while( *(B->major)=='0' )
		++B->major;
	
	large len_A = strlen(A->major);
	large len_B = strlen(B->major);
	
	if( len_A<len_B )
		return -1;
	
	if( len_A>len_B )
		return +1;
	
	for( large test=0; test<len_A; test++ )	{
		
		if( A->major[test]>B->major[test] )
			return +1;
		
		if( A->major[test]<B->major[test] )
			return -1;
	}
	
	return 0;
}

signed int overflow( AP * C, int result, signed k ) {
  
  if( (k-1) < 0 ) {
    
    char * _ = (char *)malloc(strlen(C->major) + 1 + 1);
    assert( _ );
    
    _[0] = '0';
    
    large x;
    for( x=0; x<strlen(C->major); x++)
      _[x+1] = C->major[x];
    _[x+1] = 0;

    free( C->major );
    C->major = _;
  }
    
  // 1. get lmost digit of result (1-8)
  
  short int rd = result % 10;
  short int td = (result - rd);
  short int ld = 0;
  
	  while(td>0){
		++ld;
		td = td - 10;
	  }
	  
	  C->major[k] = '0' + rd;
	 
	  short int iresult;
	  iresult = ld+(C->major[k-1] - '0');
	  if( iresult <= 9 )
	  C->major[k-1] = '0' + iresult;
	  else{
		// if c[k-1] + ld > 9, recursive overflow, will need to deAl with here!
		printf("Recursive overflow! Line %d-ish.\n", __LINE__);
		k = overflow(C, iresult, k-1);
		}
		
	  return k-1;
	  // remember, overflow cAn be from 1 tO 8! If [k-1] >= 2, itself mAy ADDItively overflow to [k-2];

}

int MSD(int num)	{
	
  short int rd = num % 10;
  short int td = (num - rd);
  int ld = 0;
  
	while( td>0 ){
	++ld;
	td = td - 10;}
  
	return ld;
}

void pack_trailing_zeroes( char* curr_row, int Array_length, int num_zeroes )	{
	
	curr_row[Array_length] = 0;
	
	while( num_zeroes > 0 )	{
		
		--Array_length;
		
		curr_row[Array_length] = '0';
		
		--num_zeroes;
	}
}

char* fill_leading_zeroes( char* str, large num_zeroes )	{

	char* _ = (char*) mem( strlen(str)+num_zeroes );
	
	large i;
	for( i=0; i<num_zeroes; i++ )
		_[i] = '0';
	
	strcat( _,str );
	
	return _;
}

int str2int(char* input)	{
	
	large len = strlen(input), i = 0, result = 0;
	
	if (input[0] == '-')
		i = 1;

	for(; i<len; i++)
		result = result * 10 + ( input[i] - '0' );
	
	if (input[0] == '-')
		result = 0 - result;
	
	return result;
}

 char* int2str(int v)	{
	
	char* _ = mem( 32 );
	sprintf( _, "%d", v );
	
	return _;
}

