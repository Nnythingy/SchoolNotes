#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command_nowait "$SLEEPLONGA && $PROG_RESULT -1 && $SLEEPLONGC"

wait_for_string "execve(\"$SLEEPLONGA\""
SLA_PID="$(pgrep_sid sla)"
send_usr1_wait_sigchld "$SLA_PID"

run_command info

kill_testee
