# APlib
An arbitrary-precision library.

In development. Currently produces correct results for 2 signed integer inputs.

To compile, type "make test" on the command-line. Assumes you have GCC available.

Invoke:

test %1 %2 %3



4 functions so far:

ADD(a, b)
SUB(a, b)
MUL(a, b)
EXP(a, b)

EXP() converts a negative exponent (param b), to a positive integer, just by changing the sign.

As the lib is ultimately for ap real-valued numbers, the functions take as operands an object called AP, which has a .major and .minor component.
Populate the .major component of 2 AP operands with an ascii-char based Integer string (e.g. a.major -> "1234").
A simple '[AP] obj.major = strdup("[1234567890]+");' statement will do, as an example. Having decided to slightly re-engineer the library thus far, I am porting the code away from requiring a composite object to only requiring inputs to be decimal digit (technically also binary digit) c-strings. When progressing from Integer to FP AP arithmatic, the fractional part will simply be a 2nd digital c-string.

Also in the repo is my header file "Dave_IEEE754.h". (APlib.c actually includes it). Alongside developing the APlib arbitrary-precision arithmetic library, I am developing support for IEEE754-2008. It has functions for reading an internal float/double to a c-string binary string, optionally with multiple-of-8 leading padding of 0's, writing such a string out to a native float/double object, converting a c-string binary string to Big-Endian. My dev system (Intel-compatible IA-64) is little-endian, so this is a useful function for being able to read the output string when it's printed to stdout (for example, without it, the sign bit is bit 24 - 0-based - instead of the MSB (bit 31). There are even 2 helper functions, "_2kMax", and "_2kMin", that will take an AP decimal number object, and return the exponent k of the minimum greater (or maximum smaller) 2k value (any number that is a k-power of 2 - useful when working with Binary.)


In "test.c" are some simple test functions to ensure ongoing correctness of the functions in the library.

So far, along with the 4 arithmetic functions that work on arbitrary-length Integers (the only limit is in how much memory the OS will provide via any malloc(...) call), I have functions that convert arbitrary-length Integer base10 digit-strings to a binary string (DEC_2_BIN). It works, but doesn't pad the binary string to 8-bit boundaries if you set the 2nd parameter to 0. However, if you make the 2nd paramater 1, or any non-falsey answer, then it will pad the output binary digit string with leading 0's to a string length of a multiple of 8. This simply means that for example, a decimal value such as 32, will be converted to 00100000, rather than 100000, when passed an arg of "1". However, it is arbitrary-precision, again subject to the memory limits of your memory manager.





Bye for now.

