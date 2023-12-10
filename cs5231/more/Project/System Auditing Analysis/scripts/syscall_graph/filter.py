import json


AUDIT_LOG = '../auditbeat-20221106.ndjson'

filtered = []

with open(AUDIT_LOG, 'r') as f:
    for line in f:
        event = json.loads(line.strip())
        
        # Check if event is a syscall
        if 'auditd' not in event or 'message_type' not in event['auditd'] or event['auditd']['message_type'] != 'syscall':
            continue

        # Check if event is a syscall from the target process
        if 'process' not in event or 'name' not in event['process'] or event['process']['name'] != 'program9':
            continue
    
        print(event['process']['name'], 'syscall', event['auditd']['data']['syscall'])


        filtered.append(line)

with open('filtered.json', 'w') as f:
    for line in filtered:
        f.write(line)