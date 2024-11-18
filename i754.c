#include "i754.h"
#include "stringy.h"

// DEV FOR HARDWARE OPTIMIZATION of aplib

float = 32 bits,
double = 64 bits,

In (n * m), if m := 2k-form, eg, n*2,n*4,n*8,n*16 etc, then a BIT-SHIFT LEFT will work for integers. BIT-SHIFT RIGHT is division.

	10/2	5
	10/3	3.3333
	10/4	2.5
	
	100/2	50
	100/3	33.3333
	100/4	25
	
	32 bits can store [0, 4294967295], which is a max of 10 digits.
	64 bits is [0, 18446744073709551615], which is 20 digits.
	128 bits should be 40 digits [0, 340282366920938463463374607431768211455].


1/n = 1/a + 1/b + 1/c + 1/d + 1/e + 1/f .....
where a + b + c + d + e + f... <= n




loop:

x = 2;
y = (n - x);
if( y <= 2x	)	{

	x *= 2;

	if( y == 2x )
		push( y );
}





/////////

// DAVELIB::i754::Interface
struct i754 getInterface_i754()	{ return *(initi754()); }
struct i754 * initi754()	{
	
	struct i754 * lib = malloc( sizeof(struct i754) );
	
	lib->readFloat = IEEE_readFloat;
	lib->readDouble = IEEE_readDouble;
	
	lib->convertFloatString2BigEndian = IEEE_convertFloatString2BigEndian;
	lib->convertDoubleString2BigEndian = IEEE_convertDoubleString2BigEndian;
	
	lib->getFloatBit = IEEE_getFloatBit;
	lib->getDoubleBit = IEEE_getDoubleBit;
	
	lib->writeFloat = IEEE_writeFloat;
	lib->writeDouble = IEEE_writeDouble;
	
	return lib;
}




// BITWISE FNCS //

// THE FUNCTION BELOW ADDS 1 TO A BINARY STRING
char* INCB( char* bstr ){

	int i = strlen( bstr );
	
	//char align = i % 8;
	// if 0, the bit-string is byte-aligned.
	// otherwise, align contains the 8-p misalignment.
	// (8-align) leading 0's would need to be padded.
	
	char* _ = (char*)malloc( i+1 );
	
	for( int k=0; k<=i; k++ )
	_[k] = bstr[k];
	
	
	--i;
	
	// if odd (bit 0 = 0), flip bit to add 1.
	if( _[i]=='0' )
		_[i] = '1';
	
	// value is even, so need to shift the bit substring left.
	else{
		while( _[i]=='1' )	{
			
			_[i] = '0';
			--i;
			
			if( i<0 )
				break;
		}
		
		if( i<0 ){
		// bitsring needs to be extended
		}
		else
		_[i] = '1';
	}

	return _;
}

// THE FUNCTION BELOW FLIPS (INVERTS) A BIT-STRING
char* FLIPB( char* bstr ){

	int dcount = strlen(bstr);
	char* _ = (char*)malloc( dcount+1 );
	
	int i;
	
	// invert inbound bitstring
	for( i=0; i<dcount; i++ )
		if( bstr[i]=='1' )
			_[i] = '0';
		else
			_[i] = '1';
	
	_[i] = '\0';
	
	return _;
}

// THIS FUNCTION CALCULATES THE 2'S COMPLEMENT OF A BIT-STRING.
// DEP: FLIPB( char* ), INCB( char* )
char* _2sComplement( char* bstr )	{

	char* _ = INCB( FLIPB( bstr ) );
	//printf( "2's-Complement of %s is: %s\n", bstr, _ );

	return _;
}



// CORE FNCS
struct i754_Float * IEEE_writeFloatStruct( float * f )	{
	
	struct i754_Float * a = (struct i754_Float *)malloc( sizeof(i754_Float) );
	
	//char * i = (char *)a;
	
	char * k = (char *)f;
	
	a->sign = (int) ( (k[3] & 0b10000000 ) >> 7 );
	a->exponent = (int) ((unsigned)k[3]) & 0b01111111;
	
	char * temp = (char *)malloc(25);
	char * section = (char *)malloc(9);
	
	char * f_str = IEEE_readFloat( *f );
	
	// 24 bits
	a->significand = (int) (str2int( IEEE_convertFloatString2BigEndian(f_str) /*k[2] . k[1] . k[0]*/) & 0b00000000111111111111111111111111);
	
	printf( "a->significand = %d\n", a->significand );
	
	free( temp );
	free( section );
	
	return a;
}
float IEEE_readFloatStruct( struct i754_Float* f )	{

	float a;
	
	char * str = (char *)malloc(33);
	str[32] = '\0';
	
	str[24] = '0' + f->sign;
	
	int i;
	for( i=0; i<24; i++ )
		str[i] = '0' + ( ( f->significand & (1 << (23-i))     )?1:0 );
	
	for( i=25; i<32; i++ )
		str[i] = '0' + ( ( f->exponent &    (1 << ((32-i)-7)) )?1:0 );
	
	IEEE_writeFloat( &a, str );
	return a;
}		
char * IEEE_convertDoubleString2BigEndian( char * str )	{
	
	char * be_string = malloc(64 + 1);
	
	int offset = 0;
	
	int i;

	for( i=63; i<63+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';

	for( i=54; i<54+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=45; i<45+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';

	for( i=36; i<36+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=27; i<27+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=18; i<18+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=9; i<9+8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=0; i<8; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset] = '\0';
	
	return be_string;
}
char * IEEE_convertFloatString2BigEndian( char * str )	{
	
	char * be_string = malloc(32 + 1);
	
	int offset = 0;
	
	int i;
	
	for( i=24; i<32; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=16; i<24; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=8; i<16; i++ )
		be_string[offset++] = str[i];
	
	//be_string[offset++] = ' ';
	
	for( i=0; i<8; i++ )
		be_string[offset++] = str[i];
	
	be_string[offset] = '\0';
	
	return be_string;
}

char * IEEE_readFloat( float f )	{

	typedef struct container	{

		float f;

	} container;
	
	struct container * tc = (struct container *)malloc( sizeof(float) ); // 4 bytes for the float. Change to sizeof(double), which is 8, for a double.
	
	tc->f = f;
	
	char * offset = (char *) tc;
	char * str = malloc(32 + 1); // 3 for the in-between spaces, 1 for the null-terminator of the string.
	// double := 64 + 7 + 1
	
	int ptr = 0;

	for(int i=0; i<4; i++)	{ // iterate through each of the 4 bytes of the float. (change to 8 when parsing a double.)
		
		for(int k=7; k>=0; k--)	{ // iterate from the MSB (bit 7), to the LSB (bit 0) of an individual byte of the memory.
			
			int r = (*offset) & (1 << k); // is bit 'k' of offset pointer set to 1, or not? In other words, is the &-exp TRUE, or FALSE?
			if( r==0 )
				str[ptr++] = '0';
			else
				str[ptr++] = '1';
		}
		
		++offset; // move pointer "char * offset" along the struct 1 byte
		
		//str[ptr++] = ' ';
	}
		
	str[ptr] = '\0';
	
	return str; // !string returned is little-endian on a little-endian system.
}
char * IEEE_readDouble( double f )	{

	typedef struct container	{

		double f;

	} container;
	
	struct container * tc = malloc( sizeof(double) ); // 4 bytes for the float. Change to sizeof(double), which is 8, for a double.
	
	tc->f = f;
	
	char * offset = (char *) tc;
	char * str = malloc(64 + 1); // 3 for the in-between spaces, 1 for the null-terminator of the string.
	// double := 64 + 7 + 1
	
	int ptr = 0;

	for(int i=0; i<8; i++)	{ // iterate through each of the 4 bytes of the float. (change to 8 when parsing a double.)
		
		for(int k=7; k>=0; k--)	{ // iterate from the MSB (bit 7), to the LSB (bit 0) of an individual byte of the memory.
			
			int r = (*offset) & (1 << k); // is bit 'k' of offset pointer set to 1, or not? In other words, is the &-exp TRUE, or FALSE?
			if( r==0 )
				str[ptr++] = '0';
			else
				str[ptr++] = '1';
		}
		
		++offset; // move pointer "char * offset" along the struct 1 byte
		
		//str[ptr++] = ' ';
	}
		
	str[ptr] = '\0';
	
	return str; // !string returned is little-endian on a little-endian system.
}

void IEEE_writeFloat(float * dest, char * str)	{
	
	assert( strlen(str)==(32) );
	
	char * mem = (char *)dest;
	char bitmask;
	
	int offset = 0;
	for( int i=0; i<4; i++ )	{

		bitmask = 0;

		for( int k=0; k<8; k++ )
			bitmask += (str[offset++] - '0') << (7 - k);

		(mem[i]) = bitmask;
	}
}
void IEEE_writeDouble(double * dest, char * str)	{
	
	assert( strlen(str)==(64) );
	
	char * mem = (char *)dest;
	char bitmask;
	
	for( int i=0; i<8; i++ )	{
		
		int offset = 0;
		bitmask = 0;

		for( int k=0; k<8; k++ )
			bitmask += (str[offset++] - '0') << (7 - k);

		(mem[i]) = bitmask;
	}
}

char* IEEE_getFloatBit( char * str, LARGE offset )	{
	
	if( offset>(31) )
		return ADD( AP1,AP1 )->integer;
	
	//if( offset==8 offset==17 offset==26 )
		//++offset;
	
	if( str[offset]=='1' )
		return AP1->integer;
	else
		return AP0->integer;
}
char* IEEE_getDoubleBit( char * str, LARGE offset )	{
	
	if( offset>(63) )
		return ADD( AP1,AP1 )->integer;
	
	//if( offset==8 offset==17 offset==26 offset==35 offset==44 offset==53 offset==62 )
		//++offset;
	
	if( str[offset]=='1' )
		return AP1->integer;
	else
		return AP0->integer;
}

