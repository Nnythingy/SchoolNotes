""" 
# week 2 qn 1
# Each node in the BGP protocol is an ISP or AS. A BGP hijacking attack allows an attacker to (choose the most applicable option):

# Impersonate a network node

# Perform a “man-in-the-middle” attack by modifying traffic between two nodes

# Eavesdrop on traffic for a network segment

# Deny traffic to a network segment

# Route all traffic for a particular network segment through a node they control

# √All of the above
 """
""" 
# week 2 qn 2
# IP Spoofing refers to:

# Modifying IP packet data payload in transit
 
# Eavesdropping on IP data payload

# None of the above

# √Modifying the source address in an IP packet
 """
""" 
# week 2 qn 3
# An IP Smurf attack allows an attacker:
# Modify in-transit network data between a user and a server

# √Overload a network node by having other nodes send it large amounts of data

# Impersonate another user

# All of the above

# Eavesdrop on network traffic
  """
""" 
# week 2 qn 4
# If an attacker can guess the initial sequence number used by a specific host in TCP, 
# what consequences does this have? Assume the attacker is "off-path", i.e., cannot eavesdrop
# or intercept packets directly in transit between the host and other nodes. Also the attacker
# can only guess the sequence number used by a single host, and not other nodes.

# All of the above

# An attacker can use this to force existing (established) TCP sessions to close

# An attacker can use this to intercept an existing (established) TCP session

# √An attacker can use this to impersonate another node / IP address and send counterfeit information to the host (server)

# An attacker can use this to impersonate another node / IP address and receive privileged information sent by the server
 """
""" 
# week 2 qn 5
# DNS Cache Poisoning of a specific node allows an off-path network attacker to
# (choose all that apply):
# Impersonate a user to a website

# √Intercept communication between a web server and a given client

# √Impersonate a website

# Intercept communication between a web server and all users
 """
""" 
# week 2 qn 6
# Consider a stateless network firewall that has an accuracy of 99%.
# 99% of the legitimate packets are allowed and 99% of malicious packets are dropped.
# 1,000,000 packets are passed through the firewall of which 100 of the packets are malicious
# and the rest are not. Answer the following questions:

# 1. How many malicious packets are dropped by the firewall?  99

# 2. How many legitimate packets are dropped by the firewall? 9999

# 3. A packet is dropped by the firewall. What is the chance that the packet is actually legitimate (false positive)? 99%

# Bayes rule:
# P(A|B) = P(B|A)*P(A) / P(B)
# P(A) = P(A|B)*P(B) + P(G|!B)*P(!B)
# P(B) = P(B|A)*P(A) + P(B|!A)*P(!A)

def bayes_theorem(p_b, p_a_given_b, p_a_given_not_b):
   # calculate P(not B)
   not_b = 1 - p_b
   # calculate P(A)
   p_a = p_a_given_b * p_b + p_a_given_not_b * not_b
   # calculate P(B|A)
   p_b_given_a = (p_a_given_b * p_b) / p_a
   return p_b_given_a

print(bayes_theorem())
 """
""" 
# week 2 qn 7
# You have a database of known malware payloads and want to design a firewall that can
# filter out any packets detected to contain malware. Is it possible to use a stateless
# firewall to protect against all malware in the database? Briefly explain why or why not.

# NO. A stateless firewall can only check the packet header information. However since
# we want to check if the incoming packet contains any malware payload, the stateless firewall
# is unable to check the packet's payload. Hence the malware can come from a trusted source
# IP address and it would not be detected as malware.
 """
""" 
# week 2 qn 8
# Does a stateless network firewall protect against application level vulnerabilities?
# Briefly justify your answer. If you answered true, explain how you would configure the
# firewall to provide such protection. If you answered false, explain how the attack can bypass the firewall.

# False (a stateless firewall cannot effectively be used to protect against such an attack)
# A stateless firewall is unable to protect against any application level vulnerability.
# This is because a stateless firewall can only inspect IP packet headers and decide to
# drop or allow them based on configured rules, it would be unable to detect any malware
# in the packet payload.
 """
