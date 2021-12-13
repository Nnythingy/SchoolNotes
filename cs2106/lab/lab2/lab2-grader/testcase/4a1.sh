#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command_nowait "$PERIODICWRITE"

wait_for_string "execve(\"$PERIODICWRITE\""
sleep 6

PID="$(get_exec_pid pw)"
send_signal_to_pg "SIGTSTP" "$TESTEE_PID"
wait_for_string "si_pid=$PID"

run_command_nowait "fg $PID"
sleep 6

kill_testee
