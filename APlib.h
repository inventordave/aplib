// APlib.h

#ifndef DAVE_APLIB
#define DAVE_APLIB

// STDLIB INC'S
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>


// CUSTOM INC'S
#include "ansivt2.h"


// SUGAR
#define NEW_LINE printf("\n");
#define NL NEW_LINE
#define bool int


// STATIC DEFS
#define MAX_LENGTH_AP_PART 1023 //Make this any number of bytes you want. The new_ap(int, int) function will +1 for the '\0' null-terminator. Default = 1023.




// CORE DATA STRUCTURES/TYPES
#define ollie unsigned long long int
typedef struct	AP {

	char * major;
	char * minor;
	char sign;
	
	int length;
	int major_length;
	int minor_length;
	
} AP;


typedef char OPCODE; // +, -, *, /, ^ (exp), and, or, not...

typedef struct	APExp	{ // AP op AP

	AP A;
	AP B;

	OPCODE _operator;

} APExp;

typedef struct APExpC	{ // (AP op AP) op (AP op AP)
	
	APExp A;
	APExp B;
	
	OPCODE _operator;

} APExpC;

typedef struct APExpC_2	{ // (APExpC op APExpC)

	APExpC A;
	APExpC B;
	
	OPCODE _operator;
	
} APExpC_2;


// FNC PROTOTYPES
AP new_ap(int maj, int min);
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
extern int DIV_BY_2_PRINT_ROWS;
AP DIV_BY_2(AP a);

AP EXP(AP a, AP b);

char * AND(char * lhs, char * rhs);
char * OR (char * lhs, char * rhs);
char * EX_OR(char * lhs, char * rhs);
char * NOT(char * v);


int lcm_test(int, int[], int[]);
int LCM(int, int, int);
int GCD(int a, int b, int lcm);

char * DEC_2_BIN(AP input, int packed);
char * BIN_2_DEC(char * bin);

int _2kMax(AP input);
int _2kMin(AP input);

void free_ap(AP a);
int MSD(int num);
void pack_trailing_zeroes( char * curr_row, int array_length, int num_zeroes );
char * fill_leading_zeroes( char * str, int num_zeroes );

int str2int(char *input);
char * int2str(int v);


#endif

