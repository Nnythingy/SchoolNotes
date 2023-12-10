log_file = 'task1.log'

accessed_files = {}

with open(log_file, 'r') as f:
    for row in f.readlines():
        if 'malicious-prog' in row.lower():
            prog = row.split()[-1:][0]
            if prog in accessed_files.keys():
                accessed_files[prog] += 1
            else:
                accessed_files[prog] = 1

sorted_accessed_files = sorted(accessed_files.items(),
        key=lambda x: (-x[1], x[0])
        )

# Get the top 10 path accesses
top_10_paths = sorted_accessed_files[:10]

# Print the top 10 path accesses and their counts
for path, count in top_10_paths:
    print(f'{path} {count}')
