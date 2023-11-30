#ifndef BYPASS_ANSIVT_GUARD

	#define BYPASS_ANSIVT_GUARD 1
	
	extern char ansivt;
	
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
	
	extern char resetAnsiVtCodes(char);
	void swap4color( char *, char * );

#endif
