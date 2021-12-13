from socket import *
import sys
import zlib

def swapSeqNum(oldNum):
    if (oldNum == 0):
        return 1
    return 0

serverName = 'localhost'
serverPort = int(sys.argv[1])
clientSocket = socket(AF_INET, SOCK_DGRAM)
seqNum = 0

while (1):
    message = sys.stdin.buffer.read1(51)
    
    if len(message) == 0:
        break

    checksum = str(zlib.crc32(str(seqNum).encode() + message))
    padding = '0'*(12-len(checksum))
    checksum = padding + checksum
    packet = checksum.encode() + str(seqNum).encode() + message
    clientSocket.sendto(packet,(serverName, serverPort))
    clientSocket.settimeout(0.05)

    while (1):
        try:
            incPacket = clientSocket.recv(64)
            ACK = incPacket.decode()[-4:]
            # timeout of 50ms
        except:
            ACK = ''
        else:
            if (ACK[:3] == 'ACK'):
                if (ACK[3:4] == str(seqNum)):
                    seqNum = swapSeqNum(seqNum)
                    break
        clientSocket.sendto(packet,(serverName, serverPort))


clientSocket.close()
