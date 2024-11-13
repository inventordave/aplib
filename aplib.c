// APLIB_C

#include "lib.h"
#include "stringy.h"
// #include "colour.h"
#include "aplib.h"

#include "stringy.h"

AP AP0;
AP AP1;
AP DefaultPrecision;


void parseAP(char * str)	{

	AP A = NewAP( 0,0 );
	
	if( str[0] == '-' )	{

		A->sign = '-';
		++str;
	}
	else if( str[0] == '+' )
		++str;
	else	{

		A->integer = strdup(str);
		A->sign = '+';
	}

	return;
}

// LOG OPERATOR DEV

AP NLOG( AP x )	{

	return NLOGP( x, DefaultPrecision );
}

AP NLOGP( AP x, AP epsilon )	{
	
	// Using Newton's method, the iteration simplifies to (implementation) 
	// which has cubic convergence to ln(x).
	// double ln(double x, double epsilon)
	
	AP yn = SUB( x,AP1 ); // using the first term of the taylor series as initial-value
	AP yn1 = CopyAP( yn );
	AP diff = NewAP( 0,0 );
	AP AP2 = ADD( AP1,AP1 );
	
	do
	{
		FreeAP( diff );
		FreeAP( yn );
		
		yn = CopyAP( yn1 );
		FreeAP( yn1 );

		// pow(v) should be in c stdlib, calculates the value of Euler's constant (irrational, approx 2.71828) raised to power v.
		// powAP(v) is a

		AP gParam = powAP( yn );
		AP dParam = SUB( x,gParam );
		FreeAP( gParam );
		
		AP fParam = powAP( yn );
		AP eParam = ADD( x,fParam );
		FreeAP( fParam );
		
		AP cParam = DIV( dParam, eParam );
		FreeAP( dParam );
		FreeAP( eParam );
		
		AP bParam = MUL( AP2, cParam );
		FreeAP( cParam );
		
		yn1 = ADD( yn, bParam ); 
		FreeAP( bParam );

		diff = SUB(yn,yn1);

	} while ( CmpAP_abs( diff, epsilon )>0 );

	FreeAP( yn );
	FreeAP( yn1 );
	FreeAP( diff );
	FreeAP( AP2 );
	
	return yn1;
}

AP LOGb( AP A, AP base )	{

	int base_ = str2int( base->integer );
	return LOGb_( A, base_ );
}

// log_b(x) = ln(x)/ln(b).
AP LOGb_( AP A, int base )	{

	AP Base = NewAP( 0,0 );
	
	char* t = int2str( base );
	char* _ = getstring( t );
	setPartW( Base, _ );
	
	free( t );
	free( _ );
	
	AP nlA = NLOG( A );
	AP nlN = NLOG( Base );

	FreeAP( Base );
	
	AP result = DIV( nlA, nlN );

	FreeAP( nlA );
	FreeAP( nlN );

	return result;
}

// logn(x) = ln(x)/ln(n).
char* LOGb_raw( char* A, int base )	{

	char* nlA = NLOG_str( A );
		char* base_str = int2str( base );
	char* nlN = NLOG_str( base_str );
	
	char* result = DIV_str( nlA, nlN );

	free( base_str );
	free( nlA );
	free( nlN );

	return result;
}


AP ConvertAPBase( AP, AP base );
AP ConvertAPBase_( AP, int base );

char* ConvertBase( char* A, int prev_base, int new_base ); // This stub is also to remind me to do alt. implementations.
// A lot of calls to operators are not going to require full AP structures, just digitstrings.

// NB:
//
//the logarithmic identities for rational numbers:
//
//logB(x/y) = logB(x) - logB(y)
//
// This is computationally only useful for quick calculation of a log of a rational (N/M, or "divisor-form").
// It won't increase z=DIV(x,y) speed in APlib, by indirection through z=(x/y)=b_exp(log_b(x/y))
// APlib still provides functions for calculating natural logs y=NLOG(x) and y=LOGb(x), an exponent y in a defined base b for scalar x.
//
// Also, if	"AP logb_x_div_y = LOGb( DIV(x,y) );"
// is quicker than
//		"AP logb_x_div_y = LOGb(x) - LOGb(y);"
//
// then the logarithmic identity for rational numbers has little implementation benefit in APlib, except for convenience.
//
// A macro would therefore suffice:
//
// #define LOGb_xy( x,y,b ) SUB( LOGb(x,b)-LOGb(y,b) )
//
// where [OP_CLASS]_xy naming convention indicates an input of a rational x/y, in form of 2 parameters notionally called x and y.
//
// An alt macro for LOGb as so:
// #define alt_LOGb( x,b ) ( { AP xt=(NLOG(x));AP bt=(NLOG(b)); AP rt=(DIV(xt,bt)); FreeAP(xt);FreeAP(bt); (rt); } )
// NOTE TO SELF: I need to test the above macro, and if it works, see if I can remove the block-level delimiters.
// 		I have placed a note in my TODO List.

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

L setPartW( AP A, char * _ )	{

	return setPart( A, _, PartW );
}
L setPartF( AP A, char * _ )	{

	return setPart( A, _, PartF );
}

L setPart( AP A, char * digits, L part )	{

	if( part==SignPart )	{

		A->sign = *digits;
		
		if( A->sign==digits[0] )
		return SUCCESS;
		else
		return FAIL;
	}

	char* _ = NULL;
	if( part==PartW )
		_ = A->integer;
	else
		_ = A->fractional;

	if( _!=NULL )
		free( _ );

	_ = getstring( digits );

	if( part==PartW )
		A->integer = _;
	else
		A->fractional = _;

	return strlen( _ );
}


L DIVBY2_PRINT_ROWS = 1;

// CORE BOOLEAN OPERATORS
AP AND( AP LHS, AP RHS )	{
	
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
AP NOT(AP v)	{
	
	
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
	
	AP _2 = (APL)malloc( sizeof( APP ) );
	_2->integer = _;
	return _2;
}
AP OR( AP LHS, AP RHS)	{

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
	
	AP _b = NewAPr( 0,0 );
	
	_b->integer = b_str;
	
	return _b;
}
AP XOR( AP LHS, AP RHS )	{

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
	
	AP _ = (APL)malloc( sizeof(APP) );
	_->integer = bstr;
	return _;
}
AP NAND( AP LHS, AP RHS )	{
	
	AP C = AND( LHS,RHS );
	AP _ = NOT( C );
	free( C );
	
	return _;
}

// NOP (No-Operation). It returns an AP, or AP0, value.
AP NOP( AP A ){

	return CopyAP( A );
}

// CORE ARITHMETIC OPERATORS

int INC( AP A )	{

	AP _;
	_ = ADD( A,AP1 );
	free( A );
	A = _;

	return 1;
}
int DEC( AP A )	{

AP _;
_ = SUB( A,AP1 );
free( A );
A = _;

return -1;
}

AP ADD( AP A, AP B )	{ return ADDP( A, B, DefaultPrecision ); }
AP ADDP( AP A, AP B, AP P )	{
	
	char sign_A = A->sign;
	char sign_C = '.';

	/*
	1. If the signs are the same, add the numbers and keep the sign.
	2. If the signs are different, subtract the numbers and take the sign of the bigger* number.
	*/

	if( sign_A == B->sign )
		sign_C = sign_A;

	large strlen_a = strlen(A->integer);
	large strlen_b = strlen(B->integer);

	int AorB = CmpAP_abs( A,B );

	large size = ( !AorB ? strlen_b : strlen_a );
	AP C = NewAP( size+1,0 );

	signed value;
	signed valA, valB, valC;

	signed int i, j, k;
	
	valC = 0;
	for( i=strlen_a-1, j=strlen_b-1, k=size; k>0; i--, j--, k--)	{
	
		if(i>=0)
			valA = A->integer[i] - '0';
		else
			valA = 0;

		if(j>=0)
			valB = B->integer[j] - '0';
		else
			valB = 0;

		if( sign_C == '.' )
			valB *= -1;
		
		valA += valC;

		valC = 0;

		value = valA + valB;

		if( sign_C==sign_A ){
			if( value>9 )	{
				
				value = value - 10;
				valC = +1;
			}
		}

		else	{ //if( sign_C=='.' ) // A->sign != B->sign

			if( value<0 )	{

				value = ( 10 + valA ) + valB;
				valC = -1;
			}
		}

		C->integer[k] = '0' + value;
	}

	if( sign_C==sign_A )
		C->sign = sign_C;
	else{

		if( AorB < 0 ){
			C->sign = B->sign;
		}
		else
			C->sign = A->sign;
	}

	return C;
}
AP SUB( AP A, AP B )	{ return SUBP( A, B, DefaultPrecision ); }
AP SUBP( AP A, AP B, AP P )	{

	// SUB Algorithm:
	// The subtraction of a real number (the subtrahend [B]) from another (the minuend [A]) can be defined as the addition of the minuend [A] and the additive inverse of the subtrahend [B].
	flipSign(B);
	AP result = ADD(A, B);
	flipSign(B);

	return result;
}
AP MUL( AP A, AP B )	{ return MULP( A, B, DefaultPrecision ); }

AP MULP_new( AP A, AP B, AP P )	{ // seems to be multiplying each row to 1/2 it's intended value

	// 1. Multiply each digit of A with each digit of B. For each digit of B, a result row is generated.
	// 2. Then add those result rows together.

	AP C = CopyAP( AP0 );

	L NUM_ROWS = strlen( B->integer );
	L strlen_A = strlen( A->integer );
	
	L max_len_row = strlen_A + 1 + (NUM_ROWS-1);


	char** ResultRows = (char**) malloc( sizeof(char*) * NUM_ROWS );
	if( ResultRows==NULL )	{

		printf(" Unable to allocate memory in file '%s' at line number %d.\n" ,__FILE__, __LINE__ );
		exit( 1 );
	}

	char* result_row = (char*) malloc( max_len_row + 1 );
	result_row[max_len_row] = '\0';

	int A_;
	int B_;
	int C_;
	int D_;
	int overflow;
	int value;

	int i, n;
	int c = max_len_row-1;
	int t;
	for( i=0; i<NUM_ROWS; i++ )	{

		t = 0;
		overflow = 0;

		while( (t++)<i )
			result_row[c-t] = '0'; // trailing zeroes in each successive result row.


		B_ = B->integer[NUM_ROWS-1-i] - '0';

		for( n=strlen_A-1; n>=0; n-- )	{


			A_ = A->integer[n] - '0';
			C_ = (A_+ overflow) * B_;

			overflow = 0;

			if( C_>9 )	{

				value = C_ % 10;
				D_ = C_;

				while( D_ > 9  )	{

					overflow++;
					D_ -= 10;
				}
			}
			else
				value = C_;
			
			result_row[c-(t++)] = value + '0';

		}

		while( (c-t) >= 0 )
			result_row[ c-(t++) ] = '0';

		

		ResultRows[i] = getstring( result_row );
	}

	AP R = CopyAP( AP0 );
	AP _;

	--i;
	for( n=i; n>=0; n-- )	{

		//free( R->integer );

		setPartW( R, ResultRows[n] );

		_ = CopyAP( C );
		FreeAP( C );

		C = ADD( _, R );

		FreeAP( _ );
	}

	// When multiplying two numbers with the same sign,
	// the product is positive. When multiplying two numbers with
	// unlike signs, the product is negative.

	if( A->sign==B->sign )
		C->sign = '+';
	else
		C->sign = '-';

	return C;

}

AP MULP( AP A, AP B, AP P )  {

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


	AP C = NewAP( 1,0 );
	AP D = NewAP( 1,0 );
	AP _;

	for( int t = 0; t < q; t++ )	{
		
		char * result_row = ResultArray[t];
		
		if(result_row==NULL)
			assert(result_row);
		
		free( D->integer );
		
		D->integer = strdup(result_row);
		
		_ = CopyAP( C );
		
		FreeAP( C );
		
		C = ADD( _,D );
		FreeAP( _ );
	}
	
	C->sign = TT_MUL( A,B );
	return C;
}
AP DIV( AP A, AP B )	{

	return DIVP( A, B, DefaultPrecision );
}
AP DIVP( AP A, AP B, AP P )  {

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


AP RESET0( AP A ) { setPartW( A,AP0->integer ); setPartF( A,AP0->integer ); return A; }
AP RESET1( AP A ) { setPartW( A,AP1->integer ); setPartF( A,AP0->integer ); return A; }


struct _APLIB* Init_APLIB(){
	
	// Initialise
	AP0 = NewAP( 1,0 );
	AP0->integer[0] = '0';
	AP1 = NewAP( 1,0 );
	AP1->integer[0] = '1';
	DefaultPrecision = AP0; // Sets default precision to indicate the length of the largest string between the 2 operands.

	struct _APLIB* APLIB = (struct _APLIB*)malloc( sizeof(struct _APLIB) );
	
	/**
	// Temp commenting-out

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

	*/
	return APLIB;
	
}

void setSign( AP A,char S ){

	if( S!='+' ){
		if( S!='-' )
		A->sign='+';
		else
		A->sign='-';}
	else
		A->sign = S;
}


AP RECIPROCAL2( AP A, AP B ){
	
	return RECIPROCAL2P( A,B,DefaultPrecision );
}


AP RECIPROCALP( AP A, AP DefaultPrecision ){
	
	return DIV( AP1,A ); 
}

AP RECIPROCAL2P( AP A,AP B,AP DefaultPrecision ){
	
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

	int i, strlen_bin = strlen(bin);
	
	for( i=0; i<strlen_bin; i++ )	{

		digit->integer[0] = bin[i];
		
		sprintf(_j->integer, "%d", strlen_bin-1-i); // itoa()
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
		
		AP temp;
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
			// if it is, the remainder is noted as a binary digit 1, And the remainder itself discarded.

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
char d( AP A, L index ){
	
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

void setDigit( AP A, L index, char d ){
			
	A->integer[index] = d;
}


#define strlen strlen_
L strlen_( char * str )	{
	
	L i = 0;
	while( str[i++] != '\0' )
		;
	return i-1;
}


LARGE lenp( AP A ){
	
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
AP DIVBY2( AP A )	{
		
	int overflow = 0;
	int value;
	L strlen_a = strlen( A->integer );
	AP _ = (APL)malloc( sizeof(APP) );
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

AP EXP(AP A, AP B)	{
	
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
L DSTRING2LARGE( AP A ){

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
AP APLCM( AP A, AP B ){
	
	AP M1 = CopyAP( AP0 );
	AP M2 = CopyAP( AP0 );
	
	#define MAX_ITER 4096
	// It is AP pointers stored in the memory, because it is pointers allocated by the Operator functions that are passed.
	AP R1[MAX_ITER] = (APL)calloc( sizeof(APL), MAX_ITER );
	AP R2[MAX_ITER] = (APL)calloc( sizeof(APL), MAX_ITER );
	
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

AP LCM( AP A, AP B )	{

	AP M1;
	AP M2;
	#define MAX_ITER 4096
	APL* R1 = (APL*) calloc( sizeof(APL), MAX_ITER );
	APL* R2 = (APL*) calloc( sizeof(APL), MAX_ITER );
	
	AP AP_MAX_ITER = NewAP( 0,0 );
	free( AP_MAX_ITER->integer );
	AP_MAX_ITER->integer = int2str ( MAX_ITER );
	
	AP val = ADD( AP1, AP1 ), inc = CopyAP( AP0 ), match = CopyAP( AP0 );
	
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
AP LCMTESTSTR( aptr max, aptr* R1, aptr* R2 )	{
	
	aptr a = NewAPr( 0,0 );
	aptr b = NewAPr( 0,0 );
	for (FreeAP(a), a = CopyAP( AP0 ); CmpAP_abs( a,max )<=1; INC(a) )
		for (FreeAP(b), b = CopyAP( AP0 ); CmpAP_abs( b,max )<=1; INC(b) )
			if ( CmpAP_abs( R1[str2int(a->integer)],R2[str2int(b->integer)] )==0 )
				return a;
			
	return b;
}

AP lcm_example(int argc, char **argv)	{
	
	/*
	int flagSet = 0;
	
	if((argc == 4) && (argv[3][0] == '-') && (argv[3][1] == 'n'))	{
		
		//printf("flag set!\n");
		flagSet = 1;
	}
	*/

	AP a;
	AP b;
	a = NewAPr( 0,0 );
	free( a->integer );
	a->integer = argv[1];
	
	b = NewAPr( 0,0 );
	free( b->integer );
	b->integer = argv[2];
	
	AP lcm = LCM( a, b );
	//int gcd = 1; // = GCD(A, B, lcm);
	
	FreeAP( a );
	FreeAP( b );
	
	//printf( "lcm := (%d)\ngcd := (%d)\n", lcm, gcd );
	
	return lcm;
}

AP NewAPr( large integer_range, large fractional_range )	{

AP 	_ = NewAP( integer_range,fractional_range );
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



void FreeAP( AP A )	{
	
	if( A->integer!=NULL )
	free( A->integer );

	if( A->fractional!=NULL )
	free( A->fractional );

	if( A!=NULL )
	free( A );
	
	return;
}		


// SIGN FNCS
char getSign( AP A )	{

	return A->sign;
}


void set_sign( AP A, char sym )	{

	if( sym!='-' )
		sym='+';
	
	A->sign = sym;
	return;
}


void flipSign( AP A )	{

	if( A->sign == '-' )
		A->sign = '+';
	else
		A->sign = '-';
	
	return;
}

char TT_ADD( AP A, AP B )	{
	
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

char TT_MUL( AP A, AP B )	{

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

// scint CmpAP_abs( APL, AP )
scint CmpAP_abs( AP A, AP B )	{
	
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



scint CmpAP_signed( AP A, AP B )	{
	
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

