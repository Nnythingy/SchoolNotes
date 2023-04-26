import matplotlib.pyplot as plt
import numpy as np
from pcapng import FileScanner
from pcapng.blocks import EnhancedPacket
from scapy.layers.inet import IP
from scapy.layers.l2 import Ether
from datetime import datetime

ICMP_VALUES = ['Echo Reply', '', '', 
               'Destination Unreachable', '', 'Redirect Message',
               '', '', 'Echo Request',
               'Router Advertisement', 'Router Solicitation', 'Time Exceeded',
               'Parameter Problem: Bad IP header', 'Timestamp', 'Timestamp reply']
FIXED_SERVICE_AND_PORTS = [
    {'name':'IEC 61850 MMS and Siemens S7', 'port' : [102]},
    {'name' : 'Modbus TCP', 'port' : [502]},
    {'name' : 'Niagara Fox', 'port' : [1911, 4911] },
    {'name' : 'Ethernet IP', 'port' : [2222, 44818]},
    {'name' : 'IEC 60870-5-104', 'port' : [2404]},
    {'name' : 'DNP3', 'port' : [19999, 20000]},
    {'name' : 'SSH', 'port' : [22]},
    {'name' : 'BACnet', 'port' : [47808]}, ]
SGHONEYPOT = '172.31.20.47'
SGROUTER = '172.31.16.1'
BRHONEYPOT = '172.31.42.31'
BRROUTER = '172.31.32.1'

brazil = 'BR/oct/brmerged.pcap'
singapore = 'SG/oct/sgmerged.pcap'

brip = []
sgip = []
# format {day : [count, packet size]}
brpacketsize = {}
sgpacketsize = {}

# Opening the brpcapng file
with open(brazil, "rb") as brf:
    brscanner = FileScanner(brf)

    # Looping through the blocks in the file
    for block in brscanner:
        if isinstance(block, EnhancedPacket):
            decoded = Ether(block.packet_data)
            _pl1 = decoded.payload

            if isinstance(_pl1, IP) and _pl1.src != BRHONEYPOT and _pl1.src != BRROUTER:
                _pl2 = _pl1.payload
                brip.append(_pl1.src)
                brday = datetime.utcfromtimestamp(block.timestamp).strftime('%d')
                if brday in brpacketsize:
                    brpacketsize[brday][0] += 1
                    brpacketsize[brday][1] += len(_pl2)
                else:
                    brpacketsize[brday] = [1, len(_pl2)]

with open(singapore, "rb") as sgf:
    sgscanner = FileScanner(sgf)

    # Looping through the blocks in the file
    for block in sgscanner:
        if isinstance(block, EnhancedPacket):
            decoded = Ether(block.packet_data)
            _pl1 = decoded.payload

            if isinstance(_pl1, IP) and _pl1.src != SGHONEYPOT and _pl1.src != SGROUTER:
                _pl2 = _pl1.payload
                sgip.append(_pl1.src)
                sgday = datetime.utcfromtimestamp(block.timestamp).strftime('%d')
                if sgday in sgpacketsize:
                    sgpacketsize[sgday][0] += 1
                    sgpacketsize[sgday][1] += len(_pl2)
                else:
                    sgpacketsize[sgday] = [1, len(_pl2)]

print(list(set(brip) & set(sgip)))
print(len(list(set(brip) & set(sgip))))

# preparing the data for packet counter histogram
totalCount = [[],[]]
for i in brpacketsize.values():
    totalCount[0].append(i[0])
for i in sgpacketsize.values():
    totalCount[1].append(i[0])

totalSize = [[],[]]
for i in brpacketsize.values():
    totalSize[0].append(i[1])
for i in sgpacketsize.values():
    totalSize[1].append(i[1])

# graph for packet count
country = ["Brazil", "Singapore"]
x = np.arange(len(brpacketsize.keys()))
width = 0.25  # the width of the bars
multiplier = 0
fig, ax = plt.subplots(layout='constrained')

for i in totalCount:
    offset = width * multiplier
    rects = ax.bar(x + offset, i, width)
    ax.bar_label(rects, padding=3)
    multiplier += 1

ax.legend(["Brazil", "Singapore"])
ax.set_xticks(x, list(brpacketsize.keys()))
plt.ylabel='Packet Count'
plt.xlabel='Day'
plt.title='2017 October'
plt.show()

# graph for packet size
country = ["Brazil", "Singapore"]
x = np.arange(len(brpacketsize.keys()))
y = np.arange(max(max(totalSize)))
width = 0.25  # the width of the bars
multiplier = 0
fig, ax = plt.subplots(layout='constrained')

for i in totalSize:
    offset = width * multiplier
    rects = ax.bar(x + offset, i, width=width)
    ax.bar_label(rects, fmt='{:,.0f}', padding=3)
    multiplier += 1

ax.legend(["Brazil", "Singapore"])
ax.set_ylabel='Packet Size'
ax.set_xlabel='Day'
ax.set_title='2017 October'
ax.set_xticks(x, list(brpacketsize.keys()))
plt.show()