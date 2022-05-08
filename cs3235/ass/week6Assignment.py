""" #qn 1 password hashing
# The password database of a particular system is stored as a set of unsalted hashes using a known hash function h. Assume that h is a cryptographically secure hash function mapping {0, 1}^* to {0, 1}^k, and is publicly known. When a user logs in with password p, the system grants the user access iff h(p) matches the entry for the user in the database. 
# (Assume all users choose unique passwords known only to themselves. )
# If k = 16, how many guesses would an attacker, who doesn’t know the victim’s password, need to make in order to have a probability of logging in as the victim of at least 0.9%? 
# k = 16
k = 30
totalHash = pow(2, k)
prob = 0.9
guesses = totalHash*prob
print(guesses)

# Question is different from a birthday attack since it is about the number of times taken to
# attack and find a hash of the same value, instead of the probability that there already exists a collision
# in the message -> hash space
 """

""" #qn 2 birthday attack
# the birthday attack formula is prob = 1-(totalComb-1/totalComb)^(n*(n-1)/2)

from itertools import combinations
import math
import cmath

prob = 0.25
k = 16
totalCombinations = pow(2,k)
oneMinusProb = 1 - prob
logOneMinusProb = math.log(oneMinusProb)
remainingCombinations = totalCombinations-1
probRemainingCombinations = remainingCombinations / totalCombinations
logProbRemainingCombinations = math.log(probRemainingCombinations)

def quadratic(a, b, c):
    # calculate the discriminant
    d = (b**2) - (4*a*c)

    # find two solutions
    sol1 = (-b-cmath.sqrt(d))/(2*a)
    sol2 = (-b+cmath.sqrt(d))/(2*a)
    print('The solution are {0} and {1}'.format(sol1,sol2))
quadratic(1, -1, -2*(logOneMinusProb/logProbRemainingCombinations))
 """

""" #qn6 padding oracle
import requests

ciphertext = "75896b6dc9282fc16bbf7584413cd3db7de1b37b984cbec7ac0eff3e4b1f4bef55455bd405a38fb03b88178f05cd1099b4ffb2896379257ea08188f53603acfcf785c5b26744849ead4181a42569ffaf"
website = "http://padding-oracle.et.r.appspot.com/q"
blocksize = 16 # actual block size to change
blocksize = 2 * blocksize # times 2 since 2 characters = 1 byte

# 1st change n-1 block to affect padding of n block
# save fake value ^ pad as intermediate
# save intermediate ^ og n-1 block as real message
# to change new padding - intermediate ^ pad
def paddingOracle(block):
    attBlk = ciphertext[blocksize*(block-1):blocksize*(block+1)]
    print(f"attack block from {blocksize*(block-1)} to {blocksize*(block+1)}")
    message = ""
    intermediate = ""
    blk1 = attBlk[:blocksize]
    blk2 = attBlk[blocksize:]
    for k in (range(1,17)):
        newpad = ""
        attpos = blocksize - k*2
        if len(intermediate) > 0:
            for i in range(0, int(len(intermediate)/2)):
                hexinter = intermediate[i*2 : (i+1)*2]
                x = attpos + 2 + i*2
                # hexblk = blk2[x:x+2]
                # newpad = newpad + "{:02x}".format(int(hexinter,16) ^ int(hexblk,16) ^ k)
                newpad = newpad + "{:02x}".format(int(hexinter,16) ^ k)

        for j in range(256):
            attbyte= "{:02x}".format(j)
            iv = blk1[:attpos] + attbyte + newpad
            ogct = ciphertext[:blocksize*(block-1)] 
            newct = ogct + iv + blk2
            params = {"p":"5", "info":newct}
            attack = requests.get(website,params)
            if attack.status_code == 404 or attack.status_code == 200: #200 is for the original padding
                intermediate = "{:02x}".format(j^k) + intermediate
                m = j^k^int(blk1[attpos:attpos+2],16)
                message = "{:02x}".format(m) + message
                attack.close
                break
            attack.close
            if j == 255:
                print("toh")

    return message

m = paddingOracle(1) + paddingOracle(2) + paddingOracle(3) + paddingOracle(4) #paddingOracle(5)
bytes_array = bytes.fromhex(m)
ascii_str = bytes_array.decode()
print(ascii_str)
#Cryptography is typically bypassed, not penetrated
 """