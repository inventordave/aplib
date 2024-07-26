// APLIB-OUTPUT.c
#include <stdlib.h>
#include <string.h>

#include "APlib-output.h"

char * formatSign(char sign)	{
	
	return (sign=='-'?FG_BRIGHT_RED:FG_BRIGHT_GREEN);
}

char * formatBinary(char *bin_string)	{

	int bin_string_length = strlen(bin_string);
	
	char * _1 = "1";
	char * _0 = "0";
	
	char * str = (char *)malloc( bin_string_length + 50 + 1 );
	int str_length = bin_string_length + 50;
	
	int flag = 0;
	
	if( bin_string[0]=='0' )
		flag=1;
	else if( bin_string[0]=='1' )
		flag=0;
	
	for( int i=0; i<bin_string_length; i++ )	{
		
		if( bin_string[i]=='1' )	{
			
			if( flag==0 )	{
				
				strcat( str, FG_BRIGHT_BLUE );
				flag=1;
			}
			strcat( str, _1 );
		}
		else if( bin_string[i]=='0' )	{
			
			if( flag==1 )	{
				
				strcat( str, FG_BRIGHT_YELLOW );
				flag=0;
			}
			strcat( str, _0 );
		}
		
		if( strlen(str) >= (str_length-10) )	{
			
			str = realloc( str, strlen(str)+50 );
			str_length += 50;
		}
	}
	
	return str;
}

char * formatAP(AP A)	{
	
	char * str = (char *)malloc( strlen(A.major)+1+1+(8*3) );
	
	strcpy( str, formatSign(A.sign) );
	str[ strlen(str) ] = A.sign;
	
	strcat( str, FG_BRIGHT_CYAN );
	strcat( str, A.major );
	strcat( str, NORMAL );
	
	return str;
}

void print( char * str )	{
	
	printf( "%s", str );
	free( str );
	
	return;
}


void normal()	{

	printf( "%s", NORMAL );
}

char * c(char * str, char * col)	{

	char * str2 = (char *)malloc( strlen(str) + 16 + 1);
	sprintf( str2, "%s%s%s", col, str, NORMAL );
	return str2;
}

