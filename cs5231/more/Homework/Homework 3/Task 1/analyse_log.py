from collections import defaultdict

PARSED_LOG_FILE = 'task1_parsed.log'

# Dictionary with a default value of 0 for non-existent keys
usr_files = defaultdict(int)

# Open parsed log file
with open(PARSED_LOG_FILE, 'r') as f:
    for line in f:
        # Remove angle brackets and split line into list
        line_stripped = line.strip()[1:-1]

        # Get file path from log
        filepath = line_stripped.split(', ')[-1]

        # Skip if file path is not in /usr/include/linux
        if not filepath.startswith('/usr/include/linux'):
            continue

        # Increment file access count
        usr_files[filepath] += 1

# Sort files into a list
# 1. By number of times accessed
# 2. Then alphabetically
sorted_usr_files = sorted(
    usr_files.items(),
    key=lambda x: (-x[1], x[0])
)

# Print top 10 files
for filepath, count in sorted_usr_files[:10]:
    print(count, filepath)
