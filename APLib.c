// APlib.c

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "APLib.h"
#include "Dave_IEEE754.h"


int main(int argc, char **argv)	{
	
	int y = str2int(argv[1]);
	int x = _2k_BinarySearch(y);
	
	printf("Nearest Max 2k exponent for value %d is %d\n", y, x);
	
	
	return 0;
	/**
	AP _a = new_ap( strlen(argv[1]), 0 );
	_a.major = strdup( argv[1] );
	int result1 = _2kMax(_a);
	int result2 = _2kMin(_a);
	
	printf( "For value '%s', the nearest Max 2k-form is 2 ^ %d, nearest Min 2k-form is 2 ^ %d\n", _a.major, result1, result2 );
	
	return 0;
	*/
	
	AP a = new_ap( strlen(argv[1]), 0 );
	a.major = strdup( argv[1] );
	
	char * result = DEC_2_BIN(a);
	printf( "String = %s\n", result );
	
	return 0;
	
	
	if( argc < 3 )	{
		
		printf("Please pass 2 (possibly signed) integers on the cmd-line, and invoke the program again. Exiting...\n");
		exit(0);
	}
	
	NL;
	
	AP A, B, C;
	A = new_ap( 10, 0 );
	B = new_ap( 10, 0 );
	
	// Arg A
	if( argv[1][0] == '-' )	{
		
		A.sign = '-';
		++argv[1];
		A.major = strdup(argv[1]);
	}
	else if( argv[1][0] == '+' )	{

		A.sign = '+';
		++argv[1];
		A.major = strdup(argv[1]);
		
	}
	else	{
		
		A.major = strdup(argv[1]);
		A.sign = '+';
	}
	
	// Arg B
	if( argv[2][0] == '-' )	{
		
		B.sign = '-';
		++argv[2];
		B.major = strdup(argv[2]);
	}
	else if( argv[2][0] == '+' )	{

		B.sign = '+';
		++argv[2];
		B.major = strdup(argv[2]);
		
	}
	else	{
			
		B.sign = '+';
		B.major = strdup(argv[2]);
	}
	
	printf( "Values Entered:\na = %c%s\nb = %c%s\n", A.sign, A.major, B.sign, B.major );
	
	NL;
	
	// ADD
	C = ADD(A, B);
	printf( "%c%s ADD %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	NL;
	
	// SUB
	C = SUB(A, B);
	printf( "%c%s SUB %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	NL;

	// MUL
	C = MUL(A, B);
	printf( "%c%s MUL %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	NL;
	
	// EXP
	C = EXP(A, B);
	if( C.sign=='-' )
		B.sign='+';
	
	printf( "%c%s EXP %c%s = %c%s\n", A.sign, A.major, B.sign, B.major, C.sign, C.major );
	
	printf( "\nCompleted.\n" );
	
	return 0;
}


// This function takes a decimal AP Integer, and returns a char * binary-format string.
// Does not assume string-length-binaries of byte-padding, i.e, an input of 64 will return 1000000 (7 digits), not 01000000 (8 digits).
// It is, however, a method for converting Dec->Bin.
char * DEC_2_BIN(AP input)	{ 

	int length = strlen(input.major);
	int flag = 1;
	AP stack[length];
	
	
	char binary_stack[256];
	int pointer;
	int bs_pointer = 0;
	
	AP a = new_ap( length, 0 );
	
	AP result = new_ap( length, 0 );
	
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
	
	for(int k=0; k<bs_pointer; k++)	{
		
		b_str[k] = binary_stack[bs_pointer-1-k];
	}
	
	return b_str;
}


int _2kMax(AP input)	{
	
	char * bin_string = DEC_2_BIN(input);
	
	int len_bin_string = strlen(bin_string);
	
	if( bin_string[0]=='1' ) // only necessary for bit-strings with leading '0's, which is not true for return values of DEC_2_BIN()
	for( int i=1; i < len_bin_string; i++ )	{
		
		if( bin_string[i]=='1' )	{
			
			return len_bin_string;
		}
	}

	return len_bin_string-1;
}

int _2kMin(AP input)	{
	
	char * bin_string = DEC_2_BIN(input);
	
	int len_bin_string = strlen(bin_string);
	
	for( int i=0; i<len_bin_string; i++ )	{
		
		if( bin_string[i]=='1')	{
			
			return len_bin_string - 1 - i;
		}
	}
	
	return 0;
}


AP EXP(AP a, AP b)	{
	
	// if b (exp) is negative, flip sign.
	
	if( sign(&b)=='-' )	{
		
		b.sign='+';
		printf("\nExponent is negative. Converting to positive (%c%s)\n", b.sign, b.major );
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
  
  return a;
  
  // return ( result = 1/(MUL(a,b) )
}


signed short int cmp(AP * a, AP * b)	{
	
	ollie len_a = strlen(a->major);
	ollie len_b = strlen(b->major);
	
	if( len_a<len_b )
		return -1;
	
	if( len_a>len_b )
		return +1;
	
	for( ollie test=0; test<len_a; test++ )	{
		
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
    
    ollie x;
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



AP new_ap(ollie maj, ollie min)	{

	AP result;
	result.major = (char *)malloc(maj+1);
	result.minor = (char *)malloc(min+1);
	
	if( (result.major==NULL)||(result.minor==NULL) )	{
		
		printf("AP new_ap(...) failed 1 or 2 of 2 malloc() calls! Exiting...\n");
		exit(0);
	}
	
	ollie i;
	
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
	
	ollie i;
	for( i=0; i< (ollie)strlen(a->major); i++)
		a->major[i] = '0';
	
	a->major[i] = '\0';
	
	for( i=0; i< (ollie)strlen(a->minor); i++)
		a->minor[i] = '0';
	
	a->minor[i] = '\0';
	
	a->sign = '+';
}
		

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

short int maximum(short int a, short int b)	{

	if( b>a )
		return b;
	
	return a;
}

short int minimum(short int a, short int b)	{
	
	if( b<a )
		return b;
	
	return a;
}

