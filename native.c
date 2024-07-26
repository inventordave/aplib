

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "native.h"

#define toggle char
#define L 171
#define R 79

#define ON 1
#define OFF 0


// i = ith prime number, if n is set, i is ignored. n will test for a prime number. f is a flag, set to TRUE if you want the ith prime number, or if you want to test if the arg u pass is literally prime.
large isprime ( large i, toggle f )	{
	
	toggle report;
	
	if( f==L )	{
		// trial division algorithm, divide n by every integer between 2 and sqrt(n), as at n = a . b, either a
		// or b will not be bigger than sqrt(n), which means all tests have been performed
		
		if( i==1 )	{
			// base case: 1, the smallest prime number is 2...
			
			if( report==ON )
				printf("1 is too small to be a prime number! The smallest prime number is 2.");
			
			return 0;
		}
		
		if( i==2 )	{
			// base case 2, it interferes with the test conditional, as 2 % 2 == 0, which fails the value 2 for the test. 
			// Subsequent n % k tests don't have to check if n == k, as k will never be more than sqrt(n)
			
			if( report==ON )
				printf("2 is the 1st Prime, you know that!");
			
			return 2;
		}
		
		large sqrt_ = ceil(sqrt(n)) + 1;
		for (large k = 2; k < sqrt_; k++)
			if( (i % k) == 0 )	{
				
				if( report==ON )
					printf("%d is NOT prime. It was divisable at %d.\n", i, k);
				
				return 0;
			}
		
		if( report==ON )
			printf("%d IS A PRIME NUMBER!\n", n);
		
		return i;
	}
	

	large j = 3;
	large k = 0;
	large p = 0;
	
	#ifndef TRUE
	#define TRUE 1
	while( TRUE )	{
		
		if(
		
		p = isprime(j, R)// 
		
		){
			
			++k;
			if( k==i )
				break;
			
		}
		
		++j;

	}
	// p <--- i-th prime number
	
	if( report==ON )
		printf("Prime number %d is %d.", i, p);
	
	// RETURN VALUE
	return p;
}



