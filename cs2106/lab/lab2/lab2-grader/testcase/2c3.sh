#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

cleanup_read_and_increment

run_command "$READ_AND_INCREMENT && $READ_AND_INCREMENT 3 0 && $READ_AND_INCREMENT 4 1 && $READ_AND_INCREMENT && $READ_AND_INCREMENT 1 0 0 0 1 && $READ_AND_INCREMENT && $READ_AND_INCREMENT && $READ_AND_INCREMENT 5 1 && $READ_AND_INCREMENT 100 1 1 0 0 0 0 1"

sleep 2

check_file_contents "./counter0" "8" "counter0"
check_file_contents "./counter1" "109" "counter1"

cleanup_read_and_increment

kill_testee
