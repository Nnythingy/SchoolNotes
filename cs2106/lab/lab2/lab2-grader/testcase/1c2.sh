#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command ./...res 2106
wait_for_string "execve(\"./...res"
ECHO_PID="$(get_child_pid $LOGFILE "execve(\"./...res")"
if [ -z "$ECHO_PID" ]; then
  sleep 0.5
  kill_testee
  exit 1
fi
run_command info
sleep 1

run_command "/bin/sleep 3"
wait_for_string_timeout 6 "execve(\"/bin/sleep"
SLEEP_PID="$(get_child_pid $LOGFILE "execve(\"/bin/sleep")"
if [ -z "$SLEEP_PID" ]; then
  sleep 0.5
  kill_testee
  exit 1
fi

run_command info

# get_exit_status_blocking $SLEEP_PID
send_usr1_wait_sigchld $SLEEP_PID
wait_until_zombie $SLEEP_PID
run_command info
# get_exit_status_blocking $SLEEP_PID
kill_testee
