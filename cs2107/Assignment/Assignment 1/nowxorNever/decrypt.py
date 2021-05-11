#!/usr/bin/python3

'''
"""
Xor tool to encrypt a file with XOR cypher using a key
Inspired from http://www.daniweb.com/software-development/python/code/216632/text-encryptiondecryption-with-xor-python
Usage: python xor.py plain_text_file 'secret_key'
Will result in a *.xor file
"""

from sys import argv
from StringIO import StringIO

def crypt(t, k):
    old = StringIO(t)
    new = StringIO(t)

    for position in xrange(len(t)):
        bias = ord(k[position % len(k)])
        old_char = ord(old.read(1))
        new_char = chr(old_char ^ bias)
        new.seek(position)
        new.write(new_char)

    new.seek(0)
    return new.read()

if len(argv) != 3:
    print ("Usage: python xor.py plain_text_file 'secret_key'")
else:
    f_in = open(argv[1], 'rb')
    f_out = open('%s.png' % argv[1], 'wb')
    key = argv[2]
    f_out.write(crypt(f_in.read(), key))
    f_in.close()
    f_out.close()
'''

'''
key = "3064657030646570";
keylen = len(key)
with open("encrypted_file.png") as f:
    with open("decrypted.png") as file:
        ciphertext = f.read()
        cipherlength = len(ciphertext)
        number = cipherlength/keylen
        if cipherlength%keylen == 0 :
            for i in number:
                key = key + key
        file.append(hex(ciphertext) ^ hex(key))
        '''

print(hex(0x60ed223e3a696f6a ^ 0x89504e470d0a1a0a))
