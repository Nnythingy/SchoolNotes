#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command_nowait "$CHILDREN"

wait_for_string "execve(\"$CHILDREN\""
sleep 4

send_signal_to_pg "SIGINT" "$TESTEE_PID"

wait_for_string "children-child-SIGINT"
wait_for_string "children-child-child-SIGINT"

print_pass_message "SIGINT"

kill_testee
