// APlib.h

typedef struct	{

	char * major;
	char * minor;
	char sign;
	
} FP;

const unsigned char COMPLETE = 0;
const unsigned char MAJOR = 1;
const unsigned char MINOR = 2;

unsigned char PART = COMPLETE;

void copy(FP * out, FP * in);

void next(unsigned char * PART)	{
	
	*PART -= 1;
}
char sign(FP * in)	{

	in->sign = (in->sign == '+' ? '-' : '+');
	
	return in->sign;
}

FP createFP(int major, int minor);

FP PLUS(FP A, FP B);
FP MINUS(FP A, FP B);

