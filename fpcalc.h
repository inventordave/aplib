// Calc

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define large unsigned long long int

typedef struct ap	{

	char* wholepart;
	char *fp;
	large decimalp;
	char sign;
} ap;

int main( int argc, char** argv )	{



	return 0;
}

/**


1. from [0] of pattern.


l-r (range)

delimeters:

[]
()
{}
" "

\[c] // inside quoted string, escape sequences are not domained by the regexp scanner.


if( c==" )
	if( escape_code==0 )
		if( inside_q_str==0 )
			inside_q_str=1
		else
			inside_q_str=0
	else
		; // vanilla single charpoint pattern
		literal_pattern .= "

if( c==[ )
	if( escape_code==0 )
		inside_delimiter_[.push( offset(c) );
		subpattern.new();
	else
		literal_pattern .= [

if( c==] )
	if( escape_code==0 )
		inside_delimiter_[.pop()
		subpattern.close()
		if( lookahead()=={ )
			range_postfix = true;

	else literal_pattern .= ]
	
if( c=={ )
	if range_postfix==true
	++k;
	if( c==type(num) )
		range.lower = c;
	else
		error();
	
	++k;
	if( c==, )
		++k;
		if( c==type(num) )
			range.higher=c;
		else
			range.higher=-1;
	else
		if( c!=} )
			error();
		
	if( c==} )


*
+
?




*/