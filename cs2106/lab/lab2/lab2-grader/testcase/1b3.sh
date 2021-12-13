#!/bin/bash

TESTCASE="$(basename "${BASH_SOURCE[0]}" .sh)"
SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
. "$SCRIPT_DIR/../test_init.sh"

UUID="$(uuidgen)"
run_command "$UUID"
sleep 1

UUID="$(uuidgen)"
run_command "$UUID &"
sleep 1

kill_testee
