#!/bin/bash


setup_script=$1
table1_script=$2
table2_script=$3
PARAMS_FILE=$4
ID_FILE=$5

sudo mysql -u root < $setup_script

read user_id < $ID_FILE

csrf_token=$(sha1sum <<< $user_id | awk '{print $1}')

# first script
case4tokens=$(sed -n '1p' $PARAMS_FILE)
read cookie_value flag_value <<< $case4tokens

sed -e 's/!!COOKIE_VALUE!!/'"$cookie_value"'/g' \
	-e 's/!!FLAG_VALUE!!/'"$flag_value"'/g' \
	-e 's/!!CSRF_TOKEN!!/'"$csrf_token"'/g' $table1_script | sudo mysql -u root


# second script
case4tokens=$(sed -n '2p' $PARAMS_FILE)
read cookie_value flag_value <<< $case4tokens
voucher_id=$(python3 -c 'import random; print(random.randint(2, 10**9))')

sed -e 's/!!COOKIE_VALUE!!/'"$cookie_value"'/g' \
	-e 's/!!FLAG_VALUE!!/'"$flag_value"'/g' \
	-e 's/!!VOUCHER_ID!!/'"$voucher_id"'/g' \
	-e 's/!!CSRF_TOKEN!!/'"$csrf_token"'/g' $table2_script | sudo mysql -u root

