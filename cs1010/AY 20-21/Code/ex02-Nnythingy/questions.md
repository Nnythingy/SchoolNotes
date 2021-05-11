Exercise 2: Binary, Rectangle, Fibonacci
----------------------------------------

Question 1: Binary
------------------

In this question, you are asked to convert a number
represented in binary format (using digits 0 and 1) into
the decimal format (using digits 0 and 9).

A number in decimal format is represented with base 10.
The last digit (rightmost) corresponds to the unit of
1, the next digit (second last) corresponds to the unit
of 10, and so on. So, one can write the decimal number,
for instance, 7146 as 7×1000 + 1×100 + 4×10 + 6×1.

A number represented in binary uses base 2 instead of
base 10.  The last digit corresponds to 1 . The second last
digit correponds to 2, the third last digit corresponds
to 4, and so on. So, the binary number 1101, for instance,
corresponds to 1×8 + 1×4 + 1×1 = 13.

Write a program called binary that reads in a positive
integer consists of only 0s and 1s from the standard input,
treats it as a binary number, and prints the corresponding
decimal number to the standard output.  

Sample run
----------

ooiwt@pe113:~/ex03-ooiwt$ ./binary
1101
13
ooiwt@pe113:~/ex03-ooiwt$ ./binary
111
7
ooiwt@pe113:~/ex03-ooiwt$ ./binary
10110100
180

Question 2: Rectangle
---------------------

Write a program called rectangle that reads two positive
integers from the standard input, corresponding to the
width and the height of the rectangle. The width and height
must be at least 2. Draw a rectangle on the screen using
the special ASCII characters #define "╔" "╗" "╝"
"╚" "═" "║", which corresponds to the top left, top
right, bottom right, bottom left, top/bottom edge, and
left/right edge of the rectangle respectively. Strings
consisting of these special characters have been
given to you in rectangle.c and we have defined them as
constants. For instance, "╔" is called `TOP_LEFT`, and to
print this out, you can write

```
cs1010_print_string(TOP_LEFT);
```

Sample Run
----------

ooiwt@pe113:~/ex03-ooiwt$ ./rectangle
2 2
╔╗
╚╝
ooiwt@pe113:~/ex03-ooiwt$ ./rectangle
2 10
╔╗
║║
║║
║║
║║
║║
║║
║║
║║
╚╝
ooiwt@pe113:~/ex03-ooiwt$ ./rectangle
10 10
╔════════╗
║        ║
║        ║
║        ║
║        ║
║        ║
║        ║
║        ║
║        ║
╚════════╝


Question 3: Fibonnaci
---------------------

The Fibonacci sequence is a sequence of numbers 1, 1, 2, 3,
5, 8, 13, ... Fibonacci numbers often appear in mathematics
as well as in nature and have many fascinating properties.

The Fibonacci sequence can be constructed as follows. The
first Fibonacci number is 1. The second Fibonacci number
is also 1. Subsequently, the i-th Fibonacci number is
computed as the sum of the previous two Fibonacci numbers,
the (i-2)-th, and the (i-1)-th.

Write a program called fibonacci that reads a positive
integer number n from the standard input, and print the
n-th Fibonacci number to the standard output. Your program
must not use recursion.

Sample Run
----------
ooiwt@pe113:~/ex03-ooiwt$ ./fibonacci
1
1
ooiwt@pe113:~/ex03-ooiwt$ ./fibonacci
10
55
ooiwt@pe113:~/ex03-ooiwt$ ./fibonacci
83
99194853094755497
