#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

UUID="$(uuidgen)"
run_command "/bin/sleep $UUID"
wait_for_string "execve(\"/bin/sleep"
SLEEP_PID="$(get_child_pid $LOGFILE execve\(\"/bin/sleep)"
if [ -z "$SLEEP_PID" ]; then
  sleep 0.5
  kill_testee
  exit 1
fi

sleep 3
run_command info
sleep 0.2
kill_testee
