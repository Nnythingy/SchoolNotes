#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

cleanup_read_and_increment
remove_tmp_files

write_to_tmp_file "hello world"

run_command "$READ_AND_INCREMENT && $REDIRECT_IN_BOTH < $TMPFILE > ${TMPFILE}1 2> ${TMPFILE}2 && $READ_AND_INCREMENT 4 0 && $SLEEPSHORT && $REDIRECT_IN_ERR < ${TMPFILE}0 > $TMPFILE && $READ_AND_INCREMENT 1 0 0 0 1 && /usr/bin/sha256sum < ./counter0 > ${TMPFILE}3 && $PR hey 2> ${TMPFILE}2 && $SLEEPLONG"

sleep 2

check_file_contents "./counter0" "5" "read and increment"
check_file_contents "$TMPFILE" "hello world" "redirections"
check_file_contents "${TMPFILE}1" "hello world" "redirections"
check_file_contents "${TMPFILE}2" "hello world" "redirections"

cleanup_read_and_increment
remove_tmp_files

kill_testee
