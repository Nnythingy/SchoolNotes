#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command "$SLEEPLONGA &"
wait_for_string "execve(\"$SLEEPLONGA\""
SLA_PID="$(get_child_pid $LOGFILE "execve(\"$SLEEPLONGA")"
if [ -z "$SLA_PID" ]; then
  sleep 0.5
  kill_testee
  exit 1
fi

run_command "$SLEEPLONGB &"
wait_for_string "execve(\"$SLEEPLONGB\""
SLB_PID="$(get_child_pid $LOGFILE "execve(\"$SLEEPLONGB")"
if [ -z "$SLB_PID" ]; then
  sleep 0.5
  kill_testee
  exit 1
fi

run_command "$SLEEPLONGC &"
wait_for_string "execve(\"$SLEEPLONGC\""
SLC_PID="$(get_child_pid $LOGFILE "execve(\"$SLEEPLONGC")"
if [ -z "$SLC_PID" ]; then
  sleep 0.5
  kill_testee
  exit 1
fi

run_command terminate $SLC_PID
sleep 0.2

run_command terminate $SLB_PID
sleep 0.2

run_command terminate $SLA_PID
sleep 0.2

run_command terminate $SLC_PID
sleep 0.2

pgrep_live_log sl

kill_testee
