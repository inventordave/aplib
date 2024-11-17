// MEMORY_C

#include "memory.h"

#ifndef L
#define L unsigned long long int
#endif

char* strtolower( char* _ )	{
	
	L strlen__ = strlen( _ );
	char* s = (char*)malloc( strlen__ + 1 );
	char* t = s;
	char c;
	while( strlen__-- )	{

		c = *(_++);
		if( (c>='A') && (c<='Z') )
		*t++ = c - ('A' - 'a');
	}
	
	*t = 0;
	
	return s;
}
char* strtoupper( char* _ )	{

	L strlen__ = strlen( _ );
	char* s = (char*)malloc( strlen__ + 1 );
	char* t = s;
	char c;
	while( strlen__-- )	{

		c = *(_++);
		if( (c>='a') && (c<='z') )
		*t++ = c - ('A' - 'a');
	}
	
	*t = 0;
	
	return s;
}

void* davealloc( L size, uint8_t item )	{
	#include <ctype.h>
	void* _ = malloc( size );
	char* t = (char*)_;
	
	while( (size--) > 0 )
		*t++ = item;

	return _;
}

