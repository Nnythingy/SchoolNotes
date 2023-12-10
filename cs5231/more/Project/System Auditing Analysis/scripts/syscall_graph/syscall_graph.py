import json
import sys

import graphviz


def generate_syscall_list(auditbeat_file, is_pid, target_prog, target_syscalls):
    '''
    syscalls = [
        {
            'sequence': <seq>,
            'pid': <pid>,
            'process_name': <process_name>,
            'syscall': <syscall>,
            'result': <result>,
            'exit': <exit>,
        },
        ...
    ]
    '''
    syscalls = []

    file_descriptors = {
        '0': 'stdin',
        '1': 'stdout',
        '2': 'stderr'
    }

    with open(auditbeat_file, 'r') as f:
        # Sort lines by sequence number
        lines = sorted(f.readlines(), key=lambda x: int(
            json.loads(x)['auditd']['sequence']))

        for line in lines:
            event = json.loads(line.strip())

            if 'process' not in event or \
                    (is_pid and event['process']['pid'] != int(target_prog)) or \
                    'name' not in event['process'] or \
                    (not is_pid and event['process']['name'] != target_prog):
                continue

            auditd_message_type = event['auditd']['message_type']
            if auditd_message_type != 'syscall':
                continue

            auditd_seq = event['auditd']['sequence']
            pid = event['process']['pid']
            process_name = event['process']['name']
            syscall = event['auditd']['data']['syscall']
            result = event['auditd']['result']
            exit = event['auditd']['data']['exit'] if 'exit' in event['auditd']['data'] else None
            file = event['file']['path'] if 'file' in event else None
            data = event['auditd']['data']

            if target_syscalls and syscall not in target_syscalls:
                continue

            # Update file descriptors if openat syscall
            if syscall == 'openat':
                fd = event['auditd']['data']['exit']
                file_descriptors[fd] = file

            # Update file descriptors if a0 is a file descriptor
            if file is None and \
                    syscall in ['fstat', 'read', 'pread', 'write', 'writev', 'dup', 'dup2'] and \
                    'a0' in event['auditd']['data'] and \
                    str(int(event['auditd']['data']['a0'], 16)) in file_descriptors:
                fd = str(int(event['auditd']['data']['a0'], 16))
                file = file_descriptors[fd]

            # Add syscall to syscall list
            syscalls.append({
                'sequence': auditd_seq,
                'pid': pid,
                'process_name': process_name,
                'syscall': syscall,
                'result': result,
                'exit': exit,
                'file': file,
                'data': data
            })

    # Sort syscalls by sequence
    syscalls.sort(key=lambda x: x['sequence'])

    # Write syscall list to file
    with open('syscalls.json', 'w') as f:
        json.dump(syscalls, f, indent=4)

    return syscalls


def is_node_in_graph(g, node):
    for nodes in g.body:
        if node in nodes:
            return True
    return False


def draw_syscall_graph(syscalls):
    # Create a new graph
    g = graphviz.Digraph(comment='Syscall Graph', format='png')

    # Set graph attributes
    g.attr('graph', layout='dot', overlap='false', splines='true')

    # Add syscalls to single cluster
    with g.subgraph(name='cluster_syscalls') as c:
        for i, syscall in enumerate(syscalls):
            # Add syscall node
            label = (
                f'{syscall["sequence"]}\n'
                f'{syscall["syscall"]}\n'
                f'{syscall["pid"]} {syscall["process_name"]}\n'
                f'Result: {syscall["result"]}\n'
                f'Exit: {syscall["exit"]}'
            )
            c.node(
                str(syscall["sequence"]),
                label=label,
                shape='box',
                style='rounded,filled',
                fillcolor='lightblue'
            )

            # Add file node
            file = syscall['file']
            if file is not None and not is_node_in_graph(g, file):
                g.node(
                    file,
                    label=file,
                    shape='ellipse',
                    style='filled',
                    fillcolor='lightpink'
                )

            # Add edge between syscall and file
            if file is not None:
                g.edge(str(syscall['sequence']), file)

            # Add edge between syscall and previous syscall
            if i > 0:
                g.edge(str(syscalls[i-1]['sequence']),
                       str(syscall['sequence']))

    # Save graph to file
    g.render(cleanup=True, filename='syscall_graph')


if __name__ == '__main__':
    if not 4 <= len(sys.argv) <= 5 or\
            sys.argv[2] not in ['-p', '-n'] or \
            (sys.argv[2] == '-p' and not sys.argv[3].isdigit()):
        print(
            'Usage: python3 syscall_graph.py <auditbeat_log.ndjson> <-p|-n> <pid|name> [syscalls]')
        print('Examples:')
        print('python3 syscall_graph.py auditbeat.ndjson -p 1234')
        print('python3 syscall_graph.py auditbeat.ndjson -n program11')
        print('python3 syscall_graph.py auditbeat.ndjson -n program11 openat,read,pread,write')
        sys.exit(1)

    auditbeat_file = sys.argv[1]
    is_pid = sys.argv[2] == '-p'
    target_prog = sys.argv[3]
    target_syscalls = sys.argv[4].split(',') if len(sys.argv) == 5 else None

    syscall_list = generate_syscall_list(
        auditbeat_file, is_pid, target_prog, target_syscalls)
    draw_syscall_graph(syscall_list)
