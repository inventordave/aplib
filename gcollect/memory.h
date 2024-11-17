// MEMORY_H

#ifndef DAVELIB_MEMORY_H
#define DAVELIB_MEMORY_H
	#ifndef L
	#define L unsigned long long int
	#endif

char* strtolower( char* _ );
char* strtoupper( char* _ );
void* davealloc( L size, uint8_t item );

#endif

