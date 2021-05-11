#!/usr/bin/python3
# pwntools is a very powerful library for doing exploitation
from pwn import *

# TODO: Update with actual values
HOST = "cs2107-ctfd-i.comp.nus.edu.sg"
PORT = 2773
BINARY = "./addressbook"

#r = remote(HOST, PORT)  # to open a connection to the remote service, aka the challenge
r = process(BINARY)   # use process instead of remote to execute the local version of the program
#pause()

# TODO: Fill in your payload
r.sendline(b"2")
PADDING = 0x1
r.sendline("1")
r.sendline("1")

# earlier, the script helps us send/receive data to/from the service
# with interactive, we can directly interact with the service
r.interactive()
