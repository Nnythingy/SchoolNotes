# Breakdown of testcases

Testcases are broken down in the following format `NC`, where `N` is the corresponding exercise number, and `C` is the component being tested according to the order below: 

**ex1**: (a) foreground program, (b) background program, (c) info\
**ex2**: (a) wait, (b) terminate, (c) chained programs, (d) info, (e) quit\
**ex3**: (a) one redirection, (b) two redirections, (c) three redirections, (d) redirection for chained programs\
**ex4**: (a) \<Ctrl-Z\> + fg (b) \<Ctrl-C\>

## Exercise 1

### 1a
1. Test `{program}`
    - Check if program is run
2. Test `{program} (args...)`
    - Check if program is run with correct args
3. Check that program waits for ongoing command before running another command
4. Check program runs properly with multiple args

### 1b
1. Test `{program} &` and `{program} (args...) &`
    - Check if program is run in background (with correct args if present)
2. Check that program runs next command without waiting for background command 
3. Tests non-existing program files for `&` and non-`&` versions
    - Check that a process is not spawned
    - Check for correct output
  
### 1c
1. Test `info` for background commands
    - Check if `info` gives correct status for currently running program
    - Check if `info` gives correct status for exited program
2. Test `info` for foreground commands
    - Check if `info` gives correct nonzero exit codes
    - Check if `info` gives correct status and exit code when a running process exits
3. Test `info` for commands with improper args
    - Check that processes still spawn, but with appropriate exit code

## Exercise 2

### 2a
1. Test `wait {PID}`
    - Check if running programs are waited for
2. Check that exited programs are not waited for again

### 2b
1. Test `terminate {PID}`
    - Check if running programs are sent SIGTERM
2. Test `terminate {PID}` for multiple background commands
    - Check that already killed programs are not sent SIGTERM

### 2c
1. Test `{program1} && {program2}`
    - Check that program2 runs after program1
    - Check that both `wait(program1)` and `wait(program2)` are done
2. Test `{program1} (args...) && {program2} (args...)`
    - Check if both programs run with the correct args
    - Check that program2 runs after program1
    - Check that both `wait(program1)` and `wait(program2)` are done
3. Test a long chained command of 9 commands in total, with and without args
    - Check that the programs run in order
    - Check that the programs are waited in order
4. Test a long chained command of 9 commands in total, with and without args. One of the middle commands will return non-zero exit status.
    - Check that the rest of the chain is not executed
5. Test a long chained command of 9 commands in total, with and without args. One of the middle commands will point to a non-existing program.
    - Check that the rest of the chain is not executed, and a child process is not spawned for the non-existing program

### 2d
1. Test `info` for chained command without errors
    - Check that all programs have the correct status and exit code
2. Test `info` for chained command with errors
    - Check that `info` only lists programs without errors 
    - Check that `info` does not list extra programs
3. Test `info` for terminating
    - Check that `info` updates with the correct "Terminating" status 

### 2e
1. Test `quit` with a number of (exited) foreground + background commands
    - Check if all running processes (and only these processes) are sent the SIGTERM signal
    - Check if all running processes (and only these processes) are waited for before the shell exits
2. Test `quit` with a mix of exited and running background commands


## Exercise 3

### 3a
1. Test input redirection in foreground/background
    - Test `{program} (arg) < {file} (&)` with existing and non-existing file
2. Test output redirection in foreground/background
    - Test `{program} (arg) > {file} (&)` with existing and non-existing file, check permissions of created file
3. Test error redirection in foreground/background
    - Test `{program} (arg) 2> {file} (&)` with existing and non-existing file, check permissions of created file

### 3b
1. Test in/out redirections in foreground/background
    - Test `{program} (arg) < {file1} > {file2} (&)`
2. Test in/err redirections in foreground/background
    - Test `{program} (arg) < {file1} 2> {file2} (&)`
3. Test out/err redirections in foreground/background
    - Test `{program} (arg) > {file1} 2> {file2} (&)`

### 3c
1. Test in/out/err redirection in foreground/background
    - Test `{program} < {file1} > {file2} 2> {file3} (&)`

### 3d
1. Test a long chained command of 9 commands in total, with and without args, with and without redirection
2. Test a long chained command of 9 commands in total, with and without args, with and without redirection, one of the middle commands will have a non-existing input file.
    - Check that the rest of the chain is not executed, and a child process is not spawned for the program with the non-existing input file
3. Test a long chained command of 9 commands in total, with and without args, with and without redirection, one of the middle commands will exit with non-zero exit status + error output redirected into a file.
    - Check that the rest of the chain is not executed, and the error output is correctly captured into the file

## Exercise 4 (BONUS)

### 4a
1. Test if SIGTSTP signal is sent correctly, test if fg works
2. Test if SIGTSTP (and fg) works with redirection
3. Test if SIGTSTP (and fg) works with chained commands

### 4b
1. Test if SIGINT signal is sent correctly
2. Test if SIGINT works with redirection
3. Test if SIGINT works with chained commands