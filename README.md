# APlib
An arbitrary-precision library.

In development. Currently produces correct results for 2 signed integer inputs.

Get my repo https://github.com/inventordave2/ColorConsole

It is expected in order to compile APLib in it's current form.

Test:

aplib %1 %2

Where the operands are signed arbitrary-precision Integers.

2 functions:

ADD(a, b)
SUB(a, b)

As the lib is ultimately for ap real-valued numbers, the functions take as operands an object called AP, which has a .major and .minor component.
Populate the .major component of 2 operands with an ascii-char based Integer string (e.g. a.major -> "1234")

