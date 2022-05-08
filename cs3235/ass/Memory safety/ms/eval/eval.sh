#!/bin/bash

# NOTE: turn off ASLR

CUR_DIR=$(dirname $(readlink -f "$BASH_SOURCE"))
export TEST_DIR=/testfolder

sudo mkdir -p $TEST_DIR
sudo chown student:student $TEST_DIR

JUDGE_TIME_LIMIT=5s


export QEMU_64="qemu-x86_64 -L /usr/x86_64-linux-gnu/ -0 prog"
export QEMU_32="qemu-i386 -L /usr/lib32/ -0 prog"
export WRKDIR="$1"

function get_test_dir {
	echo "$TEST_DIR/$1"
}

function print_start_case {
	local case_no=$1
	echo "======= Case $case_no ======="
}

function start_case {
	local case_no=$1
	local flag=$(python3 -c 'import random; print(random.randint(1, 10**18))')
	echo $flag | tee $(get_test_dir $case_no)/flag.txt
}

function end_case {
	local case_no=$1
	local outcome=$2
	#$JUDGE_EVAL_SCRIPTS_DIR/setup/cleanup.sh "$case_no" > /dev/null 2>&1
	if [ "$outcome" -eq 1 ]; then
		echo "Case $case_no evaluated (passed)."
	else
		echo "Case $case_no evaluated (failed)."
	fi
	echo
}

function run {
    echo "env -i PWD=$(pwd) $(readlink -f $1)"
}

cd $WRKDIR

if [ -f ".studentid" ]; then
    export USERNAME="$(cat .studentid)"
else
    echo ".studentid not found"
    exit 1
fi


$JUDGE_EVAL_SCRIPTS_DIR/setup/global_setup.sh "$USERNAME" > /dev/null 2>&1

# buffer overflow
flag=$(start_case "a")
print_start_case "a"
case_test_dir=$(get_test_dir "a")
cp $WRKDIR/a/exploit{1,2} $case_test_dir
cd $case_test_dir
if unbuffer /bin/bash -c "$(run $case_test_dir/a) \"\" < /dev/null 2>/dev/null" 2>/dev/null | grep -q $flag; then \
	outcome=1
else
	outcome=0
fi
end_case "a" $outcome


# format string
flag=$(start_case "b")
print_start_case "b"
case_test_dir=$(get_test_dir "b")
cp $WRKDIR/b/input $case_test_dir
cd $case_test_dir
if (/bin/bash -c "$(run $case_test_dir/b) \"\" < $case_test_dir/input 2>/dev/null" 2>/dev/null \
	| grep -q $flag) || \
    (unbuffer /bin/bash -c "$(run $case_test_dir/b) \"\" < $case_test_dir/input 2>/dev/null" 2>/dev/null \
	| grep -q $flag); then
	outcome=1
else
	outcome=0
fi
end_case "b" $outcome


# c
flag=$(start_case "c")
print_start_case "c"
case_test_dir=$(get_test_dir "c")
cp $WRKDIR/c/{exploit,input} $case_test_dir
cd $case_test_dir
if unbuffer /bin/bash -c "$(run $case_test_dir/c) \"\" < $case_test_dir/input 2>/dev/null" 2>/dev/null \
	| grep -q $flag; then
	outcome=1
else
	outcome=0
fi
end_case "c" $outcome


# d
flag=$(start_case "d")
print_start_case "d"
case_test_dir=$(get_test_dir "d")
cp $WRKDIR/d/input $case_test_dir
cd $case_test_dir
if unbuffer /bin/bash -c "$(run $case_test_dir/d) \"\" < $case_test_dir/input 2>/dev/null" 2>/dev/null \
	| grep -q $flag; then
	outcome=1
else
	outcome=0
fi
end_case "d" $outcome


# e
flag=$(start_case "e")
print_start_case "e"
case_test_dir=$(get_test_dir "e")
cp $WRKDIR/e/args $case_test_dir
cd $case_test_dir
if (/bin/bash -c "$(run $case_test_dir/e) \"$(cat $case_test_dir/args)\" 2>/dev/null" 2>/dev/null \
	| grep -q $flag) || \
    (unbuffer /bin/bash -c "$(run $case_test_dir/e) \"$(cat $case_test_dir/args)\" 2>/dev/null" 2>/dev/null \
	| grep -q $flag); then
	outcome=1
else
	outcome=0
fi
end_case "e" $outcome

$JUDGE_EVAL_SCRIPTS_DIR/setup/global_cleanup.sh "$USERNAME" > /dev/null 2>&1

sudo rm -rf $TEST_DIR

