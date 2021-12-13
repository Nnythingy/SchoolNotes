#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

# Foreground
remove_tmp_files

UUID="$(arggen)"
write_to_tmp_file "$UUID"
run_command "$REDIRECT_IN_ERR < $TMPFILE 2> ${TMPFILE}1"
wait_for_string_in_file_timeout 1 "$UUID" "${TMPFILE}1"

check_file_contents "${TMPFILE}1" "$UUID" "< 2> foreground"

# Background
remove_tmp_files

UUID="$(arggen)"
write_to_tmp_file "$UUID"
run_command "$REDIRECT_IN_ERR < $TMPFILE 2> ${TMPFILE}1 &"
wait_for_string_in_file_timeout 1 "$UUID" "${TMPFILE}1"

check_file_contents "${TMPFILE}1" "$UUID" "< 2> background"

kill_testee
