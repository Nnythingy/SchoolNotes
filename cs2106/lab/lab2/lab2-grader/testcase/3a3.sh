#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

# Existing file

# Write a random string to tmp file
write_to_tmp_file "$(arggen)"

UUID="$(arggen)"
run_command "$REDIRECT_IN_ERR $UUID 2> $TMPFILE"
wait_for_string "execve(\"$REDIRECT_IN_ERR"
wait_for_string_in_file_timeout 1 "$UUID" "$TMPFILE"

check_file_contents "$TMPFILE" "$UUID" "2> existing file"

# Non-existing file
remove_tmp_files

UUID="$(arggen)"
run_command "$REDIRECT_IN_ERR $UUID 2> $TMPFILE"
wait_for_string "execve(\"$REDIRECT_IN_ERR"
wait_for_string_in_file_timeout 1 "$UUID" "$TMPFILE"

check_file_contents "$TMPFILE" "$UUID" "2> non-existing file"
check_tmp_file_permissions "2> non-existing file"

# Background
remove_tmp_files

UUID="$(arggen)"
run_command "$REDIRECT_IN_ERR $UUID 2> $TMPFILE &"
wait_for_string "execve(\"$REDIRECT_IN_ERR"
wait_for_string_in_file_timeout 1 "$UUID" "$TMPFILE"

check_file_contents "$TMPFILE" "$UUID" "2> background non-existing file"
check_tmp_file_permissions "2> background non-existing file"

kill_testee
