// NATIVE_H

#ifndef APLIB_TOOLS_NATIVE_OPTIONS_H
#define APLIB_TOOLS_NATIVE_OPTIONS_H

char * itoa2(int v);
double qdiv(double n, double d);
double qdiv_i(int n, int d);

char * cat(int c, char * s, ...);
char * safecat(char * s, char * rhs);
double expound(double base, int exp);
APL prime(APL, APL, short unsigned int);
APL primedata(APL min, APL max, APL step);

#define LARGE unsigned long long int
#define large LARGE

APL isprime ( APL );

#endif

