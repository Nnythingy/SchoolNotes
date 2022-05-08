#!/bin/bash


export TEST_DIR="$JUDGE_EVAL_SCRIPTS_DIR/student"

#export WRKDIR="$1"

CURDIR="$(dirname "$(readlink -f "$0")")"

sudo mkdir -p "$TEST_DIR"
sudo chown student:student "$TEST_DIR"

cd $CURDIR

./.gen_userid.sh ./.studentid


if [ -f ".studentid" ]; then
    export USERNAME="$(cat .studentid)"
else
    echo ".studentid not found"
    exit 1
fi

"$JUDGE_EVAL_SCRIPTS_DIR"/setup/global_setup.sh "$USERNAME" > /dev/null 2>&1

testcases="a b c d e"
for t in $testcases; do
	flag=$(python3 -c 'import random; print(random.randint(1, 10**18))')
	echo $flag > "$TEST_DIR"/$t/flag.txt
done


