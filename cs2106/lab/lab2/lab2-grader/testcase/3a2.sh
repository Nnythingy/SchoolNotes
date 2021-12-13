#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

# Existing file

# Write a random string to tmp file
write_to_tmp_file "$(arggen)"

UUID="$(arggen)"
run_command "$REDIRECT_IN_OUT $UUID > $TMPFILE"
wait_for_string "execve(\"$REDIRECT_IN_OUT"
wait_for_string_in_file_timeout 1 "$UUID" "$TMPFILE"

check_file_contents "$TMPFILE" "$UUID" "> existing file"

# Non-existing file
remove_tmp_files

UUID="$(arggen)"
run_command "$REDIRECT_IN_OUT $UUID > $TMPFILE"
wait_for_string "execve(\"$REDIRECT_IN_OUT"
wait_for_string_in_file_timeout 1 "$UUID" "$TMPFILE"

check_file_contents "$TMPFILE" "$UUID" "> non-existing file"
check_tmp_file_permissions "> non-exsiting file"

# Background
remove_tmp_files

UUID="$(arggen)"
run_command "$REDIRECT_IN_OUT $UUID > $TMPFILE &"
wait_for_string "execve(\"$REDIRECT_IN_OUT"
wait_for_string_in_file_timeout 1 "$UUID" "$TMPFILE"

check_file_contents "$TMPFILE" "$UUID" "> background non-existing file"
check_tmp_file_permissions "> background non-exsiting file"

kill_testee
