#!/usr/bin/python3
from bs4.element import ContentMetaAttributeValue
import requests
from bs4 import BeautifulSoup

def testChar(password:str, found:str, start:int, end:int):
    website = "http://ctf.nus-cs2107.com:2772/"
    payload = {
        'creds' : password
    }
    ogReq = requests.post(website, data=payload)
    daSauce = BeautifulSoup(ogReq.text, 'html.parser')
    data = daSauce.find('p', {'id':'new-creds'})

    for i in range(10,126):
        newPassword = password + "\n" + found + chr(i)
        newPayload = {
            'creds' : newPassword
        }
        newReq = requests.post(website, data=newPayload)
        newSauce = BeautifulSoup(newReq.text, 'html.parser')
        newData = newSauce.find('p', {'id': 'new-creds'})
        if (newData.text[start:end] == data.text[start:end]):
            return found + chr(i)

found = ""
blocks = 6
for i in range((16*blocks - 2), 0, -1):
    password = "A" * i
    found = testChar(password, found, 0, 32 * blocks)
    #add new character to those previously found
    print(found)

'''
import sys

def split_len(seq, length):
    return [seq[i:i+length] for i in range(0, len(seq), length)]

def oracle(chosen):
    secret = "foobarbaz1234567890%sSecret42" % chosen # target to decrypt
    secret = getPadding(secret)
    if display:
        displaySecret(secret) # For illustrative purposes
    ct = cipher.encrypt(secret)
    return ct

def getPadding(secret):
    pl = len(secret)
    mod = pl % 16
    if mod != 0:
        padding = 16 - mod
        secret += "X" * padding
    return secret

def displaySecret(secret):
    split = split_len(secret, 16)
    display = ""
    for i in split:
        for j in split_len(i, 1):
            display += j + " "
        display += " "

    print ("pt: %s" % display)

def displayCiphertext(ct):
    split = split_len(ct, 16)
    display = ""

    for i in split:
        display += i.encode('hex') + " "

    print ("ct: %s" % (display))

if __name__ == "__main__":
    if len(sys.argv) < 2:
        exit("Usage: %s plaintext" % sys.argv[0])

    display=True # Toggle for verbose out put
    key = "deadbeefcafecode"
    cipher = AES.new(key, AES.MODE_ECB, "\x00" * 16)
    cipher.block_size=8

    chosen = sys.argv[1]
    ct = oracle(chosen)
    if display:
        displayCiphertext(ct)
    else:
        print (ct.encode('hex'))
        '''
