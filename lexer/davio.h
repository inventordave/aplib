// DAVELIB_DAVIO_H

#ifndef DAVELIB_DAVIO_H
#define DAVELIB_DAVIO_H

// GLOBALS
typedef struct FileContents	{

	char** 	lines;
	int		lineCount;

} FileContents;

typedef struct FileContext	{

	char* fileContents;
	int length;

} FileContext;

// FUNCTIONS
struct FileContext readFile( char* filename );
struct FileContents read_f_split( char* fn, char* delim );


#endif // DAVELIB_DAVIO_H

