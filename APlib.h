// APlib.h

// Make this any number of bytes you want. The new(int, int) function will +1 for the '\0' null-terminator. Default = 1023.
#define MAX_LENGTH_AP_PART 1023
// ((2^8)^8)^4 is probably the magnitude of MAX_VALUE(long long int) on 64-bit Intel-ISA-compatible architectures
// or, 2^(8*8*4), or, 2^256

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

AP new(ollie maj, ollie min);
void clear(AP * a);

void flip_sign(AP * a);
void set_sign(AP * a, char sym);
char sign(AP * a);

signed short int cmp(AP a, AP b);
char tt(AP a, AP b);

AP ADD(AP a, AP b);
AP SUB(AP a, AP b);

// SUB(A,B): if ( abs(b) > abs(a)), flip_sign(sub(b,a))

