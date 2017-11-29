This version uses GNU readline
Contains a modified (written in C++) from
Chapter 3 of "flex & bison"
I do not like the way it uses all these casts,there is a better solution

built in functions:

sqrt
log
exp
input
print

requires flex/bison 

use

$> x = 0

$> while (x < 5) do x = x + 1; print(x)

$> if x == 5 then print(x); else print(0);

$> let f(a,b)=a*b;

$> y = f(10, 10)

$> print(y)

Example:

	x = input()

	y = input()

	value = x*y


