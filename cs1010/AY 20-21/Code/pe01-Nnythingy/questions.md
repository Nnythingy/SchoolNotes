CS1010 Practical Exam I 20/21 Semester 1
----------------------------------------

INSTRUCTIONS TO CANDIDATES

1. This assessment paper contains 5 questions.

2. The total marks for this assessment is 30. Answer ALL
   questions.

3. This is an OPEN BOOK assessment.  You are only allowed to
   refer to written/printed notes.  No online resources/digital
   documents are allowed, except those accessible from the PE
   nodes (peXXX.comp.nus.edu.sg) (e.g., man pages are allowed).

4. You can assume that all the given inputs are valid.

5. You can assume that the types `long` and `double` suffice for
   storing integer values and real values respectively, for the
   purpose of this examination.

6. You should see the following in your home directory:

   - The skeleton code error.c, twilight.c, reverse.c,
     factors.c and looknsay.c 
   - A file named Makefile to automate compilation and 
     testing 
   - A file named test.sh to invoke the program with its 
     test cases 
   - Two directories, inputs and outputs, within which you 
     can find some sample inputs and outputs 
   - `compile_flags.txt` which contains the compilation flags.

7. You can run the command `make` to automatically compile and
   (if compiled successfully) run the tests.

8. Solve the given programming tasks by editing the given
   skeleton code. You can leave the files in your home
   directory and log off after the asssessment is over. There
   is no need to submit your code.

9. Only the code written in error.c, twilight.c, reverse.c,
   factors.c, and looknsay.c directly under your home directory
   will be graded. Make sure that you write your solution in
   the correct file.

10. Marking criteria are (i) correctness, (ii) style, and
    (iii) efficiency.  One mark is allocated for style for each
    question. One mark is allocated to efficiency for Question 4.  
	The rest is allocated for correctness.

11. Note that correctness is defined in the broad sense of
    using the various programming constructs in C (type,
    function, variable, loops, conditionals, arithmetic
    expressions, logical expressions) properly – not just
    producing the correct output.

12. You should write code that is clean, neat, and readable
    to get the mark allocated to style.


# Question 1: Error (4 marks) 
-----------------------------

Mr. Bean is a sloppy engineer and he always refers to a
number by ignoring the k least significant digits.  For
instance, if k = 2, he would just refer to the number 1893
as "roughly 1800".   For this example, he incurs an error of
93/1893 = 0.049128 = 4.9128% in his calculation.

Write a program `error.c` that determines the percentage of
error that Mr. Bean makes.  The program should take in two
positive integers from the standard input:

- k is the number of least significant digits that Mr. Bean
  ignores.  k is no more than the number of digits in n.  
- n is the number of that Mr. Bean is referring to.

Your program should print to the standard output, the percentage 
of error incurred by Mr. Bean when he estimates the number n 
by ignoring the last k digits.

Sample Run 
---------- 
```
ooiwt@pe101:~/$ ./error 
2 1893 
4.9128
ooiwt@pe101:~/$ ./error 
3 5000 
0.0000
ooiwt@pe101:~/$ ./error 
4 9876 
100.0000
```

# Question 2: Twilight (4 marks)
-------------------------------- 
Twilight refers to the time just before sunrise and just
after sunset.  There are three categories of twilight,
depending on how far the sun is below horizon.

On 3rd October 2020, the starting time and ending time
(inclusive) of each twilight in Singapore are as follows:

Category              | Before Sunrise | After Sunset
----------------------|----------------|---------------
Astronomical Twilight | 5:41 - 6:05    | 19:42 - 20:25
Nautical Twilight     | 6:06 - 6:29    | 19:18 - 19:41 
Civil Twilight        | 6:30 - 6:50    | 18:57 - 19:17

Write a program `twilight.c` that reads in two positive
integers from the standard input, representing the hour and
the minute of the time of the day respectively, and then
determine if the given time falls within the twilight
period, and if so, what category it is.

If the given time does not fall within the twilight period,
print `not twilight` to the standard output.  Otherwise,
print either `astronomical`, `nautical`, or `civil` if the
given time falls under the category of astronimical
twilight, nautical twilight, or civil twilight,
respectively.

Sample Run 
---------- 
```
ooiwt@pe101:~/$ ./twilight 
6 20
nautical
ooiwt@pe101:~/$ ./twilight 
19 42 
astronomical
ooiwt@pe101:~/$ ./twilight 
6 40 
civil
ooiwt@pe101:~/$ ./twilight 
12 00 
not twilight
```

# Question 3: Reverse (6 marks)
-------------------------------

We define the reverse of an integer as another integer with
the digits rearranged in reversed order (ignoring leading
zeros).

For instance, the reverse of 1234 is 4321.  The reverse of
1000 is 1.

Write a program `reverse.c` that:
- reads in a positive integer n from the standard input
- prints out _the square_ of the reverse of n to the standard 
  output.

CONSTRAINT: Your program must solve this problem _recursively_ 
and your code must not contains any loops (`for`, `while`, or 
`do-while`).  You are not allowed to use arrays to solve this
problem.

Sample Run 
---------- 
```
ooiwt@pe101:~/$ ./reverse 
1000 
1
ooiwt@pe101:~/$ ./reverse 
1234 
18671041
```

# Question 4: Factors (8 marks)
-------------------------------

Recall that a prime number is an integer larger than 1 that
can only be divisible by 1 or itself.

Give a positive integer n, we wish to factorize n into its
prime factors. Recall that factors of n are positive
integers no larger than n that n can be divided by. For
example: 1, 2, 3, 4, 6, 8, 12, 24 are all the factors of 24.
Among these factors, 2 and 3 are prime numbers so they are
the prime factors.

Given any positive integer n, with prime factors p0, p1, p2,
.. pk, we can write n as the product of only its prime
factors.

For instance,

  168 = 2 x 2 x 2 x 3 x 7

Here, we multiple the prime factor 2 three times, the prime
factor 3 one time, and the prime factor 7 one time.

We can write any number n as

  n = p0^q0 * p1^q1 * .. * pk^qk

where a^b denotes "a to the power of b", for prime factors
p0 to pk (in increasing order).

We call q0, q1, .. qk the exponenets of prime factors of n.

For instance, the exponents of the prime factors of 168 is
3, 1, 1.

Write a program `factors.c` that reads from the standard
input a positive integer n (n > 1), and prints to the
standard output, the prime factors and the corresponding 
exponents.  Print each prime factor and its exponent, 
separated by a space, on a new line.

NOTE: There is one mark allocated to efficiency for this
question.  Here, we do not require advanced factorization 
or primarity checks algoritms to solve this question. It
suffices to avoid obvious redundant work to obtain this
efficiency mark.  As a reference, you may run the program
`~cs1010/factors` to compare the speed of your code against
the expected answer.


Sample Run 
---------- 
```
ooiwt@pe101:~$ ./factors
168
2 3
3 1
7 1
ooiwt@pe101:~$ ./factors
24
2 3
3 1
ooiwt@pe101:~$ ./factors
7
7 1
```

Note: The original question has an error in the outputs of 
sample runs above.  This file has corrected the error.

# Question 5: Look-n-Say (8 marks)
----------------------------------

This question is dedicated to the great mathematician John
H. Conway who passed away this year due to COVID-19.

Among the many mathematical endeavors John H. Conway studied
is the look-and-say sequence.  The sequence starts with a
given number n.  The (i+1)-th number in the sequence is
generated by "saying out" the i-th number.

For instance, let's say that we start with the number n = 1.

Looking at the number "1", we say (there is) "one 1".  So
the next number in the sequence is 11.

Looking at the number "11", we say (there are) "two 1s".  So
the next number in the sequence is 21.

The number "21" has "one 2 and one 1".  So the next number
in the sequence is 1211.

The number "1211" has "one 1, one 2, and two 1s".  So the
next number in the sequence is 111221.

The look-and-say sequence starting with 1 is thus 1, 11, 21,
1211, 111221, 312211, 13112221, ..

The numbers in the sequence can grow to many digits quickly.
For this question, we will only say out at most the last 8
digits in the sequence.  In the sequence above, the next
number after 13112221 is 1113213211.  Instead of saying
"1113213211", we will generate the next number by saying the
last 8 digit "13213211" only and so we will get
"11131211131221" as the next number in the sequence.

Write a program 'looknsay.c' that reads in from the standard
input:

- A positive number n, that represents the first number in
  the sequence.  You may assume that n does not contain the
  digits 0.  
- A positive number k

and prints to the standard output, the k-th number in the
look-and-say sequence starting with n.

CONSTRAINT: You are not allowed to solve this problem using
arrays.

Sample Run 
---------- 
``` 
ooiwt@pe101:~$ ./looknsay 
1 1 
1
ooiwt@pe101:~$ ./looknsay 
1 9
11131211131221
ooiwt@pe101:~$ ./looknsay 
999999999999999 2 
89 
```
