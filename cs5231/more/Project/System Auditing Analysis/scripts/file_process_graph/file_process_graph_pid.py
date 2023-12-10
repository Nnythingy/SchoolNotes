import json
import os
import sys

import graphviz

def generate_file_process_graph(auditbeat_file, allowed_prefix=None):
    process_list = {}
    file_list = {}
    
    # Read the auditbeat log file
    with open(auditbeat_file, 'r') as f:
        for line in f:
            # Convert JSON string to dictionary
            event = json.loads(line.strip())

            # Skip events that are not process events
            if 'process' not in event or 'file' not in event or 'path' not in event['file'] or 'user' not in event or 'name' not in event['user']:
                continue
            
            # Get the process name and the file name
            executable_path = event['process']['executable'] if 'executable' in event['process'] else ''
            name = event['process']['name'] if 'name' in event['process'] else executable_path.split(
                '/')[-1]
            pid = event['process']['pid'] if 'pid' in event['process'] else None
            user = event['user']['name'] if 'user' in event and 'name' in event['user'] else None
            file_path = event['file']['path'] if 'path' in event['file'] else None

            if file_path is None or (allowed_prefix is not None and not file_path.startswith(allowed_prefix)):
                continue

            # Add the process to the process list
            if pid not in process_list:
                process_list[pid] = {
                    'name': name,
                    'executable_path': executable_path,
                    'pid': pid,
                    'user': user,
                    'files': {}
                }

            # Add the file to the file list
            if file_path not in file_list:
                file_list[file_path] = 0
            file_list[file_path] += 1

            if file_path not in process_list[pid]['files']:
                process_list[pid]['files'][file_path] = 0
            process_list[pid]['files'][file_path] += 1
            
    file_process_graph = {
        'processes': process_list,
        'files': file_list
    }

    with open('file_process_pid.json', 'w') as f:
        json.dump(file_process_graph, f, indent=4)
    
    return file_process_graph


def draw_graph(file_process_graph, output_filename):
    graph_name = output_filename.split(os.sep)[-1].rsplit('.', 1)[0]
    graph = graphviz.Digraph(graph_name, comment='File Process Graph', format='png')
    graph.attr('graph', layout='neato', overlap='false', splines='true')

    for pid, process in file_process_graph['processes'].items():
        label = (
            f'{process["name"]} ({process["pid"]})\n'
            f'{process["executable_path"]}\n'
            f'User: {process["user"]}\n'
            f'Files Opened: {len(process["files"])}'
        )
        graph.node(str(pid), label=label, shape='box', style='rounded,filled', fillcolor='lightblue')
        for file_path, count in process['files'].items():
            graph.edge(str(pid), file_path, label=str(count))
    
    for file_path in file_process_graph['files'].keys():
        label = (
            f'{file_path}\n'
            f'Opened {file_process_graph["files"][file_path]} time(s)'
        )
        graph.node(file_path, label, shape='ellipse', style='filled', fillcolor='lightpink')
    
    graph.render(graph_name, cleanup=True)


if __name__ == '__main__':
    if len(sys.argv) < 3 or len(sys.argv) > 4:
        print('Usage: python3 file_process_graph_pid.py <auditbeat_log.ndjson> <output_filename> [allowed_file_prefix]')
        print('Example: python3 file_process_graph_pid.py auditbeat.ndjson file_process_graph_pid.png /home')
        sys.exit(1)

    auditbeat_file = sys.argv[1]
    output_file = sys.argv[2]
    allowed_prefix = sys.argv[3] if len(sys.argv) > 3 else None

    file_process_graph = generate_file_process_graph(auditbeat_file, allowed_prefix)

    if len(file_process_graph['files']) > 100:
        print('Warning: The graph contains more than 100 files. This may take a long time to render.')
        print('Consider using a more specific file prefix to reduce the number of files.')
        print('Press Ctrl+C to cancel.')

    draw_graph(file_process_graph, output_file)