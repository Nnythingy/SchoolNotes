#!/bin/bash

run_testee() {
  # initially this was a new guid every time, but for easier parsing let's just
  # use one guid..
  DIVIDER="bfa06e76-6ffe-46aa-b71e-426bf7fb37f2"
  LOGFILE="$1.$TESTCASE.trace"
  TMPFILE="$1.$TESTCASE.tmp"
  declare -gi COMMAND_COUNT=0
  rm -f "$LOGFILE"
  coproc setsid -w -- "$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"/strace -f -b execve -e trace='execve,kill,fork,clone,wait4' -qqq -s 1024 -- "$1" "$DIVIDER" &>> "$LOGFILE"
  TESTEE_PID=$!
  echo "----------testeepid: $TESTEE_PID" >> "$LOGFILE"
}

# might be worth writing a small utility for this, this is quite unwieldy and creates like 5 processes :/
wait_for_string_in_file_timeout() {
  chmod u+rw "$3" &>/dev/null
  timeout --preserve-status -s 9 "$1" tail -n +0 -F $3 | sed "/${2//\//\\/}/ q100" &>/dev/null
  if [[ $? -ne 100 ]]; then
    echo "Timeout while waiting for string $2 in file $3" >> "$LOGFILE"
    kill_testee
    exit 0
  fi
}

wait_for_string_timeout() {
  wait_for_string_in_file_timeout "$1" "$2" "$LOGFILE"
}

wait_for_string() {
  wait_for_string_timeout 4 "$1"
}

wait_command_no() {
  wait_for_string "----------${DIVIDER}-${1}-END----------"
}

wait_command() {
  wait_command_no $COMMAND_COUNT
}

run_command() {
  echo "----------command: $@" >> "$LOGFILE"
  echo "$@" >&${COPROC[1]}
  wait_command
  COMMAND_COUNT+=1
}

run_command_no_exec_check() {
  echo "----------nocheckcmd: $@" >> "$LOGFILE"
  echo "$@" >&${COPROC[1]}
  wait_command
  COMMAND_COUNT+=1
}

run_command_nowait() {
  echo "----------command: $@" >> "$LOGFILE"
  echo "$@" >&${COPROC[1]}
  COMMAND_COUNT+=1
}

kill_testee() {
  if [ -n "$COPROC_PID" ] && [ -f "/proc/$TESTEE_PID/stat" ]; then
    kill -9 $(ps -s "$COPROC_PID" -o pid=)
  fi
  wait $TESTEE_PID &>/dev/null
  TESTEE_EXIT=$?
  case "$TESTEE_EXIT" in
  0 | 137) ;;
  *)
    >&2 echo "Non-successful exit: $TESTEE_EXIT $PWD"
    echo "----------exitcode: $TESTEE_EXIT" >> "$LOGFILE"
    ;;
  esac
}

wait_until_zombie() {
  local -i count=0
  until [ $count -ge 50 ] || [ ! -f "/proc/$1/stat" ] || [ "$(cat /proc/$1/stat 2>/dev/null | cut -d' ' -f3)" = "Z" ]; do
    sleep 0.1
    count+=1
  done
}

pgrep_sid() {
  pgrep -s "$TESTEE_PID" "$@"
}

pgrep_sid_log() {
  echo "----------pids $(pgrep_sid "$@" | xargs -n100 echo)" >> "$LOGFILE"
}

pgrep_live() {
  pids=$(pgrep -s "$TESTEE_PID" "$@")
  ps -o s= -o pid= $pids | sed -n 's/^[^ZT][[:space:]]\+//p' | tr '\n' ' '
}

pgrep_live_log() {
  echo "----------pids $(pgrep_live "$@" )" >> "$LOGFILE"
}


print_logfile_expected_log() {
  SERVICE_NO=$1
  shift
  echo "----------logfile${SERVICE_NO}-expected-BEGIN----------" >> "$LOGFILE"
  "$@" >> "$LOGFILE"
  echo "----------logfile${SERVICE_NO}-expected-END----------" >> "$LOGFILE"
}

print_logfile_log() {
  echo "----------logfile$1-BEGIN----------" >> "$LOGFILE"
  chmod u+r "service$1.log" &> /dev/null
  cat "service$1.log" >> "$LOGFILE" 2> /dev/null
  echo "----------logfile$1-END----------" >> "$LOGFILE"
}

arggen() {
  dd if=/dev/urandom bs=6 count=1 2>/dev/null | base64
}

send_usr1_wait_sigchld() {
  echo "$(pgrep sla)" >> "$LOGFILE"
  kill -USR1 "$1"
  wait_for_string "si_pid=$1"
  sleep 0.25
}

get_exec_pid() {
  FINDSTRING="/execve\(\"\.\/\.\.\.$1/"
  EXECPID=$(awk "$FINDSTRING" "$LOGFILE" | grep -o -P '(?<=\[pid).*(?=] execve)' | xargs)
  echo $EXECPID
}

send_signal_to_pid() {
  echo "-$1" "$2" >> "$LOGFILE"
  kill "-$1" "-$2"
}

send_signal_to_pg() {
  echo "-$1" "-$2" >> "$LOGFILE"
  kill "-$1" "-$2"
}

send_signal_to_pg_wait_sigchld() {
  send_signal_to_pg "$1" "$2"
  wait_for_string_timeout 6 "si_pid=$2"
  sleep 0.25
}

get_exit_status_blocking() {
  wait "$1" &>/dev/null
  PROG_EXIT=$?
  echo "----------exit status for $1: $PROG_EXIT" >> "$LOGFILE"
}

get_child_pid() {
  line=$(cat $1 | grep "$2" | tail -1)
  pid_regex="pid[[:space:]]+([0-9]+)"
  if [[ $line =~ $pid_regex ]]
  then
    echo "${BASH_REMATCH[1]}"
  else
    echo ""
  fi
}

cleanup_read_and_increment() {
  rm -f counter* &> /dev/null || :
}

write_to_tmp_file() {
  echo "$1" > "$TMPFILE"
}

remove_tmp_files() {
  rm -f "$TMPFILE"* &> /dev/null || :
}

check_tmp_file_permissions() {
  if [[ "$(stat -c %A $TMPFILE)" =~ ^.rw.r..r..$ ]]; then
    echo "----------pass: $1" >> "$LOGFILE"
  else
    echo "----------fail: Wrong permissions for $1" >> "$LOGFILE"
  fi
}

check_file_contents() {
  if [ "$(cat $1)" == "$2" ]; then
    echo "----------pass: $3" >> "$LOGFILE"
  else
    echo "----------fail: Expected $2, got $(cat $1) for $3" >> "$LOGFILE"
  fi
}

print_pass_message() {
  echo "----------pass: $1" >> "$LOGFILE"
}
