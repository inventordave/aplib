#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>

#include "fractionalcalc.tab.h"

#include "APLIB.h"
#include "colour.h"
#include "stringy.h"

// LEX FNC'S. (Will replace these with my 'simplelexer.c' library.
int yylex();
int yyerror(const char*);

void printVars();

// These are deprecated functions. They perform digitstring-truncation, which
// is a feature precision, which 'APLIB' will implement instead. 
char *convert(double x);
char *trim(double x);
char *(*function)(); 


scint truthy(double);

// These methods of encoding FALSE, TRUE, NULL,
// will be seperated from any Real- or Integer-valued scalar[0,N]
// by APLIB.
double _FALSE;
double _TRUE;
double _Null;
scint truthyFlag;

// User-defined Variables & Expression-Variables
double vars[256] = { -10000 };
char*  evars[256] = { '\0' };

scint optionsFlag = 0;

char* enum_str;
extern double generateExpValue(char *);

#define NUM_STRING_LENGTH 325 // max length of fractional (double) number, including decimal point. Obvs is way less than 100.

