APlib.

An arbitrary-precision library.

In development, going reasonably well. Currently produces correct results for 2 signed integer inputs for the core arithmetic operators (implemented as functions).

Essentially, you simply include "APlib.h" and/or "Dave_IEEE754.h" in your program source, and by the miracle of quantum mechanics, electrical engineering, and boolean logic, the lovely functions that I have implemented thus far will be available to your user program.
Also, if file "cc/ansivt2.h" is being requested by the compiler, go to my "ColorConsole" repo at https://github.com/inventordave2/ColorConsole, and clone it into an immediate subdirectory "./cc/" of the directory containing your copy of "Dave_IEEE754.h"/"APlib.h". ColorConsole is a vanilla ANSI/VT implementation, or in other words, it generates colourized output to the console (bear in mind, I am developing this on a Windows box, not Linux, so I target the Windows command console).

To compile the test suite, type "make ap" on the command-line. Assumes you have GCC available.

Invoke:

ap %1 %2 %3

Where the 3 operands are (possibly signed) integer strings.


4 core arithmetic operators so far:

ADD(a, b)
SUB(a, b)
MUL(a, b)
EXP(a, b)
(Note: EXP() currently converts a negative exponent (param b), to a positive integer, simply by changing the sign.)

As well as several secondary functions:

DIV_BY_2(ap a)
BIN_2_DEC(cstring str)
DEC_2_BIN(ap a, int packed)
"_2kMax(ap a)"
"_2kMin(ap a)"


As the lib is ultimately for ap real-valued numbers, the functions take as operands an object called AP, which has a .major and .minor component. Populate the .major component of 2 AP operands with an ascii-char based Integer string (e.g. a.major -> "1234").
A simple '[AP] obj.major = strdup("[1234567890]+");' statement will do, as an example.

Also in the repo is my header file "Dave_IEEE754.h". Alongside developing the APlib arbitrary-precision arithmetic library, I am developing support for IEEE754-2008. It has functions for reading an internal float/double to a c-string binary string, optionally with multiple-of-8 leading padding of 0's, writing such a string out to a native float/double object, converting a c-string binary string to Big-Endian. My dev system (Intel-compatible IA-64) is little-endian, so this is a useful function for being able to read the output string when it's printed to stdout (for example, without it, the sign bit is bit 7 - 0-based - instead of the MSB (bit 31). There are even 2 helper functions, "_2kMax", and "_2kMin", that will take an AP decimal number object, and return the exponent k of the minimum greater (or maximum smaller) 2k value (any number that is a k-power of 2 - useful when working with Binary.)

In "test.c" (compiles to "ap.exe") are some simple test functions to ensure ongoing correctness of the functions in the library. After each test function completes, the test suite will pause for you to press any key to continue onto the next test.

So far, along with the 4 arithmetic functions that work on arbitrary-length Integers (the only limit is in how much memory the OS will provide via any malloc(...) call), I have functions that convert arbitrary-length Integer base10 digit-strings to a binary string (DEC_2_BIN). It works, but doesn't pad the binary string to 8-bit boundaries if you set the 2nd parameter to 0. However, if you make the 2nd paramater 1, or any non-falsey answer, then it will pad the output binary digit string with leading 0's to a string length of a multiple of 8. This simply means that for example, a decimal value such as 32, will be converted to 00100000, rather than 100000, when passed an arg of "1". However, it is arbitrary-precision, again subject to the memory limits of your memory manager.

The APlib/IEEE754 library is not finished yet, but in general the functionality that has been implemented so far can be expected to work. The codebase is not very large, so anyone with basic experience should be able to see clearly what functions are available, get a good sense of how to invoke a given function correctly, and then once establishing the correctness of their output, look inside the given function body, and see how I've approached this subsystem.

CURRENT TO-DO:
The next core arithmetic operator (function) to implement is DIV(a,b), which implements a/b (division). The method I am using is emulating the paper-based "long division" technique. I similarly implemented MUL(a,b) (a x b) by using the paper-based "multiply-per-digit-fused-add-rows" method we all know from school.

I am also integrating my ANSI/VT lightweight colourization library into the APlib suite, in the form of an APlib pretty-printer, for displaying the operands and results from the APlib arithmetic operations to the console (stdout). Useful functions would be suchlike the generation of a Latex or SVG string for rendering an APlib Expression (such as A/B, for example) in the respective output encoding. One application might be putting the APlib runtime on a web server, and building a browser front-end.

I have a Bison/Flex sample program I wrote, which was a simple calculator, and skeleton expression evaluator. I also have (not on github) a term re-writer function, so if I had enough time in front of me, I could bring all these subsystems together and we would eventually have a pretty great arbitrary-precision suite of front-end and back-end components. I have even written my own Lexer and Parser (in Javascript), so a modified version of the C language ("C-" ?) that supported ap (therefore arbitrary-length) numerical values !and literals! might be a fun endgame.


I hope my coding of this library so far hasn't been too sh^t. Also in there are a smattering of lightweight but useful general helper functions. There is a skeleton implementation of a method for processing args/switches passed to your user program on the command-line. It's very simple, and you would need to use the skeleton function to guide you to code the specific if-blocks for checking for a specific potential arg/switch. Just look at "getOptions.c" for the general idea. Also in that TU is a general skeleton function for pre-processing input strings for validity/safety-checking. It's called "sanitizeStr(...)" and is very simple, checking an input c-string char-by-char for any invalid chars (as defined by you when you implement the concrete function), and responding if it finds one.

Dave (Lee).

Nov 2023

