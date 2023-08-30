#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static signed int M1 = 0, M2 = 0;
#define MAX_ITER 4096
static int R1[MAX_ITER] = {0}, R2[MAX_ITER] = {0};
static int val = 1, inc = 0, match = 0;

int str2int(char *);
inline int test(int);
int LCM(int, int, int);
int GCD(int a, int b, int lcm);


int LCM(int a, int b, int flag)	{

	if(flag)	{
		
		//printf("Flag set!\n");
		val = 2;
	}
	
	M1 = str2int(argv[1]); M2 = str2int(argv[2]);
	
	while (!match)	{
		
		if (inc >= MAX_ITER)	{
			
			printf("Overflow error: More than %d iterations required.\n", MAX_ITER);
			exit(1);
		}
		
		R1[inc] = (int)M1*val; R2[inc] = (int)M2*val;
		
		match = test(inc);
		
		++inc;
		++val;
	}
	
	//printf("The LCM for %d and %d is %d.\n", M1, M2, R1[inc-1]);

	return R1[inc-1];
}

int main_lcm(int argc, char **argv)	{
	
	int flagSet = 0;
	
	if((argc == 4) && (argv[3][0] == '-') && (argv[3][1] == 'n'))	{
		
		//printf("Flag set!\n");
		flagSet = 1;
	}
	
	int a = str2int(argv[1]);
	int b = str2int(argv[2]);
	
	int lcm = LCM(a, b, flagSet);
	int gcd = 1 // = GCD(a, b, lcm);
	
	printf( "lcm := (%d)\ngcd := (%d)\n", lcm, gcd );
	
	return 0;
}

inline int test(int max)	{
	
	for (int a = 0; a <= max; a++)
		for (int b = 0; b <= max; b++)
			if (R1[a]==R2[b])
				return 1;
			
	return 0;
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

