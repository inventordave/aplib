// NATIVE_H

#ifndef APLIB_TOOLS_NATIVE_OPTIONS_H
#define APLIB_TOOLS_NATIVE_OPTIONS_H

char * itoa2(int v);
double qdiv(double n, double d);
double qdiv_i(int n, int d);


#define cint short unsigned int
char 	* cat(int c, char * s, ...);
char * safecat(char * s, char * rhs);
double expound(double base, int exp);
AP prime(APL, APL, cint);


double expound(double base, int exp);
//AP prime(APL, APL, cint);

AP primedata(AP min, AP max, AP step);

#define LARGE unsigned long long int
#define large LARGE

AP isprime ( AP );

#endif

