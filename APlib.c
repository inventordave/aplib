// APLIB_C

#include "lib.h"
#include "aplib.h"

AP AP0;
AP AP1;
AP DefaultPrecision;

struct __APLIB__ APLIB_;

char MUL_SYM = '*';
char ADD_SYM = '+';
char SUB_SYM = '-';
char DIV_SYM = '/';
char EXP_SYM = 'e';
char AND_SYM = '&';
char NOT_SYM = '~';
char OR_SYM =  '|';
char XOR_SYM = '^';
char NAND_SYM = '@';
char POSITIVE_SYM = '+';
char NEGATIVE_SYM = '-';
char DELIMETER_SYM = '.';
char BASE10_SYM = '0';
char BASE2_SYM = '2';
char BASE16_SYM = 'H';
char* ALL_DIGITAL_SYMBOLS = "0123456789abcdefABCDEF.hHxX";

int maxLoopsSet;

statusCode setPartW( AP* A, char * _ )	{

	return setPart( A, _, PartW );
}
statusCode setPartF( AP* A, char * _ )	{

	return setPart( A, _, PartF );
}

statusCode setPart( AP* A, char * digits, int sign_maj_min )	{

	if( sign_maj_min==SignPart )	{

		A->sign = *digits;
		
		if( A->sign==digits[0] )
		return SUCCESS;
		else
		return FAIL;
	}

	char * _;
	
	if( sign_maj_min==1 )
		_ = A->major;
	else
		_ = A->minor;
	
	if( strlen(_) < strlen(digits) )
		_ = (char *)realloc(_, strlen(digits)+1);

	
	large i;
	for( i=0; i<strlen(_); i++ )
		_[i] = digits[i];
	
	_[i] = '\0';
	
	return i;
}


int DIVBY2_PRINT_ROWS = 0;

// CORE BOOLEAN OPERATORS
char * AND(char * LHS, char * RHS)	{
	
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
			
		b_str[k] = '0' + ( (a-'0') & (b-'0') );
	}
	
	assert( k==-1 );
	
	return b_str;
}
char * NOT(char * v)	{
	
	char * output = (char *)malloc( strlen(v) + 1 );
	int i;
	for( i=0; i<strlen(v); i++ )
		if( v[i]=='0' )
			output[i] = '1';
		else if( v[i]=='1' )
			output[i] = '0';
		else
			assert(0);
		
	output[i] = '\0';
	
	return output;
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
char * XOR(char * LHS, char * RHS)	{

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

		b_str[k] = '0' + ( (a-'0') ^ (b-'0') );
	}

	assert( k==-1 );
	
	
	return b_str;
}


char * NAND(char * LHS, char * RHS)	{
	
	char * _ = AND( LHS,RHS );
	char * C = NOT( _ );
	
	free( _ );
	return C;
}



// NOP (No-Operation). It returns an AP1 value.
AP NOP( AP A, AP B ){

	return CopyAP( &AP1 );
}

// CORE ARITHMETIC OPERATORS
AP ADD( AP A, AP B )	{ return ADDP( A, B, DefaultPrecision ); }
AP ADDP( AP A, AP B, AP P )	{
	
	int flag = 0;
	
	int size = ( strlen(B.major) > strlen(A.major) ? strlen(B.major) : strlen(A.major) );
	AP C = NewAP(size+1, 0);


	signed short int value;
	signed short int valA, valB, valC;
	
	signed int i, j, k;
	
	if( getSign(&A) == getSign(&B) )	{
		
		for( i=strlen(A.major)-1, j=strlen(B.major)-1, k=strlen(C.major)-1; k>0; i--, j--, k--)	{
		
			if(i>=0)
				valA = A.major[i] - '0';
			else
				valA = 0;
			
			if(j>=0)
				valB = B.major[j] - '0';
			else
				valB = 0;
			
			valC = (C.major[k] - '0');	
			
			valA += valC;

				
			value = valA + valB;

			if( value>=10 )	{
				
				value -= 10;
				C.major[k-1] += 1;
			}
			
			C.major[k] = '0' + value;
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
	
	
	if( ( tt( &A,&B )=='-' ) && (flag==0) )
		C.sign = '-';

	
	char * _ = (char *)malloc(strlen(C.major)+1);
	strcpy(_, C.major);
	for( i=0; i<(int)strlen(_); i++ )
		if( _[i] == '0' )
			++C.major;
		else
			break;
	
	free( _ );
	
	if( *C.major == '\0' )
		--C.major;
	
	return C;
}
AP SUB( AP A, AP B )	{ return SUBP( A, B, DefaultPrecision ); }
AP SUBP( AP A, AP B, AP P )	{
	
	if( (A.sign=='+') && (B.sign=='+') && ( (CmpAP(&A,&B)==+1) || (CmpAP(&A,&B)==0) ) )	{

		int i, j, k, valA, valB, valC;
		AP C = NewAP(strlen(A.major)+1,0);
		for( i=strlen(A.major)-1, j=strlen(B.major)-1, k=strlen(C.major)-1; k>0; i--, j--, k--)	{
		
			if(i>=0)
				valA = A.major[i] - '0';
			else
				valA = 0;
			
			if(j>=0)
				valB = B.major[j] - '0';
			else
				valB = 0;
			
			valC = (C.major[k] - '0');	
			
			valA += valC;

			if( valA<valB )	{
				
				C.major[k-1] -= 1;
				valA += 10;
			}

			int value = valA - valB;
			C.major[k] = '0' + value;
		}
	
		
		int len = strlen(C.major);
		char * _ = malloc(len+1);
		_ = strdup( C.major );
		for( i=0; i<len; i++ )
			if( _[i] == '0' )
				++C.major;
			else
				break;
	
		free( _ );
	
		if( *C.major == '\0' )
			--C.major;
		
		return C;
	}
	
	// Alt. SUB Algorithm:
	// The subtrAction of A reAl number (the subtrAhend [B]) from Another (the minuend [A]) cAn be defined As the ADition of the minuend [A] And the ADitive inverse of the subtrAhend [B].
	flipSign(&B);
	AP res = ADD(A, B);
	flipSign(&B);

	return res;
}
AP MUL( AP A, AP B )	{ return MULP( A, B, DefaultPrecision ); }
AP MULP( AP A, AP B, AP P )  {

	int MAX_NUM_MUL_ROWS = ( strlen(A.major)>strlen(B.major) ? strlen(A.major) : strlen(B.major) );
	
	char ** ResultArray = (char **)calloc(MAX_NUM_MUL_ROWS, sizeof(char *));
	int q = 0;

	for( int k = strlen(B.major)-1; k>=0; k-- )	{
		
		int rev_offset_B = strlen(B.major) - 1 - k;
		
		int curr_row_length = strlen(A.major) + 1 + rev_offset_B;
		char * curr_row = (char *)malloc( curr_row_length + 1 );
		curr_row[ curr_row_length ] = '\0';
		pack_trailing_zeroes( curr_row, curr_row_length, rev_offset_B );
		
		int prev_overflow = 0;
		
		int p = curr_row_length - 1 - rev_offset_B;
		
		for( int i = strlen(A.major)-1; i>=0; i-- )	{
			
			int _A = A.major[i] - '0';
			int _B = B.major[k] - '0';
			
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
		
		free( D.major );
		
		D.major = strdup(result_row);
		
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
	
	//char * wp;
	//char * fp;
	
	AP C = NewAP(0, 0);
	large offset = strlen(B.major) - 1;
	AP Remainder = NewAP( strlen(B.major) , 0 );
	
	large i;
	for(i=0;i<strlen(B.major);i++)
		Remainder.major[i] = A.major[i];
	
	Remainder.major[i] = '\0';
	
	AP Dropdown = NewAP(1, 0);
	
	AP v = NewAP(1, 0); v.major[0] = '0';
	AP inc = NewAP(1, 0); inc.major[0] = '1';
	
	AP temp;
	AP v2;
	AP result;
	large strlen_A = strlen(A.major);
	//large strlen_minor_A = LSD_OFFSET(A.minor);
	
	if( strlen(A.major)>strlen(B.major) )
		Dropdown.major[0] = A.major[offset+1];
	else
		Dropdown.major[0] = '0';
	
	
	int LOOPS = 0;
	
	int MAX_LOOPS = 100;

	//int count = 0;
	loop:
	while( offset<strlen_A )	{
		
		++LOOPS;
		if( LOOPS>MAX_LOOPS )
			goto maxiterations;
		
		v.major[0] = '0';
		
		temp = MUL( B,v );
		while( CmpAP( &temp,&Remainder ) < 1 )	{
			
			v2 = ADD(v, inc);
			free( v.major );
			v = CopyAP(&v2);
			free( v2.major );
			
			free( temp.major );
			temp = MUL( B,v );
		}
		
		v2 = SUB(v, inc);
		free( v.major );
		v = CopyAP(&v2);
		free( v2.major );
		
		result = MUL( B,v );
		v2 = SUB(Remainder, result);
		free( result.major );
		free( Remainder.major );
		Remainder = CopyAP(&v2);
		free( v2.major );

		
		#define CONCAT(__A,__B) strcat(__A.major, __B.major)
		
		//printf( "Row %d:\t'%s' + '%s'\n", count, C.major, v.major );
		//++count;
		CONCAT( C,v );
		
		if( !fractional )
			if( L0==1 )	{

				if( v.major[0]=='0' )	{
					
						++C.major;
				}
				else
					L0=0;
			}
		
		if( Remainder.major[0] > '0' )
			CONCAT( Remainder,Dropdown );
		else	
		if( offset != (strlen(B.major)-1) )
			Remainder.major[0] = Dropdown.major[0];

		if( fractional )	{
			
			if( CmpAP( &Remainder,&AP0 ) == 0 )	{
				break;
			}
		}
		else	{

			if( (offset+1)<strlen_A )
				
				Dropdown.major[0] = A.major[offset+1];
			else
				Dropdown.major[0] = '0';
		}

		++offset;
	}
	
	
	// fractional overflow
	
	if( fractional==0 )	{
		
		fractional = 1;

		if( CmpAP( &C,&AP0 )==0 )
			--C.major;
		
		//wp = strdup( C.major );
	}
	
	offset = 0;
	Dropdown.major[0] = '0';
	
	if( CmpAP( &Remainder,&AP0 ) == 1 )
		goto loop;
	
	maxiterations: // Upper-bound for precision of calculation reached.
	// RESULT COMPUTED.
	
	//printf( "The fixed-point for the Answer is positioned to the right of digit %d.\n", (int) strlen_A-1 );
	
	for( i=0; i<(strlen_A-1); i++ )
		printf( "%c", C.major[i] );
	
	printf( "." );
	
	for( ; i<strlen(C.major); i++ )	
		printf( "%c", C.major[i] );
	
	NL;
	
	printf( "\n\nSystem paused. Press any (sensible) key to continue..." );
	pause();
	
	return C;
}



// SKELETON FNC'S FOR FUTURE OPERATORS.
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


// BASE CONVERSION FNCS
char * BIN_2_DEC(char * bin)	{ /** Converts base2 (binary) string to base10 (decimal) string.

*/

	AP dec = NewAP( strlen(bin)+1, 0 );
	AP mult = NewAP( strlen(bin)+1, 0 );
	
	AP digit = NewAP(1, 0);
	
	AP _2 = NewAP(1, 0);
	AP _j = NewAP(10, 0);
	
	_2.major = strdup( "2" );

	int i, j;
	
	for( i=0, j=strlen(bin)-1; i<strlen(bin); i++, j-- )	{

		digit.major[0] = bin[i];
		
		sprintf(_j.major, "%d", j); // itoa()
		mult = EXP( _2, _j );
		dec = ADD( dec, MUL(digit, mult) );
	}
	
	FreeAP( &mult );
	FreeAP( &digit );
	FreeAP( &_2 );
	FreeAP( &_j );
	
	char * result = (char *)malloc( strlen(dec.major)+1 );
	result = strdup( dec.major );

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
	t.major = strdup( "0" );
	
	AP Check = CopyAP( &input );
	while ( flag )	{
		
		Check=DIVBY2(Check);

		if( DIVBY2_PRINT_ROWS==1 )
			printf( "\t%c%s\n", Check.sign, Check.major );
			
		++length;
		
		if( CmpAP(&Check,&t)<= 0 )
			flag = 0;
	}
	
	//printf( "length := %d\n", ( packed==1 ? ((length%8==0) ? length: length + (8-(length%8))) : length) );

	AP stack[strlen(input.major)];
	char binary_stack[length+1];

	length = strlen(input.major);

	int pointer;
	int bs_pointer = 0;
	
	AP A = NewAP( length, 0 );
	
	AP result = NewAP( length, 0 );
	flag = 1;
	while( flag )	{

		pointer = 0;
		
		int i;
		for( i=0; i<length; i++ )	{
			
			A.major[i] = input.major[i];
			
			pack_trailing_zeroes( A.major, length, (length-i-1) );
			
			int dividend = A.major[i] - '0';
			int remainder = dividend % 2;
			int quotient = dividend / 2;
			
			result.major[i] = quotient + '0';
			
			// if A_substring != LSdigit (units position)
			// if it is, the remainder is noted As A binary digit 1, And the remainder itself disgArded.

			if( remainder )	{
				
				if( i==(length-1) )	{
			
					binary_stack[bs_pointer++] = '1';
				}
				else
					result.major[i+1] = '5';
			}
			else	{
				
				if( i==(length-1) )	{
			
					binary_stack[bs_pointer++] = '0';
				}
				else
					result.major[i+1] = '0';
			}

			pack_trailing_zeroes( result.major, length, (length-i-2) );
			
			stack[pointer++] = CopyAP(&result);

			// finAlly...
			
			A.major[i] = '0';
			result.major[i] = '0';
			result.major[i+1] = '0';
		}	
		

		input.major = strdup( "0" );
		for(int k = 0; k < pointer; k++ )
			input = ADD(input, stack[k]);
		
		length = strlen(input.major);
		
		int l = strlen(A.major)-strlen(input.major);
		
		for( int z=0; z<l; z++ )
			++A.major;

		pack_trailing_zeroes( A.major, length, length);
		
		AP t = NewAP(1,0);
		t.major = strdup( "0" );
		
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
large min2k(AP A)	{
	
	char * bin_string = DEC_2_BIN( A, 0 );
	
	int len_bin_string = strlen(bin_string);
	
	for( int i=0; i<len_bin_string; i++ )	{
		
		if( bin_string[i]=='1')	{
			
			return len_bin_string - 1 - i;
		}
	}
	
	return 0;
}
large max2k(AP A)	{
	
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



	



statusCode APInit()	{

	DefaultPrecision = NewAP( 0, 0 ); // Sets default precision to indicate the length of the largest string between the 2 operands.
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

char * substring_(char * source, large stArt, large end)	{

	char * _ = (char *)malloc( (end-stArt)+1+1 );
	
	large i;
	for( i=0;i<(end-stArt)+1;i++ )
		_[i] = source[stArt+i];
	
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
		_ = bkp.major;
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


AP DIVBY2(AP A)	{
	
	int overflow = 0;
	int value;
	int i;
	for( i=0; i<strlen(A.major); i++ )	{
		
		loop:
		
		value = A.major[i] - '0';
		
		if( value>9	)	{
			// roll over the remainder
			char remainder = value % 10;
			char _ = value - remainder;
			A.major[i] = '0' + _;
			A.major[i+1] += remainder;	
		}

		value = A.major[i] - '0';
		
		int result = floor( value/2 );
		result += overflow;
		A.major[i] = result + '0';
		
		if( A.major[i] - '0' >= 10 )
			goto loop;
		
		if( value%2!= 0 )
			overflow = 5;
		else
			overflow = 0;

	}
	
	A.major[i] = '\0'; //NULL
	
	int len = strlen( A.major );
	for( i=0; i<len; i++ )
		if( A.major[i]=='0' )	{
			
			++A.major;
			--len;
			--i;
		}
		else
			break;

	if( A.major[0]=='\0' )
		--A.major;
	
	return A;
}



void init_()	{
	
	AP0 = NewAP( 1,0 );
	AP0.major[0] = '0';
	AP1 = NewAP( 1,0 );
	AP1.major[0] = '1';
	DefaultPrecision = NewAP( 0, 0 ); // Sets default precision to indicate the length of the largest string between the 2 operands.
		
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

int lcm_test(int max, int R1[], int R2[])	{
	
	for (large A = 0; A <= max; A++)
		for (large B = 0; B <= max; B++)
			if (R1[A]==R2[B])
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
AP NewAP( large maj, large min )	{

	AP result;
	result.major = (char *)malloc(maj+1);
	result.minor = (char *)malloc(min+1);
	
	if( (result.major==NULL)||(result.minor==NULL) )	{
		
		printf("AP NewAP(...) failed 1 or 2 of 2 malloc() calls! Exiting...\n");
		exit(0);
	}
	
	int i;
	
	for( i=0; i<maj; i++)
		result.major[i] = '0';
	
	result.major[maj] = '\0';
	
	for( i=0; i<min; i++)
		result.minor[i] = '0';
	
	result.minor[min] = '\0';
	
	result.sign = '+';
	return result;
}

AP CopyAP(AP * A)	{
	
	AP _ = NewAP(strlen(A->major),strlen(A->minor));
	
	strcpy(_.major, A->major);
	strcpy(_.minor, A->minor);
	
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

char tt( AP* A, AP* B )	{
	
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

