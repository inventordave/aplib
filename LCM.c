#include <stdio.h>
#include <string.h>

static signed int M1 = 0, M2 = 0;
static int R1[1000] = {0}, R2[1000] = {0};
static int val = 1, inc = 0, match = 0;

int str2int(char *);
int test(int);
int calcLCM(int, char **);

int main(int argc, char **argv)	{
	
	return calcLCM(argc, argv);
}

int calcLCM(int argc, char **argv)	{
	
	if (argc < 3)	{
		
		printf("Usage: LCM first_integer second_integer [-n]\n");
		return 1;
	}
	
	if((argc == 4) && (argv[3][0] == '-') && (argv[3][1] == 'n'))	{
		
		//printf("Flag set!\n");
		val = 2;
	}
	
	M1 = str2int(argv[1]); M2 = str2int(argv[2]);
	
	while (!match)	{
		
		if (inc > 999)	{
			
			printf("Overflow error: More than %d iterations required.\n", inc-1);
			return 1;
		}
		
		R1[inc] = (int)M1*val; R2[inc] = (int)M2*val;
		
		match = test(inc);
		
		inc++;
		val++;
	}
	
	printf("The LCM for %d and %d is %d.\n", M1, M2, R1[inc-1]);
	
	return 0;
}

int test(int max)	{
	
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