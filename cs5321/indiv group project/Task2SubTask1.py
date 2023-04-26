from scapy.all import *
import whois

localIP = ['10.0', '172.16', '192.168']
allIP = []

# Opening the brpcapng file
with PcapReader("APT-trace.pcap") as ins:
    for pkt in ins:
        flag = 0

        _pl1 = pkt.payload

        for ip in localIP:
            length = len(ip)
            if (_pl1.src[:length] == ip):
                flag = 1
        
        if flag == 0 and _pl1.src not in allIP:
            allIP.append(_pl1.src)

ipInfo = {}
for checkIp in allIP:
    obj = whois.whois(checkIp)
    try:
        ipInfo[checkIp] = [str(obj['domain_name']),
                       str(obj['state']) + ' ' + str(obj['country'])]
    except KeyError:
        ipInfo[checkIp] = [str(obj['domain_name']),
                       str(obj['registrant_state_province']) + ' ' + str(obj['registrant_country'])]
        

import csv
with open('t2st1.csv','w') as f1:
    w = csv.writer(f1)
    w.writerows(ipInfo.items())
