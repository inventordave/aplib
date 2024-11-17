AP v0.1

# an arbitrary-precision AriTHmAtiC library, 
developed by "Dave".

Licensed under <a href="https://github.com/inventordave/DAVELICENSE">DAVELICENCE 1.0</a>

# -/-------

## OVERVIEW

Makefile assumes GCC Make, targeting GCC or CLANG C.
"colour" implements ANSI/VT in the control-code implementation part, and makes a basic check for Windows vs Linux. If the output terminal doesn't support ANSIVT mode, then stdout strings will experience some unnecessary clutter from the ANSIVT escape sequences. If this happens, turn off aplib's colourizer by either:

1) Compiling with the Makefile target "nocolour", or
2) adding switch -Dcm0 to the compiler cmd-line invocation (e.g. gcc -Dcm0 [...] ). 

The library is still fleshing-out, and going reasonably well.
The library typically produces correct results for 2 integer inputs for the core arithmetic operators (implemented as functions).
It also therefore typically produces correct results for fp outputs, for any rational A/B.

Essentially, you simply include "APLIB.h" in your program source, invoke the APLIB Makefile target "aplib",
and by the miracle of quantum mechanics, electrical engineering, and boolean logic,
the lovely functions that I have implemented so far become available to your program.

# Guide for nosies
The arithmetic algorithms I am implementing are based on how long division, long multiplication, and addition (therefore subtraction) are taught in schools. This means the length of the digit strings is irrelevant to the actual arithmetic technique, except to say different-length strings being used as operands need to be aligned.
To see what I'm doing in my active sandbox, type "make sandbox". (output binary is 'test.exe')

// IGNORE_SECTION
# Invocation

test.exe %1 %2 %3

operand %1 is the desired Operator (see below).
operands %2 and %3 are integer decimal strings.
// END_OF_IGNORE_SECTION


## APLIB INTERNALS

# Core arithmetic operators
ADD( A,B )
SUB( A,B )
MUL( A,B )
DIV( A,B )
EXP( A,B )

# 1/A, and B/A
RECIPROCAL( A )
RECIPROCAL2( A,B )

# Core boolean operators.
AND( A,B )
OR( A,B )
XOR( A,B )
NOT( A )
NAND( A,B )

# handy quick A/2
DIVBY2( AP A )

# Converts a binary-format string to decimal-format
BIN_2_DEC( cstring A )
# Converts a decimal-format string to binary-format
DEC_2_BIN( AP A )

# max2k: gives the nearest 2k-form power of 2 higher/equal to the input decimal.
# min2k: gives the nearest 2k-form power of 2 lower/equal to the input decimal.
max2k( AP A )
min2k( AP A )


# GetOptions.h
There is a skeleton implementation of a method for processing args/switches passed to (any of) your user program(s) on the command-line instead of using the C stdlib getopt() function.
It's very simple, and you would need to use the skeleton function to guide you to "fill-in" the specific if-blocks for checking for a specific arg/switch.
Just look at "getOptions.c" for the general idea.

Also in the codebase is a general function for pre-processing input strings for validity/safety-checking. It's called "sanitizeStr(...)" (there are actually 2 versions), and is very simple, checking an input c-string char-by-char for invalid chars (defined by you when you 'concrete' the function, and initiating an action if it finds one, unless you use the 2nd version, in which case you can dynamically set).


# INFORMATIVE SECTION

As the lib is ultimately for ap real-valued numbers, the functions currently take as operands an object called AP, which has an .integer and .fractional component. (Slight misnomer, they really mean major/whole part and fractional/minor part.)
IF interfacing to the operator-functions yourseflf, populate the .integer component of 2 AP operands with an ascii-char based Integer string (e.g. a.integer <- "1234").

	// Example methods:
 	ap_obj.integer = getstring( "decimal/binary/hexadecimal string from ASCII ranges (0-9a-zA-Z)" );
  	setPartW( alt_ap_object, "decimal/binary/hexadecimal string from ASCII ranges (0-9a-zA-Z)" );

You can safely use functions:

	setPart(...)
	setPartW(...)
	setPartF(...)

Look them up in 'aplib.h'.

Also in the repo is my header file "i754.h". Alongside developing the APLIB arbitrary-precision arithmetic library, I am developing support for IEEE754-2008.
My 'i754' library has developing support for reading an internal float/double to a base2 (ascii '0' + {0,1} ) cstring, optionally with multiple-of-8 leading padding of 0's and writing such a string out to a native float/double object. You can also convert a base2 string to Big-Endian (useful because Intel-compatible IA-64 is Little-Endian).
For example, without it, on IA-64, the sign bit is bit 7 instead of the MSB 31, which is counter-intuitive for abstract over literal thinkers.

# Current status.
The APLIB/i754 library is still in development, but in general the functionality that has been implemented so far can be expected to work.
The codebase is not very large, so anyone with basic programming experience should be able to see clearly what functions are available, and get a good sense of how to invoke a given function correctly, and then once establishing the correctness of their output, look inside the given function body, and see how I've approached this subsystem.

I am integrating my ANSI/VT lightweight colourization library ("colour") into the APLIB suite, to provide an APLIB pretty-printer, for displaying operands and results from the APLIB arithmetic operations to the console (stdout) in ANSI/VT colourization.

I have Bison/Flex sample programs I wrote, which are a simple but flexible calculator, and a skeletal expression evaluator (they are not yet using APlib, but they will, thus the files are in this repo).
I also have (not on GitHub) a term re-writer function, so if I have enough time in front of me, I could bring all these subsystems together,
and we would eventually have a pretty great arbitrary-precision suite of front-end and back-end components.

I hope my coding of this library so far hasn't been too sh^t. Also in there are a smattering of lightweight but useful general helper functions.

DAVE.

