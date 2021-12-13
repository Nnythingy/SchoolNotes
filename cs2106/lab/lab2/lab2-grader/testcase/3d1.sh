#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

cleanup_read_and_increment
remove_tmp_files

write_to_tmp_file "hello world"

run_command_nowait "$READ_AND_INCREMENT && $REDIRECT_IN_BOTH < $TMPFILE > ${TMPFILE}1 2> ${TMPFILE}2 && $READ_AND_INCREMENT 4 0 && $SLEEPSHORT && $REDIRECT_IN_ERR < ${TMPFILE}1 > $TMPFILE && $READ_AND_INCREMENT 1 0 0 0 1 && /usr/bin/sha256sum < ./counter0 > ${TMPFILE}3 && $PR hey 2> ${TMPFILE}2 && $SLEEPLONG"

wait_for_string "execve(\"$SLEEPLONG"

SHA_OUT=$(sha256sum < ./counter0)

check_file_contents "./counter0" "6" "read and increment"
check_file_contents "$TMPFILE" "" "redirections"
check_file_contents "${TMPFILE}1" "hello world" "redirections"
check_file_contents "${TMPFILE}2" "" "redirections"
check_file_contents "${TMPFILE}3" "$SHA_OUT" "sha256sum"

cleanup_read_and_increment
remove_tmp_files

kill_testee
