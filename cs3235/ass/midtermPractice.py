from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from base64 import b64encode
import gmpy2

""" 
# prac midterms birthday attack
# this is because there are 40 distinct places to change, then either good or bad version
versionToSign = pow(2,40)

prob = 0.01
i = 0
while True:
    totalHash = pow(2, i)
    if (versionToSign/totalHash <= prob):
        print(i)
        break
    i += 1
 """
""" 
# prac midterms padding oracle
ciphertext = "4d068729d585ffd15b87dbb3bce82131adccd5feed25889503b8b612075a07f5"
blocksize = 16 # actual block size to change
blocksize = 2 * blocksize # times 2 since 2 characters = 1 byte

iv = ciphertext[:blocksize]
att = ciphertext[blocksize:]

intermediate = int("26",16)^int("2",16)
realValue = hex(intermediate^int("21",16))
print(realValue)

# 1st change n-1 block to affect padding of n block
# save fake value ^ pad as intermediate
# save intermediate ^ og n-1 block as real message
# to change new padding - intermediate ^ pad
 """
""" 
# prac midterms qn3 security principles
# security by obscurity is bad VIOLATED BY The key to the house is stashed below the doormat
# Principle of Least Privilege VIOLATED BY A user account that performs log backup to a server has administractive rights to install packages on the server
# Overall security is as weak as the weakest link VIOLATED BY Your sysadmin uses a rng to create her passwords, refreshing them each month; however her password
# recovery qn is "What is the colour of your car"
# Allowlisting is better than blocklisting VIOLATED BY An anitvirus checks programs against a database of known malware
 """
""" 
# pract midterms qn 4
# In cryptography, perfect forward secrecy (PFS) is a property of a crypto system in which compromises of long-term keys at a time t do not compromise
# session keys before time t, even when all public communication is logged by the adversary. Consider the following choices for generating a session key
# (which are modelled on SSL / TLS). Which method(s) below provides perfect forward secrecy? Choose all that apply and justify your answer.

# Server publishes an RSA public key. Client sends to the server a random value encrypted with the server’s public key, 
# which is then used as the session key for AES-CTR encryption between the client and the server.

# Server publishes an ElGamal public key. Client sends to the server a random value encrypted with the server’s public key, 
# which is then used as the session key for AES-CTR encryption between the client and the server.

# √Server publishes an RSA public key. Client chooses p, g, and a as per DHKE and encrypts A (i.e. g**a mod p) to server, encrypted with the server’s public key.
# Server responds with B (i.e. g**b mod p). Both sides now use the shared secret g**ab mod p (i.e. result of DHKE)
# as the session key for AES-CTR encryption between the client and the server.

# √Server publishes an ElGamal public key. Client chooses p, g, and a as per DHKE and encrypts A (i.e. g**a mod p) to server, encrypted with the server’s public key.
# Server responds with B (i.e. g**b mod p). Both sides now use the shared secret g**ab mod p (i.e. result of DHKE)
# as the session key for AES-CTR encryption between the client and the server.
 """

""" 
# prac midterms qn 5
# Let G be a finite cyclic group (eg. G = Zp* ) with generator g and p is a prime.

# Suppose Diffie-Hellman DH(gx,gy) = gxy is hard to compute in G. Which of the following you think is/are also difficult to compute? Select all the options that are correct.

# √(gx,gy) =(√g)^(xy + x + y + 1)

# (gx,gy) =(g^2)^(x + y)

# (gx,gy) =(√g)^(x + y)

# √(gx,gy) =√(g^xy)
 """
""" 
# pract midterms qn 6
# You have access to a symmetric cipher (E,D) and a key space K. 

# A key k can be split between two people p1, p2. We generate k1 and k1’ such that  k1 ⊕ k1’ = k. We give one key k1 to one person p1 and one key k1’ to the
# other person p2. To decrypt we need both keys. Say we want to distribute the key k to three people p1, p2, p3. We generate two random pairs (k1, k1’) and
# (k2, k2’) such that k1 ⊕ k1’ = k2 ⊕ k2’ = k. Any two pieces can decrypt but no single one can decrypt. Select all the options that are correct.

# p1 = (k1, k2), p2 = (k1’), p3 = (k2’) 

# √p1 = (k1, k2), p2 = (k1’ , k2), p3 = (k2’) 

# p1 = (k1, k2), p2 = (k1, k2), p3 = (k2’)

# p1 = (k1, k2), p2 = (k2, k2'), p3 = (k1’)

# √p1 = (k1, k2), p2 = (k1 , k2'), p3 = (k1’)
 """

""" 
# pract midterms qn 7
# Wendy visits the public wifi network at an airport. She connects to https://free-air-wifi.com and encounters an HTTPS certificate error.
# Upon finding out that the certificate is self-signed by the airport authorities (call them airport.com), she decides to accept the issuer
# as a root CA permanently, because she urgently wants to connect to her work email. 

# Which of the following attacks become possible? If you answer ‘yes’, explain how the attack succeeds.
# You can assume that all other assumptions in the HTTPS threat model hold.

# √Airport.com, if malicious, can decrypt Wendy’s web session with https://gmail.com while she is on the airport wifi.

# A malicious website https://evil.com, which doesn’t collude with airport.com, can now intercept the user’s visits to https://gmail.com

# Other malicious airport passengers, who are also on the airport.com wifi network, can decrypt Wendy’s communication with https://gmail.com

# ASes (or ISPs) routing Wendy’s traffic from the airport to https://gmail.com can decrypt her session without colluding with airport.com while she is on the airport wifi.

# √After Wendy leaves the airport, an AS (or ISP) routing Wendy’s traffic can decrypt Wendy’s web session with https://gmail.com if they collude with airport.com
 """
""" 
# prac midterms qn 8
# Testing why ECBC-MAC must use a fixed IV 0
# If not can reuse the tag 't' given by the previous MAC of message 'm'

# This is done by creating a fake IV of IV' = blk 1 of m ^ blk 1 of m' ^ IV

message = b"Kareem owes Prateek $500"
hexMsg = message.hex()
tag1 = "7eb4131ef980d67ae5ad84a714a53a1d28840830118d7444fecf410216a9d877"
iv1 = tag1[:32]
mac1 = tag1[32:]

fakeMsg = b"Shruti owes Prateek $500"
hexFake = fakeMsg.hex()
blk1Fake = hexFake[:32]
blk1Real = hexMsg[:32]

fakeIV = int(blk1Real,16)^int(blk1Fake,16)^int(iv1,16)
strFakeIV = hex(fakeIV)[2:]
print(strFakeIV+mac1)
 """