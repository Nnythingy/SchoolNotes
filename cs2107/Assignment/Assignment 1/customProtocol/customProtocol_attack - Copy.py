#!/usr/bin/python3
import random


alphabet = r"abcdefghijklmnopqrstuvwxyz+-_0123456789{}"

def encrypt(message: str):
    random.seed(2107)
    acc = []
    for letter in message:
        shift = random.randint(0, len(alphabet))
        new_index = (alphabet.index(letter) + shift) % len(alphabet)
        print(new_index)
        acc.append(alphabet[new_index])

    return "".join(acc)


def decrypt(message: str):
    random.seed(2107)
    str = []
    for letter in message:
        shift = random.randint(0,len(alphabet))
        old_index = (alphabet.index(letter) - shift) % len(alphabet)
        str.append(alphabet[old_index])

    return "".join(str)


if __name__ == "__main__":
    #with open('flag.txt') as file:
    #    flag = file.read().strip()
    #ct = encrypt(flag)
    #print(ct)

#    print(encrypt("test"))
    print(decrypt("e11wft9}t4q0hdjntg8x7it6"))


#vqrl
