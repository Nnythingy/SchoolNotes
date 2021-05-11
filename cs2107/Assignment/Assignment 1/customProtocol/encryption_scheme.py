import random


alphabet = r"abcdefghijklmnopqrstuvwxyz+-_0123456789{}"

def encrypt(message: str):
    random.seed(2107)
    acc = []
    for letter in message:
        shift = random.randint(0, len(alphabet))
        new_index = (alphabet.index(letter) + shift) % len(alphabet)
        acc.append(alphabet[new_index])

    return "".join(acc)




if __name__ == "__main__":
    with open('flag.txt') as file:
        flag = file.read().strip()
    ct = encrypt(flag)
    print(ct)

