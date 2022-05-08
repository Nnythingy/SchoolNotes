""" 
# this is for week 3 qn 1
# confidentiality only
 """
""" 
# this is for week 3 qn 2
# G2(s) = G(s1, s2, . . . , s|s|-1 ) || s|s| only
 """
""" 
# this is for week 3 qn 3
# -The key space must be at least as big as the message space in order to have perfect security.
# - In perfect security, the following statement holds, where M is a random variable in the message space, m is the plaintext message, C is a random variable in the ciphertext space, and c1 and c2 are arbitrary ciphertexts.
# Pr[ M = m | C = c1 ] = Pr[ M = m | C = c2 ]
 """
""" 
# this is for week 3 qn 4
# If one considers an adversary which has no limits on computational power, the one-time pad does not have perfect secrecy
# - False
 """
""" 
# this is for week 3 qn 5
# Which of the following are examples of secure sockets?
# - SSL Socket
# - HTTPS connection
 """
""" 
# this is for week 3 qn 6
# Suppose you obtain two ciphertexts C, and C′ encrypted using the one-time pad. You happen to know that one was encrypted with key K and the other with its bitwise complement K’ respectively. What can you infer about the corresponding plaintext messages, M and M'?
# You can infer M ⊕ M'
 """
""" # this is for week 3 qn 7
A simple encryption scheme takes a message M ∈ {0, 1, 2, 3, 4} and encrypts using a shared random key K ∈ {0, 1, 2, 3, 4}. Suppose you do this by representing both K and M using three bits (000, 001, 010, 011, 100) each, and then calculating the XOR of their bitwise representations.

Is this scheme perfectly secure? Give a brief but clear explanation of your reasoning.

Hint: Use the definition of perfect security using the ciphertext "101".
- False
- To form the ciphertext "101",  the only way would be to XOR 100 and 001 as either message or key.  This would mean that an attacker after knowing that the ciphertext is "101", only has to guess from the message and key space from 0 to 4 ,1 and 4. Thus the probability of knowing the plaintext message after seeing the ciphertext is reduced thus there is no perfect secrecy.

"""
""" 
#this is for week 3 quiz qn 8
# The concept to solve this is to swap the exact part of Agnes Driscoll to Mallory ZeEvil while keeping
# the front and back offset exactly the same

plaintext = b"Agnes Driscoll"
offset = 8 * 2
oldciphertext = "5d6bd5b690abb24823195d8ba48a31228c312ee031d50d705229ae21bf26bdee70b5b38d430d40"
ciphertext = oldciphertext[offset:offset+28]

ciphertexthex = int(ciphertext, 16)
# bytes.hex() changes it to a string of hex
# int (hexstring, 16) changes the hex string to hex number
plaintexthex = int(plaintext.hex(), 16)

key = plaintexthex ^ ciphertexthex

check = ciphertexthex ^ key
checkhex = bytes.fromhex(hex(check)[2:])
print(checkhex.decode())

targettext = b"Mallory ZeEvil"
newCipherText = hex(int(targettext.hex(), 16) ^ key)[2:]
print(oldciphertext[:offset] + newCipherText + oldciphertext[offset+28:])
# 5d6bd5b690abb2482f1f5f82b8d80c70bf2708f934d50d705229ae21bf26bdee70b5b38d430d40
 """
"""
# week 3 question 9
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from base64 import b64encode

message1 = b"I really really love crypto"
key = bytes.fromhex("688d849dfc70c9cdf242531180575e37e74b0d432ddc5e4bd96e4c8c8d194388")
iv = bytes.fromhex("6f686873566938aabd64721273f461cd")
cipher = AES.new(key, AES.MODE_CBC, iv)

ctBytes = cipher.encrypt(pad(message1, AES.block_size))
print(ctBytes.hex())
# 80022b4bd50cda0fcb28cdd662e3d5e4b9690e4739c36aa4659a75b8f906deaf

message2 = b"I really really hate crypto"
cipher2 = AES.new(key, AES.MODE_CBC, iv)
ctBytes2 = cipher2.encrypt(pad(message2, AES.block_size))
print(ctBytes2.hex())
# 80022b4bd50cda0fcb28cdd662e3d5e46c400923821072d7929040a386a318dd 

iv2 = bytes.fromhex("777975af3109288a9542971f495918f3")
cipher3 = AES.new(key, AES.MODE_CBC, iv2)
ctBytes3 = cipher3.encrypt(pad(message2, AES.block_size))
print(ctBytes3.hex())
# 03b51da5c1286c57930bdfcb347bf26fc0e094626ff3421e912d49f1bf220678
 """