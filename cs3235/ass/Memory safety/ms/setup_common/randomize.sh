#!/bin/bash

USERNAME=$1
TASK=$2
DIR="$3"

h=$(sha1sum << EOF
$USERNAME
$TASK
EOF
)
h=$(echo "$h" | awk '{print $1}')

read buf_size rand_int < <(python3 -c 'import random; random.seed(0x'$h'); print(random.randint(128, 256), random.randint(1, 10**9))')

sed -i -e 's/!!BUF_SIZE!!/'$buf_size'/g' \
	-e 's/!!RAND_INT!!/'$rand_int'/g' \
   	"$DIR"/*.c

