// APLIB_C

#include "lib.h"
#include "stringy.h"
#include "colour.h"
#include "aplib.h"

#include "stringy.h"

AP AP0;
AP AP1;
APL DefaultPrecision;

struct _APLIB APLIB;

char* MUL_SYM = "*";
char* ADD_SYM = "+";
char* SUB_SYM = "-";
char* DIV_SYM = "/";
char* EXP_SYM = "e";
char* AND_SYM = "&";
char* NOT_SYM = "~";
char* OR_SYM =  "|";
char* XOR_SYM = "^";

char* POSITIVE_SYM = "+";
char* NEGATIVE_SYM = "-";
char* DELIMETER_SYM = ".";
char* BASE10_SYM = "0";
char* BASE2_SYM = "2";
char* BASE16_SYM = "H";
char* ALL_DIGITAL_SYMBOLS = "0123456789abcdefABCDEF.hHxX";

L MAX_LENGTH = 4096-1;

L setPartW( APL A, char * _ )	{

	return setPart( A, _, PartW );
}
L setPartF( APL A, char * _ )	{

	return setPart( A, _, PartF );
}

L setPart( APL A, char * digits, L part )	{

	if( part==SignPart )	{

		A->sign = *digits;
		
		if( A->sign==digits[0] )
		return SUCCESS;
		else
		return FAIL;
	}

	char * _;
	
	if( part==1 )
		_ = A->integer;
	else
		_ = A->fractional;
	
	if( _==NULL )	{
		_ = (char*)malloc(2);
		_[0] = '0';
	}
	if( strlen(_) < strlen(digits) )
		_ = (char *)realloc(_, strlen(digits)+1);

	
	large i;
	for( i=0; i<strlen(digits); i++ )
		_[i] = digits[i];
	
	_[i] = '\0';
	
	return i;
}


L DIVBY2_PRINT_ROWS = 1;


APL RESET0( APL A ) { setPartW( A,AP0->integer ); setPartF( A,AP0->integer ); A->sign='+'; return A; }
APL RESET1( APL A ) { setPartW( A,AP1->integer ); setPartF( A,AP1->integer ); A->sign='-'; return A; }

// CORE BOOLEAN OPERATORS
APL AND( APL LHS, APL RHS )	{
	
	char* A = LHS->integer;
	char* B = RHS->integer;
	
	L strlen_a = strlen( A );
	L strlen_b = strlen( B );
	L len = ( strlen_a >= strlen_b ? strlen_a : strlen_b );
	
	char* bstr = (char*)malloc( len+1 );
	bstr[len] = '\0';

	// both binary strings are the same length.
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
APL NOT(APL v)	{
	
	
	APLS _v = v->integer;
	L strlen_v = strlen( _v );
	register char* _ = (char*)malloc( strlen_v+1 );
	LARGE i;
	for( i=0; i<strlen_v; i++ )
		if( _v[i]=='0' )
			_[i] = '1';
		else if(
		_v[i]=='1')
		_[i] = '0';
		else
		assert(0);
		
	_[i] = '\0';
	
	APL _2 = (APL)malloc( sizeof( APP ) );
	_2->integer = _;
	return _2;
}
APL OR( APL LHS, APL RHS)	{

	char * A;
	char * B;
	
	A = LHS->integer; B = RHS->integer;
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
	
	APL _b = NewAPr( 0,0 );
	
	_b->integer = b_str;
	
	return _b;
}
APL XOR( APL LHS, APL RHS )	{

	char* A = LHS->integer;
	char* B = RHS->integer;
	
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
	
	APL _ = (APL)malloc( sizeof(APP) );
	_->integer = bstr;
	return _;
}

// CORE ARITHMETIC OPERATORS
APL ADD( APL A, APL B )	{ return ADDP( A, B, DefaultPrecision ); }
APL ADDP( APL A, APL B, AP P )	{
	
	
	
	int flag = 0;
	
	large strlen_a = strlen(A->integer);
	large strlen_b = strlen(B->integer);
	large size = ( strlen_b > strlen_a ? strlen_b : strlen_a );
	APL C = NewAPr( size+1,0 );

	scint value;
	scint valA, valB, valC;
	
	signed int i, j, k;
	
	if( getSign(A) == getSign(B) )	{
		
		for( i=strlen_a-1, j=strlen_b-1, k=size; k>0; i--, j--, k--)	{
		
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

				
			value = valA + valB;

			if( value>=10 )	{
				
				value -= 10;
				C->integer[k-1] += 1;
			}
			
			//C->integer[k] = '0' + value;
			
			setDigit( C,k,('0'+value) );

		}
	}
	else	{
		
	//SubtrAct the smAller Absolute value from the lArger Absolute value And give the Answer the sAme sign As the number with the lArger Absolute value
		char tsign;
		if( CmpAP_abs(A,B)==-1 )	{
			
			tsign = B->sign;
			
			AP temp;
			temp = A;
			A = B;
			B = temp;
		}
		else
			tsign = A->sign;
		
		A->sign = '+';
		C->sign = '+';
		C = SUB( A,B );
		C->sign = tsign;
		flag = 1;
	}
	
	
	if( ( TT_ADD( A,B )=='-' ) && (flag==0) )
		C->sign = '-';

	
	register char * _ = (char *)malloc(strlen(C->integer)+1);
	strcpy(_, C->integer);
	for( i=0; i<(int)strlen(_); i++ )
		if( _[i] == '0' )
			++C->integer;
		else
			break;
	
	free( _ );
	
	if( *C->integer == '\0' )
		--C->integer;
	
	return C;
}
AP SUB( APL A, APL B )	{ return SUBP( A, B, DefaultPrecision ); }
APL SUBP( APL A, APL B, AP P )	{
	

	if( (A->sign=='+') && (B->sign=='+') && (CmpAP_abs(A,B)>=1) ){

		int i, j, k, valA, valB, valC;
		APL C = NewAPr(strlen(A->integer),0);
		for( i=strlen(A->integer)-1, j=strlen(B->integer)-1, k=strlen(C->integer)-1; k>0; i--, j--, k--){
		
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
			C->integer[k] = '0' + value; }
		
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
	APL result = ADD(A, B);
	flipSign(B);

	return result;
}
AP MUL( APL A, APL B )	{ return MULP( A, B, DefaultPrecision ); }
AP MULP( APL A, APL B, APL P )  {

	int MAX_NUM_MUL_ROWS = ( strlen(A->integer)>strlen(B->integer) ? strlen(A->integer) : strlen(B->integer) );
	
	char ** ResultArray = (char **)calloc(MAX_NUM_MUL_ROWS, sizeof(char *));
	int q = 0;

	for( int k = strlen(B->integer)-1; k>=0; k-- )	{

		int rev_offset_B = strlen(B->integer) - 1 - k;
		
		int curr_row_length = strlen(A->integer) + 1 + rev_offset_B;
		char * curr_row = (char *)malloc( curr_row_length + 1 );
		curr_row[ curr_row_length ] = '\0';
		PackTrailingZeroes( curr_row, curr_row_length, rev_offset_B );
		
		int prev_overflow = 0;
		
		int p = curr_row_length - 1 - rev_offset_B;
		
		for( int i = strlen(A->integer)-1; i>=0; i-- )	{
			
			int _A = A->integer[i] - '0';
			int _B = B->integer[k] - '0';
			
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
		
		free( D->integer );
		
		D->integer = strdup(result_row);
		
		APL _ = (APL)malloc( sizeof( APP ) );
		*_ = *C;
		free( C->fractional	);
		free ( C );
		
		C = ADD( _,D );
		FreeAP( _ );
	}
	
	C->sign = TT_MUL( A,B );
	return C;
}
AP DIV( APL A, APL B )	{

	return DIVP( A, B, DefaultPrecision );
}
AP DIVP( APL A, APL B, APL P )  {

	int fractional = 0;
	int L0 = 1;
	
	//char * integer;
	//char * fractional;
	
	AP C = NewAP(0, 0);
	large offset = strlen(B->integer) - 1;
	AP Remainder = NewAP( strlen(B->integer) , 0 );
	
	large i;
	for(i=0;i<strlen(B->integer);i++)
		Remainder->integer[i] = A->integer[i];
	
	Remainder->integer[i] = '\0';
	
	AP Dropdown = NewAP(1, 0);
	
	AP v = NewAP(1, 0); v->integer[0] = '0';
	AP inc = NewAP(1, 0); inc->integer[0] = '1';
	
	AP temp;
	AP v2;
	AP result;
	large strlen_A = strlen(A->integer);
	//large strlen_minor_A = LSD_OFFSET(A.fractional);
	
	if( strlen(A->integer)>strlen(B->integer) )
		Dropdown->integer[0] = A->integer[offset+1];
	else
		Dropdown->integer[0] = '0';
	
	
	int LOOPS = 0;
	
	int MAX_LOOPS = 100;

	//int count = 0;
	loop:
	while( offset<strlen_A )	{
		
		++LOOPS;
		if( LOOPS>MAX_LOOPS )
			goto maxiterations;
		
		v->integer[0] = '0';
		
		temp = MUL( B,v );
		while( CmpAP_abs( temp,Remainder ) < 1 )	{
			
			v2 = ADD(v, inc);
			free( v->integer );
			v = CopyAP(v2);
			free( v2->integer );
			
			free( temp->integer );
			temp = MUL( B,v );
		}
		
		v2 = SUB(v, inc);
		free( v->integer );
		v = CopyAP(v2);
		free( v2->integer );
		
		result = MUL( B,v );
		v2 = SUB(Remainder, result);
		free( result->integer );
		free( Remainder->integer );
		Remainder = CopyAP(v2);
		free( v2->integer );

		
		#define CONCAT(__A,__B) strcat(__A->integer, __B->integer)
		
		//printf( "Row %d:\t'%s' + '%s'\n", count, C->integer, v->integer );
		//++count;
		CONCAT( C,v );
		
		if( !fractional )
			if( L0==1 )	{

				if( v->integer[0]=='0' )	{
					
						++C->integer;
				}
				else
					L0=0;
			}
		
		if( Remainder->integer[0] > '0' )
			CONCAT( Remainder,Dropdown );
		else	
		if( offset != (strlen(B->integer)-1) )
			Remainder->integer[0] = Dropdown->integer[0];

		if( fractional )	{
			
			if( CmpAP_abs( Remainder,AP0 ) == 0 )	{
				break;
			}
		}
		else	{

			if( (offset+1)<strlen_A )
				
				Dropdown->integer[0] = A->integer[offset+1];
			else
				Dropdown->integer[0] = '0';
		}

		++offset;
	}
	
	
	// fractional overflow
	
	if( fractional==0 )	{
		
		fractional = 1;

		if( CmpAP_abs( C,AP0 )==0 )
			--C->integer;
		
		//integer = strdup( C->integer );
	}
	
	offset = 0;
	Dropdown->integer[0] = '0';
	
	if( CmpAP_abs( Remainder,AP0 ) == 1 )
		goto loop;
	
	maxiterations: // Upper-bound for precision of calculation reached.
	// RESULT COMPUTED.
	
	//printf( "The fixed-point for the Answer is positioned to the right of digit %d.\n", (int) strlen_A-1 );
	
	for( i=0; i<(strlen_A-1); i++ )
		printf( "%c", C->integer[i] );
	
	printf( "." );
	
	for( ; i<strlen(C->integer); i++ )	
		printf( "%c", C->integer[i] );
	
	NL;
	
	printf( "\n\nSystem paused. Press any (sensible) key to continue..." );
	pause();
	
	return C;
}


char poke( char* in, char* out, L offset ) {
	
	L c = 0;
	do {
	out[offset++] = in[c++];
	}while(in[c] != '\0');
	
	return in[--c];
}

void setSign( APL A,char S ){

	if( S!='+' ){
		if( S!='-' )
		A->sign='+';}
	else
		A->sign = S;
}


APL RECIPROCAL2( APL A, APL B ){
	
	return RECIPROCAL2P( A,B,DefaultPrecision );
}
APL RECIPROCALP( APL A, APL DefaultPrecision ){
	
	return DIV( AP1,A ); 
}

APL RECIPROCAL2P( APL A,APL B,APL ){
	
	return DIV( B,A );
}

// BASE CONVERSION FNCS
char * BIN_2_DEC(char * bin)	{ /** Converts base2 (binary) string to base10 (decimal) string.

*/

	AP dec = NewAP( strlen(bin)+1, 0 );
	AP mult = NewAP( strlen(bin)+1, 0 );
	
	AP digit = NewAP(1, 0);
	
	AP _2 = NewAP(1, 0);
	AP _j = NewAP(10, 0);
	
	_2->integer[0] = '2';

	int i, j;
	
	for( i=0, j=strlen(bin)-1; i<strlen(bin); i++, j-- )	{

		digit->integer[0] = bin[i];
		
		sprintf(_j->integer, "%d", j); // itoa()
		mult = EXP( _2, _j );
		dec = ADD( dec, MUL(digit, mult) );
	}
	
	FreeAP( mult );
	FreeAP( digit );
	FreeAP( _2 );
	FreeAP( _j );
	
	char * result = (char *)malloc( strlen(dec->integer)+1 );
	result = strdup( dec->integer );

	FreeAP( dec );
	
	return result;
}
char * DEC_2_BIN(char*  input, L packed)	{
/**
PArAm "int packed" is A flag to determine if the returned binary string should be rounded in length to A multiple of 8.
In other words, 127 would be "01111111" insteAd of "1111111". An Argument of 0 meAns "do not round", A non-0 value meAns "round up string-length to multiple of 8".
*/

	L length = 0;
	int flag = 1;

	AP t = CopyAP( AP0 );
	
	AP Check = NewAPr( 0,0 );
	free( Check->integer );
	Check->integer = getstring( input );
	
	while ( flag )	{
		
		APL temp;
		temp = DIVBY2( Check );
		temp->fractional = getstring( "0" );
		FreeAP( Check );
		
		Check = CopyAP( temp );
		free( temp );
		
		if( DIVBY2_PRINT_ROWS==1 )
			printf( "\t%c%s\n", Check->sign, Check->integer );
			
		++length;
		
		if( CmpAP_abs(Check,t)<= 0 )
			flag = 0;
	} 
	
	const L strlen_input = strlen(input);
	AP* stack = (AP*)calloc( sizeof(AP), strlen_input );
	char binary_stack = (char*)calloc( length+1, 1 );

	length = (L)strlen(input);

	int pointer;
	int bs_pointer = 0;
	
	AP A = NewAP( length, 0 );
	
	AP result = NewAP( length, 0 );
	flag = 1;
	while( flag )	{

		pointer = 0;
		
		L i;
		for( i=0; i<length; i++ )	{
			
			A->integer[i] = input[i];
			
			PackTrailingZeroes( A->integer, length, (length-i-1) );
			
			int dividend = A->integer[i] - '0';
			int remainder = dividend % 2;
			int quotient = dividend / 2;
			
			result->integer[i] = quotient + '0';
			
			// if a_substring != LSdigit (units position)
			// if it is, the remainder is noted As A binary digit 1, And the remainder itself disgArded.

			if( remainder )	{
				
				if( i==(length-1) )	{
			
					binary_stack[bs_pointer++] = '1';
				}
				else
					result->integer[i+1] = '5';
			}
			else	{
				
				if( i==(length-1) )	{
			
					binary_stack[bs_pointer++] = '0';
				}
				else
					result->integer[i+1] = '0';
			}

			if( result->fractional==NULL ){
			
				AP __ = CopyAP( AP0 );
				result->fractional = getstring( __->integer );
				free( __ );
			}

			PackTrailingZeroes( result->integer, length, (length-i-1) );
			
			stack[pointer++] = CopyAP(result);

			// finally...
			
			A->integer[i] = '0';
			result->integer[i] = '0';
			result->integer[i+1] = '0';
		}	
		

		input[0] = '0';
		AP input2 = NewAPr( 0,0 );
		free( input2->integer );
		input2->integer = getstring( input );
		
		AP input3;
		
		for(int k = 0; k < pointer; k++ )	{
			
			if( stack[k]->(&integer)<10000 )
				stack[k] = CopyAP( AP0 );
			
			input3 = ADD(input2, stack[k]);
			FreeAP( input2 );
			input2 = CopyAP( input3 );
			FreeAP( input3 );
		}
		
		free( input );
		input = getstring( input2->integer );
		
		
		length = strlen(input);
		
		int l = strlen(A->integer)-strlen(input);
		
		for( int z=0; z<l; z++ )
				++A->integer;

		PackTrailingZeroes( A->integer, length, length);
		
		AP t = NewAP(1,0);
		t->integer[0] = '0';
		
		if( CmpAP_abs(input2,t)==0 )
			flag = 0;
		
		FreeAP( input2 );
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
		
		char * padding = (char *)malloc(extra+1);
		
		int i;
		for( i=0; i<extra; i++ )
			padding[i] = '0';
	
		padding[i] = '\0';
		
		char * temp = (char *)malloc( strlen(b_str)+extra+1 );
		
		strcpy( temp, padding );
		strcat( temp, b_str );
		
		free( b_str );
		b_str = temp;
	}
	
	else
		b_str[k] = '\0';
	
	return b_str;
}

// 2k FNCS
L Min2K(AP A)	{
	
	char * bin_string = DEC_2_BIN( A->integer, 0 );
	
	int len_bin_string = strlen(bin_string);
	
	for( int i=0; i<len_bin_string; i++ )	{
		
		if( bin_string[i]=='1')	{
			
			return len_bin_string - 1 - i;
		}
	}
	
	return 0;
}
L Max2K(AP A)	{
	
	char * bin_string = DEC_2_BIN(A->integer, 0);
	
	int len_bin_string = strlen(bin_string);
	
	int i = 0;
	loop:
	if( bin_string[i]=='1' )	{
		// only necessary because of bit-strings with leading '0's, which is not always true for return values of DEC_2_BIN()
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

#define strlen strlen_
large strlen_(char * str)	{
	
	large i = 0;
	while( str[i++] != '\0' )
		;
	return i-1;
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


#define ASCII '0'
APL DIVBY2( APL A )	{
		
	int overflow = 0;
	int value;
	L strlen_a = strlen( A->integer );
	APL _ = (APL)malloc( sizeof(APP) );
	_->integer = zmem( strlen_a );
	_->fractional = getstring( "0" );
	LARGE i;
	_->integer[0] = A->integer[0];
	for( i=0; i<strlen_a; i++ ) {
	
		if( i<strlen_a-1 )
			_->integer[i+1] += (A->integer[i+1] - '0');

		loop:

		value = _->integer[i] - '0';
		
		if( value>9	)	{
		
			// roll over the remainder
			char remainder = value % 10;
			char c = value - remainder;
			_->integer[i] = '0'+c;
			
			if( i<strlen_a-1 )
				_->integer[i+1] += remainder;
		}

		value = A->integer[i] - '0';
#
		// value>>1 (value/2)
		int result = floor( value/2 );
		result += overflow;
		_->integer[i] = result + '0';

		if(_->integer[i] - '0' >= 10 )
			goto loop;

		if( value%2!= 0 )	{
			
			overflow = 5;
		}
		else{
			
			overflow = 0;
		}

	}
	
	
	_->sign = A->sign;

	//_->integer[i] = '\0'; //NULL-TERMINCATOR
	addnult( _->integer,i );
		
		/*// ARCHAIC SUBSECTION FOR TRIMMING LEADING ZERO'S BY SHUNTING THE POINTER FROM THE FRONT.
		int len = i;
		for( i=0; i<len; i++ )
			if( _.integer[i]=='0' )	{
				
				++_.integer;
				--len;
				--i;
			}
			else
				break;

		if( _->integer[0]=='\0' )
			--_.integer;
		*/
		
	return _;
}
#undef ASCII


// VARIOUS MATH FNCS
L DSTRING2LARGE( APL A ){

char* _ = A->integer;
L e = strlen(_)-1;

char* d = (char*)malloc( 2 );
d[0] = _[e];
d[1] = '\0';

L value = atoi(d) * 1;
for( L i=e-1; i>=0; i-- ){
d[0] = _[i];
value += atoi(d) * (10*(e-i)); }

return value;}

/*
APL APLCM( APL A, APL B ){
	
	APL M1 = CopyAP( AP0 );
	APL M2 = CopyAP( AP0 );
	
	#define MAX_ITER 4096
	// It is APL pointers stored in the memory, because it is pointers allocated by the Operator functions that are passed.
	APL R1[MAX_ITER] = (APL)calloc( sizeof(APL), MAX_ITER );
	APL R2[MAX_ITER] = (APL)calloc( sizeof(APL), MAX_ITER );
	
	AP val = CopyAP( AP1 );
	AP inc = CopyAP( AP0 );
	
	AP Match = CopyAP( AP0 );
	
	string maxiter = int2str(MAX_ITER);
	AP APMAXITER = NewAP( strlen(maxiter),0 );
	setPartW( APMAXITER, maxiter );
	
	while( !CmpAP_abs(Match,AP0) ){		
	if( CmpAP_abs( inc,APMAXITER ) ){
	printf("Overflow error: More than %d iterations required.\n", MAX_ITER);
	exit(1);}

	R1[ DSTRING2LARGE(inc) ] = MUL( A,val );
	R2[ DSTRING2LARGE(inc) ] = MUL( B,val );
	
	Match = LCMTESTSTR( inc,R1,R2 );
	
	INC( inc );
	INC( val ); }
	
	return R1[ DSTRING2LARGE(inc)+1 ];
}
*/

APL NewAPr( large integer_range, large fractional_range )	{

	APL _ = (APL)malloc( sizeof(AP) );
	_ = NewAP( integer_range,fractional_range );
	return _;
}

// CREATE, DUPLICATE, RESET & FREE AP TYPE FNCS
AP NewAP( large integer_length, large fractional_length )	{

	if( integer_length>MAX_LENGTH_AP_PART )
		integer_length = MAX_LENGTH_AP_PART;

	if( fractional_length>MAX_LENGTH_AP_PART )
		fractional_length = MAX_LENGTH_AP_PART;

	AP result = (AP)malloc( sizeof( APP ) );
	result->integer = (char *)malloc(integer_length+1);
	result->fractional = (char *)malloc(fractional_length+1);
	
	if( (result->integer==NULL)||(result->fractional==NULL) )	{
		
		printf("AP NewAP(...) failed 1 or 2 of 2 malloc() calls! Exiting...\n");
		exit(0);
	}
	
	int i;
	
	for( i=0; i<integer_length; i++)
		result->integer[i] = '0';
	
	result->integer[integer_length] = '\0';
	
	for( i=0; i<fractional_length; i++)
		result->fractional[i] = '0';
	
	result->fractional[fractional_length] = '\0';
	
	result->sign = '+';
	return result;
}

AP CopyAP(AP A)	{
	
	AP _ = NewAP(strlen(A->integer),strlen(A->fractional));
	
	strcpy(_->integer, A->integer);
	strcpy(_->fractional, A->fractional);
	
	if( A->sign )
	_->sign = A->sign;
	else
	_->sign = '+';
	
	return _;
}


void ClearAP(AP A)	{
	
	large i;
	for( i=0; i< strlen(A->integer); i++)
		A->integer[i] = '0';
	A->integer[i] = '\0';
	
	for( i=0; i< strlen(A->integer); i++)
		A->integer[i] = '0';
	A->integer[i] = '\0';
	
	A->sign = '+';
	
	return;
}


void FreeAP( APL A )	{
	
	free( A->integer );
	free( A->fractional );
	free( A );
	
	return;
}		


// SIGN FNCS
char getSign( APL A )	{

	return A->sign;
}


void set_sign( APL A, char sym )	{

	if( sym!='-' )
		sym='+';
	
	A->sign = sym;
	return;
}


void flipSign( APL A )	{

	if( A->sign == '-' )
		A->sign = '+';
	else
		A->sign = '-';
	
	return;
}

char TT_ADD( APL A, APL B )	{
	
	signed int a = CmpAP_abs(A,B);
	
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

char TT_MUL( APL A, APL B )	{

	if( getSign(A)!=getSign(B) )
		return '-';
	
	return '+';
}



AP RECIPROCAL( AP A )	{

	return RECIPROCALP( A,DefaultPrecision );;
}


// GENERAL HELPER FNCS
char** getaplibsymbols(){
	
char** symbols = (char**)malloc( sizeof( char* )*655536 ); // this implies up to 64k symbols in list.

symbols[DELIMITERS] = getstring( "([{}])" );
symbols[OP_UNKNOWN] = getstring("UNKNOWN");
//symbols[OP_] = getstring("");	
symbols[OP_AND] = getstring("AND");
symbols[OP_OR] = getstring("OR");
symbols[OP_XOR] = getstring("XOR");
symbols[OP_NOT] = getstring("NOT");
symbols[OP_PLUS] = getstring("+");
symbols[OP_MINUS] = getstring("-");
symbols[OP_STAR] = getstring("*");
symbols[OP_FORWARDSLASH] = getstring("/");

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

return symbols; }

int INC( AP A ){

AP _;
_ = ADD( A,AP1 );
free( A );
A = _;

return 1; }
int DEC( AP A ){

AP _;
_ = SUB( A,AP1 );
free( A );
A = _;

return -1; }

scint CmpAP_abs_ws( APL A, APL B )	{
	
	if( A->sign=='+' && B->sign=='-' ) return  1;
	if( A->sign=='-' && B->sign=='+' ) return -1;

	APP copy_A, copy_B;	
	copy_A.integer = A->integer;
	copy_B.integer = B->integer;

	large i;
	i=0;
	while( *(A->integer[i++])=='0' )
		++copy_A.integer;
	
	i=0;
	while( *(B->integer[i++])=='0' )
		++copy_B.integer;
	
	large len_A = strlen(copy_A.integer);
	large len_B = strlen(copy_B.integer);

	if( len_A>len_B )	return +1;	
	if( len_A<len_B )	return -1;

	for( large test=0; test<len_A; test++ )	{
		
		if( (copy_A.integer[test]) > (copy B.integer[test]) )	return +1;
		if( (copy_A.integer[test]) < (copy_B.integer[test]) )	return -1;
	}
	
	return +0;
}


signed int OverFlow( AP C, int result, signed k ) {
  
  if( (k-1) < 0 ) {
    
    char * _ = (char *)malloc(strlen(C->integer) + 1 + 1);
    assert( _ );
    
    _[0] = '0';
    
    large x;
    for( x=0; x<strlen(C->integer); x++)
      _[x+1] = C->integer[x];
    _[x+1] = 0;

    free( C->integer );
    C->integer = _;
  }
    
  // 1. get lmost digit of result (1-8)
  
  scint rd = result % 10;
  scint td = (result - rd);
  scint ld = 0;
  
	  while(td>0){
		++ld;
		td = td - 10;
	  }
	  
	  C->integer[k] = '0' + rd;
	 
	  scint iresult;
	  iresult = ld+(C->integer[k-1] - '0');
	  if( iresult <= 9 )
	  C->integer[k-1] = '0' + iresult;
	  else{
		// if c[k-1] + ld > 9, recursive overflow, will need to deAl with here!
		printf("Recursive overflow! Line %d-ish.\n", __LINE__);
		k = OverFlow(C, iresult, k-1);
		}
		
	  return k-1;
	  // remember, overflow can be from 1 to 8! If [k-1] >= 2, itself may additively overflow to [k-2];

}

L MSD(int num)	{
	
  scint rd = num % 10;
  scint td = (num - rd);
  int ld = 0;
  
	while( td>0 ){
	++ld;
	td = td - 10;}
  
	return ld;
}

void PackTrailingZeroes( char* curr_row, L length, L num_zeroes )	{

	if( num_zeroes>length )
		num_zeroes=length;
	while( num_zeroes-- )
		curr_row[--length] = '0';
}


char* fill_leading_zeroes( char* str, large num_zeroes )	{

	char* _ = (char*) mem( strlen(str)+num_zeroes );
	
	large i;
	for( i=0; i<num_zeroes; i++ )
		_[i] = '0';
	
	strcat( _,str );
	
	return _;
}
