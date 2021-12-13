#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command "$PROG_LAZY &"
wait_for_string "execve(\"$PROG_LAZY\""

run_command info
sleep 0.2

LAZ_PID="$(pgrep_sid ...laz)"
run_command terminate $LAZ_PID
sleep 1

run_command info

kill_testee
