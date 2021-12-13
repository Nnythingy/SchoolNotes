#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command "$SLEEPSHORT 2 && $PR hello"
wait_for_string_timeout 6 "print-hello"

print_pass_message "ok"

kill_testee
