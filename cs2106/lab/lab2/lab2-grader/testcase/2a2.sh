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

kill -USR1 "$SLA_PID"
sleep 0.5

run_command wait $SLA_PID
sleep 1

run_command wait $SLA_PID
sleep 1

kill_testee
