# Assignment 9
## Feedback for Nnythingy

**LATE!** This assignment is submitted 8 minutes after the deadline.  There is a 1% penalty for every 5 minutes late, capped at 80%.

You will eventually receive only 99% of the marks awarded below.

# digits
This question is jointly graded by a bot and a tutor.

We found the binary executable for `digits`.  It appears that your code compiles without errors.


The tutor has marked your code.  You can find [the comments from your tutor here](https://github.com/nus-cs1010-2021-s1/as09-Nnythingy/commit/77b82d195f6e334b755b1943a94b0daad5d19e40).

Deduction by tutor: 2 (correctness), 0 (efficiency), 0 (documentation), 0 (style).

Output from the bot:

* Your code seems to have a memory leak.  There is a -1 penalty for not freeing memory that is allocated on the heap.  Please make sure any memory that you asked for are returned back after you are done.  It's polite to do so!
* No invalid memory read detected.
* No invalid memory write detected.
* Your program seems to survive even when memory allocation fails.  Good.
* `clang` and `clang-tidy` are happy with your `digits.c`.  No warnings are generated.  :confetti_ball:
* No documentation-related warnings are generated. 

| Criteria      | Marks          |
| --------------|--------------- |
| Correctness   | 22 |
| Efficiency    | 10     |
| Style         | 0     |
| Documentation | 0     |
| **TOTAL**     | **32**     |
