import matplotlib.pyplot as plt
from pcapng import FileScanner
from pcapng.blocks import EnhancedPacket
from scapy.layers.inet import IP, TCP, UDP, ICMP
from scapy.layers.l2 import Ether

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
HONEYPOT = '172.31.20.47'
ROUTER = '172.31.16.1'

# Opening the pcapng file
with open("SG/oct/sgmerged.pcap", "rb") as f:
    scanner = FileScanner(f)

    # format {srcip : [protocol 1, service, count]}
    details = dict()

    # Looping through the blocks in the file
    for block in scanner:
        if isinstance(block, EnhancedPacket):
            decoded = Ether(block.packet_data)
            _pl1 = decoded.payload

            if isinstance(_pl1, IP) and _pl1.src != HONEYPOT and _pl1.src != ROUTER:
                _pl2 = _pl1.payload
                if isinstance(_pl2, ICMP):
                    if (_pl1.src in details) and (details[_pl1.src][1] == _pl2.type): 
                        #if srcip already exists, add 1 to total count
                        count = details[_pl1.src][2] 
                        details[_pl1.src] = ['ICMP', ICMP_VALUES[_pl2.type], count + 1]

                    else:
                        details[_pl1.src] = ['ICMP', ICMP_VALUES[_pl2.type], 1]
                    continue

                if isinstance(_pl2, TCP) or isinstance(_pl2, UDP):
                    protocol = _pl2.name
                    service = ''

                    # these source port here are crucial,
                    # the "attacker" are trying to use legitimate
                    # ports to interact with honeypot
                    if _pl2.sport == 80 and protocol == 'TCP':
                        service = 'HTTP'
                    elif _pl2.sport == 443 and protocol == 'TCP':
                        service = 'HTTPS'
                    elif _pl2.sport == 123 and protocol == 'UDP':
                        service = 'Network Time Protocol'
                    elif _pl2.sport == 53 and protocol == 'UDP':
                        continue
                    else:
                        for item in FIXED_SERVICE_AND_PORTS:
                            for port in item['port']:
                                if _pl2.dport == port:
                                    service = item['name']

                    if (_pl1.src in details) and (details[_pl1.src][1] == service): 
                        #if srcip already exists, add 1 to total count
                        count = details[_pl1.src][2]
                        details[_pl1.src] = [protocol, service, count + 1]
                    else:
                        details[_pl1.src] = [protocol, service, 1]
                    continue

    graphService = {}
    for resultlist in details.values():
        # adding the total counts of each service
        if resultlist[1] in graphService:
            graphService[resultlist[1]] += resultlist[2]
        else:
            graphService[resultlist[1]] = resultlist[2]

    graphService = dict(sorted(graphService.items(), key=lambda x:x[1], reverse=True))
    # plt.plot(list(graphService.keys())[:10], list(graphService.values())[:10])
    fig, ax = plt.subplots()
    barContainer = ax.barh(list(graphService.keys())[:10], list(graphService.values())[:10])
    ax.set(ylabel='Services', xlabel='Count', title='Top 10 Services')
    ax.bar_label(barContainer, fmt='{:,.0f}')
    plt.show()