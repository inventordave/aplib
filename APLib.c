// APlib.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <windows.h>
#include <signal.h>
#include <assert.h>

#include "APLib.h"


int main(int argc, char **argv)	{
	

	//print_ASCII(32, 126);
	
	if( argc>1 )
		
	if( !strcmp(argv[1], "ascii") )	{
	
		char start, end;
		if(argc>=3)
			start = (char)atoi(argv[2]);
		else
			start = 32;
		
		if(argc>=4)
			end = (char)atoi(argv[3]);
		else
			end = 127;
		
		print_ASCII( start, end );
		exit(0);
	}
	
	if( argc < 3 )	{
		
		printf("Please pass 2 (possibly signed) integers on the cmd-line, and invoke the program again. Exiting...\n");
		exit(0);
	}
	
	NL;
	
	AP A, B, C;
	A = new( 10, 0 );
	B = new( 10, 0 );
	
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
	
	printf("Values Entered:\na = %c%s\nb = %c%s\n", A.sign, A.major, B.sign, B.major);
	
	NL;
	
	// ADD
	C = ADD(A, B);
	printf("%c%s ADD %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major);
	
	NL;
	
	// SUB
	C = SUB(A, B);
	printf("%c%s SUB %c%s = %c%s", A.sign, A.major, B.sign, B.major, C.sign, C.major);
	
	printf("\n");
	
	//printf("Hmmm....\n");
	
	//printf("A = %s, B = %s\n", A.major, B.major);
	// MUL
	C = MUL(A, B);
  printf("%c%s MUL %c%s = %c%s\n", A.sign, A.major, B.sign, B.major, C.sign, C.major);
	
	printf("\nCompleted.\n");
	exit(0);

}


AP ADD(AP a, AP b)	{
		
	int size = ( strlen(b.major) > strlen(a.major) ? strlen(b.major) : strlen(a.major) );
	AP c = new(size+1, 0);
	//clear(&c);

	// temporary catch
	// if abs(a)>=abs(b) && sign(a)=='-' then sub(a,b), set_sign(c, '-')
	
	if( ( abs(atoi(a.major))>abs(atoi(b.major)) ) && sign(&a)=='-' )	{
		
		set_sign(&a, '+');
		
		if( sign(&b)=='+' )
			c = SUB(a,b);

		else	{

			set_sign(&b, '+');
			c = ADD(a, b);
		}
		
		set_sign(&c, '-');
		return c;
	}

	signed short int value;
	signed short int valA, valB, valC;

	signed int i, j, k;
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
		
		
		if( sign(&a) == '-' )
			valA = 0 - valA;

		if( sign(&b) == '-' )
			valB = 0 - valB;
		
		
		loop_:
		
		value = valA + valB + valC;
		
		if( value<0 )	{
			
			c.major[k-1] -= 1;
			
			valA += 10;
			goto loop_;

		}

		else if( value>=10 )	{
			
			c.major[k] = '0' + (value - 10);
			c.major[k-1] += 1;
		}

		else
			c.major[k] = '0' + value;
	}
	
	if( c.major[0] < '0' )
		c.major[0] = '0' + ('0' - c.major[0]);
	
	
	if( tt(a,b)=='-' )
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
	
	AP c;

	/**
	Subtraction is anti-commutative, meaning that if one reverses the terms in a difference left-to-right, the result is the negative of the original result. Symbolically, if a and b are any two numbers, then

	a − b = −(b − a)
	*/
	if( cmp(a,b)==-1 )	{

		c = SUB(b,a);
		flip_sign(&c);
		
		return c;
	}
	
	// SUB algorithm:
	// The subtraction of a real number (the subtrahend [B]) from another (the minuend [A]) can be defined as the addition of the minuend [A] and the additive inverse of the subtrahend [B].
	flip_sign(&b);
	c = ADD(a, b);
	

	return c;
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

AP MUL(AP a, AP b)  {

	#define MAX_NUM_MUL_ROWS 100
	
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


	AP c = new(10,0);
	AP d = new(10,0);
	
	for( int t = 0; t < q; t++ )	{
		
		char * result_row = ResultArray[t];
		
		if(result_row==NULL)
			continue;
		
		d.major = strdup(result_row);
		
		c = ADD(c, d);
	}
	
	return c;
}

AP DIV(AP a, AP b)  {
  
  return a;
}


signed short int cmp(AP a, AP b)	{
	
	ollie len_a = strlen(a.major);
	ollie len_b = strlen(b.major);
	
	if( len_a<len_b )
		return -1;
	
	if( len_a>len_b )
		return +1;
	
	for( ollie test=0; test<len_a; test++ )	{
		
		if( a.major[test]>b.major[test] )
			return +1;
		
		if( a.major[test]<b.major[test] )
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



char tt(AP a, AP b)	{
	
	if( (sign(&a)=='+') && (sign(&b)=='+') ) // x2, a < b, a > b
		return '+';
	
	if( ( cmp(a, b)==-1 ) && (a.sign=='-') && (b.sign=='+') )
		return '+';

	if( ( cmp(a, b)==+1 ) && (a.sign=='+') && (b.sign=='-') )
		return '+';
	
	return '-';
}

AP new(ollie maj, ollie min)	{

	AP result;
	result.major = (char *)malloc(maj+1);
	result.minor = (char *)malloc(min+1);
	
	if( (result.major==NULL)||(result.minor==NULL) )	{
		
		printf("AP new(...) failed 1 or 2 of 2 malloc() calls! Exiting...\n");
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
	
	AP _ = new(strlen(a->major),strlen(a->minor));
	
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

