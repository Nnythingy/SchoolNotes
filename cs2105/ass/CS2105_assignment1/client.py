#!/usr/bin/python3

from socket import *

serverName = "localhost"
serverPort = 5555

message = "POST /key/Test content-length 6  CS2105"
message1 = "GET /key/Test  "
message2 = "DELETE /key/Test  "

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
clientSocket.send(message.encode())
received = clientSocket.recv(2048)
print("server:" + received.decode())
clientSocket.close()

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
clientSocket.send(message1.encode())
received = clientSocket.recv(2048)
print("server:" + received.decode())
clientSocket.close()

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
clientSocket.send(message2.encode())
received = clientSocket.recv(2048)
print("server:" + received.decode())
clientSocket.close()

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
clientSocket.send(message1.encode())
received = clientSocket.recv(2048)
print("server:" + received.decode())
clientSocket.close()
