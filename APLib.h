// APlib.h

#ifndef DAVE_APLIB
#define DAVE_APLIB

// Make this any number of bytes you want. The new_ap(int, int) function will +1 for the '\0' null-terminator. Default = 1023.
#define MAX_LENGTH_AP_PART 1023
// ((2^8)^8)^4 is probably the magnitude of MAX_VALUE (long long int) on 64-bit Intel-ISA-compatible architectures
// or, 2^(8*8*4), or, 2^256 (64*4)

#define NEW_LINE printf("\n")
#define NL NEW_LINE

#define ollie unsigned long long int
typedef struct	{

	char * major;
	char * minor;
	char sign;
	
	ollie length;
	ollie major_length;
	ollie minor_length;
	
} AP;

void free_ap(AP a)	{
	
	free( a.major );
	free( a.minor );
}

int MSD(int num);
void pack_trailing_zeroes( char * curr_row, int array_length, int num_zeroes );

typedef struct	{
	
	AP n;
	AP m;
	
	char sign;
	
} N_M;

#define EXTEND_STRING 		\
		char * temp = malloc( strlen(c.major) + 1 + l); \
		strcpy( temp, c.major ); \
		\
		for(int x=0; x < l; x++)	{	\
			\
			strcat( temp, "0");	\
		}	\
		\
		free( c.major ); \
		c.major = temp;


AP new_ap(ollie maj, ollie min);
void clear(AP * a);
AP copy(AP * a);
void flip_sign(AP * a);
void set_sign(AP * a, char sym);
char sign(AP * a);

signed short int cmp(AP *, AP *);
signed int overflow(AP * c, int result, signed int k);
char tt(AP a, AP b);
char tt_mul(AP * a, AP * b);

AP ADD(AP a, AP b);
AP SUB(AP a, AP b);

AP MUL(AP a, AP b);
AP DIV(AP a, AP b);

AP EXP(AP a, AP b);

char * DEC_2_BIN(AP input, int packed);
char * BIN_2_DEC(char * bin);
AP DIV_BY_2(AP a);
int _2kMax(AP input);
int _2kMin(AP input);

int str2int(char *input);

char * int2str(int v);



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
	
	return a;
}


char * BIN_2_DEC(char * bin)	{

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


// This function takes a decimal AP Integer, and returns a char * binary-format string.
// Does not assume string-length-binaries of byte-padding, i.e, an input of 64 will return 1000000 (7 digits), not 01000000 (8 digits).
// It is, however, a method for converting Dec->Bin.
// Param "int packed" is a flag to determine if the returned binary string should be rounded in length to a multiple of 8.
// In other words, 127 would be "01111111" instead of "1111111". An argument of 0 means "do not round", a non-0 value means
// "round up string-length to multiple of 8".
char * DEC_2_BIN(AP input, int packed)	{ 

	int length = 0;
	
	int flag = 1;

	AP t = new_ap( 1,0 );
	t.major = strdup( "0" );
	
	AP check = copy(&input);
	while ( flag )	{
		
		check=DIV_BY_2(check);
		++length;
		
		if( cmp(&check,&t)<= 0 )
			flag = 0;
	}
	
	
	printf( "length := %d\n", ( packed==1 ? ((length%8==0) ? length: length + (8-(length%8))) : length) );

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


int _2kMax(AP input)	{
	
	char * bin_string = DEC_2_BIN(input, 0);
	
	int len_bin_string = strlen(bin_string);
	
	if( bin_string[0]=='1' ) // only necessary for bit-strings with leading '0's, which is not always true for return values of DEC_2_BIN()
	for( int i=1; i < len_bin_string; i++ )	{
		
		if( bin_string[i]=='1' )	{
			
			return len_bin_string;
		}
	}

	return len_bin_string-1;
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
  
/**

	a[i-end] = a[i] + '0' * end
	
	for( b=0; b<strlen(b); b++ )
		


a = 1242
b = 26

47.769....





*/

 return new_ap(1, 0);

}


signed short int cmp(AP * a, AP * b)	{
	
	
	while( *(a->major)=='0' )
		++a->major;
	
	while( *(b->major)=='0' )
		++b->major;
	
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


void print_ASCII(char start, char end)	{
	
	if( (start<32 || end<32) )	{
		
		printf("A scurrilous attempt was made to print the non-printable ascii characters below codepoint 32. Or even those new-fangled extended-ascii characters above codepoint 127. This is an outrage, and the function is immediately returning!");
		return;
	}
	
	if( start>end )	{
	
		char temp;
		temp = start;
		start = end;
		end = temp;
	}
	
	for( signed short int i=start; ; i+=5 )	{
		
		if( i>end )
			i = end;
		
		char j=(char)i;
		signed int k = (end-i);
		
		if( k>4 )
			k=4;
		
		switch(k)
		{
			case 4:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 3:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 2:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 1:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 0:
				printf("[%d]:=(%c)", j, j);
			default:
				NL;
			break;
		}
		
		if(i==end)
			return;
	}
}

#endif