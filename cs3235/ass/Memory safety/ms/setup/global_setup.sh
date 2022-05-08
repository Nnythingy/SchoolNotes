#!/bin/bash

username="$1"
TASKS="a b c d e"

make -C $JUDGE_EVAL_SCRIPTS_DIR/flag

for task in $TASKS; do
	cp -r $JUDGE_EVAL_SCRIPTS_DIR/$task $TEST_DIR/
	$JUDGE_EVAL_SCRIPTS_DIR/setup_common/setup_flag.sh $task $TEST_DIR/$task $JUDGE_EVAL_SCRIPTS_DIR/flag/flag
	$JUDGE_EVAL_SCRIPTS_DIR/setup_common/randomize.sh "$username" $task $TEST_DIR/$task
	make -C $TEST_DIR/$task
done

