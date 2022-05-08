#!/bin/bash

ATTACKER_DIR="$1"
PARAMS_FILE="$2"
ID_FILE="$3"
CASE_COUNT=5

read user_id < $ID_FILE

csrf_token=$(sha1sum <<< $user_id | awk '{print $1}')

echo $PARAMS_FILE
case4tokens=$(sed -n '4p' $PARAMS_FILE)
read cookie_value flag_value <<< $case4tokens
find $ATTACKER_DIR -type f -exec sed -i \
	-e 's/!!COOKIE_VALUE!!/'"$cookie_value"'/g' \
	-e 's/!!FLAG_VALUE!!/'"$flag_value"'/g' \
	-e 's/!!CSRF_TOKEN!!/'"$csrf_token"'/g' {} + 2>/dev/null

