#include <stdlib.h>
#include <string.h>
#include "colour.h"
#include "c_static.h"

char ResetAnsiVtCodes(int f)	{
	
	if(f == 0)	{

		strcpy((char *)FG_BLACK, "");
		strcpy((char *)FG_RED, "");
		strcpy((char *)FG_GREEN, "");
		strcpy((char *)FG_YELLOW, "");
		strcpy((char *)FG_BLUE, "");
		strcpy((char *)FG_MAGENTA, "");
		strcpy((char *)FG_CYAN, "");
		strcpy((char *)FG_WHITE, "");

		strcpy((char *)FG_BRIGHT_BLACK, "");
		strcpy((char *)FG_BRIGHT_RED, "");
		strcpy((char *)FG_BRIGHT_GREEN, "");
		strcpy((char *)FG_BRIGHT_YELLOW, "");
		strcpy((char *)FG_BRIGHT_BLUE, "");
		strcpy((char *)FG_BRIGHT_MAGENTA, "");
		strcpy((char *)FG_BRIGHT_CYAN, "");
		strcpy((char *)FG_BRIGHT_WHITE, "");

		strcpy((char *)BG_BLACK, "");
		strcpy((char *)BG_RED, "");
		strcpy((char *)BG_GREEN, "");
		strcpy((char *)BG_YELLOW, "");
		strcpy((char *)BG_BLUE, "");
		strcpy((char *)BG_MAGENTA, "");
		strcpy((char *)BG_CYAN, "");
		strcpy((char *)BG_WHITE, "");

		strcpy((char *)BG_BRIGHT_BLACK, "");
		strcpy((char *)BG_BRIGHT_RED, "");
		strcpy((char *)BG_BRIGHT_GREEN, "");
		strcpy((char *)BG_BRIGHT_YELLOW, "");
		strcpy((char *)BG_BRIGHT_BLUE, "");
		strcpy((char *)BG_BRIGHT_MAGENTA, "");
		strcpy((char *)BG_BRIGHT_CYAN, "");
		strcpy((char *)BG_BRIGHT_WHITE, "");

		strcpy((char *)NORMAL, "");
	}
	
	else if(f == 1)	{
		
		strcpy((char *)FG_BLACK, "[30m");
		strcpy((char *)FG_RED, "[31m");
		strcpy((char *)FG_GREEN, "[32m");
		strcpy((char *)FG_YELLOW, "[33m");
		strcpy((char *)FG_BLUE, "[34m");
		strcpy((char *)FG_MAGENTA, "[35m");
		strcpy((char *)FG_CYAN, "[36m");
		strcpy((char *)FG_WHITE, "[37m");

		strcpy((char *)FG_BRIGHT_BLACK, "[90m");
		strcpy((char *)FG_BRIGHT_RED, "[91m");
		strcpy((char *)FG_BRIGHT_GREEN, "[92m");
		strcpy((char *)FG_BRIGHT_YELLOW, "[93m");
		strcpy((char *)FG_BRIGHT_BLUE, "[94m");
		strcpy((char *)FG_BRIGHT_MAGENTA, "[95m");
		strcpy((char *)FG_BRIGHT_CYAN, "[96m");
		strcpy((char *)FG_BRIGHT_WHITE, "[97m");

		strcpy((char *)BG_BLACK, "[40m");
		strcpy((char *)BG_RED, "[41m");
		strcpy((char *)BG_GREEN, "[42m");
		strcpy((char *)BG_YELLOW, "[43m");
		strcpy((char *)BG_BLUE, "[44m");
		strcpy((char *)BG_MAGENTA, "[45m");
		strcpy((char *)BG_CYAN, "[46m");
		strcpy((char *)BG_WHITE, "[47m");

		strcpy((char *)BG_BRIGHT_BLACK, "[100m");
		strcpy((char *)BG_BRIGHT_RED, "[101m");
		strcpy((char *)BG_BRIGHT_GREEN, "[102m");
		strcpy((char *)BG_BRIGHT_YELLOW, "[103m");
		strcpy((char *)BG_BRIGHT_BLUE, "[104m");
		strcpy((char *)BG_BRIGHT_MAGENTA, "[105m");
		strcpy((char *)BG_BRIGHT_CYAN, "[106m");
		strcpy((char *)BG_BRIGHT_WHITE, "[107m");

		strcpy((char *)NORMAL, "[0m");
	}
	
	return (ansivt = f);
}


int ANSI_IS(){
	
	return 17179;
}

struct AVTC* ActivateColorConsole(){
	
	if( ANSI->is!=ANSI_IS ){
		
		printf( "ANSI Env Variable not initialised! Initialising...\n" );
		ANSI_init();
	}
	
	struct AVTC* _ = (struct AVTC*)malloc( sizeof(struct AVTC) );
	_->ResetAnsiVtCodes = ResetAnsiVtCodes;
	_->SetVT = SetVT;
	_->f = SetStyle;
	
	_->ANSIVT_FG = ANSI->ANSIVT_FG;
	_->ANSIVT_BG = ANSI->ANSIVT_BG;
	
	_->fg = fg;
	_->bg = bg;
	
	_->ansivt = 1;

	ANSI->c = _;
	
	return _;
}

char* fg( char* c ){ if(c!=0) ANSI->c->SetVT( c,0 ); return ANSI->c->ANSIVT_FG; }
char* bg( char* c ){ if(c!=0) ANSI->c->SetVT( 0,c ); return ANSI->c->ANSIVT_BG; }

char* SetVT( char* fg, char* bg )	{
	
	char* fg_ = 0;
	char* bg_ = 0;
	
	int i;
	
	FG:
	if( fg==0 || streq( fg,"0" ) )
		goto BG;
	
	for( i=0; i<16; i++ ){

		if( streq( fg, ANSIVT_CTABLE[i][0] ) ){
			
			fg_ = getstring( ANSIVT_CTABLE[i][1] );
			printf( "%s", fg_ );
			ANSI->c->ANSIVT_FG = fg;
			break;
		}
	}
	
	BG:
	if( bg==0 || streq( bg,"0" ) )
		goto NEXT;

	for( i=16; i<(16*2); i++ ){

		if( streq( bg, ANSIVT_CTABLE[i][0] ) ){
			
			bg_ = getstring( ANSIVT_CTABLE[i][1] );
			printf( "%s", bg_ );
			ANSI->c->ANSIVT_BG = bg;
			break;
		}
	}

	NEXT:
	char* _ = mem( strlen(ANSIVT_FG)+strlen(ANSIVT_BG) + strlen("//") );
	_[0] = '\0';

	if( strlen(ANSI->c->ANSIVT_FG) )	
	safecat( _, ANSI->c->ANSIVT_FG );
	else
	safecat( _,"Default" );
	
	safecat(  _,"//" );	
	
	if( strlen(ANSI->c->ANSIVT_BG) ) 
	safecat( _,ANSI->c->ANSIVT_BG );
	else
	safecat( _,"Default" );	

	return _;
}

void Init_ANSIVT_CTABLE(){

if( ANSI->is != ANSI_IS ){
printf( "ANSI VT System not Initialised! Initialising...\n" );
ANSI.c = ANSI_init();}

char* ANSIVT_CTABLE[64][2] = { {0},{0} };

uint32_t i=0;
//FG
ANSIVT_CTABLE[i][0]= "black";
ANSIVT_CTABLE[i++][1]= FG_BLACK;

ANSIVT_CTABLE[i][0]= "red";
ANSIVT_CTABLE[i++][1]= FG_RED;

ANSIVT_CTABLE[i][0]= "green";
ANSIVT_CTABLE[i++][1]= FG_GREEN;

ANSIVT_CTABLE[i][0]= "yellow";
ANSIVT_CTABLE[i++][1]= FG_YELLOW;

ANSIVT_CTABLE[i][0]= "blue";
ANSIVT_CTABLE[i++][1]= FG_BLUE;

ANSIVT_CTABLE[i][0]= "magenta";
ANSIVT_CTABLE[i++][1]= FG_MAGENTA;

ANSIVT_CTABLE[i][0]= "cyan";
ANSIVT_CTABLE[i++][1]= FG_CYAN;

ANSIVT_CTABLE[i][0]= "white";
ANSIVT_CTABLE[i++][1]= FG_WHITE;

ANSIVT_CTABLE[i][0]= "bright_black";
ANSIVT_CTABLE[i++][1]= FG_BRIGHT_BLACK;

ANSIVT_CTABLE[i][0]= "bright_red";
ANSIVT_CTABLE[i++][1]= FG_BRIGHT_RED;

ANSIVT_CTABLE[i][0]= "bright_green";
ANSIVT_CTABLE[i++][1]= FG_BRIGHT_GREEN;

ANSIVT_CTABLE[i][0]= "bright_yellow";
ANSIVT_CTABLE[i++][1]= FG_BRIGHT_YELLOW;

ANSIVT_CTABLE[i][0]= "bright_blue";
ANSIVT_CTABLE[i++][1]= FG_BRIGHT_BLUE;

ANSIVT_CTABLE[i][0]= "bright_magenta";
ANSIVT_CTABLE[i++][1]= FG_BRIGHT_MAGENTA;

ANSIVT_CTABLE[i][0]= "bright_cyan";
ANSIVT_CTABLE[i++][1]= FG_BRIGHT_CYAN;

ANSIVT_CTABLE[i][0]= "bright_white";
ANSIVT_CTABLE[i++][1]= FG_BRIGHT_WHITE;

// BG
ANSIVT_CTABLE[i][0]= "black";
ANSIVT_CTABLE[i++][1]= BG_BLACK;

ANSIVT_CTABLE[i][0]= "red";
ANSIVT_CTABLE[i++][1]= BG_RED;

ANSIVT_CTABLE[i][0]= "green";
ANSIVT_CTABLE[i++][1]= BG_GREEN;

ANSIVT_CTABLE[i][0]= "yellow";
ANSIVT_CTABLE[i++][1]= BG_YELLOW;

ANSIVT_CTABLE[i][0]= "blue";
ANSIVT_CTABLE[i++][1]= BG_BLUE;

ANSIVT_CTABLE[i][0]= "magenta";
ANSIVT_CTABLE[i++][1]= BG_MAGENTA;

ANSIVT_CTABLE[i][0]= "cyan";
ANSIVT_CTABLE[i++][1]= BG_CYAN;

ANSIVT_CTABLE[i][0]= "white";
ANSIVT_CTABLE[i++][1]= BG_WHITE;

ANSIVT_CTABLE[i][0]= "bright_black";
ANSIVT_CTABLE[i++][1]= BG_BRIGHT_BLACK;

ANSIVT_CTABLE[i][0]= "bright_red";
ANSIVT_CTABLE[i++][1]= BG_BRIGHT_RED;

ANSIVT_CTABLE[i][0]= "bright_green";
ANSIVT_CTABLE[i++][1]= BG_BRIGHT_GREEN;

ANSIVT_CTABLE[i][0]= "bright_yellow";
ANSIVT_CTABLE[i++][1]= BG_BRIGHT_YELLOW;

ANSIVT_CTABLE[i][0]= "bright_blue";
ANSIVT_CTABLE[i++][1]= BG_BRIGHT_BLUE;

ANSIVT_CTABLE[i][0]= "bright_magenta";
ANSIVT_CTABLE[i++][1]= BG_BRIGHT_MAGENTA;

ANSIVT_CTABLE[i][0]= "bright_cyan";
ANSIVT_CTABLE[i++][1]= BG_BRIGHT_CYAN;

ANSIVT_CTABLE[i][0]= "bright_white";
ANSIVT_CTABLE[i++][1]= BG_BRIGHT_WHITE;

// RESET
ANSIVT_CTABLE[i][0] = "default";
ANSIVT_CTABLE[i++][1] = NORMAL;

// i contains a count of all the colour codes. Should be 33.
ANSI->c.ANSIVT_CTABLE = ANSIVT_CTABLE;
ANSI->c.fg( "white" );
ANSI->c.bg( "black" );

return;  }


AVTC Init_AVTC(){
		
AVTC _ = (AVTC)malloc( sizeof(AVTC) );

&_->ResetAnsiVtCodes = ResetAnsiVtCodes;
&_->SetVT = SetVT;
&_->fg = fg;
&_->bg = bg;
&_->f;
&_->ANSIVT_FG = "default";

	return ( _ ); }

void ANSI_init(){
	
	ANSI = (_ANSI*)malloc( sizeof(struct _ANSI) );
	ANSI->ANSIVT_FG = "default";
	ANSI->ANSIVT_BG = "default";
	
	ANSI->is = ANSI_IS;
	ANSI->c = Init_AVTC();
	
}

