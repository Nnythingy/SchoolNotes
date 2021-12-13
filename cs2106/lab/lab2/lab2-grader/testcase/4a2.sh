#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

run_command_nowait "$PERIODICWRITE > $TMPFILE"

wait_for_string "execve(\"$PERIODICWRITE\""
wait_for_string_in_file_timeout 10 "periodic-write-5" "$TMPFILE"

PID="$(get_exec_pid pw)"
send_signal_to_pg "SIGTSTP" "$TESTEE_PID"
wait_for_string "si_pid=$PID"

cp "$TMPFILE" "${TMPFILE}1"

run_command_nowait "fg $PID"
sleep 6

NUMDIFF="$(diff -y --suppress-common-lines $TMPFILE ${TMPFILE}1 | grep '^periodic-write-[0-9]\+\s*<$' | wc -l)"

echo "Number of lines different = $NUMDIFF" >> "$LOGFILE"

if [ "$NUMDIFF" -gt 0 ]; then
  print_pass_message "fg"
fi

cat "$TMPFILE" >> "$LOGFILE"

kill_testee
