#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// #include <windows.h>
#include "lib.h"
#include "colour.h"
#include "stringy.h"
#include "c_static.h"
#include "stringy.h"

char* ANSIVT_FG = (char*)0;
char* ANSIVT_BG = (char*)0;

struct _ANSI* ANSI = (_ANSI*)0;

char* ANSIVT( char* str, char cc[], LARGE offsets[], int _frees ){
LARGE str_width = strlen(str);
LARGE width = str_width + (strlen(cc)*VTCODEWIDTH);
char* _ = mem( width );
char* bucket = mem( width );
char* vtcodestr;





LARGE q=0;
LARGE t=0;
while( t<str_width ){

	LARGE p;
	for( p=0; p<offsets[q]; p++ ) // offsets are relative.
		bucket[p] = str[t++];
	bucket[p] = '\0';
	
	safecat( _,bucket );
	vtcodestr = getVTCodeString( *cc );
	safecat( _,vtcodestr );
	
	free( vtcodestr );
	
	++cc;
	++q;
	
	if( *cc == '\0' ){
		
		LARGE y = strlen(_);
		for( LARGE x=t;x<str_width; x++ )
			_[y++]=str[x];
		_[y] = '\0';			
		break;}}

return _; }



char ResetAnsiVtCodes(char f)	{
	
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
		
		// printf( "ANSI Env Variable not initialised! Initialising...\n" );
		ANSI_init();
	}
	
	struct AVTC* _ = (struct AVTC*)malloc( sizeof(struct AVTC) );
	_->RVC = ResetAnsiVtCodes;
	_->SVT = SetVT;
	//_->f = SetStyle;
	
	_->ANSIVT_FG = ANSI->ANSIVT_FG;
	_->ANSIVT_BG = ANSI->ANSIVT_BG;
	
	_->fg = fg;
	_->bg = bg;
	
	_->ansivt = 1;

	ANSI->c = _;
	
	return _;
}

char* fg( char* c ){
	if(c!=0)
		ANSI->c->SVT( c,(char*)0 );
	return ANSI->ANSIVT_FG;

}

char* bg( char* c ){
	if(c!=0)
		ANSI->c->SVT( (char*)0,c );
	return ANSI->ANSIVT_BG;
}

char* SetVT( char* fg, char* bg )	{
	
	char* fg_ = 0;
	char* bg_ = 0;
	
	int i;
	
	//FG:
	if( fg==(char*)0 )
		goto BG;
	
	for( i=0; i<16; i++ ){

		if( streq( fg, ANSI->c->ANSIVT_CTABLE[i*4] ) ){
			
			fg_ = getstring( *(ANSI->c->ANSIVT_CTABLE + (i*4) + 4) );
			printf( "%s", fg_ );
			ANSI->ANSIVT_FG = fg;
			ANSI->c->fg( fg_ );
			break;
		}
	}
	
	BG:
	if( bg==(char*)0 )
		goto NEXT;

	for( i=16; i<(16*2); i++ ){

		if( streq( bg, ANSI->c->ANSIVT_CTABLE[i*4] ) ){
			
			bg_ = getstring( ANSI->c->ANSIVT_CTABLE[(i*4)+4] );
			printf( "%s", bg_ );
			ANSI->ANSIVT_BG = bg;
			ANSI->c->bg( bg_ );
			break;
		}
	}

	NEXT:
	char* _ = mem( strlen(ANSIVT_FG)+strlen(ANSIVT_BG) + strlen("//") );
	_[0] = '\0';

	if( strlen(ANSI->ANSIVT_FG) )	
	safecat( _, ANSI->ANSIVT_FG );
	else
	safecat( _,"Default" );
	
	safecat(  _,"//" );	
	
	if( strlen(ANSI->ANSIVT_BG) ) 
	safecat( _,ANSI->ANSIVT_BG );
	else
	safecat( _,"Default" );	

	return _;
}

void Init_ANSIVT_CTABLE(){

	if( ANSI->is != ANSI_IS ){
		
		printf( "ANSI VT System not Initialised! Initialising...\n" );
		ANSI_init();
	}

	char** ANSIVT_CTABLE/*64*2*/ = (char**)malloc( (64*2) * sizeof(char*) );

	uint32_t i=0;
	//FG
	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "black" ); // BASE + (i*4) + (0*4)
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BLACK;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "red" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_RED;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "green" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_GREEN;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "yellow" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_YELLOW;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "blue" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BLUE;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "magenta" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_MAGENTA;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "cyan" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_CYAN;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "white" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_WHITE;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_black" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BRIGHT_BLACK;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_red" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BRIGHT_RED;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_green" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BRIGHT_GREEN;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_yellow" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BRIGHT_YELLOW;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_blue" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BRIGHT_BLUE;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_magenta" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BRIGHT_MAGENTA;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_cyan" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BRIGHT_CYAN;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_white" );
	*(ANSIVT_CTABLE + (i*4) + 4)= FG_BRIGHT_WHITE;

	// BG
	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "black" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BLACK;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "red" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_RED;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "green" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_GREEN;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "yellow" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_YELLOW;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "blue" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BLUE;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "magenta" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_MAGENTA;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "cyan" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_CYAN;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "white" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_WHITE;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_black" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BRIGHT_BLACK;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_red" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BRIGHT_RED;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_green" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BRIGHT_GREEN;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_yellow" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BRIGHT_YELLOW;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_blue" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BRIGHT_BLUE;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_magenta" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BRIGHT_MAGENTA;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_cyan" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BRIGHT_CYAN;

	*(ANSIVT_CTABLE + (i*4) + 0)= getstring( "bright_white" );
	*(ANSIVT_CTABLE + (i*4) + 4)= BG_BRIGHT_WHITE;

	// RESET
	*(ANSIVT_CTABLE + (i*4) + 0) = getstring( "default" );
	*(ANSIVT_CTABLE + (i*4) + 4) = NORMAL;

	// i contains a count of all the colour codes. Should be 33.
	ANSI->c->ANSIVT_CTABLE = ANSIVT_CTABLE;
	ANSI->c->fg( "white" );
	ANSI->c->bg( "black" );

	return; 
}

void colorMode()	{

	int color;

	#ifdef windows

	#define STD_OUTPUT_HANDLE ((DWORD)-11)
	//#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	color = (int) SetConsoleMode(
		StdHandle,
		0x0001 | 0x0002 | ENABLE_VIRTUAL_TERMINAL_PROCESSING
	);

	#else
		color = 1;
		// Assuming Linux is the target architecture instead.
	#endif


	//sprintf( msg_str, "ResponseCode(SetConsoleMode) := '%s'.\n", (color == 0 ? "FAIL" : "SUCCESS") );
	//print( msg_str );
	
	if(color == 0)	{
		
		printf( "ANSI/VT Support Not Available.\n" );
		ResetAnsiVtCodes(0);
	}
	else
		ResetAnsiVtCodes(1);

	return;
}



AVTC* Init_AVTC(){
		
AVTC* _ = (AVTC*)malloc( sizeof(AVTC) );

_->RVC = ResetAnsiVtCodes;
_->SVT = SetVT;
_->fg = fg;	
_->bg = bg;
//_->f;
_->ANSIVT_FG = "default";

_-> ANSIVT_CTABLE = (char**)malloc( (FG_COLORS+BG_COLORS+1)*2 * sizeof(char*) );	

	return ( _ ); }

void ANSI_init(){
	
	ANSI = (_ANSI*)malloc( sizeof(struct _ANSI) );
	ANSIVT_FG = "default";
	ANSIVT_BG = "default";
	ANSI->ANSIVT_FG = ANSIVT_FG;
	ANSI->ANSIVT_BG = ANSIVT_BG;
	
	ANSI->is = ANSI_IS;
	ANSI->c = Init_AVTC();
	ANSI->SetVT = SetVT;
	
}


char* getVTCodeString( char cc )	{

	return *(ANSI->c->ANSIVT_CTABLE + (cc*4) + 4);
}

