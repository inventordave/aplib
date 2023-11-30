// APLIB_C

#include "APlib.h"
int DIV_BY_2_PRINT_ROWS = 0;

char * AND(char * lhs, char * rhs)	{
	
	char * a;
	char * b;
	
	a = lhs; b = rhs;
	int len = ( strlen(a) >= strlen(b) ? strlen(a) : strlen(b) );
	
	char * b_str = (char *)malloc( len+1 );
	b_str[len] = '\0';

	// both binary string are the same length.
	char A = '0';
	char B = '0';
	
	int t, i, j, k;
	for( i=strlen(a)-1,j=strlen(b)-1, k=len-1; ; i--, j--, k-- )	{
		
		t = 0;
		
		if( i<0 )	{
			
			A = '0';
			++t;
		}
		else
			A = a[i];
		
		if( j<0 )	{
			
			B = '0';
			++t;
		}
		else
			B = b[j];
		
		if( t==2 )
			break;
			
		b_str[k] = '0' + ( (A-'0') & (B-'0') );
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

char * OR(char * lhs, char * rhs)	{

	char * a;
	char * b;
	
	a = lhs; b = rhs;
	int len = ( strlen(a) >= strlen(b) ? strlen(a) : strlen(b) );
	
	char * b_str = (char *)malloc( len+1 );
	b_str[len] = '\0';

	// both binary string are the same length.
	char A = '0';
	char B = '0';
	
	int t, i, j, k;
	for( i=strlen(a)-1,j=strlen(b)-1, k=len-1; ; i--, j--, k-- )	{
		
		t = 0;
		
		if( i<0 )	{
			
			A = '0';
			++t;
		}
		else
			A = a[i];
		
		if( j<0 )	{
			
			B = '0';
			++t;
		}
		else
			B = b[j];
		
		if( t==2 )
			break;
			
		b_str[k] = '0' + ( (A-'0') | (B-'0') );
	}
	
	assert( k==-1 );
	
	return b_str;
}

char * EX_OR(char * lhs, char * rhs)	{

	char * a;
	char * b;
	
	a = lhs; b = rhs;
	int len = ( strlen(a) >= strlen(b) ? strlen(a) : strlen(b) );
	
	char * b_str = (char *)malloc( len+1 );
	b_str[len] = '\0';

	// both binary string are the same length.
	char A = '0';
	char B = '0';
	
	int t, i, j, k;
	for( i=strlen(a)-1,j=strlen(b)-1, k=len-1; ; i--, j--, k-- )	{

		t = 0;

		if( i<0 )	{

			A = '0';
			++t;
		}
		else
			A = a[i];

		if( j<0 )	{

			B = '0';
			++t;
		}
		else
			B = b[j];

		if( t==2 )
			break;

		b_str[k] = '0' + ( (A-'0') ^ (B-'0') );
	}

	assert( k==-1 );

	return b_str;
}


// BASE CONVERSION FNCS
char * BIN_2_DEC(char * bin)	{ /** Converts base2 (binary) string to base10 (decimal) string.

*/

	AP dec = new_ap( strlen(bin)+1, 0 );
	AP mult = new_ap( strlen(bin)+1, 0 );
	
	AP digit = new_ap(1, 0);
	
	AP _2 = new_ap(1, 0);
	AP _j = new_ap(10, 0);
	
	_2.major = strdup( "2" );

	int i, j;
	
	for( i=0, j=strlen(bin)-1; i<strlen(bin); i++, j-- )	{

		digit.major[0] = bin[i];
		
		sprintf(_j.major, "%d", j); // itoa()
		mult = EXP( _2, _j );
		dec = ADD( dec, MUL(digit, mult) );
	}
	
	free_ap( mult );
	free_ap( digit );
	free_ap( _2 );
	free_ap( _j );
	
	char * result = (char *)malloc( strlen(dec.major)+1 );
	result = strdup( dec.major );

	free_ap( dec );
	
	return result;
}

char * DEC_2_BIN(AP input, int packed)	{  /** This function takes a decimal (base10) AP Integer, and returns a binary (base2) string.
Does not assume string-length-boundaries of byte-padding, i.e, an input of 64 will return 1000000 (7 digits), not 01000000 (8 digits).
It is, however, a method for converting Dec->Bin.
Param "int packed" is a flag to determine if the returned binary string should be rounded in length to a multiple of 8.
In other words, 127 would be "01111111" instead of "1111111". An argument of 0 means "do not round", a non-0 value means "round up string-length to multiple of 8".
*/

	int length = 0;
	int flag = 1;

	AP t = new_ap( 1,0 );
	t.major = strdup( "0" );
	
	AP check = copy(&input);
	while ( flag )	{
		
		check=DIV_BY_2(check);

		if( DIV_BY_2_PRINT_ROWS==1 )
			printf( "\t%c%s\n", check.sign, check.major );
			
		++length;
		
		if( cmp(&check,&t)<= 0 )
			flag = 0;
	}
	
	//printf( "length := %d\n", ( packed==1 ? ((length%8==0) ? length: length + (8-(length%8))) : length) );

	AP stack[strlen(input.major)];
	char binary_stack[length+1];

	length = strlen(input.major);

	int pointer;
	int bs_pointer = 0;
	
	AP a = new_ap( length, 0 );
	
	AP result = new_ap( length, 0 );
	flag = 1;
	while( flag )	{

		pointer = 0;
		
		int i;
		for( i=0; i<length; i++ )	{
			
			a.major[i] = input.major[i];
			
			pack_trailing_zeroes( a.major, length, (length-i-1) );
			
			int dividend = a.major[i] - '0';
			int remainder = dividend % 2;
			int quotient = dividend / 2;
			
			result.major[i] = quotient + '0';
			
			// if a_substring != LSDigit (units position)
			// if it is, the remainder is noted as a binary digit 1, and the remainder itself disgarded.

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
			
			stack[pointer++] = copy(&result);

			// finally...
			
			a.major[i] = '0';
			result.major[i] = '0';
			result.major[i+1] = '0';
		}	
		

		input.major = strdup( "0" );
		for(int k = 0; k < pointer; k++ )
			input = ADD(input, stack[k]);
		
		length = strlen(input.major);
		
		int l = strlen(a.major)-strlen(input.major);
		
		for( int z=0; z<l; z++ )
			++a.major;

		pack_trailing_zeroes( a.major, length, length);
		
		AP t = new_ap(1,0);
		t.major = strdup( "0" );
		
		if( cmp(&input,&t)==0 )
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
int _2kMax(AP input)	{
	
	char * bin_string = DEC_2_BIN(input, 0);
	
	int len_bin_string = strlen(bin_string);
	
	int i = 0;
	loop:
	if( bin_string[i]=='1' )	{
		// only necessary for bit-strings with leading '0's, which is not always true for return values of DEC_2_BIN()
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

int _2kMin(AP input)	{
	
	char * bin_string = DEC_2_BIN(input, 0);
	
	int len_bin_string = strlen(bin_string);
	
	for( int i=0; i<len_bin_string; i++ )	{
		
		if( bin_string[i]=='1')	{
			
			return len_bin_string - 1 - i;
		}
	}
	
	return 0;
}


// CORE ARITHMETIC OPERATORS
AP ADD(AP a, AP b)	{
	
	int flag = 0;
	
	int size = ( strlen(b.major) > strlen(a.major) ? strlen(b.major) : strlen(a.major) );
	AP c = new_ap(size+1, 0);


	signed short int value;
	signed short int valA, valB, valC;
	
	signed int i, j, k;
	
	if( sign(&a) == sign(&b) )	{
		
		for( i=strlen(a.major)-1, j=strlen(b.major)-1, k=strlen(c.major)-1; k>0; i--, j--, k--)	{
		
			if(i>=0)
				valA = a.major[i] - '0';
			else
				valA = 0;
			
			if(j>=0)
				valB = b.major[j] - '0';
			else
				valB = 0;
			
			valC = (c.major[k] - '0');	
			
			valA += valC;

				
			value = valA + valB;

			if( value>=10 )	{
				
				value -= 10;
				c.major[k-1] += 1;
			}
			
			c.major[k] = '0' + value;
		}
	}
	else	{
		
	//Subtract the smaller absolute value from the larger absolute value and give the answer the same sign as the number with the larger absolute value
		char tsign;
		if( cmp(&a,&b)==-1 )	{
			
			tsign = b.sign;
			
			AP temp;
			temp = a;
			a = b;
			b = temp;
		}
		else
			tsign = a.sign;
		
		a.sign = '+';
		b.sign = '+';
		c = SUB(a,b);
		c.sign = tsign;
		flag = 1;
	}
	
	
	if( (tt(a,b)=='-') && (flag==0) )
		c.sign = '-';

	
	char * _ = (char *)malloc(strlen(c.major)+1);
	strcpy(_, c.major);
	for( i=0; i<(int)strlen(_); i++ )
		if( _[i] == '0' )
			++c.major;
		else
			break;
	
	free( _ );
	
	if( *c.major == '\0' )
		--c.major;
	
	return c;
}

AP SUB(AP a, AP b)	{
	
	if( (a.sign=='+') && (b.sign=='+') && ( (cmp(&a,&b)==+1) || (cmp(&a,&b)==0) ) )	{

		int i, j, k, valA, valB, valC;
		AP c = new_ap(strlen(a.major)+1,0);
		for( i=strlen(a.major)-1, j=strlen(b.major)-1, k=strlen(c.major)-1; k>0; i--, j--, k--)	{
		
			if(i>=0)
				valA = a.major[i] - '0';
			else
				valA = 0;
			
			if(j>=0)
				valB = b.major[j] - '0';
			else
				valB = 0;
			
			valC = (c.major[k] - '0');	
			
			valA += valC;

			if( valA<valB )	{
				
				c.major[k-1] -= 1;
				valA += 10;
			}

			int value = valA - valB;
			c.major[k] = '0' + value;
		}
	
		
		int len = strlen(c.major);
		char * _ = malloc(len+1);
		_ = strdup( c.major );
		for( i=0; i<len; i++ )
			if( _[i] == '0' )
				++c.major;
			else
				break;
	
		free( _ );
	
		if( *c.major == '\0' )
			--c.major;
		
		return c;
	}
	
	// Alt. SUB algorithm:
	// The subtraction of a real number (the subtrahend [B]) from another (the minuend [A]) can be defined as the addition of the minuend [A] and the additive inverse of the subtrahend [B].
	flip_sign(&b);
	AP res = ADD(a, b);
	flip_sign(&b);

	return res;
}

AP MUL(AP a, AP b)  {

	int MAX_NUM_MUL_ROWS = ( strlen(a.major)>strlen(b.major) ? strlen(a.major) : strlen(b.major) );
	
	char ** ResultArray = (char **)calloc(MAX_NUM_MUL_ROWS, sizeof(char *));
	int q = 0;

	for( int k = strlen(b.major)-1; k>=0; k-- )	{
		
		int rev_offset_B = strlen(b.major) - 1 - k;
		
		int curr_row_length = strlen(a.major) + 1 + rev_offset_B;
		char * curr_row = (char *)malloc( curr_row_length + 1 );
		curr_row[ curr_row_length ] = '\0';
		pack_trailing_zeroes( curr_row, curr_row_length, rev_offset_B );
		
		int prev_overflow = 0;
		
		int p = curr_row_length - 1 - rev_offset_B;
		
		for( int i = strlen(a.major)-1; i>=0; i-- )	{
			
			int _a = a.major[i] - '0';
			int _b = b.major[k] - '0';
			
			int result = _a * _b;
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


	AP c = new_ap(10,0);
	AP d = new_ap(10,0);
	
	for( int t = 0; t < q; t++ )	{
		
		char * result_row = ResultArray[t];
		
		if(result_row==NULL)
			assert(result_row);
		
		free( d.major );
		
		d.major = strdup(result_row);
		
		c = ADD(c, d);
	}
	
	c.sign = tt_mul(&a, &b);
	return c;
}

AP DIV(AP a, AP b)  {

	return new_ap(1, 0);
}

AP DIV_BY_2(AP a)	{
	
	int overflow = 0;
	int value;
	int i;
	for( i=0; i<strlen(a.major); i++ )	{
		
		loop:
		
		value = a.major[i] - '0';
		
		if( value>9	)	{
			// roll over the remainder, ie value=10-value
			
			int value2 = value;
			
			while( value2 >= 0 )
				value2 -= 10;
			
			value2 += 10;

			a.major[i] = '0' + value2;
			a.major[i+1] += (value % 10);	
		}

		value = a.major[i] - '0';
		
		int result = floor( value/2 );
		result += overflow;
		a.major[i] = result + '0';
		
		if( a.major[i] - '0' >= 10 )
			goto loop;
		
		if( value%2!= 0 )
			overflow = 5;
		else
			overflow = 0;

	}
	
	a.major[i] = '\0'; //NULL
	
	int len = strlen( a.major );
	for( i=0; i<len; i++ )
		if( a.major[i]=='0' )	{
			
			++a.major;
			--len;
			--i;
		}
		else
			break;

	if( a.major[0]=='\0' )
		--a.major;
	
	return a;
}

AP EXP(AP a, AP b)	{
	
	// if b (exp) is negative, flip sign.
	if( sign(&b)=='-' )	{
		
		b.sign='+';
		printf("Exponent is negative. Converting to positive (%c%s)\n", b.sign, b.major );
	}
	
	// a * a, b-1 times
	// if b=0, result = 1
	AP c = new_ap(1, 0);
	c.major = strdup( "1" );
	
	AP temp = new_ap(1,0);
	temp.major = strdup( "0" );
	
	if( cmp(&b,&temp)==0 )	{
		
		return c;
	}
	else	{
		
		AP d = SUB(b, c);
		AP e = new_ap(1,0);
		e.major = strdup( "0" );
		AP result = copy(&a);
		while( cmp(&d, &e)==+1 )	{
			
			result = MUL(result, a);
			d = SUB(d,c);
		}
		
		if( sign(&a)=='-' )
			result.sign='-';
		
		return result;
	}
}


// VARIOUS MATH FNCS
int LCM(int a, int b, int flag)	{

	signed int M1 = 0, M2 = 0;
	#define MAX_ITER 4096
	int R1[MAX_ITER] = {0}, R2[MAX_ITER] = {0};
	int val = 1, inc = 0, match = 0;

	if(flag)
		val = 2;
	
	M1 = a; M2 = b;
	
	while (!match)	{
		
		if (inc >= MAX_ITER)	{
			
			printf("Overflow error: More than %d iterations required.\n", MAX_ITER);
			exit(1);
		}
		
		R1[inc] = (int)M1*val; R2[inc] = (int)M2*val;
		
		match = lcm_test(inc, R1, R2);
		
		++inc;
		++val;
	}
	
	//printf("The LCM for %d and %d is %d.\n", M1, M2, R1[inc-1]);

	return R1[inc-1];
}

int lcm_test(int max, int R1[], int R2[])	{
	
	for (int a = 0; a <= max; a++)
		for (int b = 0; b <= max; b++)
			if (R1[a]==R2[b])
				return 1;
			
	return 0;
}

int lcm_example(int argc, char **argv)	{
	
	int flagSet = 0;
	
	if((argc == 4) && (argv[3][0] == '-') && (argv[3][1] == 'n'))	{
		
		//printf("Flag set!\n");
		flagSet = 1;
	}
	
	int a = str2int(argv[1]);
	int b = str2int(argv[2]);
	
	int lcm = LCM(a, b, flagSet);
	int gcd = 1; // = GCD(a, b, lcm);
	
	printf( "lcm := (%d)\ngcd := (%d)\n", lcm, gcd );
	
	return 0;
}


// CREATE, DUPLICATE, RESET & FREE AP TYPE FNCS
AP new_ap(int maj, int min)	{

	AP result;
	result.major = (char *)malloc(maj+1);
	result.minor = (char *)malloc(min+1);
	
	if( (result.major==NULL)||(result.minor==NULL) )	{
		
		printf("AP new_ap(...) failed 1 or 2 of 2 malloc() calls! Exiting...\n");
		exit(0);
	}
	
	int i;
	
	for( i=0; i<maj; i++)
		result.major[i] = '0';
	
	result.major[maj] = '\0';
	
	for( i=0; i<min; i++)
		result.minor[i] = '0';
	
	result.minor[min] = '\0';

	result.length = maj + min;
	result.major_length = maj;
	result.minor_length = min;
	
	result.sign = '+';
	return result;
}

AP copy(AP * a)	{
	
	AP _ = new_ap(strlen(a->major),strlen(a->minor));
	
	strcpy(_.major, a->major);
	strcpy(_.minor, a->minor);
	
	_.sign = a->sign;
	
	_.length = a->length;
	_.major_length = a->major_length;
	_.minor_length = a->minor_length;
	
	return _;
}

void clear(AP * a)	{
	
	int i;
	for( i=0; i< (int)strlen(a->major); i++)
		a->major[i] = '0';
	
	a->major[i] = '\0';
	
	for( i=0; i< (int)strlen(a->minor); i++)
		a->minor[i] = '0';
	
	a->minor[i] = '\0';
	
	a->sign = '+';
}

void free_ap(AP a)	{
	
	free( a.major );
	free( a.minor );
}		


// SIGN FNCS
char sign(AP * a)	{

	return a->sign;
}

void set_sign(AP * a, char sym)	{

	if( sym!='+' && sym!='-' )
		sym='+';
	
	a->sign = sym;
}

void flip_sign(AP * a)	{

	if( a->sign == '-' )
		a->sign = '+';
	else
		a->sign = '-';
}

char tt(AP a, AP b)	{
	
	signed int ag = cmp(&a,&b);
	
	if( (sign(&a)=='+') && (sign(&b)=='+') ) // x2, a < b, a > b
		return '+';
	
	if( (ag==-1) && (a.sign=='-') && (b.sign=='+') )
		return '+';
	
	if( (ag==-1) && (a.sign=='-') && (b.sign=='-') )
		return '-';
	
	if( (ag==-1) && (a.sign=='+') && (b.sign=='-') )
		return '-';
	
	
	if( (ag==+1) && (a.sign=='-') && (b.sign=='-') )
		return '-';

	if( (ag==+1) && (a.sign=='+') && (b.sign=='-') )
		return '+';
	
	if( (ag==+1) && (a.sign=='-') && (b.sign=='+') )
		return '-';
	
	return '+';
	
}

char tt_mul(AP * a, AP * b)	{

	if( sign(a)!=sign(b) )
		return '-';
	
	return '+';
}


// GENERAL HELPER FNCS
signed short int cmp(AP * a, AP * b)	{
	
	
	while( *(a->major)=='0' )
		++a->major;
	
	while( *(b->major)=='0' )
		++b->major;
	
	int len_a = strlen(a->major);
	int len_b = strlen(b->major);
	
	if( len_a<len_b )
		return -1;
	
	if( len_a>len_b )
		return +1;
	
	for( int test=0; test<len_a; test++ )	{
		
		if( a->major[test]>b->major[test] )
			return +1;
		
		if( a->major[test]<b->major[test] )
			return -1;
	}
	
	return 0;
}

signed int overflow(AP * c, int result, signed int k) {
  
  if( (k-1) < 0 ) {
    
    char * temp = (char *)malloc(strlen(c->major) + 1 + 1);
	
    if( temp==NULL )  {
      
      printf("AP MUL(...) malloc() call failed to allocate block! Exiting.\n");
      exit(1);
    }
    
    temp[0] = '0';
    
    int x;
    for(x = 0; x < strlen(c->major); x++) {
      
      temp[x+1] = c->major[x];
    }
    temp[x+1] = 0;
    
    
    free( c->major );
    c->major = temp;
    
  }
  
  
  // 1. get lmost digit of result (1-8)
  
  short int rd = result % 10;
  short int td = (result - rd);
  short int ld = 0;
  
  while(td>0) {
  
    ++ld;
    td = td - 10;
  }
  
  c->major[k] = '0' + rd;
  

  short int iresult = ld+(c->major[k-1] - '0');
  
  if( iresult <= 9 )  {
      
    c->major[k-1] = '0' + iresult;
      
  }
  else  {
    
    // if c[k-1] + ld > 9, recursive overflow, will need to deal with here!
    printf("Recursive overflow! Line %d-ish.\n", __LINE__);
    k = overflow(c, iresult, k-1);
    
  }
    
  return k-1;
  // remember, overflow can be from 1 t0 8! If [k-1] >= 2, itself may additively overflow to [k-2];

}

int MSD(int num)	{
	
  short int rd = num % 10;
  short int td = (num - rd);
  int ld = 0;
  
  while(td>0) {
  
    ++ld;
    td = td - 10;
  }
  
  return ld;
}

void pack_trailing_zeroes( char * curr_row, int array_length, int num_zeroes )	{
	
	curr_row[array_length] = 0;
	
	while( num_zeroes > 0 )	{
		
		--array_length;
		
		curr_row[array_length] = '0';
		
		--num_zeroes;
	}
}

char * fill_leading_zeroes( char * str, int num_zeroes )	{

	char * _ = (char *)malloc( strlen(str) + num_zeroes + 1 );
	
	int i;
	for( i=0; i<num_zeroes; i++ )
		_[i] = '0';
	
	strcat( _, str );
	
	return _;
}

int str2int(char *input)	{
	
	int len = strlen(input), i = 0, result = 0;
	
	if (input[0] == '-')
		i = 1;

	for(; i<len; i++)
		result = result * 10 + ( input[i] - '0' );
	
	if (input[0] == '-')
		result = 0 - result;
	
	return result;
}

 char * int2str(int v)	{
	
	char * str = (char *)malloc(32);
	
	sprintf(str, "%d", v); // itoa()
	
	return str;
}
