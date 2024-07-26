// DEV_TESTING SANDBOX

// INC'S
#include "stdlib.h"
#include "lib.h"
#include "aplib.h"
#include "sandbox.h"

main

char * formatString( char * fmt, ... )	{

	char * str = (char *)malloc(1024);
	str[0] = '\0';

	//sprintf( str, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );

	return str;
}