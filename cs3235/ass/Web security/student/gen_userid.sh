#!/bin/bash

FILE_OUT="$1"

function check_nusnet {
	local studentID="$1"
	if [ "${#studentID}" -ne 8 ]; then
		echo "NUSNET ID must be 8 characters long!"
		exit 1
	fi
	if [ "${studentID:0:1}" != "e" ]; then
		echo "NUSNET ID must start with e!"
		exit 1
	fi
}

read -p "NUSNET ID (starting with e): " studentID
check_nusnet "$studentID"

echo "$studentID" > "$FILE_OUT"
