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
APL NAND( APL LHS, APL RHS )	{
	
	APL C = AND( LHS,RHS );
	APL _ = NOT( C );
	free( C );
	
	return _;
}

// NOP (No-Operation). It returns an AP, or AP0, value.
APL NOP( APL A ){

	return CopyAP( A );
}

// CORE ARITHMETIC OPERATORS

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

APL ADD( APL A, APL B )	{ return ADDP( A, B, DefaultPrecision ); }
APL ADDP( APL A, APL B, AP P )	{
	
	signed sign_A = getSign(A)=='+' ? +1 : -1;
	signed sign_B = getSign(B)=='+' ? +1 : -1;
	int flag = 0;
	
	large strlen_a = strlen(A->integer);
	large strlen_b = strlen(B->integer);

	int AorB = CmpAP_abs( A,B );

	large size = ( !AorB ? strlen_b : strlen_a );
	APL C = NewAPr( size+1,0 );

	signed value;
	signed valA, valB, valC;
	
	APL temp;

	if( !AorB )	{

		temp = B;
		B = A;
		A = temp;
	}

	signed int i, j, k;
		
	for( i=strlen_a-1, j=strlen_b-1, k=size; k>0; i--, j--, k--)	{
	
		if(i>=0)
			valA = A->integer[i] - '0';
		else
			valA = 0;
		
		valA *= sign_A;

		if(j>=0)
			valB = B->integer[j] - '0';
		else
			valB = 0;

		valB *= sign_B;
		
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

	/**
	else	{
		
	//Subtract the smaller absolute value from the larger absolute value and give the answer the same sign as the number with the larger absolute value
		char tsign;
		char asign = A->sign;
		char bsign = B->sign;

		char AorB = CmpAP_abs(A,B);
		if( AorB==-1 )
			tsign = bsign;
		else
			tsign = asign;
		
		A->sign = '+';
		B->sign = '+';

		C = ( AorB>-1 ? SUB( A,B ) : SUB( B,A ) );
		C->sign = tsign;

		A->sign = asign;
		B->sign = bsign;
	}
	*/

	/*
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
	*/

	if( !AorB )	{

		temp = B;
		B = A;
		A = temp;
	}

	if( CmpAP_signed( A, B ) )

	return C;
}
AP SUB( APL A, APL B )	{ return SUBP( A, B, DefaultPrecision ); }
AP SUBP( APL A, APL B, AP P )	{

	// Alt. SUB Algorithm:
	// The subtraction of a real number (the subtrahend [B]) from another (the minuend [A]) can be defined as the addition of the minuend [A] and the additive inverse of the subtrahend [B].
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

	AP C = NewAP(0, 0);
	char* Cc = C->integer;
	large offset = strlen(B->integer) - 1;
	AP Remainder = NewAP( strlen(B->integer) , 0 );
	
	large i;
	for(i=0;i<strlen(B->integer);i++)
		Remainder->integer[i] = A->integer[i];
	
	Remainder->integer[i] = '\0';
	
	AP Dropdown = CopyAP( AP0 );
	
	AP v = CopyAP( AP0 );
	AP inc = CopyAP( AP1 );
	
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
	
	int MAX_LOOPS = 50;

	//int count = 0;
	
	int loopCount = strlen_A;
	loop:
	while( offset<loopCount )	{
		
		++LOOPS;
		if( LOOPS>MAX_LOOPS )
			goto maxiterations;
		
		v->integer[0] = '1';
		
		temp = MUL( B,v );
		while( CmpAP_abs( temp,Remainder ) < 1 )	{
			
			FreeAP( temp );
			
			v2 = ADD(v, inc);
			FreeAP( v );
			v = CopyAP(v2);
			FreeAP( v2 );

			temp = MUL( B,v );
		}
		FreeAP( temp );
		 
		v2 = SUB(v, inc);
		FreeAP( v );
		v = CopyAP(v2);
		FreeAP( v2 );
		
		result = MUL( B,v );
		
//		if( cmp_dstr( result->integer,Remainder->integer )>0 ) ;
		
		v2 = SUB(Remainder, result);
		FreeAP( result );
		FreeAP( Remainder );
		Remainder = CopyAP(v2);
		FreeAP( v2 );

		#define CONCAT(__A,__B) strcat(__A, __B)
		
		//printf( "Row %d:\t'%s' + '%s'\n", count, C->integer, v->integer );
		//++count;
		CONCAT( Cc,v->integer );

		if( fractional )	{
			Dropdown->integer[0] = '0';
		}
		
		if( !fractional )	{

			if( (offset+1)<strlen_A )
				Dropdown->integer[0] = A->integer[offset+1];
			else	{
				Dropdown->integer[0] = '0';
			}
		}
		
		CONCAT( Remainder->integer,Dropdown->integer );
		
		
		//if( fractional && !CmpAP_abs(Remainder,AP0) )
		//	break;

/*
		#define report printf
		int r;
		if( (r = cmp_dstr( Remainder->integer, B->integer )) >=0 )	{
			
			report( "Remainder = %s\nDivisor = %s\nLOOPS = %d\nC = %s.%s\n", Remainder->integer, B->integer ,LOOPS, C->integer, C->fractional );
			fflush( stdout );
			char ch;
			if( (ch = getchar())=='q' )
				exit(0);
		}
*/
		++offset;
	}
	
	
	// fractional overflow
	if( !fractional )	{
		
		if( CmpAP_abs( Remainder, AP0 )!=0 )	{

			fractional = 1;
			Cc[ strlen(Cc) ] = '\0';
			Cc = C->fractional;
			//offset = 0;
			loopCount = MAX_LOOPS+1;
			goto loop;
		}
	}
	
	maxiterations: // Upper-bound for precision of calculation reached.
	// RESULT COMPUTED.
	Cc[ strlen(Cc) ] = '\0';
	
	if( cmp_dstr( C->integer, AP0->integer ) )
		printf( "%s", C->integer );
	else
		printf( "0" );
	
	if( cmp_dstr( C->fractional, AP0->integer ) )
		printf( ".%s", C->fractional );
	NL;


	/**
	for( i=0; i<strlen_A; i++ )
		printf( "%c", C->integer[i] );
	
	printf( "." );
	
	for( ; i<strlen(C->integer); i++ )	
		printf( "%c", C->integer[i] );
	*/
	NL;

	//printf( "\n\nSystem paused. Press any (sensible) key to continue..." );
	//pause();
	
	return C;
}


// SKELETON FNC'S FOR FUTURE OPERATO
AP CROSS( AP A, AP B )	{

	return CROSSP( A, B, DefaultPrecision );
}
AP CROSSP( AP A, AP B, AP P )	{
	
	return CopyAP( AP1 );
}
AP DOT( AP A, AP B )	{

	return DOTP( A, B, DefaultPrecision );
}
AP DOTP( AP A, AP B, AP P )	{

	return CopyAP( AP1 );
}

char poke( char* in, char* out, L offset ) {
	
	L c = 0;
	do {
	out[offset++] = in[c++];
	}while(in[c] != '\0');
	
	return in[--c];
}


APL RESET0( APL A ) { setPartW( A,AP0->integer ); setPartF( A,AP0->integer ); return A; }
APL RESET1( APL A ) { setPartW( A,AP1->integer ); setPartF( A,AP0->integer ); return A; }


struct _APLIB* Init_APLIB(){
	
	// Initialise
	AP0 = NewAP( 1,0 );
	AP0->integer[0] = '0';
	AP1 = NewAP( 1,0 );
	AP1->integer[0] = '1';
	DefaultPrecision = AP0; // Sets default precision to indicate the length of the largest string between the 2 operands.

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
	APLIB->RECIPROCAL2P = RECIPROCAL2P;
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

	APLIB->DSTRING2LARGE = DSTRING2LARGE;


	APLIB->RESET0 = RESET0;
	APLIB->RESET1 = RESET1;

	// Add the 'sign' helpers.
	APLIB->flipSign = flipSign;
	APLIB->getSign = getSign;
	APLIB->setSign = setSign;
	

	APLIB->ANSI = ANSI;
	//APLIB->ANSI->c = (AVTC*)malloc( sizeof(AVTC) );
	
	ANSI_init();
	Init_ANSIVT_CTABLE();
	ResetAnsiVtCodes(1);
	colorMode();

	return APLIB;
	
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
char* BIN_2_DEC(char * bin)	{ /** Converts base2 (binary) string to base10 (decimal) string.

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

// The function below (DEC_2_BIN) is not finished. I forgot about it, because I keep getting drunk. It's fun programming when you're drunk, but you always forget what you were working on!!
char* DEC_2_BIN(char*  input, L packed)	{
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
	char* binary_stack = (char*)calloc( length+1, 1 );

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

// DIGIT-WISE FNCS
char d( APL A, L index ){
	
	return A->integer[index];
}

// assumes a packed-digit string of 4 bits/digit.
char* unpack( char* _ ) {
	
	L strlen__ = strlen( _ );

	int BITMASK_LOWER = 15;
	int BITMASK_UPPER = 255-15; //240, which is 11110000 (128+64+32+16)
	char t;
	
	L i, j;
	char* _U = (char*)calloc( 1, (strlen__>>2) + 1 );
	for( i=0, j=0; i<strlen__; i++ ) {
		
		t = _[i] & BITMASK_LOWER;
		if( t==10 )	t=0;
		
		_U[j++] = t + '0';
		
		t = (_[i] & BITMASK_UPPER)>>4;
		if( t==0 )
			_U[j++] = '\0';
		else if( t==10 )
			_U[j++] = '0';

	}

	if( _U[j-1]!='\0' )
		_U[j] = '\0';

	return _U;
}

// assumes an unpacked string of 1 char per decimal digit.
char* pack( char* _ ) {
	
	L strlen__ = strlen( _ );

	char* _P = (char*)calloc( 1, (strlen__>>1) + 2 );
	char t;
	
	L i,j;
	for( i=0,j=0; i<strlen__-1; i+=2, j++ )	{
		
		t = _[i] - '0';
		if( t==0 )
			t=10;
		
		char nd = (_[i+1] - '0');
		if( nd==0 )
			nd=10;
		
		t += ( nd << 4 );
		
		_P[j] = t;		
	}

	if( i==strlen__-1 )	{

	t = _[i] - '0';
	if( t==0 )
		t=10;
	
	_P[j++] = t;
	
	}
	_P[j] = '\0';
	return _P;
}

void setDigit( APL A, L index, char d ){
			
	A->integer[index] = d;
}


#define strlen strlen_
L strlen_( char * str )	{
	
	L i = 0;
	while( str[i++] != '\0' )
		;
	return i-1;
}


LARGE lenp( APL A ){
	
	LARGE length = strlen( A->integer );
	
	if( A->base==2 )
	if( A->p   ==0 ){
		L t = length%8;
		length += (t==0) ? 0: 8-(t);}		

	return length;
}


L LSD_OFFSET(char * A)	{

	large strlen_A = strlen( A );

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
char* substring_(char* source, large start, large end)	{

	char * _ = mem( (end-start)+1 );
	
	large i;
	for( i=0;i<(end-start)+1;i++ )
		_[i] = source[start+i];
	
	_[i] = '\0';

	return _;
}


char* ACCUMULATE( char* apstr ) {

	// init.
	L strlen_apstr = strlen( apstr );
	
	char* _ = (char*)malloc( strlen_apstr+2 );
	
	{
		#if ACC_COPY==1
		AP bkp = NewAP( strlen_apstr, 0 );
		_ = bkp->integer;
		#else
		_ = apstr;
		#endif
	}
	_[0] = apstr[0];
	
	char c;
	large i;
	for( i=strlen_apstr; i>0; --i )	{
		
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
		else // this is a roll-up function, not a roll-down function.
			_[i-1] = apstr[i-1];

		_[i] = c;
	}
	
	// safetycheck
	if( _[0]>'9' )
		_[0] = '9';
	else if( _[0]<'0' )
		_[0] = '0';
	
	if(_[0]=='0')// this is digit zero, not the nullchar.
		++_;

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

APL EXP(APL A, APL B)	{
	
	// ResultObject
	
	AP _;
	

	// if B (exp) is negative
	if( getSign(B)=='-' )	{

		B->sign = '+';
		
		AP C = EXP( A,B );
		
		AP D = DIVIDE( AP1, C );
		
		//FreeAP( &_ );

		B->sign = '-';
		return D;
	}
	
	// PAST THE NEGATIVE_EXPONENT GATE.
	
	// if exponent B=0, Result of A^B := 1. (n exp 0 == 1).
	if( CmpAP_abs( B,AP0 )==0 )
		return CopyAP( AP1 );
	
	AP D = SUB( B,AP1 );
	
	_ = CopyAP(A);
	
	while( CmpAP_abs( D,AP0 )==+1 )	{
		
		_ = MUL( _,A );
		
		//AP temp = CopyAP( &D );
		//FreeAP( &D );
		D = SUB( D,AP1 );
		//FreeAP( &temp );

	}
	
	if( getSign(A)=='-' )
		_->sign='-';
	
	return _;
}


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

APL LCM( APL A, APL B )	{

	APL M1;
	APL M2;
	#define MAX_ITER 4096
	APL* R1 = (APL*) calloc( sizeof(APL), MAX_ITER );
	APL* R2 = (APL*) calloc( sizeof(APL), MAX_ITER );
	
	APL AP_MAX_ITER = NewAP( 0,0 );
	free( AP_MAX_ITER->integer );
	AP_MAX_ITER->integer = int2str ( MAX_ITER );
	
	APL val = ADD( AP1, AP1 ), inc = CopyAP( AP0 ), match = CopyAP( AP0 );
	
	M1 = A; M2 = B;
	
	while (! CmpAP_abs( match, AP0 ))	{
		
		if ( CmpAP_abs( inc, AP_MAX_ITER)>=0 )	{
			
			printf( "Overflow error: More thAn %d iterAtions required.\n", MAX_ITER );
			exit( 1 );
		}
		
		//*(ANSI->c->ANSIVT_CTABLE + (i*4) + 0)
		*( R1+ str2int(inc->integer)*sizeof(APL) ) = MUL( M1, val ); *(R2+ str2int(inc->integer)*sizeof(APL) ) = MUL( M2,val );
		
		//match = lcm_test(inc, R1, R2);
		match = LCMTESTSTR(inc, R1, R2);

		INC( inc );
		INC( val );
	}
	
	// print( "The LCM for %d And %d is %d.\n", M1, M2, R1[inc-1]);

	return *( R1 + (str2int(inc->integer)-1)*sizeof(APL) );
}

#define aptr APL
APL LCMTESTSTR( aptr max, aptr* R1, aptr* R2 )	{
	
	aptr a = NewAPr( 0,0 );
	aptr b = NewAPr( 0,0 );
	for (FreeAP(a), a = CopyAP( AP0 ); CmpAP_abs( a,max )<=1; INC(a) )
		for (FreeAP(b), b = CopyAP( AP0 ); CmpAP_abs( b,max )<=1; INC(b) )
			if ( CmpAP_abs( R1[str2int(a->integer)],R2[str2int(b->integer)] )==0 )
				return a;
			
	return b;
}

APL lcm_example(int argc, char **argv)	{
	
	/*
	int flagSet = 0;
	
	if((argc == 4) && (argv[3][0] == '-') && (argv[3][1] == 'n'))	{
		
		//printf("flag set!\n");
		flagSet = 1;
	}
	*/

	APL a;
	APL b;
	a = NewAPr( 0,0 );
	free( a->integer );
	a->integer = argv[1];
	
	b = NewAPr( 0,0 );
	free( b->integer );
	b->integer = argv[2];
	
	APL lcm = LCM( a, b );
	//int gcd = 1; // = GCD(A, B, lcm);
	
	FreeAP( a );
	FreeAP( b );
	
	//printf( "lcm := (%d)\ngcd := (%d)\n", lcm, gcd );
	
	return lcm;
}

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



APTR DEC_2_HEX( APTR A,L packed ){

	aplibstdreturn(2);
}
APTR HEX_2_DEC( APTR A ){

	aplibstdreturn(10);
}
APTR DEC_2_OCTAL( APTR A, L precisiom ){

	aplibstdreturn(8);
}
APTR OCTAL_2_DEC( APTR A ){

	aplibstdreturn(10);
}

APTR BIN_2_OCTAL( APTR A ){

	aplibstdreturn(8);
}
APTR OCTAL_2_BIN( APTR A ){

	aplibstdreturn(2);
}



void FreeAP( APL A )	{
	
	//if( A->integer!=NULL )
	free( A->integer );

	//if( A->fractional!=NULL )
	free( A->fractional );

	//if( A!=NULL )
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
char** GetAPSymbols(){
	
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
symbols[OP_MODULO] = getstring("%");
symbols[OP_MODULO_ASSIGN] = getstring("%=");
symbols[OP_MODULO_ISEQUALTO] = getstring("%==");
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


char peek( large c, char* _ ){
// clearly, char at str[0] is considered digit "1"
return _[c - 1];}

// scint CmpAP_abs( APL, APL )
scint CmpAP_abs( APL A, APL B )	{
	
	if( A->integer == NULL )
		printf( "Warning. Arg A in CmpAP_abs is NULLptr.\n" );
	if( B->integer == NULL )
		printf( "Warning. Arg B in CmpAP_abs is NULLptr.\n" );
	
	APP Ac, Bc;
	
	Ac.integer = A->integer;
	Bc.integer = B->integer;
	
	L i = 0;
	
	if( A->integer != NULL )
		while( A->integer[i++]=='0' )
		++Ac.integer;
	
	i = 0;
	if( B->integer != NULL )
	while( B->integer[i++]=='0' )
		++Bc.integer;
	
	large len_A = strlen(Ac.integer);
	large len_B = strlen(Bc.integer);
	
	if( len_A<len_B )	{
	
		return -1;
	}
	
	
	if( len_A>len_B )	{
		
		return +1;
	}
	
	
	for( L test=0; test<len_A; test++ )	{
		
		if( Ac.integer[test]>Bc.integer[test] ){
		return +1;}
		
		
		if( Ac.integer[test]<Bc.integer[test] ){
			return -1;}
	}
	
	return 0;
}



scint CmpAP_signed( APL A, APL B )	{
	
	if( A->sign=='-' && B->sign=='+' )
		return -1;
	if( A->sign=='+' && B->sign=='-' )
		return +1;
	
	APP Ac, Bc;
	
	Ac.integer = A->integer;
	Bc.integer = B->integer;
	
	L i = 0;
	
	if( A->integer != NULL )
		while( A->integer[i++]=='0' )
		++Ac.integer;
	
	i = 0;
	if( B->integer != NULL )
	while( B->integer[i++]=='0' )
		++Bc.integer;
	
	large len_A = strlen(Ac.integer);
	large len_B = strlen(Bc.integer);
	
	if( len_A<len_B )	{
		
		if( !( A->sign=='+' && B->sign=='-') )
			return +1;
		
		return -1;
	}
	
	
	if( len_A>len_B )	{
	
		if( ( A->sign=='-' ) )
		return -1;
		
		return +1;
	}
	
	
	for( L test=0; test<len_A; test++ )	{
		
		if( Ac.integer[test]>Bc.integer[test] ){
			if( A->sign=='-' )
				return -1;
			else
		return +1;}
		
		
		if( Ac.integer[test]<Bc.integer[test] ){
			if( A->sign=='+' )
				return -1;
			else
		return +1;}
	}
	
	return 0;
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

	while(td>0)	{

		++ld;
		td = td - 10;
	}

	C->integer[k] = '0' + rd;

	scint iresult;
	iresult = ld+(C->integer[k-1] - '0');
	if( iresult <= 9 )
		C->integer[k-1] = '0' + iresult;
	else	{

		// if c[k-1] + ld > 9, recursive overflow, will need to deal with here!
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

