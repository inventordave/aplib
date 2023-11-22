APlib.

An arbitrary-precision library.

In development, going reasonably well. Currently produces correct results for 2 signed integer inputs for the core arithmetic operators (implemented as functions).

Essentially, you simply include "APlib.h" and/or "Dave_IEEE754.h" in your program source, and by the miracle of quantum mechanics, eletrical engineering, and boolean logic, the lovely functions that I have implemented thus far will be available to your user program.

To compile the test suite, type "make test" on the command-line. Assumes you have GCC available.

Invoke:

test %1 %2 %3

4 core arithmetic operators so far:

ADD(a, b)
SUB(a, b)
MUL(a, b)
EXP(a, b)
(Note: EXP() currently converts a negative exponent (param b), to a positive integer, simply by changing the sign.)

As well as several secondary functions:

DIV_BY_2(a)
BIN_2_DEC()
DEC_2_BIN()
%_2kMax(a)
%_2kMin(a)


As the lib is ultimately for ap real-valued numbers, the functions take as operands an object called AP, which has a .major and .minor component. Populate the .major component of 2 AP operands with an ascii-char based Integer string (e.g. a.major -> "1234").
A simple '[AP] obj.major = strdup("[1234567890]+");' statement will do, as an example.

Also in the repo is my header file "Dave_IEEE754.h" (APlib.c actually includes it). Alongside developing the APlib arbitrary-precision arithmetic library, I am developing support for IEEE754-2008. It has functions for reading an internal float/double to a c-string binary string, optionally with multiple-of-8 leading padding of 0's, writing such a string out to a native float/double object, converting a c-string binary string to Big-Endian. My dev system (Intel-compatible IA-64) is little-endian, so this is a useful function for being able to read the output string when it's printed to stdout (for example, without it, the sign bit is bit 24 - 0-based - instead of the MSB (bit 31). There are even 2 helper functions, "_2kMax", and "_2kMin", that will take an AP decimal number object, and return the exponent k of the minimum greater (or maximum smaller) 2k value (any number that is a k-power of 2 - useful when working with Binary.)

In "test.c" are some simple test functions to ensure ongoing correctness of the functions in the library.

So far, along with the 4 arithmetic functions that work on arbitrary-length Integers (the only limit is in how much memory the OS will provide via any malloc(...) call), I have functions that convert arbitrary-length Integer base10 digit-strings to a binary string (DEC_2_BIN). It works, but doesn't pad the binary string to 8-bit boundaries if you set the 2nd parameter to 0. However, if you make the 2nd paramater 1, or any non-falsey answer, then it will pad the output binary digit string with leading 0's to a string length of a multiple of 8. This simply means that for example, a decimal value such as 32, will be converted to 00100000, rather than 100000, when passed an arg of "1". However, it is arbitrary-precision, again subject to the memory limits of your memory manager.

The APlib/IEEE754 library is not finished yet, but in general the functionality that has been implemented so far can be expected to work. The codebase is not very large, so anyone with basic experience should be able to see clearly what functions are available, get a good sense of he to invoke a given function correctly, and then once establishing the correctness of their output, look inside the given function body, and see how I've approached this subsystem.

CURRENT TO-DO:
The next core arithmetic operator (function) to implement is DIV(a,b), which implements a/b (division). The method I am using is emulating the paper-based "long division" technique. I similarly implemented MUL(a,b) (a x b) by using the paper-based "multiply-per-digit-fused-add-rows" method we all know from school.

I hope my coding of this library so far hasn't been too sh^t.

Dave (Lee).

Nov 2023

