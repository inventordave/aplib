// NATIVE_H

#ifndef aplib_TOOLS_NATIVE_OPTIONS_H
#define aplib_TOOLS_NATIVE_OPTIONS_H

char * itoa2(int v);
double qdiv(double n, double d);
double qdiv_i(int n, int d);

char * cat(int c, char * s, ...);
char * safecat(char * s, char * rhs);
double expound(double base, int exp);
int prime(unsigned int, unsigned, short unsigned int);
int primedata(unsigned int min, unsigned int max, unsigned int step);

