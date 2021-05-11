#!/usr/bin/python3
from bs4.element import ContentMetaAttributeValue
import requests
from Crypto.Cipher import AES
from bs4 import BeautifulSoup
import math

#already know len(hex(c)) == 544
#already know blockSize == 32
#blockSize = findBlockSize()

def findc ():
    website = "http://ctf.nus-cs2107.com:2773/"
    r = requests.get(website)
    soup = BeautifulSoup(r.text, 'html.parser')
    c = soup.find('p', {'id':'old-creds'})
    return c.text

def findBlockSize (c:int):
    website = "http://ctf.nus-cs2107.com:2773/"
    for i in range(1,len(hex(c))):
        r = requests.post(website, data={'data' : hex(c).lstrip("0x")[:-i]})
        if (r.text != "Internal Server Error."):
            return i

def plaintext ():
    pass

def padding (c:int, found:str, cip:str, block:int, currPad:int, newpad:str):
    website = "http://ctf.nus-cs2107.com:2773/"
    blockEnd = 544-32*block
    previous = hex(c).lstrip("0x")[0:544-blockEnd-64]
    padBlock = hex(c).lstrip("0x")[blockEnd-32:blockEnd] #getting the last block
    ivBlock = hex(c).lstrip("0x")[blockEnd-64:blockEnd-32] #getting the last block
    ogAttByte = ivBlock[32-(2*currPad):32-(2*(currPad-1))]
    
    for i in range (1,255):
        newAttByte = hex(i).lstrip("0x")
        if len(newAttByte) == 1:
            newAttByte = "0" + newAttByte

        newCipher = previous + ivBlock[:-2*currPad] + newAttByte + newpad + padBlock
        payload = {
            'data' : newCipher
        }
        ogReq = requests.post(website, data=payload)
        daSauce = BeautifulSoup(ogReq.text, 'html.parser')
        data = daSauce.find('p', {'id':'result'})
        if ((data.text == "Successful!") and (newAttByte != ogAttByte)):
            plaintext = hex(1 ^ int(ogAttByte,16) ^ i).lstrip("0x")
            print(ogAttByte)
            if len(plaintext) == 1:
                plaintext = "0" + plaintext
            return (plaintext + found), (ogAttByte + cip)


c = findc()
found = ""
cipher = ""
for i in range(1,17):
    new = ""
    for j in range(0, int(len(found)/2)):
        a = found[0+(j)*2:(j+1)*2]
        b = cipher[0+(j)*2:(j+1)*2]
        test = hex(int(a,16) ^ int(b,16) ^ (j+2)).lstrip("0x")
        if len(test) == 1:
            test = "0" + test
        new = new + test

    found, cipher = padding(c, found, cipher, 7, i, new)
    print(found + " " + str(i))

#cs2107{k33p_Y0uR_3rr0r_m3Ss4G3S_70_y0Urs3LF}