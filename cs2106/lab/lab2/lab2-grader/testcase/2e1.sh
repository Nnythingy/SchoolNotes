#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command "$SLEEPLONG &"
wait_for_string "execve(\"$SLEEPLONG"

run_command "/bin/sleep 1"
wait_for_string "execve(\"/bin/sleep"

run_command quit
sleep 0.2
pgrep_sid_log sl
kill_testee
