#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command_nowait "$SLEEPLONGA && $SLEEPLONGB && $SLEEPLONGC"

wait_for_string "execve(\"$SLEEPLONGA\""
send_usr1_wait_sigchld "$(pgrep_sid sla)"

wait_for_string "execve(\"$SLEEPLONGB\""
send_usr1_wait_sigchld "$(pgrep_sid slb)"

wait_for_string "execve(\"$SLEEPLONGC\""

SLC_PID="$(pgrep_sid slc)"
send_usr1_wait_sigchld "$SLC_PID"
wait_until_zombie "$SLC_PID"
run_command info

kill_testee
