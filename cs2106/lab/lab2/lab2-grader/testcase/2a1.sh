#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command "$SLEEPLONG &"
wait_for_string "execve(\"$SLEEPLONG"
SL_PID="$(get_child_pid $LOGFILE "execve(\"$SLEEPLONG")"
if [ -z "$SL_PID" ]; then
  sleep 0.5
  kill_testee
  exit 1
fi

run_command wait $SL_PID
sleep 1

UUID="$(arggen)"
run_command_no_wait "$PR $UUID"
sleep 1
kill_testee
