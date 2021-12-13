#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command_nowait "$SLEEPLONG"
wait_for_string "execve(\"$SLEEPLONG"
sleep 0.2

UUID="$(arggen)"
run_command_nowait "$PR $UUID"
sleep 1
kill_testee
