#!/bin/bash

task=$1
task_dir=$2
flag=$3

echo "TASK=$task"

if [ "$task" != "c" ] && [ "$task" != "b" ]; then
	cp $flag $task_dir/
fi


