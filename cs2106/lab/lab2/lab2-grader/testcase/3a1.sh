#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

# Foreground
UUID="$(arggen)"
write_to_tmp_file "$UUID"
run_command "$REDIRECT_IN_OUT < $TMPFILE"
wait_for_string "execve(\"$REDIRECT_IN_OUT"
wait_for_string "$UUID"

# Background
UUID="$(arggen)"
write_to_tmp_file "$UUID"
run_command "$REDIRECT_IN_OUT < $TMPFILE &"
wait_for_string "execve(\"$REDIRECT_IN_OUT"
wait_for_string "$UUID"

# Non-existing file
remove_tmp_files
run_command_no_exec_check "$REDIRECT_IN_OUT < $TMPFILE"
run_command info

kill_testee