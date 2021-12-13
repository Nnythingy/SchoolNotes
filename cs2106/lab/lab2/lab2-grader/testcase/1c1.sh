#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command "/bin/sleep 5 &"
wait_for_string "execve(\"/bin/sleep"
SLEEP_PID="$(pgrep_sid sleep)"
if [ -z "$SLEEP_PID" ]; then
  sleep 0.5
  kill_testee
  exit 1
fi

# cat /proc/$SLEEP_PID/stat
run_command info
# get_exit_status_blocking $SLEEP_PID
# send_usr1_wait_sigchld $SLEEP_PID
wait_until_zombie $SLEEP_PID
run_command info
# get_exit_status_blocking $SLEEP_PID
kill_testee
