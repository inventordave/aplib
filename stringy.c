// STRINGY_C
// DAVE'S STRING LIBRARY, PACKAGED WITH DAVELIB //

// INC'S
#include "stringy.h"



// SANITIZESTR: General method for pre-processing of an input c-string (safety).
char* sanitizeStr( char* A )	{
	
	char * B = (char *)malloc( strlen(A)+1 );
	char * _ = B;
	
	while((*A) != '\0')	{
		
		switch(*A)	{

			case 92: // \ backslash
			case 34: // " double-quote
			case 42: // * star
			case 47: // / forward-slash
			case 58: // : colon
			case 60: // < lt
			case 62: // > gt
			case 63: // ? question-mark
			case 124:// | pipe

				// printf( "Invalid char ('%c') (%d).\n", *_, *_ );
				// Uncomment above line to see reporting to stdout of detected invalid chars in the input string.
				*B = '.'; // Arbitrary printable-char to replace invalid char with.
				break;
			
			default:
				*B = *A; 
				//printf( "char ok: '%c'\n", (*str) );
				break;	
		}
		
		++A;
		++B;
	}
	
	*B = '\0';
	
	return _;
}


// INT -> CSTR
char * itoad(int v)	{
	
	// snprintf (buff, sizeof(buf), "%d",n); // print int 'n' into the char[] buffer
	char * _ = allocs(16);
	
	snprintf ( _, 16, "%d", v );
	
	return _;
}


// CAT(INT NUM_STRINGS, ...)
// 1ST ARG IS NUMBER OF SUBSEQUENT CSTRING ARGS - VARIADIC
// DEPS: SAFECAT()
char * cat(int c, char * s, ...)	{
	
	va_list ap;
	char * _ = (char *)malloc(4096);
	_[4095] = '\0';
	
	strcpy(_, s);

	va_start(ap, c);
	for(scint i=0; i<c; i++)	{
	
		_ = safecat(_, (char *)va_arg(ap, char*));
	}
	va_end(ap);
	
	DEBUG_MSG("exiting cat()")
	return _;
}


#define ERR_NP_CHAR 1
char * safecat( char* s, char* rhs )	{
	
	// SAFETY
	if( (s==NULL) || (rhs==NULL) )
		return s;
	
	// check s, rhs, for nonprintable chars (0-31)
	
	unsigned int i = 0;
	char ch = '\0', chr = '\0';
	char * _s = s; char * _rhs = rhs;
	
	do	{
		
		if( ch = _s[0] )	{
			
			if( ch < (char)32 || ( (ch > 127) & (ch < 160) ) )
				return (char *)ERR_NP_CHAR;
		} // dangling-else!
		else
			--_s;

		if( chr = _rhs[0] )	{
		
			if( chr < (char)32 || ( (ch > 127) & (ch < 160) ) )
				return (char *)ERR_NP_CHAR;
		} // dangling-else!
		else
			--_rhs;
		
		++_s;
		++_rhs;

	} while (ch != '\0' || chr != '\0');
	
	char * _ = (char *)malloc( strlen(s) + strlen(rhs) +1 );
	if( _ == NULL )
		return (char *)NULL;
	
	strcpy(_, s);
	strcat(_, rhs);
	
	free(s);
	s = malloc(strlen(_) + 1);
	if( s == NULL )
		return (char *)NULL;
	
	strcpy(s, _);
	
	free(_);
	// Do safety check on composite string _, before returning the cstring pointer to the caller.
	// ... 1. remove any non-alphabetical control codes, though printable.

	return s;
}

