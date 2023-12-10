# Visualisation of System Logs from Auditbeat

## Setup

1. Install [Graphviz](https://graphviz.org/download/)  
Linux: `sudo apt install graphviz`
2. Install graphiviz python package with  
`pip install graphviz`

## Process Tree

```bash
Usage: python3 process_graph.py <auditbeat_log.ndjson> <output_filename>

Example:
python3 process_graph.py auditbeat.ndjson process_tree.png
```

![Process Tree](./process_tree/process_tree.png)

## Syscall Graph
```bash
Usage: python3 syscall_graph.py <auditbeat_log.ndjson> <-p|-n> <pid|name> [syscalls]

Examples:
python3 syscall_graph.py auditbeat.ndjson -p 1234
python3 syscall_graph.py auditbeat.ndjson -n program11
python3 syscall_graph.py auditbeat.ndjson -n program11 openat,read,pread,write
```

`syscalls` can include values from https://filippo.io/linux-syscall-table/ separated by commas.

Example: openat,read,pread,write,writev

![Syscall Graph](./syscall_graph/syscall_graph.png)

## File Process Graph
```bash
Usage: python3 file_process_graph.py <auditbeat_log.ndjson> <output_filename> [allowed_file_prefix]

Example:
python3 file_process_graph_pid.py auditbeat.ndjson file_process_graph_pid.png
python3 file_process_graph_pid.py auditbeat.ndjson file_process_graph_pid.png /home
```

`allowed_file_prefix` filters the file paths to only include those that start with the given prefix.

To generate the graph based on process ID instead of process names, use `file_process_graph_pid.py` instead.

![File Process Graph](./file_process_graph/file_process_graph.png)

![File Process Graph PID](./file_process_graph/file_process_graph_pid.png)