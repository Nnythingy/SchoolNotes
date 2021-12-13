#!/usr/local/Python-3.7/bin/python3
import sys

while(True):
	pktHeadSize = 6
	pktHead = ''
	while pktHeadSize > 0:
		pktHead += sys.stdin.buffer.read1(pktHeadSize).decode()
		pktHeadSize -= len(pktHead)
	if pktHead != "Size: ":
		break
	size = ''

	while(True):
		char = sys.stdin.buffer.read1(1)
		if char == b"B":
			break
		size += char.decode()

	size = int(size)
	while size > 0:
		data = sys.stdin.buffer.read1(size)
		sys.stdout.buffer.write(data)
		sys.stdout.buffer.flush()
		size -= len(data)
