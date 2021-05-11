from Crypto.Cipher import AES
from binascii import hexlify, unhexlify, b2a_base64, a2b_base64
import itertools

IV = "helloworldcs2107"

def pad_key(key: str):
    """Pad the key with 0s"""

    # Variables
    length = len(key)
    default_length = 32

    # Check if key exceeds length
    if length > 32:
        raise ValueError("Key value too long")

    # Padding for Cipher
    if length < default_length:
        key += '0' * (default_length - length)

    # Return the padded key
    return key

def create_cipher(key, iv):
    """Create the cipher to decode the text"""
    return AES.new(key.encode(), AES.MODE_CBC, iv.encode())

def encrypt(key: str, iv:str, message: str):
    """Encrypt the text with iv"""
    cipher = create_cipher(key, iv)

    # Cipher text in base64
    return b2a_base64(cipher.encrypt(message.encode())).decode()

def decrypt(key: str, iv:str, cipher_text: str):
    """Decrypt the text with iv"""
    ct = a2b_base64(cipher_text)
    cipher = create_cipher(key, iv)
    return cipher.decrypt(ct).decode()

def getpassword(password: str):
    try:
        print(decrypt(pad_key(password), IV, ciphertext))
        print(password)
    except UnicodeDecodeError:
        #print(password + " cannot")
        pass

def testpassword(part1: str, part2:str, part3:str):
    for i in {"", "-", "_"}:
        for j in {"", "-", "_"}:
            lines = part1 + i + part2 + j + part3
            if len(lines) > 32:
                continue
            getpassword(lines)
            getpassword(lines.title())

if __name__ == '__main__':
    with open("ciphertext")as file:
        ciphertext = file.read()
        
    with open("passwordCracking_dict - Copy") as f:
        content = f.read().splitlines()
        for first in content:
            f.close()
            with open("passwordCracking_dict - Copy") as f2:
                content2 = f2.read().splitlines()
                f2.close()
                for second in content2:
                    with open("passwordCracking_dict - Copy") as f3:
                        content3 = f3.read().splitlines()
                        f3.close()
                    for third in content3:
                        testpassword(first, second, third)

#BJYls89CuTmSw/hivpp/5t66L1k3O1b8p6ugmBh0Ivg=

#cs2107{pl5_us3_secur3_p4ssw0rd5}