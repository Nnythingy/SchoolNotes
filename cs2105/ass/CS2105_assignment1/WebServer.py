#!/usr/bin/python3
from socket import *
import sys

keyDict = {}
counterDict = {}

def readclear():
    #reads until the next whitespace
    while (1):
        if (connectionSocket.recv(1).decode() == " "):
            break

def keyfunc(httpMethod, path):
    if (httpMethod == "GET"):
        message = connectionSocket.recv(1) #header end
        if (message.decode() == " "):
            if (path in keyDict):
                reply = f'200 OK content-length {len(keyDict[path])}  '
                connectionSocket.sendall(reply.encode() + keyDict[path])
            else:
                reply = "404 NotFound  "
                connectionSocket.sendall(reply.encode())

    elif (httpMethod == "POST"):
        keyDict[path] = ''
        content = ''
        length = ''
        flag = 0
        while (flag == 0):
            while (1):
                message = connectionSocket.recv(1)
                if (message.decode() != " "):
                    content += message.decode().lower()
                    content.strip()
                else: #whitespace detected
                    if (content == "content-length"):
                        break
                    else:
                        content = ''
            while (flag == 0):
                expect = connectionSocket.recv(1)
                try:
                    int(expect.decode())
                except:
                    if (expect.decode() == " "):
                        while (1):
                            if (connectionSocket.recv(1).decode() == " "):
                                #header end, content start
                                length = int(length)
                                data = b''
                                while length > 0:
                                    newdata = connectionSocket.recv(length)
                                    data += newdata
                                    length -= len(newdata)
                                keyDict[path] = data
                                reply = "200 OK  "
                                connectionSocket.sendall(reply.encode())
                                flag = 1
                                break
                            else:
                                readclear()
                    else:
                        readclear()
                        break
                else:
                    length += expect.decode()

    elif (httpMethod == "DELETE"):
        message = connectionSocket.recv(1) #header end
        if (message.decode() == " "):
            if (path in keyDict):
                #deletes key and returns value in key
                reply = f"200 OK content-length {len(keyDict[path])}  "
                connectionSocket.sendall(reply.encode() + keyDict.pop(path,None))
            else:
                reply = "404 NotFound  "
                connectionSocket.sendall(reply.encode())

def counterfunc(httpMethod, path):
    if (httpMethod == "GET"):
        message = connectionSocket.recv(1) #header end
        if (message.decode() == " "):
            if (path in counterDict):
                reply = f"200 OK content-length 1  {counterDict[path]}"
                connectionSocket.sendall(reply.encode())
            else:
                reply = f"200 OK content-length 1  0"
                connectionSocket.sendall(reply.encode())

    elif (httpMethod == "POST"):
        message = connectionSocket.recv(1) #header end
        if (message.decode() == " "):
            if (path in counterDict):
                counterDict[path] += 1
                reply = f"200 OK  "
                connectionSocket.sendall(reply.encode())
            else:
                counterDict[path] = 1
                reply = f"200 OK  "
                connectionSocket.sendall(reply.encode())

serverPort = int(sys.argv[1])
serverSocket = socket(AF_INET, SOCK_STREAM)

serverSocket.bind(('', serverPort))
serverSocket.listen() #server ready
while (1):
    connectionSocket, clientAddr = serverSocket.accept()
    flag = 0

    while (flag == 0):
        httpMethod = ''
        path = ''
        while (1):
            message = connectionSocket.recv(1)
            if (len(message) == 0):
                flag = 1
                break
            if (message.decode() != " "):
                httpMethod += message.decode().upper()
                httpMethod.strip()
            else:
                break
        while (1):
            message = connectionSocket.recv(1)
            if not message:
                break
            if (message.decode() != " "):
                path += message.decode()
                path.strip()
            else:
                break
        if (path[1:4] == "key"):
            keyfunc(httpMethod, path[5:])
        elif (path[1:8] == "counter"):
            counterfunc(httpMethod, path[9:])
    connectionSocket.close()
