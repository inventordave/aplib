# APlib
An arbitrary-precision library.

In development. Currently produces correct results for 2 signed integer inputs.

To compile, type "make aplibc" on the command-line. Assumes you have GCC available.

Test:

aplibc %1 %2


4 functions so far:

ADD(a, b)
SUB(a, b)
MUL(a, b)
EXP(a, b)

EXP() converts a negative exponent (param b), to a positive integer, just by changing the sign.

As the lib is ultimately for ap real-valued numbers, the functions take as operands an object called AP, which has a .major and .minor component.
Populate the .major component of 2 AP operands with an ascii-char based Integer string (e.g. a.major -> "1234").
A simple '[AP] obj.major = strdup("[1234567890]+");' statement will do, as an example.

Also in the repo is my header file "Dave_IEEE754.h". (APlib.c actually includes it). Alongside developing the APlib arbitrary-precision arithmetic library, I am developing support for IEEE754-2008. In "test.c" are 2 simple test functions to show some of the functionality.

So far, along with the 4 arithmetic functions that work on arbitrary-length Integers (the only limit is in how much memory the OS will provide via any malloc(...) call), I have functions that convert arbitrary-length Integer base10 digit-strings to a binary string (DEC_2_BIN). It works, but doesn't pad the binary string to 8-bit boundaries. This simply means that for example, a decimal value such as 32, will be converted to 100000, rather than 00100000. However, it is arbitrary-precision, again subject to the memory limits of your memory manager.

There are even 2 helper functions, "_2kMax", and "_2kMin", that will take an AP decimal number object, and return the exponent k of the minimum greater (or maximum smaller) 2k value (any number that is a k-power of 2 - useful when working with Binary.)

I fear I will not get much more time to work on this library, which is a shame, and if I physically can, I will.

I hope somebody finds this repo, looks through it (it's not massive), and a re-write of a main() function aside (I use main() functions usually to run tests), maybe they'll like it, I dunno.

Bye for now.

