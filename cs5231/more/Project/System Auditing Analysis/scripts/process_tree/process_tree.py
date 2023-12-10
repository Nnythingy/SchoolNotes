import json
import os
import sys

import graphviz


def generate_process_tree(auditbeat_file):
    '''
    process_tree = {
        '<pid>': {
            'ppid': '<ppid>',
            exec: [
                {
                    'name': '<name>',
                    'executatble': '<executable>',
                    'args': [
                        '<arg1>',
                        ...
                    ],
                    'user': '<user>',
                }
            ],
            'children': [
                '<pid>',
                ...
            ]
        }
    }
    '''
    process_tree = {}

    # Read the auditbeat log file
    with open(auditbeat_file, 'r') as f:
        for line in f:
            # Convert JSON string to dictionary
            event = json.loads(line.strip())

            # Skip events that are not process events
            if 'process' not in event:
                continue

            # Get process information
            auditd_seq = event['auditd']['sequence']
            executable_path = event['process']['executable'] if 'executable' in event['process'] else ''
            name = event['process']['name'] if 'name' in event['process'] else executable_path.split(
                '/')[-1]
            pid = event['process']['pid'] if 'pid' in event['process'] else None
            ppid = event['process']['parent']['pid'] if 'parent' in event['process'] and 'pid' in event['process']['parent'] else None
            args = event['process']['args'] if 'args' in event['process'] else []
            user = event['user']['name'] if 'user' in event and 'name' in event['user'] else None

            if executable_path == '':
                continue

            # Add process to process tree
            if pid not in process_tree:
                process_tree[pid] = {
                    'ppid': None,
                    'exec': [],
                    'children': []
                }
            if ppid is not None and process_tree[pid]['ppid'] is None:
                process_tree[pid]['ppid'] = ppid
            if name not in [process['name'] for process in process_tree[pid]['exec']]:
                process_tree[pid]['exec'].append({
                    'name': name,
                    'executable': executable_path,
                    'args': args,
                    'user': user
                })

    # Add process to parent's list of children
    for pid, process in process_tree.items():
        if process['ppid'] in process_tree:
            process_tree[process['ppid']]['children'].append(pid)

    # Sort process tree by PID
    process_tree = dict(sorted(process_tree.items()))

    # Save process tree to file
    with open('process_tree.json', 'w') as f:
        json.dump(process_tree, f, indent=4)

    return process_tree


def draw_graph(process_tree, output_filename):
    # Create a new graph
    graph_name = output_filename.split(os.sep)[-1].rsplit('.', 1)[0]
    g = graphviz.Digraph(graph_name, format='png')

    # Set graph attributes
    g.attr('graph', layout='dot', overlap='false',
           splines='true', rankdir='LR')
    g.attr('node', shape='box', style='rounded,filled', fillcolor='lightblue')

    # Add processes to the graph
    for pid, process in process_tree.items():
        # Create cluster for execs
        with g.subgraph(name=f'cluster_{pid}') as c:
            # Set cluster attributes
            c.attr(label=f'PID: {pid}')

            # Add execs to the cluster
            for e in process['exec']:
                arguments = '\n'.join(e['args'])
                label = (
                    f'{e["name"]}\n'
                    f'{e["executable"]}\n\n'
                    f'{e["user"]}\n\n'
                    f'args:\n{arguments}\n\n'
                )
                c.node(f'{pid}_{e["name"].replace(":", "::")}', label=label)

            # Add cluster to the graph
            g.subgraph(c)

            # Add edges between execs
            for i in range(len(process['exec']) - 1):
                g.edge(f'{pid}_{process["exec"][i]["name"].replace(":", "::")}',
                       f'{pid}_{process["exec"][i + 1]["name"].replace(":", "::")}', style='dashed')

    # Add edges between processes
    for pid, process in process_tree.items():
        for child_pid in process['children']:
            if child_pid not in process_tree:
                continue
            g.edge(f'{pid}_{process["exec"][-1]["name"]}',
                   f'{child_pid}_{process_tree[child_pid]["exec"][0]["name"]}')

    # Save the graph to a file
    g.render(cleanup=True, filename=graph_name)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Usage: python3 process_tree.py <auditbeat_log.ndjson> <output_filename>')
        print('Example: python3 process_tree.py auditbeat.ndjson process_tree.png')
        sys.exit(1)

    auditbeat_file = sys.argv[1]
    output_file = sys.argv[2]

    process_tree = generate_process_tree(auditbeat_file)
    draw_graph(process_tree, output_file)
