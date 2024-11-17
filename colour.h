#ifndef BYPASS_ANSIVT_GUARD
#define BYPASS_ANSIVT_GUARD 1
	
#define colouriser colorMode
#define colourizer colouriser

#include "c_static.h"


void colorMode();

extern char* ANSIVT_FG;
extern char* ANSIVT_BG;

#define FG_COLORS 16
#define BG_COLORS 16


char* getVTCodeString( char );


extern char ResetAnsiVtCodes(char);
extern char* SetVT( char*, char* ); //fg and bg colour.
extern char* f( int sc ); // eg, +i, +b, -i, -b, and so on.
extern char* fg( char* );
extern char* bg( char* );


typedef struct AVTC{	

	char ansivt;
	char* ANSIVT_FG;
	char* ANSIVT_BG;
	
	char (*RVC)(char);
	char* (*SVT)( char*, char* ); //fg and bg colour.

	char* (*fg)( char* );
	char* (*bg)( char* );
	char* (*f)( char* ); // eg, +i, +b, -i, -b, and so on.

	char** ANSIVT_CTABLE;

} AVTC;

typedef struct _ANSI{

	int (*is)();
	struct AVTC* c;

	char* (*SetVT)( char*, char* );
	char* ANSIVT_FG;
	char* ANSIVT_BG;
} _ANSI;

extern struct _ANSI* ANSI;


extern int ANSI_IS();

extern void ANSI_init();



// generates the ansivt-formatted output string.
char* ANSIVT( char* str, char cc[], unsigned long long int offsets[], int _frees );





extern struct AVTC* ActivateColorConsole();
extern void Init_ANSIVT_CTABLE();

extern char FG_BLACK[8];
extern char FG_RED[8];
extern char FG_GREEN[8];
extern char FG_YELLOW[8];
extern char FG_BLUE[8];
extern char FG_MAGENTA[8];
extern char FG_CYAN[8];
extern char FG_WHITE[8];

extern char FG_BRIGHT_BLACK[8];
extern char FG_BRIGHT_RED[8];
extern char FG_BRIGHT_GREEN[8];
extern char FG_BRIGHT_YELLOW[8];
extern char FG_BRIGHT_BLUE[8];
extern char FG_BRIGHT_MAGENTA[8];
extern char FG_BRIGHT_CYAN[8];
extern char FG_BRIGHT_WHITE[8];

extern char BG_BLACK[8];
extern char BG_RED[8];
extern char BG_GREEN[8];
extern char BG_YELLOW[8];
extern char BG_BLUE[8];
extern char BG_MAGENTA[8];
extern char BG_CYAN[8];
extern char BG_WHITE[8];

extern char BG_BRIGHT_BLACK[8];
extern char BG_BRIGHT_RED[8];
extern char BG_BRIGHT_GREEN[8];
extern char BG_BRIGHT_YELLOW[8];
extern char BG_BRIGHT_BLUE[8];
extern char BG_BRIGHT_MAGENTA[8];
extern char BG_BRIGHT_CYAN[8];
extern char BG_BRIGHT_WHITE[8];

extern char NORMAL[8];

#define VTCODEWIDTH 8

extern AVTC* Init_AVTC( );

#endif

