// APlib.h

typedef struct	{

	char * major;
	char * minor;
	char sign;
	
} FP;

void copy(FP * out, FP * in);

char sign(FP * in)	{

	in->sign = (in->sign == '+' ? '-' : '+');
	
	return in->sign;
}

FP createFP(int major, int minor);

FP PLUS(FP A, FP B);
FP MINUS(FP A, FP B);

