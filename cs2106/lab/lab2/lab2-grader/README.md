# Grading script for CS2106 AY2122S1 Lab 2

## Quickstart

0. Ensure that you are on the xcne servers
1. Place your `myshell.c` file in the same folder as this README
2. Run `./grade_single.sh`

After a few minutes, the console will output a summary of your grades for each (non-bonus) component of this lab, along with specific comments for each testcase if your code did not pass it. 

To grade the bonus component, you should run `./grade_single.sh 1`. This will run tests for only the bonus component. 

## Explanation of Grading Script
_The writers of the grading script will like to thank Haowei for the codebase which was originally used for grading in AY2021S1_

All testcases are stored in the `testcases` folder, with a README within the folder to explain the purpose of each testcase. Each test is a bash script, and the system calls you used in your code are tracked using `strace` and logged into a `.trace` file. For the chained and redirection commands, temporary files may be used. 

Some testcases make use of executables that we have specifically written for testing purposes; these are compiled from the various `.c` files in this folder.

With the `.trace` files, we then use `Node.js` to read through the output of each file to ensure that they conform to our specifications as mentioned in the lab document. These files are found in the `./grader` folder. You can also manually look through the `.trace` files to see how your code behaves under each test. 

**NOTE:** Due to the stochastic nature of operating systems, it is not possible for the grading script to deterministically evaluate your code. As such, we have run the grading script multiple times and awarded you the highest grade among them. 