#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command_nowait "$CHILDREN > $TMPFILE"

wait_for_string "execve(\"$CHILDREN\""
wait_for_string_in_file_timeout 10 "children-5" "$TMPFILE"

send_signal_to_pg "SIGINT" "$TESTEE_PID"

wait_for_string_in_file_timeout 10 "children-child-SIGINT" "$TMPFILE"
wait_for_string_in_file_timeout 10 "children-child-child-SIGINT" "$TMPFILE"

print_pass_message "SIGINT"

kill_testee
