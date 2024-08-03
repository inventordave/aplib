    #include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <string.h>
	#include <float.h>
	
	#include "fpcalc.tab.h"
	
    int yylex();
    int yyerror(const char*);
	
	void printVars();
	char *convert(double x);
	char *trim(double x);
	char *(*function)(); 
	
	short int truthy(double);
	
	double _FALSE;
	double _TRUE;
	double _Null;
	short int truthyFlag;
	
	double vars[256] = { -10000 };
	char*  evars[256] = { '\0' };
	
	short int optionsFlag = 0;
	
	char* enum_str;
	extern double generateExpValue(char *);
	
	#define NUM_STRING_LENGTH 325 // max length of fp (double) number, including decimal point. Obvs is way less than 100.
