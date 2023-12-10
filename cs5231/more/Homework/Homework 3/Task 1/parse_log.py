import json

LOG_FILE = 'auditbeat-20221102.ndjson'
SUBJECT = 'malicious_prog'

file_descriptors = {
    '0': 'stdin',
    '1': 'stdout',
    '2': 'stderr'
}
parsed_logs = []

# Open auditbeat log file
with open(LOG_FILE, 'r') as f:
    # Sort the logs by auditd sequence
    log_lines = sorted(
        f.readlines(),
        key=lambda x: json.loads(x)['auditd']['sequence']
    )

    for line in log_lines:
        event = json.loads(line)

        # Filter logs to only the malicious program's syscalls
        if event['auditd']['message_type'] != 'syscall' or \
                'process' not in event or \
                'name' not in event['process'] or \
                event['process']['name'] != SUBJECT:
            continue

        # Get log event information
        auditd_sequence = event['auditd']['sequence']
        prog_name = event['process']['name']
        timestamp = event['@timestamp']
        syscall = event['auditd']['data']['syscall']
        file_path = event['file']['path'] if 'file' in event else None

        # Update file descriptor if syscall is openat
        if syscall == 'openat':
            fd = event['auditd']['data']['exit']
            if file_path is not None:
                file_descriptors[fd] = file_path
            else:
                file_path = file_descriptors[fd]

        # Get file descriptor if syscall is read or write
        if file_path is None and \
                syscall in ['read', 'pread', 'readv', 'write', 'pwrite', 'writev']:
            fd = event['auditd']['data']['a0']
            file_path = file_descriptors[fd]

        # Add parsed log to list
        parsed_logs.append(
            f'<{timestamp}, {prog_name}, {syscall}, {file_path}>')

# Write parsed logs to file
with open('task1_parsed.log', 'w') as f:
    for parsed_log in parsed_logs:
        f.write(parsed_log + '\n')
