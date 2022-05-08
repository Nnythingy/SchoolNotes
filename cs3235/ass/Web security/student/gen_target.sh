#!/bin/bash

TARGET_DIR="$1"
PARAMS_FILE="$2"
ID_FILE="$3"
CASE_COUNT=5

read user_id < $ID_FILE

csrf_token=$(sha1sum <<< $user_id | awk '{print $1}')
for i in $(seq $CASE_COUNT); do
	read cookie_value flag_value
	if [ -d $TARGET_DIR/case0$i ]; then
		find "$TARGET_DIR/case0$i" -type f -exec sed -i \
			-e 's/!!COOKIE_VALUE!!/'"$cookie_value"'/g' \
			-e 's/!!FLAG_VALUE!!/'"$flag_value"'/g' \
			-e 's/!!CSRF_TOKEN!!/'"$csrf_token"'/g' {} + 2>/dev/null
	fi
	if [ -f $TARGET_DIR/case0$i.php ]; then
		sed -i \
		-e 's/!!COOKIE_VALUE!!/'"$cookie_value"'/g' \
		-e 's/!!FLAG_VALUE!!/'"$flag_value"'/g' \
		-e 's/!!CSRF_TOKEN!!/'"$csrf_token"'/g' \
		$TARGET_DIR/case0$i.php
	fi
done < $PARAMS_FILE

chmod 777 $TARGET_DIR/global-libs/HTMLPurifier/HTMLPurifier/DefinitionCache/Serializer
