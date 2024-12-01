// MEMORY_C

#include "memory.h"

#ifndef L
#define L long long int
#endif
#ifndef large
#define large L
#endif


char* strtolower( char* _ )	{

	#ifndef CASE_DIFF
	#define CASE_DIFF ('A' - 'a')
	#endif

	large v = 0;
	char* t = _;
	while( *t++ != '\0' )
		v++;

	char* s = (char*)malloc( v + 1 );
	while( *_ != '\0' )
		( *_>='A' && *_<='Z' ) ? *s++ = (*_++) - CASE_DIFF : *s++ = (*_++) ;
	
	*s = '\0';

	return s;
}

char* strtoupper( char* _ )	{

	#ifndef CASE_DIFF
	#define CASE_DIFF ('A' - 'a')
	#endif

	large v = 0;
	char* t = _;
	while( *t++ != '\0' )
		v++;

	char* s = (char*)malloc( v + 1 );
	while( *_ != '\0' )
		( *_>='a' && *_<='z' ) ? *s++ = (*_++) + CASE_DIFF : *s++ = (*_++) ;
	
	*s = '\0';

	return s;
}

void* davealloc( large size, uint8_t item )	{

	#include <ctype.h>
	void* _ = malloc( size );
	char* t = (char*)_;
	
	while( (size--) > 0 )
		*t++ = item;

	return _;
}

