import sys
from socket import *
import zlib

serverPort = int(sys.argv[1])
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))
oldSeqNum = 9

while(1):
    # receiving message
    packet, clientAddr = serverSocket.recvfrom(64)
    checksum = str(packet[:12].decode())
    seqNum = packet[12:13].decode()
    message = packet[13:].decode()
    # check checksum for corruption
    checker = str(zlib.crc32(seqNum.encode() + message.encode()))
    padding = '0'*(12-len(checker))
    checker = str(padding + checker)

    if (checksum == checker):
        if (seqNum != oldSeqNum):
            packet = 'ACK' + str(seqNum)
            pad = '0'*(64-len(packet))
            packet = pad + packet
            serverSocket.sendto(packet.encode(),clientAddr)
            oldSeqNum = seqNum
            sys.stdout.flush()
            sys.stdout.write(message)
            continue
    packet = 'ACK' + str(oldSeqNum)
    pad = '0'*(64-len(packet))
    packet = pad + packet
    serverSocket.sendto(packet.encode(),clientAddr)

serverSocket.close()
