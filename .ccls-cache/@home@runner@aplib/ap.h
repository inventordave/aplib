// AP.H
#ifndef DAVE_AP_H
#define DAVE_AP_H

// CUSTOM INC'S
#include "APLIB.h"
#include <stdint.h>

// HELPER TYPES
extern int maxLoopsSet;

typedef struct TEST_ENTRY {
	
	void (*addr)(int argc, char **argv);
	char * ref;
	uint32_t index;
} TEST_ENTRY;
typedef struct _TESTS	{

	struct TEST_ENTRY entries[256];
	int length;
	
} _TESTS;

// HELPER FNCS
void parseAP(AP * a, char * str); // checks (char *) decimal string for leading sign, and populates AP object accordingly.

void colorMode(); // activates ANSI/VT support via "cc/colorconsole"
void ap_exit(int status); // always call this on system exit.

#endif

