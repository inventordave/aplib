// APlib.h

// Make this any number of bytes you want. The new(int, int) function will +1 for the '\0' null-terminator. Default = 1023.
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


AP new(ollie maj, ollie min);
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
				NEW_LINE;
			break;
		}
		
		if(i==end)
			return;
	}
}

